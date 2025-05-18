/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*													+:+ +:+			+:+	 */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/11/02 22:08:48 by maxgarci			#+#	#+#			 */
/*   Updated: 2025/04/30 10:55:05 by maxgarci         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_heredoc(const char *delimiter)
{
	int		fd;
	char	*line;
	size_t	delim_len;

	delim_len = strlen(delimiter);
	fd = open(HEREDOC_FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening heredoc file", 2);
		exit(FN_FAILURE);
	}
	while (1)
	{
		ft_printf(PROMPT_HEREDOC);
		fflush(stdout);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || (ft_strncmp(line, delimiter, delim_len) == 0
				&& line[delim_len] == '\n'))
			break ;
		write(fd, line, strlen(line));
		free(line);
	}
	if (line)
		free(line);
	close(fd);
}
