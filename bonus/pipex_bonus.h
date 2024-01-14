/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:43:50 by aboukdid          #+#    #+#             */
/*   Updated: 2024/01/14 22:30:07 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h> 
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../gnl/get_next_line.h"
# include <limits.h>

typedef struct s_pipex
{
	int		first_file;
	int		last_file;
	char	**result;
	int		cmd_num;
	int		pipe_num;
	int		*pipe;
	char	*path;
	int		i;
	int		id;
	int		her_doc;
}			t_pipex;

void	free_all(char **str);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, int n);
void	duup2(int fd1, int fd2);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	msg_error(char *err);
void	here_doc(char **argv, t_pipex *pipex);
void	msg_error1(char *err);
void	childs(t_pipex pipex, char **argv, char **envp);
void	free_struct(t_pipex *pipex);
void	close_files(t_pipex *pipex);
void	infile(t_pipex *pipex, char *argv);
void	outfile(t_pipex *pipex, char **argv, int argc);
void	create_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
char	**get_path(char **envp);
char	*command(char *my_argv, char **envp);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	*loops(char *s1, char *s2, char *s3);

#endif