/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:13:03 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/21 14:26:29 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Attends la fin d'execution de chaque process child et recupere la valeur
// de retour de chaque commande effectuee
void	wait_all_child(t_data *data, int n)
{
	int	i;
	int	status;

	status = 1;
	i = 0;
	if (!data->proc->pid)
		return ;
	while (i < n && g_return_val != -126)
	{
		if (data->proc->pid[i] != -1)
		{
			waitpid(data->proc->pid[i], &status, 0);
			if (WIFEXITED(status))
				g_return_val = WEXITSTATUS(status);
		}
		i++;
	}
}

// Creation tab env + execve
int	execve_binary(t_data *data, t_cmd *cmd)
{
	char	**env_tab;

	env_tab = get_env_tab(data->envp);
	if (!cmd->cmd_path)
	{
		g_return_val = error_cmd(cmd->opt);
		free_tab(env_tab);
		free_data(data);
		exit (g_return_val);
	}
	execve(cmd->cmd_path, cmd->opt, env_tab);
	free_tab(env_tab);
	return (error_cmd(cmd->opt));
}

// Execute les commandes (non builtins)
// Ne return rien si l'execution a reussie ou la valeur d'erreur
int	exec_binary(t_data *data, t_cmd *c)
{
	int		ret;

	ret = 0;
	if (!is_builtin(c->cmd) && !c->cmd_path && c->type && c->type[0] != HERE)
		return (err_msg("env not found, need an absolute path", 0, 0, 1), 1);
	data->proc->pid[c->index] = fork();
	if (data->proc->pid[c->index] == 0)
	{
		if (redir(data, c, 1))
		{
			close_pipes(data->proc);
			free_data(data);
			exit(1);
		}
		if (is_builtin(c->cmd))
			g_return_val = exec_builtin(data, c, c->opt);
		else if (is_cmd(data, c, c->cmd, data->env_path))
			g_return_val = execve_binary(data, c);
		free_data(data);
		exit(g_return_val);
	}
	return (g_return_val);
}

// Envoies la commande a la fonction de builtins ou d'exec bin
// Return le retour de chaque commande effectuee
int	send_cmd(t_data *data, t_cmd *cmd)
{
	signal(SIGQUIT, handle_sigquit); // gere le Ctrl + /
	if (!cmd->cmd || !cmd->cmd[0] || is_same(cmd->cmd, "..") // verifie si la commande est valide
		|| is_same(cmd->cmd, "."))
	{
		if (is_same(cmd->cmd, "."))
		{
			g_return_val = err_msg("bash: .: filename argument required",
					0, 0, 2); // gere l'erreure
			return (g_return_val);
		}
		if (cmd->token && cmd->token[0] && cmd->type[0] != HERE)
			return (create_files(data, cmd));
		else if (cmd->type && cmd->type[0] == HERE)
			return (exec_binary(data, cmd));
		return (error_cmd(cmd->opt));
	}
	else if (is_builtin(cmd->cmd))
		return (exec_builtin(data, cmd, cmd->opt));
	else if (is_builtin(cmd->cmd) || is_cmd(data, cmd, cmd->cmd,
			data->env_path))
		return (exec_binary(data, cmd));
	create_files(data, cmd);
	return (error_cmd(cmd->opt));
}

// Cree les pipes et s'occupe des redirections avant d'envoyer la commande
// a send_cmd
// Return 0 si il y a un probleme a la creation des pipes, sinon 0
int	execution(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd; // cmd est assigne a la premiere commande de la liste chainee de comandes
	if (!create_pipes_array(data)) // cree le tableau de pipe, cree les pipes avec la commande pipe()
		return (0);
	print_all_heredoc(data); // cree le here doc si besoin
	handle_sigint_exec(); // configure le traitement des signaux pour lex commandes
	while (cmd && g_return_val != -126) // execution des commandes 
	{
		g_return_val = send_cmd(data, cmd);
		cmd = cmd->next;
	}
	close_pipes(data->proc); // on ferme les pipes (fd des pipes)
	wait_all_child(data, data->proc->n_pipes + 1); // on attend les process enfants
	handle_signal(); // on remet le gestionnaire de signaux par defaults 
	return (1);
}
