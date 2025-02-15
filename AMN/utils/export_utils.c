/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:49:30 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/21 13:59:25 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Determine si il faut concatener une variable d'environnement (s'il y a "+=")
int	is_concat(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '+' && !str[i + 1])
			return (1);
		i++;
	}
	return (0);
}

// Gere le cas ou export VAR+=VALUE avec VAR inexistant
// Return 0 si tout fonctionne, sinon 1
int	concat_inexist(t_data *data, char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			res = ignore_charset(str, "+", 0);
			add_last_env(data, res);
			if (res)
				ft_free(res);
			return (1);
		}
		i++;
	}
	return (0);
}

// Join la valeur precedente de node->tab[1] avec tab[1] 
// Return 1 si la valeur de la variable dans t_envp a ete concatenee, sinon 0
int	concat(t_envp *node, char **tab)
{
	char	*tab_1;

	if (is_concat(tab[0]))
	{
		tab_1 = ft_strndup(node->tab[1], 0);
		if (!tab_1)
			return (0);
		ft_free(node->tab[1]);
		tab[1] = ignore_charset(tab[1], "\'\"", 1);
		node->tab[1] = ft_strjoin(tab_1, tab[1]);
		ft_free(tab_1);
		if (!node->tab[1])
			return (0);
		return (1);
	}
	return (0);
}

// parsing de la variable d'env que veut definir l'utilisateur
// Return 1 si c'est conforme, sinon 0
int	is_valid_name(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] >= '0' && str[0] <= '9')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha((int)str[i]))
			if (str[i] != '=' && (str[i] != '+' || str[i + 1] != '='))
				return (0);
		i++;
	}
	return (1);
}

// Remplace la valeur d'une variable dans t_envp si elle existe deja 
// et est redefinie par l'utilisateur
// Return 1 si tout s'est bien passe, sinon 0 (probleme de malloc strdup)
int	replace_value(t_envp *node, char *value)
{
	if (!value)
		return (1);
	ft_free(node->tab[1]);
	node->tab[1] = ft_strndup(value, 0);
	if (!node->tab[1])
		return (0);
	return (1);
}
