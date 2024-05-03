/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:29:22 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/05/03 12:16:16 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_two_nodes(t_node **stack_a, t_node **stack_b, int flag)
{
	if (flag == 0)
	{
		if ((*stack_a)->index > (*stack_a)->next->index)
		{  
			sa(stack_a);
			ft_set_pos_and_inex(stack_a, stack_b);
		}
	}
	else
	{
		if ((*stack_b)->index > (*stack_b)->next->index)
		{  
			sa(stack_b);
			ft_set_pos_and_inex(stack_a, stack_b);
		}
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
		if (tmp->value > *max_abs)
		{
			*max_rel = *max_abs;	
			*max_abs = tmp->value;
		}
		else if (tmp->value > *max_rel)
			*max_rel = tmp->value;	
		tmp = tmp->next;
	}
}

int	ft_find_min(t_node *stack_a)
{
	int		min;
	t_node	*head;

	head = stack_a;
	min = stack_a->value;
	while (stack_a->next != head)
	{
		if (stack_a->value < min)
			min = stack_a->value;
		stack_a = stack_a->next;
	}
	return (min);
}

int ft_is_ordered(t_node *stack)
{
	t_node *head;
	
	head = stack;
	if((stack)->value != ft_find_min(stack))
		return(0);
	while (stack->next != head)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void ft_make_mvts(t_node **stack_a, t_node **stack_b, int flag)
{
	if (flag == 0)
	{
		ra(stack_a);
		ft_set_pos_and_inex(stack_a, stack_b);
		ft_two_nodes(stack_a, stack_a, flag);
		ra(stack_a);
		ft_set_pos_and_inex(stack_a, stack_b);
		ra(stack_a);
		ft_set_pos_and_inex(stack_a, stack_b);
	}
	else
	{
		ra(stack_b);
		ft_set_pos_and_inex(stack_a, stack_b);
		ft_two_nodes(stack_a, stack_a, flag);
		ra(stack_b);
		ft_set_pos_and_inex(stack_a, stack_b);
		ra(stack_b);
		ft_set_pos_and_inex(stack_a, stack_b);	
	}
}

void ft_trunc_three_nodes(t_node **stack, t_node **stack_aux)
{	
	int cont;
	t_node *list_three;
	t_node *fourth_node;
	t_node *last_node;
	
	cont = -1;
	list_three = *stack;
	if (ft_len_list(*stack) > 3)
	{	
		last_node = list_three->before;
		fourth_node = list_three->next->next->next;
		list_three->next->next->next = *stack;
		list_three->before = fourth_node->before;
		ft_three_nodes(&list_three, stack_aux);
		ft_set_costs(&list_three);
		ft_set_pos_and_inex(&list_three, stack_aux);


		int	i = -1;
		int length = ft_len_list(list_three);
		ft_printf("\n|-------- list_three ---------|\n\n");
		while (++i < length)
		{
			ft_printf("list_three | pos: %d | value: %d | index: %d | cost: %d\n", (list_three)->pos, (list_three)->value, (list_three)->index, (list_three)->cost); 
			(list_three) = (list_three)->next;
		}
		ft_printf("\n|--------------------------|\n\n");

		
		ft_printf("Hola he salido del three_nodes\n");
		*stack = list_three;
		(*stack)->next->next->next = fourth_node;
		(*stack)->before = last_node;
		ft_set_costs(stack);
		ft_set_pos_and_inex(stack, stack_aux);
		
		i = -1;
		length = ft_len_list(*stack);
		ft_printf("\n|--------  STACK ---------|\n\n");
		while (++i < length)
		{
			ft_printf("stack_a | pos: %d | stack_a value: %d | index: %d | cost: %d\n", (*stack)->pos, (*stack)->value, (*stack)->index, (*stack)->cost); 
			(*stack) = (*stack)->next;
		}
		ft_printf("\n|--------------------------|\n\n");

		
	}
	else
		ft_three_nodes(stack, stack_aux);
}

void ft_look_for_highest(t_node **stack, t_node **stack_aux)
{
	int		max_abs;
	int		max_rel;
	t_node	*tmp;

	tmp = (*stack);
	ft_find_maxs(&max_abs, &max_rel, *stack);
	// tmp->next->value != max_rel || tmp->next->next->value != max_abs
	int i =0;
	while (++i < 4)
	{
		ft_trunc_three_nodes(stack, stack_aux);
		ft_printf("\n\nValues after trunc: %d %d\n", (*stack)->next->value, (*stack)->next->next->value);
		if ((*stack)->next->value == max_rel && (*stack)->next->next->value == max_abs)
			break ;
		ra(stack);
		ft_set_pos_and_inex(stack, stack_aux);
		tmp = *stack;	
		ft_printf("Values: %d %d\n\n", tmp->next->value, tmp->next->next->value);
	}
}

void 	ft_set_highest_first(t_node **stack_a, t_node **stack_b, int flag)
{
	t_node	*tmp;

	if (flag == 0)
		ft_look_for_highest(stack_a, stack_b);
	else
		ft_look_for_highest(stack_b, stack_a);

}

void	ft_order_list(t_node **stack_a, t_node **stack_b, int flag)
{
	int		max_abs;
	int		max_rel;

	ft_find_maxs(&max_abs, &max_rel, *stack_a);
	ft_printf("Max_abs = %d\n", max_abs);
	ft_printf("Max_rel = %d\n", max_rel);
	ft_set_highest_first(stack_a, stack_b, flag);
	ft_printf("He salido del set high\n");
	//ft_make_mvts(stack_a, stack_b, flag);
	// while(!ft_is_ordered(*stack_a))
	// {
	// 	if ((*stack_a)->value == max_abs && (*stack_a)->next->value == max_rel) 
	// 	{
	// 		sa(stack_a);
	// 		ra(stack_a);
	// 	}
	// 	else
	// 		ft_two_nodes(stack_a, stack_b, flag);
	// 	ra(stack_a);   
	// 	ft_set_pos_and_inex(stack_a, stack_b);
	// }                  
}

void	ft_general(t_node **stack_a, t_node **stack_b)
{	
	int		cont;
	t_node	*head;
	
	cont = 0;
	ft_check_low_index(stack_a, stack_b);
	ft_set_costs(stack_a);
	ft_set_costs(stack_b);
	head = *stack_a;
	if (ft_len_list(*stack_a) == 2)
		ft_two_nodes(stack_a, stack_b, 0);
	if (ft_len_list(*stack_b) == 2)
		ft_two_nodes(stack_a, stack_b, 1);
	else
	{
		ft_order_list(stack_a, stack_b, 0);
		//ft_order_list(stack_a, stack_b, 1);
	}
	ft_set_pos_and_inex(stack_a, stack_b);
	ft_set_costs(stack_a);
	ft_set_costs(stack_b);
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
