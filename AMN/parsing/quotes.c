/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:32:56 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/20 17:24:48 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_dollars(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			result++;
		i++;
	}
	return (result);
}

int	handle_dollar_quote(t_data *data)
{
	t_list	*tmp;

	tmp = data->list;
	while (tmp)
	{
		if (!fill_dollar_tab(tmp))
			return (0);
		if (count_dollars(tmp->str))
			handle_dollar(data, tmp);
		if (tmp->type == HERE && tmp->next)
			tmp = tmp->next;
		tmp->str = remove_quotes(tmp->str);
		tmp = tmp->next;
	}
	return (1);
}

int	check_quotes_ret(char *str)
{
	int	ret;

	ret = check_quotes(str, 0);
	if (ret == 99)
	{
		g_return_val = 99;
		return (99);
	}
	else if (ret == 2)
	{
		g_return_val = 2;
		return (2);
	}
	return (0);
}
