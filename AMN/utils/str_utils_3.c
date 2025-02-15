/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:04:44 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/18 16:27:21 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char *str, int n)
{
	int		i;
	char	*res;

	i = 0;
	if (!str || n <= 0)
		return (NULL);
	res = ft_calloc(n + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (str[i] && i < n)
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

// Return 0 si a est un separateur pour dollar, sinon 1
int	is_sep(int a)
{
	if (!ft_isalpha(a) && ft_strchr("{}()", a))
		return (1);
	return (0);
}

// strdup n char
// Return dup ou NULL si malloc fail
char	*ft_strdup_until(char *str, int n)
{
	int		i;
	char	*dup;

	i = 0;
	if (n <= 0)
		return (NULL);
	dup = ft_calloc(n + 1, sizeof(char));
	if (!dup)
		return (NULL);
	while (str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

void	fill(char *str, long long nb, int j)
{
	j--;
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (j >= 0 && str[j] != '-')
	{
		str[j] = (nb % 10) + 48;
		nb /= 10;
		j--;
	}
}

char	*ft_itoa(long long n)
{
	long long	nb;
	int			j;
	char		*str;

	nb = n;
	j = 0;
	if (n <= 0)
		j++;
	while (n != 0)
	{
		n /= 10;
		j++;
	}
	str = ft_calloc(j + 1, sizeof(char));
	if (!str)
		return (NULL);
	fill(str, nb, j);
	return (str);
}
