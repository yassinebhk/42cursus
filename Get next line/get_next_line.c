/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:22:01 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/10/02 17:22:03 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static char	*ft_remaining(struct s_vbs a, char **remaining)
{
	*remaining = ft_substr(a.buffer, a.size_line, a.readn - a.size_line, 0);
	if (!*remaining)
		return (free(*remaining), free(a.line), NULL);
	return (*remaining);
}

static char	*ft_read(struct s_vbs a, char **remaining, int fd)
{
	while (a.readn != 0)
	{
		a.buffer[a.readn] = '\0';
		a.size_line = ft_size_line(a.buffer, a.readn);
		if (!a.size_line)
			return (free(*remaining), free(a.line), NULL);
		a.line = ft_strjoin(a.line, a.buffer, a.size_line, 1);
		if (a.line == NULL)
			return (free(*remaining), free(a.line), NULL);
		if (a.size_line < a.readn)
			*remaining = ft_remaining(a, remaining);
		else if (!remaining)
			free(*remaining);
		if (a.buffer[a.size_line - 1] == '\n')
			break ;
		a.readn = read(fd, a.buffer, BUFFER_SIZE);
		if (a.readn < 0)
			return (free(*remaining), free(a.line), NULL);
		else if (a.readn == 0 && !remaining)
		{
			*remaining = NULL;
			free(*remaining);
		}
	}
	return (a.line);
}

char	*ft_newline(char **remaining, struct s_vbs a, int pos)
{
	int		i;
	char	*b;

	i = 0;
	b = ft_substr(*remaining, 0, pos + 1, 0);
	if (!b)
		return (free(*remaining), free(a.line), NULL);
	a.line = ft_strjoin(a.line, b, pos + 1, 0);
	if (!a.line)
		return (free(*remaining), NULL);
	*remaining = ft_substr(*remaining, pos + 1, ft_strlen(*remaining) - pos - 1,
			1);
	if (!*remaining)
		return (free(*remaining), free(a.line), NULL);
	return (a.line);
}

char	*get_next_line(int fd)
{
	struct s_vbs	a;
	static char		*remaining = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(remaining), NULL);
	a.line = (char *)malloc(sizeof(char));
	if (!a.line)
		return (free(remaining), NULL);
	(free(NULL), *a.line = '\0', a.str_free = 0);
	if (remaining)
	{
		if (ft_strchr(remaining, '\n') != -1)
			return (ft_newline(&remaining, a, ft_strchr(remaining, '\n')));
		a.line = ft_strjoin(a.line, remaining, ft_strlen(remaining), 0);
		remaining = NULL;
		a.str_free = 1;
	}
	a.readn = read(fd, a.buffer, BUFFER_SIZE);
	if (a.readn < 0 || (!a.str_free && a.readn == 0))
		return (free(remaining), free(a.line), NULL);
	else if (!remaining && a.readn == 0 && *a.line == '\0')
		return (free(remaining), free(a.line), NULL);
	else if (!remaining && a.readn == 0)
		return (free(remaining), a.line);
	return (ft_read(a, &remaining, fd));
}
