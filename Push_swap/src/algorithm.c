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

static void ft_update_before(t_node **stack)
{
	t_node *act;
	t_node *sig;
	int length;

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
		if ((*stack_b)->index > (*stack_b)->next->index)
			sa(stack_b);
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

void	ft_check_low_index(t_node **stack, t_node **stack_b)
{	
	t_node	*tmp;
	int 	length;
	int		i;

	i = -1;
	tmp = *stack;
	length = ft_len_list(*stack);
	while (++i < length)
	{
		if (tmp->index < (int)(length/2) + 1)
			pb(stack, stack_b);
		else
			ra(stack);
		tmp = tmp->next;
	}
	ft_set_pos_and_inex(stack, stack_b);

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

int	ft_find_min(t_node *stack)
{
	int		min;
	t_node	*head;

	head = stack;
	min = stack->value;
	while (stack->next != head)
	{
		if (stack->value < min)
			min = stack->value;
		stack = stack->next;
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

void ft_make_mvts(t_node **stack, t_node **stack_b, int flag)
{
	if (flag == 0)
	{
		ra(stack);
		ft_set_pos_and_inex(stack, stack_b);
		ft_two_nodes(stack, stack, flag);
		ra(stack);
		ft_set_pos_and_inex(stack, stack_b);
		ra(stack);
		ft_set_pos_and_inex(stack, stack_b);
	}
	else
	{
		ra(stack_b);
		ft_set_pos_and_inex(stack, stack_b);
		ft_two_nodes(stack, stack, flag);
		ra(stack_b);
		ft_set_pos_and_inex(stack, stack_b);
		ra(stack_b);
		ft_set_pos_and_inex(stack, stack_b);	
	}
}

void ft_trunc_three_nodes(t_node **stack, t_node **stackaux)
{	
	int cont;
	t_node *list_three;
	t_node *fourth_node;
	t_node *last_node;
	
	cont = -1;
	list_three = *stack;
	if (ft_len_list(*stack) > 3)
	{	
		last_node = (*stack)->before;
		fourth_node = list_three->next->next->next;
		list_three->next->next->next = *stack;
		list_three->before = fourth_node->before;
		ft_three_nodes(&list_three, stackaux);
		ft_set_pos_and_inex(&list_three, stackaux);
		*stack = list_three;
		(*stack)->next->next->next = fourth_node;
		fourth_node->before = (*stack)->next->next;
		(*stack)->before = last_node;
		last_node->next = *stack;
		ft_set_pos_and_inex(stack, stackaux);
	}
	else
		ft_three_nodes(stack, stackaux);
}

void ft_look_for_highest(t_node **stack, t_node **stackaux)
{
	int		max_abs;
	int		max_rel;
	t_node	*tmp;

	tmp = (*stack);
	ft_find_maxs(&max_abs, &max_rel, *stack);
	int i =0;
	while (tmp->next->value != max_rel || tmp->next->next->value != max_abs)
	{
		ft_trunc_three_nodes(stack, stackaux);
		if ((*stack)->next->value == max_rel && (*stack)->next->next->value == max_abs)
			break ;
		ra(stack);
		ft_set_pos_and_inex(stack, stackaux);
		tmp = *stack;	
	}
}

void 	ft_set_highest_first(t_node **stack_a, t_node **stack_b, int flag)
{
	if (!flag)
		ft_look_for_highest(stack_a, stack_b);
	else
		ft_look_for_highest(stack_b, stack_a);
}

void	ft_order_list(t_node **stack_a, t_node **stack_b, int flag)
{
	int		max_abs;
	int		max_rel;

	ft_find_maxs(&max_abs, &max_rel, *stack_a);
	ft_set_highest_first(stack_a, stack_b, flag);
	ft_make_mvts(stack_a, stack_b, flag);
	while(!ft_is_ordered(*stack_a))
	{
		if ((*stack_a)->value == max_abs && (*stack_a)->next->value == max_rel) 
		{
			sa(stack_a);
			ra(stack_a);
		}
		else
			ft_two_nodes(stack_a, stack_b, flag);
		ra(stack_a);   
		ft_set_pos_and_inex(stack_a, stack_b);
	}                  
}

void	ft_order_list_b(t_node **stack_a, t_node **stack_b, int flag)
{
	int		max_abs;
	int		max_rel;

	ft_find_maxs(&max_abs, &max_rel, *stack_b);
	ft_set_highest_first(stack_a, stack_b, flag);
	ft_make_mvts(stack_a, stack_b, flag);
	while(!ft_is_ordered(*stack_b))
	{
		if ((*stack_b)->value == max_abs && (*stack_b)->next->value == max_rel) 
		{
			sb(stack_b);
			rb(stack_b);
		}
		else
			ft_two_nodes(stack_a, stack_b, flag);
		rb(stack_b);   
		ft_set_pos_and_inex(stack_a, stack_b);
	}
	(*stack_b)->before = ft_last_node(*stack_b);
}

void	ft_order_reverse(t_node **stack_b)
{
	t_node	*ini;
	t_node	*end;
	int length;
	int tmp;
	int i;

	i = -1;
	ini = *stack_b;
	end = (*stack_b)->before;
	length = ft_len_list(*stack_b);
	while (++i < (int)(length / 2))
	{
		tmp = ini->value;
		ini->value = end->value;
		end->value = tmp;
		ini = ini->next;
		end = end->before;
	}
}

void	ft_push_ordered(t_node **stack_a, t_node **stack_b)
{	
	t_node	*tmp;
	int length;
	int i;

	i = -1;
	ft_printf("\n|--------------------------|\n\n");
	int j = -1;
	int lengt = ft_len_list(*stack_b);
	ft_printf("\n|-------- stack_b ---------|\n\n");
	while (++j < lengt)
	{
		ft_printf("stack_b | puntero %p | pos: %d | stack_b value: %d | index: %d | cost: %d\n",
			(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost);
		(*stack_b) = (*stack_b)->next;
	}
	ft_printf("\n|--------------------------|\n\n");
	ft_order_reverse(stack_b);
	length = ft_len_list(*stack_b);
	while (++i < length)
		pa(stack_a, stack_b);
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
	else
		ft_order_list(stack_a, stack_b, 0);
	if (ft_len_list(*stack_b) == 2)
		ft_two_nodes(stack_a, stack_b, 1);
	else
		ft_order_list_b(stack_a, stack_b, 1);
	ft_push_ordered(stack_a, stack_b);
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
