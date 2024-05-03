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

void	ft_two_nodes(t_node **stack, t_node **stack_b, int flag)
{
	if (flag == 0)
	{
		if ((*stack)->index > (*stack)->next->index)
			sa(stack);
	}
	else
	{
		if ((*stack_b)->index > (*stack_b)->next->index)
			sa(stack_b);
	}
	ft_set_pos_and_inex(stack, stack_b);
	ft_update_before(stack);
}

void	ft_three_nodes(t_node **stack, t_node **stack_b)
{
	if ((*stack)->index > (*stack)->next->index)
	{
		sa(stack);
		ft_set_pos_and_inex(stack, stack_b);
		ft_update_before(stack);
	}
	if ((*stack)->index > (*stack)->next->next->index)
	{
		rra(stack);
		ft_set_pos_and_inex(stack, stack_b);
		ft_update_before(stack);
	}
	if ((*stack)->next->index > (*stack)->next->next->index)
	{
		rra(stack);
		ft_set_pos_and_inex(stack, stack_b);
		ft_update_before(stack);
		sa(stack);
		ft_set_pos_and_inex(stack, stack_b);
		ft_update_before(stack);
	}
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

void ft_trunc_three_nodes(t_node **stack, t_node **stackux)
{	
	int cont;
	t_node *list_three;
	t_node *fourth_node;
	t_node *last_node;
	
	cont = -1;
	list_three = *stack;
	if (ft_len_list(*stack) > 3)
	{	


		// int	i = -1;
		// int length = ft_len_list(list_three);
		// ft_printf("\n|-------- list_three before anything ---------|\n\n");
    	// ft_printf("\n\n PUNTEROS: %p %p %p %p %p %p %p\n\n", list_three, list_three->before, list_three->before->before, list_three->before->before->before, list_three->before->before->before->before, list_three->before->before->before->before->before, list_three->before->before->before->before->before->before); 
		// while (++i < length)
		// {
		// 	ft_printf("list_three | puntero %p | pos: %d | value: %d | index: %d | cost: %d\n", (list_three), (list_three)->pos, (list_three)->value, (list_three)->index, (list_three)->cost); 
		// 	(list_three) = (list_three)->next;
		// }
		// ft_printf("\n|--------------------------|\n\n");



		last_node = (*stack)->before;
		fourth_node = list_three->next->next->next;
		list_three->next->next->next = *stack;
		list_three->before = fourth_node->before;
		ft_three_nodes(&list_three, stackux);
		ft_set_costs(&list_three);
		ft_set_pos_and_inex(&list_three, stackux);
                
		// i = -1;
		// length = ft_len_list(list_three);
		// ft_printf("\n|-------- list_three after order ---------|\n\n");
		// while (++i < length)
		// {
		// 	ft_printf("list_three | puntero %p | pos: %d | value: %d | index: %d | cost: %d\n", list_three, (list_three)->pos, (list_three)->value, (list_three)->index, (list_three)->cost); 
		// 	(list_three) = (list_three)->next;
		// }
    	// ft_printf("\n\n PUNTEROS STACK: %p %p %p %p %p %p %p\n", list_three, list_three->before, list_three->before->before, list_three->before->before->before, list_three->before->before->before->before, list_three->before->before->before->before->before, list_three->before->before->before->before->before->before); 
		// ft_printf("\n|--------------------------|\n\n");

		


		*stack = list_three;
		(*stack)->next->next->next = fourth_node;
		fourth_node->before = (*stack)->next->next;
		(*stack)->before = last_node;
		last_node->next = *stack;
		ft_set_pos_and_inex(stack, stackux);



		// ft_printf("\n|--------------------------|\n\n");
		// i = -1;
		// length = ft_len_list(*stack);
		// ft_printf("\n|-------- stack after link ---------|\n\n");
		// while (++i < length)
		// {
		// 	ft_printf("(*stack) | puntero %p | pos: %d | (*stack) value: %d | index: %d | cost: %d\n", (*stack),
		// 		(*stack)->pos, (*stack)->value, (*stack)->index, (*stack)->cost);
		// 	(*stack) = (*stack)->next;
		// }
    	// ft_printf("\n\n\n PUNTEROS BEFORE: %p %p %p %p %p %p %p %p %p\n\n\n", (*stack), (*stack)->before, (*stack)->before->before, (*stack)->before->before->before, (*stack)->before->before->before->before, (*stack)->before->before->before->before->before, (*stack)->before->before->before->before->before->before, (*stack)->before->before->before->before->before->before->before, (*stack)->before->before->before->before->before->before->before->before); 
		// ft_printf(" PUNTEROS NEXT: %p %p %p %p %p %p %p %p %p\n\n\n", (*stack), (*stack)->next, (*stack)->next->next, (*stack)->next->next->next, (*stack)->next->next->next->next, (*stack)->next->next->next->next->next, (*stack)->next->next->next->next->next->next, (*stack)->next->next->next->next->next->next->next, (*stack)->next->next->next->next->next->next->next->next); 
		// ft_printf("Next->before: %p", (*stack)->next->before);
		// ft_printf("\n|--------------------------|\n\n");


		ft_set_costs(stack);

		// ft_printf("\n\n He salido del ft_set_costs \n\n");
		// i = -1;
		// length = ft_len_list(*stack);
		// ft_printf("\n|--------  stack after update ---------|\n\n");
		// while (++i < length)
		// {
		// 	ft_printf("stack | puntero %p | pos: %d | stack value: %d | index: %d | cost: %d\n", (*stack), (*stack)->pos, (*stack)->value, (*stack)->index, (*stack)->cost); 
		// 	(*stack) = (*stack)->next;
		// }
		// ft_printf("\n|--------------------------|\n\n");

		
	}
	else
		ft_three_nodes(stack, stackux);
}

void ft_look_for_highest(t_node **stack, t_node **stackux)
{
	int		max_abs;
	int		max_rel;
	t_node	*tmp;

	tmp = (*stack);
	ft_find_maxs(&max_abs, &max_rel, *stack);
	// tmp->next->value != max_rel || tmp->next->next->value != max_abs
	int i =0;
	while (tmp->next->value != max_rel || tmp->next->next->value != max_abs)
	{
		ft_trunc_three_nodes(stack, stackux);
		// ft_printf("\n\n Values after trunc: %d %d\n", (*stack)->next->value, (*stack)->next->next->value);
    	// ft_printf("\n\n\n PUNTEROS: %p %p %p %p %p %p %p\n\n\n", (*stack), (*stack)->before, (*stack)->before->before, (*stack)->before->before->before, (*stack)->before->before->before->before, (*stack)->before->before->before->before->before, (*stack)->before->before->before->before->before->before); 
		if ((*stack)->next->value == max_rel && (*stack)->next->next->value == max_abs)
			break ;
		ra(stack);
		ft_set_pos_and_inex(stack, stackux);
		tmp = *stack;	

		// int	i = -1;
		// int length = ft_len_list((*stack));
		// ft_printf("\n|--------  stack new iter ---------|\n\n");
		// while (++i < length)
		// {
		// 	ft_printf("stack | puntero %p | pos: %d | stack value: %d | index: %d | cost: %d\n", (*stack), (*stack)->pos, (*stack)->value, (*stack)->index, (*stack)->cost); 
		// 	(*stack) = (*stack)->next;
		// }
		// ft_printf("\n|--------------------------|\n\n");
	
	}
}

void 	ft_set_highest_first(t_node **stack, t_node **stack_b, int flag)
{
	t_node	*tmp;

	if (flag == 0)
		ft_look_for_highest(stack, stack_b);
	else
		ft_look_for_highest(stack_b, stack);

}

void	ft_order_list(t_node **stack, t_node **stack_b, int flag)
{
	int		max_abs;
	int		max_rel;

	ft_find_maxs(&max_abs, &max_rel, *stack);


	// ft_printf("Max_abs = %d\n", max_abs);
	// ft_printf("Max_rel = %d\n", max_rel);
	// int	i = -1;
	// int length = ft_len_list(*stack);
	// ft_printf("\n|-------- *stack before ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("list_three | puntero %p | pos: %d | value: %d | index: %d | cost: %d\n", (*stack), (*stack)->pos, (*stack)->value, (*stack)->index, (*stack)->cost); 
	// 	(*stack) = (*stack)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");


	ft_set_highest_first(stack, stack_b, flag);
	//ft_printf("He salido del set high\n");
	ft_make_mvts(stack, stack_b, flag);



	// i = -1;
	// length = ft_len_list((*stack));
	// ft_printf("\n|--------  stack mvts ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("stack | puntero %p | pos: %d | stack value: %d | index: %d | cost: %d\n", (*stack), (*stack)->pos, (*stack)->value, (*stack)->index, (*stack)->cost); 
	// 	(*stack) = (*stack)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");



	while(!ft_is_ordered(*stack))
	{
		if ((*stack)->value == max_abs && (*stack)->next->value == max_rel) 
		{
			sa(stack);
			ra(stack);
		}
		else
			ft_two_nodes(stack, stack_b, flag);
		ra(stack);   
		ft_set_pos_and_inex(stack, stack_b);
	}                  
}

void	ft_general(t_node **stack, t_node **stack_b)
{	
	int		cont;
	t_node	*head;
	
	cont = 0;
	ft_check_low_index(stack, stack_b);
	ft_set_costs(stack);
	ft_set_costs(stack_b);
	head = *stack;
	if (ft_len_list(*stack) == 2)
		ft_two_nodes(stack, stack_b, 0);
	if (ft_len_list(*stack_b) == 2)
		ft_two_nodes(stack, stack_b, 1);
	else
	{
		ft_order_list(stack, stack_b, 0);
		ft_order_list(stack, stack_b, 1); //UTILIZAR FUNCION ABS
	}
	ft_set_pos_and_inex(stack, stack_b);
	ft_set_costs(stack);
	ft_set_costs(stack_b);
}

void	ft_algorithm(t_node **stack, t_node **stack_b)
{
	if (ft_len_list(*stack) == 2)
		ft_two_nodes(stack, stack_b, 0);
	else if (ft_len_list(*stack) == 3)
		ft_three_nodes(stack, stack_b);
	else
		ft_general(stack, stack_b);
}
