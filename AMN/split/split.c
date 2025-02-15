/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:52:09 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/02 19:24:52 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// return le nombre de mots
int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_in_charset(str[i]) == 3)
			i++;
		else if (str[i] == '"')
			count += count_words_quote(str, &i, &count);
		else if (str[i] == 39)
			count += count_words_single(str, &i, &count);
		else if (!is_in_charset(str[i]))
			count += count_words_cmd(str, &i);
		else if (is_in_charset(str[i]) == 1)
			count += count_words_redir(str, &i);
		else if (is_in_charset(str[i]) == 2)
			count += count_words_pipe(&i);
	}
	return (count);
}

// return le nombre de chars dans chaque mot
int	count_chars(char *str, int n)
{
	int	i;
	int	count;
	int	chars;

	i = 0;
	count = 0;
	chars = 0;
	while (str[i])
	{
		if (is_in_charset(str[i]) == 3)
			i++;
		else if (str[i] == '"')
			chars += count_chars_double(str, &i, &count, n);
		else if (str[i] == 39)
			chars += count_chars_single(str, &i, &count, n);
		else if (!is_in_charset(str[i]))
			chars += count_chars_cmd(str, &i, &count, n);
		else if (is_in_charset(str[i]) == 1)
			chars += count_chars_redir(str, &i, &count, n);
		else if (is_in_charset(str[i]) == 2)
			chars += count_chars_pipe(&i, &count, n);
	}
	return (chars);
}

// transcrit chaque mot dans le tab
char	*ft_putwords(char *str, int n, char *mot)
{
	int	i;
	int	index;

	index = get_index(str, n);
	i = 0;
	while (i < count_chars(str, n))
	{
		mot[i] = str[index];
		i++;
		index++;
	}
	return (mot);
}

int	ft_split(char *str, t_data *data)
{
	char	**tab;
	int		i;

	if (!str)
		return (0);
	i = 0;
	tab = ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!tab)
		return (0);
	while (i < count_words(str))
	{
		tab[i] = ft_calloc(count_chars(str, i) + 1, sizeof(char));
		if (!tab[i])
			return (ft_free(tab), 0);
		tab[i] = ft_putwords(str, i, tab[i]);
		add_last_list(data, tab[i]);
		i++;
	}
	tab[i] = 0;
	ft_free(tab);
	return (1);
}
