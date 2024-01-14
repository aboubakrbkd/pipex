/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:58:01 by aboukdid          #+#    #+#             */
/*   Updated: 2024/01/14 15:56:22 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	infile(t_pipex *pipex, char *argv)
{
	if (!ft_strncmp(argv, "here_doc", ft_strlen(argv)))
	{
		pipex->her_doc = 1;
		return ;
	}
	else
	{
		pipex->her_doc = 0;
		pipex->first_file = open(argv, O_RDONLY, 0644);
		if (pipex->first_file == -1)
			msg_error1("open1");
	}
}

void	outfile(t_pipex *pipex, char **argv, int argc)
{
	pipex->last_file = open(argv[argc - 1], O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	if (pipex->last_file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_num - 1)
	{
		if (pipe(pipex->pipe + 2 * i) == -1)
			free_struct(pipex);
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipe_num)
	{
		close(pipex->pipe[i]);
		i++;
	}
}
