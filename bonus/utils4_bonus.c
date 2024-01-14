/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:00:40 by aboukdid          #+#    #+#             */
/*   Updated: 2024/01/14 22:57:17 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	duup2(int fd1, int fd2)
{
	if (dup2(fd1, 0) == -1)
		msg_error1("dup2");
	if (dup2(fd2, 1) == -1)
		msg_error1("dup2");
}

void	msg_error(char *err)
{
	perror(err);
	exit (EXIT_FAILURE);
}

void	msg_error1(char *err)
{
	if (!ft_strncmp(err, "execve", ft_strlen(err)))
		ft_putstr_fd("execve: Bad address\n", 2);
	else if (!ft_strncmp(err, "pipe", ft_strlen(err)))
		ft_putstr_fd("error in pipe\n", 2);
	else if (!ft_strncmp(err, "open1", ft_strlen(err)))
		ft_putstr_fd("open: No such file or directory\n", 2);
	else if (!ft_strncmp(err, "malloc", ft_strlen(err)))
		ft_putstr_fd("error in malloc\n", 2);
	else if (!ft_strncmp(err, "type", ft_strlen(err)))
		ft_putstr_fd("./pipex file1 cmd1 ... cmdn file2\n", 2);
	else if (!ft_strncmp(err, "dup2", ft_strlen(err)))
		ft_putstr_fd("error in dup2\n", 2);
	else if (!ft_strncmp(err, "close", ft_strlen(err)))
		ft_putstr_fd("error in close\n", 2);
	else if (!ft_strncmp(err, "type1", ft_strlen(err)))
		ft_putstr_fd("./pipex here_doc LIMITER cmd cmd1 file\n", 2);
	exit(EXIT_FAILURE);
}

void	close_files(t_pipex *pipex)
{
	if (close(pipex->first_file) == -1)
		msg_error1("close");
	if (close(pipex->last_file) == -1)
		msg_error1("close");
}
