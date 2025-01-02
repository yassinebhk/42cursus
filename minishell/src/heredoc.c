/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:08:48 by maxgarci          #+#    #+#             */
/*   Updated: 2024/12/30 16:43:12 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc(const char *delimiter)
{
	char	*line;
	size_t	delim_len;
	int		fd;

	delim_len = strlen(delimiter);
	fd = open(HEREDOC_FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("Error opening heredoc file");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		// Muestra el prompt "heredoc>" antes de leer cada línea
		ft_printf(PROMPT_HEREDOC);
		fflush(stdout);
		// Lee la línea ingresada por el usuario
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			break ;
		}
		// Compara la línea ingresada con el delimitador para finalizar
		if (ft_strncmp(line, delimiter, delim_len) == 0
			&& line[delim_len] == '\n')
		{
			break ;
		}
		// Escribe la línea en el archivo
		write(fd, line, strlen(line));
	}
	// Cierra el archivo
	close(fd);
}
