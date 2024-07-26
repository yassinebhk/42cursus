/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvts_stack_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:57:56 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 22:17:01 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	ft_mvts_0(t_node **stack_a, t_node **stack_b, t_node *best_index)
{
	while ((--best_index->cost_change - best_index->cost) > 0)
	{
		rb(stack_b);
		ft_update_parameters(stack_a, stack_b);
	}
	while (--(best_index->cost) >= 0)
	{
		ra(stack_a);
		ft_update_parameters(stack_a, stack_b);
	}
	pb(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
}

static void	ft_mvts_1(t_node **stack_a, t_node **stack_b, t_node *best_index)
{
	while ((--best_index->cost_change - best_index->cost) > 0)
	{
		rb(stack_b);
		ft_update_parameters(stack_a, stack_b);
	}
	while (--(best_index->cost) >= 0)
	{
		rra(stack_a);
		ft_update_parameters(stack_a, stack_b);
	}
	pb(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
}

void	ft_mvts_a(t_node **stack_a, t_node **stack_b, int flag,
		t_node *best_index)
{
	if (!flag)
	{
		ft_mvts_0(stack_a, stack_b, best_index);
	}
	else
	{
		ft_mvts_1(stack_a, stack_b, best_index);
	}
}
// int cost;
// int cost_copy;
// int cost_change;
// cost_copy = best_index->cost;
// cost = best_index->cost;
// cost_change = best_index->cost;
// if (!flag)
// {
// 	while((--cost_change - cost_copy) > 0 && --(cost) >= 0)
//     {
//         rr(stack_a, stack_b);
//         ft_update_parameters(stack_a, stack_b);
//     }
// 	while((cost_change - cost_copy) > 0)
//     {
//         rb(stack_b);
//         ft_update_parameters(stack_a, stack_b);
// 		cost_change--;
//     }
//     while((cost) >= 0)
//     {
//         ra(stack_a);
//         ft_update_parameters(stack_a, stack_b);
// 		cost--;
//     }
// 	pb(stack_a, stack_b);
// 	ft_update_parameters(stack_a, stack_b);
// }