/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:20:33 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/29 09:54:34 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_output_redirection(t_command *comm)
{
	int	outpos;

	outpos = -1;
	while (++outpos < comm->num_redir)
	{
		if (comm->redir[outpos]->type == r_output
			|| comm->redir[outpos]->type == r_append)
			return (FN_FAILURE);
	}
	return (FN_SUCCESS);
}

static int	handle_output_redirections(t_node *head, int input)
{
	int			outpos;
	t_command	*c;

	outpos = -1;
	c = head->content;
	while (++outpos < c->num_redir)
	{
		if (c->redir[outpos]->type == r_output
			|| c->redir[outpos]->type == r_append)
		{
			head->fd_out = outpos;
			if (exec_comm(head, input, c->redir[outpos]->type))
				return (FN_FAILURE);
		}
	}
	return (FN_SUCCESS);
}

static int	find_input_redirection(t_command *comm)
{
	int	inpos;

	inpos = -1;
	while (++inpos < comm->num_redir)
	{
		if (comm->redir[inpos]->type == r_input
			|| comm->redir[inpos]->type == r_heredoc)
			return (FN_FAILURE);
	}
	return (FN_SUCCESS);
}

static int	handle_input_redirections(t_node *head, int output_exists)
{
	int			inpos;
	t_command	*c;

	inpos = -1;
	c = head->content;
	while (++inpos < c->num_redir)
	{
		if (c->redir[inpos]->type == r_input
			|| c->redir[inpos]->type == r_heredoc)
		{
			head->fd_in = inpos;
			if (output_exists)
			{
				if (handle_output_redirections(head, c->redir[inpos]->type))
					return (FN_FAILURE);
			}
			else if (exec_comm(head, c->redir[inpos]->type, 0))
				return (FN_FAILURE);
		}
	}
	return (FN_SUCCESS);
}

int	redirect(t_node *head)
{
	int	num_input;
	int	num_output;

	num_input = find_input_redirection(head->content);
	num_output = find_output_redirection(head->content);
	if (num_input > 0)
		return (handle_input_redirections(head, num_output));
	else if (num_output > 0)
		return (handle_output_redirections(head, 0));
	else
		return (exec_comm(head, 0, 0));
	return (FN_SUCCESS);
}
