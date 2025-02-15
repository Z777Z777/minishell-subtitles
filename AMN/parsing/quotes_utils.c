/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:43:37 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/18 18:22:36 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_quotes(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			i++;
			count += 2;
		}
		else if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
			i++;
			count += 2;
		}
		else if (str[i])
			i++;
	}
	return (count);
}

void	remove_dq(char *str, char *new, int *i, int *j)
{
	(*i)++;
	while (str[*i] != '"')
	{
		new[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

void	remove_sq(char *str, char *new, int *i, int *j)
{
	(*i)++;
	while (str[*i] != 39)
	{
		new[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	new = ft_calloc(ft_strlen(str) - ft_strlen_quotes(str, i) + 1, 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"')
			remove_dq(str, new, &i, &j);
		else if (str[i] == 39)
			remove_sq(str, new, &i, &j);
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	free (str);
	return (new);
}
