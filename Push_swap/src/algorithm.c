/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:29:22 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/30 22:29:24 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_two_nodes(t_node **stack_a, t_node **stack_b)
{
	if ((*stack_a)->index > (*stack_a)->next->index)
	{  
		sa(stack_a);
		ft_set_pos_and_inex(stack_a, stack_b);
	}
}

void	ft_three_nodes(t_node **stack_a, t_node **stack_b)
{
	if ((*stack_a)->index > (*stack_a)->next->index)
	{
		sa(stack_a);
		ft_set_pos_and_inex(stack_a, stack_b);
	}
	if ((*stack_a)->index > (*stack_a)->next->next->index)
	{
		rra(stack_a);
		ft_set_pos_and_inex(stack_a, stack_b);
	}
	if ((*stack_a)->next->index > (*stack_a)->next->next->index)
	{
		rra(stack_a);
		ft_set_pos_and_inex(stack_a, stack_b);
		sa(stack_a);
		ft_set_pos_and_inex(stack_a, stack_b);
	}
}

void	ft_check_low_index(t_node **stack_a, t_node **stack_b)
{	
	t_node	*tmp;
	int 	length;
	int		i;

	i = -1;
	tmp = *stack_a;
	length = ft_len_list(*stack_a);
	while (++i < length)
	{
		if (tmp->index < (int)(length/2) + 1)
			pb(stack_a, stack_b);
		else
			ra(stack_a);
		tmp = tmp->next;
	}
	ft_set_pos_and_inex(stack_a, stack_b);

}

void	ft_general(t_node **stack_a, t_node **stack_b)
{
	ft_check_low_index(stack_a, stack_b);
	ft_set_costs(stack_a);
	ft_set_costs(stack_b);
}

void	ft_algorithm(t_node **stack_a, t_node **stack_b)
{
	if (ft_len_list(*stack_a) == 2)
		ft_two_nodes(stack_a, stack_b);
	else if (ft_len_list(*stack_a) == 3)
		ft_three_nodes(stack_a, stack_b);
	else
		ft_general(stack_a, stack_b);
}
