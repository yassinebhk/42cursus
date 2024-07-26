/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:01:59 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 23:21:32 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static t_node	*ft_get_lowest_node(t_node *stack_b)
{
	int		len;
	int		lowest_cost;
	int		rel_pos;
	t_node	*tmp;

	rel_pos = 1;
	tmp = stack_b->next;
	len = ft_len_list(stack_b);
	lowest_cost = stack_b->cost_change;
	while (--len > 0)
	{
		if (tmp->cost_change < lowest_cost)
		{
			lowest_cost = tmp->cost_change;
			rel_pos = tmp->pos;
		}
		tmp = tmp->next;
	}
	while (--rel_pos > 0)
		stack_b = stack_b->next;
	return (stack_b);
}

static int	ft_get_lowest_value(t_node *stack)
{
	int	min;
	int	pos;
	int	len;

	pos = 1;
	min = INT_MAX;
	len = ft_len_list(stack);
	while (--len >= 0)
	{
		if (stack->value < min)
		{
			min = stack->value;
			pos = stack->pos;
		}
		stack = stack->next;
	}
	return (pos);
}

static int	ft_get_change_cost(t_node *stack, int value, int cost)
{
	int	len;
	int	change_cost;
	int	nearest;

	nearest = INT_MAX;
	change_cost = -1;
	len = ft_len_list(stack);
	while (--len >= 0)
	{
		if (stack->value < nearest && stack->value > value)
		{
			nearest = stack->value;
			change_cost = cost + stack->pos;
		}
		stack = stack->next;
	}
	if (change_cost == -1)
		return (ft_get_lowest_value(stack) + cost);
	return (change_cost);
}

t_node	*ft_cost_change(t_node *stack_aux, t_node **stack)
{
	int		len;
	t_node	*tmp;

	tmp = *stack;
	len = ft_len_list(*stack);
	while (--len >= 0)
	{
		(*stack)->cost_change = ft_get_change_cost(stack_aux, (*stack)->value,
				(*stack)->cost);
		(*stack) = (*stack)->next;
	}
	return (ft_get_lowest_node(*stack));
}
