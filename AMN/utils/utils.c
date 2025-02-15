/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:53:54 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/18 16:27:29 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*tab;
	char	*str;

	tab = malloc(n * size);
	if (!tab)
		return (NULL);
	str = tab;
	while (n > 0)
	{
		n--;
		str[n] = '\0';
	}
	return (tab);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		sign;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}

void	ft_putchar(int c)
{
	write(STDOUT_FILENO, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar((n % 10 + 48));
}
