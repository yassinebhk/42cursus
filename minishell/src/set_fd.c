/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:54 by maxgarci          #+#    #+#             */
/*   Updated: 2025/05/02 16:37:57 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_open(char *file, int flag, int permission, int old_fd)
{
	if (old_fd > 2)
		close(old_fd);
	if (permission)
		return (open(file, flag, 0644));
	else
		return (open(file, flag));
}

static int	heredoc(char *file)
{
	int	fd_in;

	read_heredoc(file);
	fd_in = open(HEREDOC_FILENAME, O_RDONLY);
	return (fd_in);
}

static int	open_and_get_fd(t_node *tmp, int i, int *fd_in, int *fd_out)
{
	int		redir;
	char	*file;

	redir = tmp->content->redir[i]->type;
	file = tmp->content->redir[i]->filename;
	if (redir == 1)
		*fd_out = ft_open(file, O_CREAT | O_WRONLY | O_TRUNC, 1, tmp->fd_out);
	else if (redir == 2)
		*fd_out = ft_open(file, O_CREAT | O_APPEND | O_WRONLY, 1, tmp->fd_out);
	else if (redir == 3)
		*fd_in = ft_open(file, O_RDONLY, 0, tmp->fd_in);
	else if (redir == 4)
		*fd_in = heredoc(file);
	if (*fd_in < 0 || *fd_out < 0)
	{
		ft_putstr_fd("Error opening ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (FN_FAILURE);
	}
	return (FN_SUCCESS);
}

int	set_fd(t_node **head)
{
	int		i;
	int		fd_out;
	int		fd_in;
	t_node	*tmp;

	tmp = *head;
	while (tmp)
	{
		i = -1;
		fd_out = 1;
		fd_in = 0;
		while (++i < tmp->content->num_redir)
		{
			if (open_and_get_fd(tmp, i, &fd_in, &fd_out))
				return (FN_FAILURE);
		}
		tmp->fd_in = fd_in;
		tmp->fd_out = fd_out;
		tmp = tmp->next;
	}
	return (FN_SUCCESS);
}
