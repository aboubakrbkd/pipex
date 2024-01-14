/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 20:33:15 by aboukdid          #+#    #+#             */
/*   Updated: 2023/12/28 20:57:34 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	countword(const char *s, char c)
{
	int	count;
	int	i;
	int	i1;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	i1 = 1;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (i1 == 1)
				count++;
			i1 = 0;
		}
		else
			i1 = 1;
		i++;
	}
	return (count);
}

static char	*ft_strndup(const char *src, int n)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)malloc(n + 1);
	if (!result)
		return (0);
	while (src[i] && i < n)
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static void	ft_freemem(char **final, int i)
{
	while (i >= 0)
	{
		free(final[i]);
		i--;
	}
	free(final);
}

static char	**ft_help(char const *s, char c, int *len, char *start)
{
	int		i;
	char	**final;

	*len = countword(s, c);
	final = (char **)malloc((*len + 1) * sizeof(char *));
	if (!final)
		return (0);
	i = 0;
	while (i < *len)
	{
		while (*s == c)
			s++;
		start = (char *)s;
		while (*s && *s != c)
			s++;
		final[i] = ft_strndup(start, s - start);
		if (!final[i])
		{
			ft_freemem(final, i);
			return (0);
		}
		i++;
	}
	final[i] = 0;
	return (final);
}

char	**ft_split(char *s, char c)
{
	int		len;
	char	**final;
	char	*start;

	start = 0;
	final = ft_help(s, c, &len, start);
	return (final);
}
