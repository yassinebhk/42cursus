/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:44:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 21:44:39 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_node	*ft_last_node(t_node *stack_a)
{
	t_node	*tmp;

	tmp = stack_a;
	while (tmp->next != stack_a)
		tmp = tmp->next;
	return (tmp);
}

static void	ft_add_back(t_node **stack_a, t_node *new_node)
{
	t_node	*last_node;

	last_node = ft_last_node(*stack_a);
	new_node->before = last_node;
	new_node->next = *stack_a;
	last_node->next = new_node;
}

static t_node	*ft_get_node(int value, int pos)
{
	t_node	*new_node;

	new_node = ft_new_node(value);
	new_node->pos = pos;
	return (new_node);
}

void	ft_fill_stack_a(t_node **stack_a, int *list, int length)
{
	int		i;
	t_node	*new_node;
	t_node	*last_node;

	i = 0;
	(*stack_a)->value = list[i];
	(*stack_a)->pos = 0;
	while (++i < length)
	{
		new_node = ft_get_node(list[i], i);
		ft_add_back(stack_a, new_node);
	}
	last_node = ft_last_node(*stack_a);
	(*stack_a)->before = last_node;
}
