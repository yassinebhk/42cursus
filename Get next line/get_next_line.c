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

// int	ft_strlen(const char *s)
// {
// 	size_t	cont;

// 	cont = 0;
// 	while (s[cont] != '\0')
// 		cont++;
// 	return (cont);
// }

// static char	*ft_strcat(char *dest, char *src, int size)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (*(dest + i) != '\0')
// 		i++;
// 	while (*src != '\0' && j < size)
// 	{
// 		*(dest + i) = *src;
// 		i++;
// 		src++;
// 		j++;
// 	}
// 	*(dest + i) = '\0';
// 	return (dest);
// }

// char	*ft_strjoin(char *s1, char *s2, int size)
// {
// 	char	*s;
// 	int		i;

// 	i = 0;
// 	s = (char *)malloc((ft_strlen(s1) + size + 1) * sizeof(char));
// 	if (!s)
// 		return (NULL);
// 	while (*(s1 + i) != '\0')
// 	{
// 		*(s + i) = *(s1 + i);
// 		i++;
// 	}
// 	*(s + i) = '\0';
// 	s = ft_strcat(s, (char *)s2, size);
// 	return (s);
// }

// char	*ft_substr(char *s, int start, int len)
// {
// 	int		cont;
// 	char	*str;

// 	cont = 0;
// 	if (start >= ft_strlen(s))
// 		len = 0;
// 	else if (start + len >= ft_strlen(s))
// 		len = ft_strlen(s) - start;
// 	str = (char *)malloc((len + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 	{
// 		*str = '\0';
// 		return (str);
// 	}
// 	while (len > 0 && *(s + start))
// 	{
// 		*(str + cont) = *(s + start);
// 		start++;
// 		cont++;
// 		len--;
// 	}
// 	*(str + cont) = '\0';
// 	return (str);
// }

/*


























*/

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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char));
	if (!line)
		return (NULL);
	*line = '\0';
	if (remaining)
		line = ft_strjoin(line, remaining, ft_strlen(remaining));
	readn = read(fd, buffer, BUFFER_SIZE);
	if (readn <= 0)
		return (free(remaining), free(line), NULL);
	while (readn != 0)
	{
		buffer[readn] = '\0';
		size_line = ft_size_line(buffer, readn);
		if (!size_line)
			return (free(remaining), free(line), NULL);
		line = ft_strjoin(line, buffer, size_line);
		if (line == NULL)
			return (free(remaining), free(line), NULL);
		if (size_line < BUFFER_SIZE)
		{
			remaining = (char *)malloc(BUFFER_SIZE - size_line + 1);
			if (!remaining)
				return (free(line), free(remaining), NULL);
			remaining = ft_substr(buffer, size_line, BUFFER_SIZE - size_line);
			if (!remaining)
				return (free(remaining), free(line), NULL);
		}
		else
			remaining = NULL;
		if (buffer[size_line - 1] == '\n')
			break ;
		readn = read(fd, buffer, BUFFER_SIZE);
		if (readn < 0)
			return (free(remaining), free(line), NULL);
		buffer[readn] = '\0';
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	fd;

// 	fd = open("hola.txt", O_RDONLY);
// 	printf("La primera linea es: %s", get_next_line(fd));
// 	printf("La segunda linea es: %s", get_next_line(fd));
// 	printf("La tercera linea es: %s", get_next_line(fd));
// 	printf("La cuartaa linea es: %s", get_next_line(fd));
// 	printf("La quintaa linea es: %s", get_next_line(fd));
// 	printf("La 6 linea es: \"%s\"", get_next_line(fd));
// 	printf("La 7 linea es: \"%s\"", get_next_line(fd));
// 	printf("La 8 linea es: \"%s\"", get_next_line(fd));
// 	close(fd);
// }
