/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_and_three_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:43:46 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 22:21:27 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	ft_update_before(t_node **stack)
{
	t_node	*act;
	t_node	*sig;
	int		length;

	length = ft_len_list(*stack);
	act = *stack;
	sig = (*stack)->next;
	while (--length > 0)
	{
		sig->before = act;
		act = sig;
		sig = sig->next;
	}
}

void	ft_two_nodes(t_node **stack_a, t_node **stack_b, int flag)
{
	if (flag == 0)
	{
		if ((*stack_a)->index > (*stack_a)->next->index)
			sa(stack_a);
	}
	else
	{
		if ((*stack_b)->index < (*stack_b)->next->index)
			sb(stack_b);
	}
	ft_set_pos_and_inex(stack_a, stack_b);
	ft_set_costs(stack_a);
	ft_update_before(stack_a);
	if (ft_len_list(*stack_b) > 1)
		ft_update_before(stack_b);
}

void	ft_three_nodes(t_node **stack, t_node **stack_aux)
{
	if ((*stack)->index > (*stack)->next->index)
	{
		sa(stack);
		ft_set_pos_and_inex(stack, stack_aux);
		ft_update_before(stack);
	}
	if ((*stack)->index > (*stack)->next->next->index)
	{
		rra(stack);
		ft_set_pos_and_inex(stack, stack_aux);
		ft_update_before(stack);
	}
	if ((*stack)->next->index > (*stack)->next->next->index)
	{
		rra(stack);
		ft_set_pos_and_inex(stack, stack_aux);
		ft_update_before(stack);
		sa(stack);
		ft_set_pos_and_inex(stack, stack_aux);
		ft_update_before(stack);
	}
	ft_set_costs(stack);
}
