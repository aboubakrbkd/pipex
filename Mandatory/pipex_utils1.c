/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:35:55 by aboukdid          #+#    #+#             */
/*   Updated: 2024/01/14 17:56:11 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check(char *my_argv)
{
	if (my_argv[0] == '/')
	{
		if (access(my_argv, F_OK | X_OK) == 0)
			return (my_argv);
		else
			msg_error("error");
	}
	return (0);
}

char	*command(char *my_argv, char **envp)
{
	char	**path;
	char	*joiner;
	char	*command_path;
	int		i;

	path = get_path(envp);
	i = 0;
	check(my_argv);
	while (path[i])
	{
		if (access(my_argv, F_OK | X_OK) == 0)
			return (my_argv);
		joiner = ft_strjoin(path[i], "/");
		command_path = ft_strjoin(joiner, my_argv);
		free(joiner);
		if (access(command_path, F_OK | X_OK) == 0)
			return (free_all(path), command_path);
		free(command_path);
		i++;
	}
	return (free_all(path), NULL);
}

static char	*loops(char *s1, char *s2, char *s3)
{
	int	i;
	int	j;
	int	len1;
	int	len2;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while (i < len1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;
	char	*result;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
	{
		free(result);
		return (0);
	}
	loops(s1, s2, result);
	return (result);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
