/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:02:03 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/10 18:13:34 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Affiche le dossier courant
int	print_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putstr(buf);
	write(STDOUT_FILENO, "\n", 1);
	ft_free(buf);
	return (0);
}

// Met a jour la variable $OLDPWD dans t_envp
void	replace_oldpwd_my_env(t_envp *envp)
{
	t_envp	*tmp;
	t_envp	*pwd_node;

	if (!envp)
		return ;
	tmp = search_node(envp, "OLDPWD");
	if (!tmp)
		return ;
	pwd_node = search_node(envp, "PWD");
	if (!pwd_node)
		return ;
	if (tmp->tab[1])
		ft_free(tmp->tab[1]);
	tmp->tab[1] = ft_strndup(pwd_node->tab[1], 0);
}

// Met a jour les variables $OLDPWD et $PWD et dans t_envp
void	replace_pwd_my_env(t_envp *envp)
{
	t_envp	*tmp;

	if (!envp)
		return ;
	replace_oldpwd_my_env(envp);
	tmp = search_node(envp, "PWD");
	if (!tmp)
		return ;
	if (tmp->tab[1])
		ft_free(tmp->tab[1]);
	tmp->tab[1] = getcwd(NULL, 0);
}
