/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:19:30 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/29 23:51:36 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	rotate_reverse(t_node **stack)
{
	(*stack) = (*stack)->before;
}

void	rra(t_node **stack_a)
{
	if (ft_len_list(*stack_a) == 1)
		ft_printf("rra\n");
	else if (ft_len_list(*stack_a) > 1)
	{
		rotate_reverse(stack_a);
		ft_printf("rra\n");
	}
}

void	rrb(t_node **stack_b)
{
	if (ft_len_list(*stack_b) == 1)
		ft_printf("rrb\n");
	else if (ft_len_list(*stack_b) > 1)
	{
		rotate_reverse(stack_b);
		ft_printf("rrb\n");
	}
}

void	rrr(t_node **stack_a, t_node **stack_b)
{
	if (ft_len_list(*stack_b) > 1 && ft_len_list(*stack_a) > 1)
	{
		rotate_reverse(stack_b);
		rotate_reverse(stack_a);
		ft_printf("rrr\n");
	}
}
