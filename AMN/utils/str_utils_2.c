/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:39:22 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/01 16:43:40 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Return 1 si [a] est alphabetique, sinon 0
int	ft_isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')
		|| (a >= '0' && a <= '9') || a == '_')
		return (1);
	return (0);
}

// Compare 2 chaines de caracteres
// Return 1 si elles sont identiques, sinon 0
int	is_same(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && (!s2[i] || (s2[i] == '+' && !s2[i + 1])))
		return (1);
	return (0);
}

// Met le resultat de s1 + s2 dans dest
// Return dest ou NULL (malloc rate)
char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strndup(s2, 0));
	if (!s2)
		return (ft_strndup(s1, 0));
	dest = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!dest)
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	return (dest);
}

// Cherche la premiere occurence de c dans str
// Return 1 si aucune occurence a ete trouvee, sinon return 0
int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (1);
	return (0);
}

// Remplace tous les caracteres de charset dans str puis free str
// Si n != 0, free str
// Return une chaine de caractere sans charset ou NULL
char	*ignore_charset(char *str, char *charset, int n)
{
	int		i;
	int		j;
	char	*dup;

	i = 0;
	j = 0;
	if (!str || str[0] == '\0')
		return (str);
	while (str[i++] && str[i] != '$')
		if (ft_strchr(charset, str[i]))
			j++;
	dup = ft_calloc(j + 2, 1);
	if (!dup)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '$')
	{
		if (ft_strchr(charset, str[i]))
			dup[j++] = str[i];
		i++;
	}
	if (n != 0)
		ft_free(str);
	return (dup);
}
