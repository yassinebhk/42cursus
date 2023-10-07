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

char	*get_next_line(int fd)
{
	int			readn;
	int			size_line;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	static char	*remaining = NULL;

	line = (char *)malloc(sizeof(char));
	if (!line)
		return (NULL);
	*line = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remaining)
		line = ft_strjoin(line, remaining, ft_strlen(remaining));
	readn = read(fd, buffer, BUFFER_SIZE);
	if (readn < 0)
		return (free(remaining), NULL);
	while (readn != 0)
	{
		buffer[readn] = '\0';
		size_line = ft_size_line(buffer, readn);
		if (!size_line)
			return (NULL);
		line = ft_strjoin(line, buffer, size_line);
		if (line == NULL)
			return (free(remaining), NULL);
		if (size_line < BUFFER_SIZE)
		{
			remaining = (char *)malloc(BUFFER_SIZE - size_line + 1);
			if (!remaining)
				return (NULL);
			remaining = ft_substr(buffer, size_line, BUFFER_SIZE - size_line);
			if (!remaining)
				return (free(remaining), NULL);
		}
		else
			remaining = NULL;
		if (buffer[size_line - 1] == '\n')
			break ;
		readn = read(fd, buffer, BUFFER_SIZE);
		if (readn < 0)
			return (free(remaining), NULL);
		buffer[readn] = '\0';
	}
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("hola.txt", O_RDONLY);
	printf("La primera linea es: %s", get_next_line(fd));
	printf("La segunda linea es: %s", get_next_line(fd));
	printf("La tercera linea es: %s", get_next_line(fd));
	printf("La cuartaa linea es: %s", get_next_line(fd));
	printf("La quintaa linea es: %s", get_next_line(fd));
	close(fd);
}
