/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:58:58 by aboukdid          #+#    #+#             */
/*   Updated: 2024/01/14 22:57:13 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_helper(char **argv, int *fd)
{
	char	*result;

	while (1)
	{
		write(1, ">>", 2);
		result = get_next_line(0);
		if ((!ft_strncmp(result, argv[2], ft_strlen(argv[2])))
			&& (ft_strlen(result) - 1 == ft_strlen(argv[2])))
		{
			free(result);
			close(fd[0]);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], result, ft_strlen(result));
		free(result);
	}
}

void	here_doc(char **argv, t_pipex *pipex)
{
	int		id;
	int		fd[2];

	if (pipe(fd) == -1)
		msg_error1("pipe");
	id = fork();
	close(fd[1]);
	if (!id)
	{
		close(fd[0]);
		here_doc_helper(argv, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		if (waitpid(id, NULL, 0) == -1)
			msg_error1("waitpid");
		pipex->first_file = fd[0];
	}
}

void	childs(t_pipex pipex, char **argv, char **envp)
{
	pipex.id = fork();
	if (pipex.id == -1)
		msg_error1("pipe");
	if (!pipex.id)
	{
		if (pipex.i == 0)
			duup2(pipex.first_file, pipex.pipe[1]);
		else if (pipex.i == pipex.cmd_num - 1)
			duup2(pipex.pipe[2 * pipex.i - 2], pipex.last_file);
		else
			duup2(pipex.pipe[2 * pipex.i - 2], pipex.pipe[2 * pipex.i + 1]);
		if (close(pipex.first_file) == -1)
			msg_error1("close");
		if (close(pipex.last_file) == -1)
			msg_error1("close");
		close_pipes(&pipex);
		pipex.result = ft_split(argv[pipex.i + pipex.her_doc], ' ');
		pipex.path = command(pipex.result[0], envp);
		if (execve(pipex.path, pipex.result, envp) == -1)
			msg_error1("execve");
	}
}

void	free_struct(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (close(pipex->first_file) == -1)
		msg_error1("close");
	if (close(pipex->last_file) == -1)
		msg_error1("close");
	while (i < pipex->pipe_num)
	{
		free(pipex->pipe);
		i++;
	}
	free(pipex->pipe);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		msg_error1("type");
	if (argc <= 5 && !ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])))
		msg_error1("type1");
	if (argc == 6 && !ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		here_doc(argv, &pipex);
	infile(&pipex, argv[1]);
	outfile(&pipex, argv, argc);
	pipex.cmd_num = argc - 3 - pipex.her_doc;
	pipex.pipe_num = 2 * (pipex.cmd_num - 1);
	pipex.pipe = malloc(sizeof(int) * pipex.pipe_num);
	if (!pipex.pipe)
		msg_error1("malloc");
	create_pipes(&pipex);
	pipex.i = -1;
	while (++pipex.i < pipex.cmd_num)
		childs(pipex, argv + 2, envp);
	close_pipes(&pipex);
	while (wait(NULL) != -1)
		;
	free(pipex.pipe);
	close_files(&pipex);
	exit(EXIT_SUCCESS);
}
