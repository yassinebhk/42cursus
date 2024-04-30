/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:41:21 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/29 23:44:22 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	rotate(t_node **stack)
{
	(*stack) = (*stack)->next;
}

void	ra(t_node **stack_a)
{
	if (ft_len_list(*stack_a) == 1)
		ft_printf("ra\n");
	else if (ft_len_list(*stack_a) > 1)
	{
		rotate(stack_a);
		ft_printf("ra\n");
	}
}

void	rb(t_node **stack_b)
{
	if (ft_len_list(*stack_b) == 1)
		ft_printf("rb\n");
	else if (ft_len_list(*stack_b) > 1)
	{
		rotate(stack_b);
		ft_printf("rb\n");
	}
}

void	rr(t_node **stack_a, t_node **stack_b)
{
	if (ft_len_list(*stack_b) > 1 && ft_len_list(*stack_a) > 1)
	{
		rotate(stack_b);
		rotate(stack_a);
		ft_printf("rr\n");
	}
}
