/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:59:57 by aboukdid          #+#    #+#             */
/*   Updated: 2024/01/14 18:04:25 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int fd[2], char *path, char **argv, char **envp)
{
	int		fd1;
	char	**result;

	fd1 = open(argv[1], O_RDWR, 0777);
	if (fd1 == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	result = ft_split(argv[2], ' ');
	path = command(result[0], envp);
	close(fd[0]);
	dup2(fd1, 0);
	dup2(fd[1], 1);
	close(fd[1]);
	close(fd1);
	execve(path, result, envp);
}

void	second_child(int fd[2], char *path, char **argv, char **envp)
{
	int		fd2;
	char	**result;

	fd2 = open(argv[4], O_RDWR | O_CREAT, 0777);
	if (fd2 == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	result = ft_split(argv[3], ' ');
	path = command(result[0], envp);
	close(fd[1]);
	dup2(fd2, 1);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd2);
	execve(path, result, envp);
}

void	parent(int fd[2], int id, int id1)
{
	close(fd[0]);
	close(fd[1]);
	waitpid(id, NULL, 0);
	waitpid(id1, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	int		fd[2];
	int		id;
	int		id1;

	if (argc != 5)
	{
		write(2, "error\n", 6);
		exit(EXIT_FAILURE);
	}
	path = NULL;
	if (pipe(fd) == -1)
		msg_error("pipe");
	id = fork();
	if (id == -1)
		msg_error("fork");
	if (id == 0)
		first_child(fd, path, argv, envp);
	id1 = fork();
	if (id1 == -1)
		msg_error("fork");
	if (id1 == 0)
		second_child(fd, path, argv, envp);
	if (id != 0 && id1 != 0)
		parent(fd, id, id1);
}
