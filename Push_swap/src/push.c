/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:41:16 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/29 20:29:27 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	push(t_node **stack_a, t_node **stack_b, char c)
{
	t_node	*new_node;

	if (c == 'a' && ft_len_list(*stack_b) > 0)
	{
		new_node = ft_new_node((*stack_b)->value);
		*stack_b = ft_pop(*stack_b);
		*stack_a = ft_add_top(*stack_a, new_node);
	}
	else if (c == 'b' && ft_len_list(*stack_a) > 0)
	{
		new_node = ft_new_node((*stack_a)->value);
		*stack_a = ft_pop(*stack_a);
		*stack_b = ft_add_top(*stack_b, new_node);
	}
}

void	pa(t_node **stack_a, t_node **stack_b)
{
	if (ft_len_list(*stack_b) > 0)
	{
		push(stack_a, stack_b, 'a');
		ft_printf("pa\n");
	}
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	if (ft_len_list(*stack_a) > 0)
	{
		push(stack_a, stack_b, 'b');
		ft_printf("pb\n");
	}
}
