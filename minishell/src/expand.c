/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:09:35 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/05/17 19:30:38 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	expand_argument(char **str, char *expanded)
{
	if (!expanded)
		return (FN_FAILURE);
	free(*str);
	*str = ft_strdup(expanded);
	if (!*str)
		return (ft_putstr_fd(ENO_MEM_ERROR, 2), free(expanded), FN_FAILURE);
	return (free(expanded), FN_SUCCESS);
}

static int	update_command_if_needed(t_node *tmp)
{
	free(tmp->content->command);
	tmp->content->command = malloc(sizeof(char) * (strlen(tmp->content->args[0])
				+ 1));
	if (!tmp->content->command)
		return (ft_putstr_fd(ENO_MEM_ERROR, 2), FN_FAILURE);
	strcpy(tmp->content->command, tmp->content->args[0]);
	return (FN_SUCCESS);
}

static int	expand_args(t_node **head, t_node *tmp)
{
	int		i;
	int		arg_needs_expansion;
	char	*expanded;

	i = -1;
	while (++i < tmp->content->num_args)
	{
		arg_needs_expansion = dollar_or_quotes(tmp->content->args[i]);
		if (!arg_needs_expansion)
			continue ;
		expanded = process_str(tmp, tmp->content->args[i],
				(*head)->last_status);
		if (expand_argument(&tmp->content->args[i], expanded) == FN_FAILURE)
			return (free(expanded), FN_FAILURE);
		if (i == 0 && update_command_if_needed(tmp) == FN_FAILURE)
			return (free(expanded), FN_FAILURE);
	}
	return (FN_SUCCESS);
}

static int	expand_redirs(t_node **head, t_node *tmp)
{
	int		i;
	int		needs_expansion;
	char	*expanded;

	i = -1;
	while (++i < tmp->content->num_redir)
	{
		needs_expansion = dollar_or_quotes(tmp->content->redir[i]->filename);
		if (!needs_expansion)
			continue ;
		expanded = process_str(tmp, tmp->content->redir[i]->filename,
				(*head)->last_status);
		if (expand_argument(&tmp->content->redir[i]->filename,
				expanded) == FN_FAILURE)
			return (free(expanded), FN_FAILURE);
	}
	return (FN_SUCCESS);
}

int	expand_commands(t_node **head)
{
	t_node	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (expand_args(head, tmp) == FN_FAILURE)
			return (FN_FAILURE);
		if (expand_redirs(head, tmp) == FN_FAILURE)
			return (FN_FAILURE);
		tmp = tmp->next;
	}
	return (FN_SUCCESS);
}
