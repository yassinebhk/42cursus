/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:41:21 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 23:07:30 by ybouhaik         ###   ########.fr       */
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
	else if (ft_len_list(*stack_b) > 1)
		rb(stack_b);
	else if (ft_len_list(*stack_a) > 1)
		ra(stack_a);
}
