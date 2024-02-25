/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:22:10 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/10/02 17:22:11 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

struct		s_v
{
	int		cont;
	char	*str;
};

struct		s_vbs
{
	int		str_free;
	int		readn;
	int		size_line;
	char	*line;
	char	buffer[BUFFER_SIZE + 1];
};

int			ft_strlen2(const char *s);
int			ft_strchr2(char *s, int c);
char		*get_next_line(int fd);
char		*ft_strjoin2(char *s1, char *s2, int size, int mlc);
char		*ft_substr2(char *s, int start, int len, int free_str);

#endif
