/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:29:22 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/05/02 16:01:03 by yassine          ###   ########.fr       */
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

void	ft_find_maxs(int *max_abs, int *max_rel, t_node *stack)
{
	int		length;
	t_node	*tmp;

	if (stack->value > stack->next->value)
	{
		*max_abs = stack->value;
		*max_rel = stack->next->value;
	}
	else
	{
		*max_rel = stack->value;
		*max_abs = stack->next->value;	
	}
	tmp = stack->next->next;
	length = ft_len_list(stack);
	while (--length > 1)
	{
		if (tmp->value > max_abs)
		{
			*max_abs = tmp->value;
			*max_rel = stack->value;	
		}
		else if (tmp->value > max_rel)
			*max_rel = tmp->value;	
		tmp = tmp->next;
	}
}

// BUSCO QUEDARME EN EL STACK_A CON LOS 3 MAYORES NUMERO Y PASO TODO AL B
// ESTO PUEDE COSTAR MUCHOS MOVIMIENTOS HAY QUE VERLO 

void	ft_general(t_node **stack_a, t_node **stack_b)
{	
	int		cont;
	int		max_abs;
	int		max_rel;
	t_node	*tmp;
	t_node	*head;
	
	cont = 0;
	ft_check_low_index(stack_a, stack_b);
	ft_set_costs(stack_a);
	ft_set_costs(stack_b);
	head = *stack_a;
	tmp = (*stack_a)->next;
	if (ft_len_list(*stack_a) == 2)
		ft_two_nodes(stack_a, stack_b);
	else
	{
		ft_find_maxs(max_abs, max_rel, *stack_a);
		//ft_printf("hola: %p %p \n", tmp, head->before);
		while (tmp->next->value != max_rel && tmp->next->next->value != max_abs)
		{
			ft_three_nodes(stack_a, stack_b);
			ra(stack_a);
			ft_set_pos_and_inex(stack_a, stack_b);
			tmp = stack_a;	
		}
		ra(stack_a);
		ft_two_nodes(stack_a, stack_a);
		ra(stack_a);
		ra(stack_a);
		//AHORA ORDENO DE DOS EN DOS 
	}
	ft_set_pos_and_inex(stack_a, stack_b);
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
