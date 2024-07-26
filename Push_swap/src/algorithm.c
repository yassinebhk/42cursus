/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:43:57 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 22:51:21 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_update_parameters(t_node **stack_a, t_node **stack_b)
{
	ft_set_pos_and_inex(stack_a, stack_b);
	ft_set_costs(stack_a);
	ft_set_costs(stack_b);
}

void	ft_push_ordered(t_node **stack_a, t_node **stack_b)
{
	t_node	*best_index;

	while (ft_len_list((*stack_b)) > 0)
	{
		best_index = ft_cost_change(*stack_a, stack_b);
		if (best_index->pos <= (int)(ft_len_list(*stack_b) / 2) + 1)
			ft_mvts_b(stack_a, stack_b, 0, best_index);
		else
			ft_mvts_b(stack_a, stack_b, 1, best_index);
	}
}

void	ft_check_low_index(t_node **stack_a, t_node **stack_b)
{
	t_node	*best_index;

	pb(stack_a, stack_b);
	pb(stack_a, stack_b);
	pb(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
	while (ft_len_list((*stack_a)) > 3)
	{
		best_index = ft_cost_change(*stack_b, stack_a);
		if (best_index->pos <= (int)(ft_len_list(*stack_a) / 2) + 1)
			ft_mvts_a(stack_a, stack_b, 0, best_index);
		else
			ft_mvts_a(stack_a, stack_b, 1, best_index);
		ft_update_parameters(stack_a, stack_b);
		ft_update_parameters(stack_a, stack_b);
		if (ft_len_list((*stack_a)) == 3)
			ft_three_nodes(stack_a, stack_b);
		else if (ft_len_list((*stack_a)) == 2)
			ft_two_nodes(stack_a, stack_b, 0);
	}
}

void	ft_general(t_node **stack_a, t_node **stack_b)
{
	ft_check_low_index(stack_a, stack_b);
	ft_push_ordered(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
	if ((*stack_a)->index != 1)
	{
		if ((*stack_a)->index > ft_len_list(*stack_a) / 2 + 1)
		{
			while ((*stack_a)->index != 1)
			{
				ra(stack_a);
				ft_update_parameters(stack_a, stack_b);
			}
		}
		else
		{
			while ((*stack_a)->index != 1)
			{
				rra(stack_a);
				ft_update_parameters(stack_a, stack_b);
			}
		}
	}
}

void	ft_algorithm(t_node **stack_a, t_node **stack_b)
{
	if (ft_len_list(*stack_a) == 2)
		ft_two_nodes(stack_a, stack_b, 0);
	else if (ft_len_list(*stack_a) == 3)
		ft_three_nodes(stack_a, stack_b);
	else
		ft_general(stack_a, stack_b);
}

// int	i = -1;
// int length = ft_len_list((*stack_a));
// //ft_printf("\n|--------  (*stack_a) ---------|\n\n");
// ft_printf("\n\n");
// while (++i < length)
// {
// 	//ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value:
//%d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos,
//(*stack_a)->value, (*stack_a)->index, (*stack_a)->cost);
// 	ft_printf("%d ", (*stack_a)->value);
// 	(*stack_a) = (*stack_a)->next;
// }
// ft_printf("\n\n");
// ft_printf("\n\n");
// i = -1;
// length = ft_len_list((*stack_b));
// while (++i < length)
// {
// 	//ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value:
//%d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos,
//(*stack_a)->value, (*stack_a)->index, (*stack_a)->cost);
// 	ft_printf("%d ", (*stack_b)->value);
// 	(*stack_b) = (*stack_b)->next;
// }
// ft_printf("\n\n");
// int i = -1;
// int length = ft_len_list((*stack_a));
// ft_printf("\n|after lowest index--------  (*stack_a) ---------|\n\n");
// while (++i < length)
// {
// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value:
//%d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos,
//(*stack_a)->value, (*stack_a)->index, (*stack_a)->cost);
// 	(*stack_a) = (*stack_a)->next;
// }
// ft_printf("\n|--------------------------|\n\n");
// i = -1;
// length = ft_len_list((*stack_b));
// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
// while (++i < length)
// {
// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value:
//%d | index: %d | cost: %d\n",
// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index,
//(*stack_b)->cost);
// 	(*stack_b) = (*stack_b)->next;
// }
// ft_printf("\n\n\n\n|---------STACK_B------------|\n\n\n\n");

// int	i = -1;
// int length = ft_len_list((*stack_a));
// ft_printf("\n|--------  (*stack_a) ---------|\n\n");
// while (++i < length)
// {
// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index:
//%d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value,
//(*stack_a)->index, (*stack_a)->cost);
// 	(*stack_a) = (*stack_a)->next;
// }
// ft_printf("\n|--------------------------|\n\n");
// i = -1;
// length = ft_len_list((*stack_b));
// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
// while (++i < length)
// {
// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index:
//%d | cost: %d\n",
// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index,
//(*stack_b)->cost);
// 	(*stack_b) = (*stack_b)->next;
// }
// ft_printf("\n|--------------------------|\n\n");
