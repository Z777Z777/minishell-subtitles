/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:27:33 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/21 14:21:45 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Reset les donnees necessaire a chaque nouveau prompt
void	reset_data(t_data *data, char *str)
{
	t_envp	*tmp;

	ft_free(str);
	if (data->list)
	{
		free_list(data->list);
		data->list = NULL;
	}
	if (data->cmd)
	{
		free_cmd(data->cmd);
		data->cmd = NULL;
	}
	if (data->proc)
	{
		free_int_tab(data->proc->pipe_fd, data->proc->n_pipes);
		if (data->proc->n_heredoc > 0)
			ft_free(data->proc->fd_heredoc);
		ft_free(data->proc->pid);
	}
	tmp = search_node(data->envp, "PATH");
	if (tmp)
		data->env_path = tmp->tab[1];
	else
		data->env_path = NULL;
}

// Affiche un prompt different selon la valeur de retour precedente 
char	*get_readline(t_data *data, char *str)
{
	str = readline("Manuo ✖✖ ");
	if (!str)
	{
		rl_clear_history();
		free_data_proc(data);
		write(STDERR_FILENO, "exit\n", 5);
		exit(g_return_val);
	}
	add_history(str);
	return (str);
}

// Cree data, affiche un prompt et execute les commandes recues
void	get_prompt(char **envp)
{
	char	*str; // 
	t_data	*data; // cree la structure data

	data = create_data(envp); //!HERE2
	str = NULL;
	while (42)
	{
		if (g_return_val == -126)
			g_return_val = 130;
		str = get_readline(data, str);
		if (!str)
			return ;
		if (check_quotes_ret(str))
			return (free_data_proc(data), get_prompt(envp));
		if (!ft_split(str, data))
			return (get_prompt(envp));
		if (!parsing(data))
			return (free_data_proc(data), get_prompt(envp));
		if (get_cmd_struct(data))
			return (get_prompt(envp));
		if (!execution(data))
			return (free_data(data));
		reset_data(data, str);
	}
}
