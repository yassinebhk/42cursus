/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:44:34 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/02 00:31:24 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_size_line(char *buffer, int readn)
{
	int	size;

	size = 0;
	if (readn <= 0)
		return (0);
	while (*(buffer + size) != '\n' && size < readn)
		size++;
	if (*(buffer + size) == '\n')
		return (size + 1);
	return (size);
}

static char	*ft_remain(struct s_vbs a, char **remain)
{
	*remain = ft_substr2(a.buffer, a.size_line, a.readn - a.size_line, 0);
	if (!*remain)
		return (free(*remain), free(a.line), NULL);
	return (*remain);
}

static char	*ft_read(struct s_vbs a, char **remain, int fd)
{
	while (a.readn != 0)
	{
		a.buffer[a.readn] = '\0';
		a.size_line = ft_size_line(a.buffer, a.readn);
		if (!a.size_line)
			return (free(*remain), free(a.line), NULL);
		a.line = ft_strjoin2(a.line, a.buffer, a.size_line, 1);
		if (a.line == NULL)
			return (free(*remain), free(a.line), NULL);
		if (a.size_line < a.readn)
			*remain = ft_remain(a, remain);
		else if (!remain)
			free(*remain);
		if (a.buffer[a.size_line - 1] == '\n')
			break ;
		a.readn = read(fd, a.buffer, BUFFER_SIZE);
		if (a.readn < 0)
			return (free(*remain), free(a.line), NULL);
		else if (a.readn == 0 && !remain)
		{
			*remain = NULL;
			free(*remain);
		}
	}
	return (a.line);
}

char	*ft_newline(char **remain, struct s_vbs a, int pos)
{
	char	*b;

	b = ft_substr2(*remain, 0, pos + 1, 0);
	if (!b)
		return (free(*remain), free(a.line), NULL);
	a.line = ft_strjoin2(a.line, b, pos + 1, 0);
	if (!a.line)
		return (free(*remain), NULL);
	*remain = ft_substr2(*remain, pos + 1, ft_strlen2(*remain) - pos - 1,
			1);
	if (!*remain)
		return (free(*remain), free(a.line), NULL);
	return (a.line);
}

char	*get_next_line(int fd)
{
	struct s_vbs	a;
	static char		*remain[2048];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	a.line = (char *)malloc(sizeof(char));
	if (!a.line)
		return (free(remain[fd]), NULL);
	(free(NULL), *a.line = '\0', a.str_free = 0);
	if (remain[fd])
	{
		if (ft_strchr2(remain[fd], '\n') != -1)
			return (ft_newline(&remain[fd], a, ft_strchr2(remain[fd], '\n')));
		a.line = ft_strjoin2(a.line, remain[fd], ft_strlen2(remain[fd]), 0);
		remain[fd] = NULL;
		a.str_free = 1;
	}
	a.readn = read(fd, a.buffer, BUFFER_SIZE);
	if (a.readn < 0 || (!a.str_free && a.readn == 0))
		return (free(remain[fd]), free(a.line), NULL);
	else if (!remain[fd] && a.readn == 0 && *a.line == '\0')
		return (free(remain[fd]), free(a.line), NULL);
	else if (!remain[fd] && a.readn == 0)
		return (free(remain[fd]), a.line);
	return (ft_read(a, &remain[fd], fd));
}
