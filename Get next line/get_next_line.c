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
// 	if (!s)
// 		return (0);
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

// char	*ft_strjoin(char *s1, char *s2, int size, int mlc)
// {
// 	char	*s;
// 	int		i;

// 	i = 0;
// 	s = (char *)malloc((ft_strlen(s1) + size + 1) * sizeof(char));
// 	if (!s)
// 		return (free(s2), free(s1), NULL);
// 	while (*(s1 + i) != '\0')
// 	{
// 		*(s + i) = *(s1 + i);
// 		i++;
// 	}
// 	*(s + i) = '\0';
// 	s = ft_strcat(s, (char *)s2, size);
// 	if (!mlc)
// 		return (free(s2), free(s1), s);
// 	else
// 		return (free(s1), s);
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
	*remaining = ft_substr(a.buffer, a.size_line, a.readn - a.size_line);
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
		else if (a.readn == 0)
			*remaining = NULL;
		a.buffer[a.readn] = '\0';
	}
	return (a.line);
}

char	*ft_newline(char **remaining, struct s_vbs a)
{
	int	i;

	i = 0;
	a.line = ft_strjoin(a.line, "\n", 1, 1);
	while (i < ft_strlen(*remaining) - 1)
	{
		*(*remaining + i) = *(*remaining + i + 1);
		i++;
	}
	*(*remaining + i) = '\0';
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
	*a.line = '\0';
	a.str_free = 0;
	if (remaining)
	{
		if (*remaining == '\n')
			return (ft_newline(&remaining, a));
		a.line = ft_strjoin(a.line, remaining, ft_strlen(remaining), 0);
		remaining = NULL;
		a.str_free = 1;
	}
	a.readn = read(fd, a.buffer, BUFFER_SIZE);
	if (a.readn <= 0)
	{
		if (!a.str_free)
			return (free(remaining), free(a.line), NULL);
		else if (!remaining)
			return (free(remaining), a.line);
		else
			return (NULL);
	}
	return (ft_read(a, &remaining, fd));
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	fd;

// 	fd = open("hola.txt", O_RDONLY);
// 	printf("La 1 linea es: \"%s\"", get_next_line(fd));
// 	printf("La 2 linea es: \"%s\"", get_next_line(fd));
// 	printf("La 3 linea es: \"%s\"", get_next_line(fd));
// 	printf("La 4 linea es: \"%s\"", get_next_line(fd));
// 	printf("La 5 linea es: \"%s\"", get_next_line(fd));
// 	printf("La 6 linea es: \"%s\"", get_next_line(fd));
// 	// printf("La 7 linea es: \"%s\"", get_next_line(fd));
// 	// printf("La 8 linea es: \"%s\"", get_next_line(fd));
// 	close(fd);
// }
