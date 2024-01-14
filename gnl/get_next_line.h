/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:55:07 by aboukdid          #+#    #+#             */
/*   Updated: 2024/01/14 16:36:44 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE INT_MAX
# endif

char	*ft_strchr(char *s, int c);
char	*ft_strjoin1(char *s1, char *s2);
int		ft_strlen(char *s);
char	*ft_next_line(char *buff);
char	*ft_get_line(char *buff);
char	*ft_read_line(int fd, char *buff);
char	*get_next_line(int fd);
char	*loops1(char *s1, char	*s2, char *s3);

#endif
