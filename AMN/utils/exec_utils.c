/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:06:08 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/10 16:59:45 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Test l'acces a av
// Return 0 si le chemin est absolu ou l'acces a reussi, sinon return 1
int	is_path(t_cmd *cmd, char *av)
{
	if (!ft_strchr(av, '/'))
		return (0);
	else if (access(av, F_OK | X_OK) == 0)
	{
		if (cmd && !cmd->cmd_path)
			cmd->cmd_path = ft_strndup(av, 0);
		return (0);
	}
	return (1);
}

// Cherche la variable PATH qui contient tous les chemins possibles de
// commandes dans l'environnement
// Return PATH de l'environnement ou NULL si elle n'a pas ete trouvee
char	*find_path_in_env(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		path = ft_strcmp(envp[i], "PATH=");
		if (path)
			return (path);
		i++;
	}
	return (NULL);
}

// Si access fonctionne, strdup le chemin dans cmd->cmd_path
// Return 1 si access a fonctionne, sinon 0
int	is_absolute_path(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (!is_path(cmd, cmd->cmd))
	{
		if (!cmd->cmd_path)
			cmd->cmd_path = ft_strndup(cmd->cmd, 0);
		return (1);
	}
	return (0);
}

// Test tous les paths possibles de la variable d'environnement PATH
// Return 1 si un path est valide et le met dans cmd->cmd_path, sinon return 0
int	find_cmd_path(t_data *data, t_cmd *cmd, char *env_path)
{
	int		i;
	char	**all_paths;
	char	*path;

	i = 0;
	if (is_absolute_path(cmd))
		return (1);
	if (!data->env_path || !cmd->cmd)
		return (0);
	all_paths = ft_split_normal(env_path, ':');
	if (!all_paths)
		return (0);
	while (all_paths[i])
	{
		path = ft_strjoin(all_paths[i], "/");
		cmd->cmd_path = ft_strjoin(path, cmd->cmd);
		ft_free(path);
		if (access(cmd->cmd_path, F_OK | X_OK) == 0)
			return (free_tab(all_paths), 1);
		ft_free(cmd->cmd_path);
		i++;
	}
	free_tab(all_paths);
	return (err_msg("No such file or directory", NULL, NULL, 0));
}

// Return 1 si str est une commande (access), sinon 0
int	is_cmd(t_data *data, t_cmd *cmd, char *str, char *env_path)
{
	int		i;
	char	**all_paths;
	char	*path;
	char	*save;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (is_builtin(str) || !is_path(cmd, str)
		|| (is_path(cmd, str) && !data->env_path))
		return (1);
	all_paths = ft_split_normal(env_path, ':');
	if (!all_paths)
		return (0);
	while (all_paths[i])
	{
		save = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(save, str);
		ft_free(save);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free(path), free_tab(all_paths), 1);
		ft_free(path);
		i++;
	}
	return (free_tab(all_paths), 0);
}
