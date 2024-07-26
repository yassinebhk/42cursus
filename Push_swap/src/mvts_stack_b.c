/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvts_stack_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:52:58 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 23:11:39 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	ft_mvts_0(t_node **stack_a, t_node **stack_b, int cost,
		int cost_change)
{
	while ((--cost_change - cost) > 0)
	{
		ra(stack_a);
		ft_update_parameters(stack_a, stack_b);
	}
	while (--(cost) >= 0)
	{
		rb(stack_b);
		ft_update_parameters(stack_a, stack_b);
	}
	pa(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
}

static void	ft_mvts_1(t_node **stack_a, t_node **stack_b, int cost_change,
		int cost)
{
	int	cont;
	int	len;

	cont = -1;
	len = ft_len_list(*stack_a);
	while (++cont < len - cost_change + 1 + cost)
	{
		rra(stack_a);
		ft_update_parameters(stack_a, stack_b);
	}
	cont = -1;
	while (++cont < (cost))
	{
		rb(stack_b);
		ft_update_parameters(stack_a, stack_b);
	}
	pa(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
}

static void	ft_mvts_2(t_node **stack_a, t_node **stack_b, int cost_change,
		int cost)
{
	while ((--cost_change - cost) > 0)
	{
		rra(stack_a);
		ft_update_parameters(stack_a, stack_b);
	}
	while (--(cost) >= 0)
	{
		rrb(stack_b);
		ft_update_parameters(stack_a, stack_b);
	}
	pa(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
}

static void	ft_mvts_3(t_node **stack_a, t_node **stack_b, int cost_change,
		int cost)
{
	while ((--cost_change - cost) > 0)
	{
		ra(stack_a);
		ft_update_parameters(stack_a, stack_b);
	}
	while (--cost >= 0)
	{
		rrb(stack_b);
		ft_update_parameters(stack_a, stack_b);
	}
	pa(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
}

static int	ft_check_before(t_node **stack_a, t_node **stack_b,
		t_node *best_index)
{
	if (best_index->cost_change == 1)
	{
		pa(stack_a, stack_b);
		return (1);
	}
	else if (best_index->cost_change == 2
		&& ft_len_list(*stack_b) == best_index->pos && best_index->pos > 1)
	{
		rrb(stack_b);
		pa(stack_a, stack_b);
		return (1);
	}
	return (0);
}

void	ft_mvts_b(t_node **stack_a, t_node **stack_b, int flag,
		t_node *best_index)
{
	int	checked;

	checked = ft_check_before(stack_a, stack_b, best_index);
	if (!flag && !checked)
	{
		if (best_index->cost_change
			- best_index->cost <= (int)(ft_len_list(*stack_a) / 2 + 1))
			ft_mvts_0(stack_a, stack_b, best_index->cost,
				best_index->cost_change);
		else
			ft_mvts_1(stack_a, stack_b, best_index->cost_change,
				best_index->cost);
	}
	else if (!checked)
	{
		if (best_index->cost_change
			- best_index->cost < (int)(ft_len_list(*stack_a) / 2))
			ft_mvts_3(stack_a, stack_b, best_index->cost_change,
				best_index->cost);
		else
			ft_mvts_2(stack_a, stack_b, best_index->cost_change,
				best_index->cost);
	}
	ft_update_parameters(stack_a, stack_b);
}

    // mvts_0
	// int coste;
	// coste = cost;
	// while((--cost_change - coste) > 0 && --(cost) >= 0)
	// {
	// 	rr(stack_a, stack_b);
	// 	ft_update_parameters(stack_a, stack_b);
	// }
	// while((cost_change - coste) > 0)
	// {
	// 	ra(stack_a);
	// 	ft_update_parameters(stack_a, stack_b);
	// 	cost_change--;
	// }
	// while((cost) >= 0)
	// {
	// 	rb(stack_b);
	// 	ft_update_parameters(stack_a, stack_b);
	// 	cost--;
	// }
	// pa(stack_a, stack_b);
	// ft_update_parameters(stack_a, stack_b);


    // mvts_1
	// int coste;
	// coste = cost;
	// while((--cost_change - coste) > 0 && --(cost) >= 0)
	// {
	// 	rrr(stack_a, stack_b);
	// 	ft_update_parameters(stack_a, stack_b);
	// }
	// while((cost_change - coste) > 0)
	// {
	// 	rra(stack_a);
	// 	ft_update_parameters(stack_a, stack_b);
	// 	cost_change--;
	// }
	// while((cost) >= 0)
	// {
	// 	rrb(stack_b);
	// 	ft_update_parameters(stack_a, stack_b);
	// 	cost--;
	// }
	// pa(stack_a, stack_b);
	// ft_update_parameters(stack_a, stack_b);