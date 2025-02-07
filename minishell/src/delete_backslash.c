/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:52:20 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/02/07 16:05:32 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	new_len_str(char *str)
{
	int		len;
	size_t	pos;

	pos = -1;
	len = 0;
	while (++pos < ft_strlen(str))
	{
		if (str[pos] != BACKSLASH)
			len++;
	}
	return (len);
}

static char *delete (char *str)
{
	int		i;
	size_t	pos;
	char	*new_str;

	i = 0;
	pos = -1;
	new_str = (char *)ft_calloc(sizeof(char), (new_len_str(str) + 1));
	if (!new_str)
		return (perror(ENO_MEM_ERROR), NULL);
	while (++pos < ft_strlen(str))
	{
		if (str[pos] != BACKSLASH)
		{
			new_str[i] = str[pos];
			i++;
		}
	}
	new_str[i] = '\0';
	return (free(str), new_str);
}

static int	iter_node(t_node **node)
{
	int	pos;

	pos = -1;
	(*node)->content->command = delete((*node)->content->command);
	if (!(*node)->content->command)
		return (0);
	while (++pos < (*node)->content->num_args)
	{
		(*node)->content->args[pos] = delete((*node)->content->args[pos]);
		if (!(*node)->content->args[pos])
			return (0);
	}
	return (1);
}

int	delete_backslash(t_node **head)
{
	int		pos;
	t_node	*tmp;

	pos = -1;
	tmp = *head;
	while (++pos < ft_len_node(*head))
	{
		if (!iter_node(&tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
