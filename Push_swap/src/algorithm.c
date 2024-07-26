/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:29:22 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/25 01:06:57 by yassine          ###   ########.fr       */
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

void ft_update_parameters(t_node **stack_a, t_node **stack_b)
{
	ft_set_pos_and_inex(stack_a, stack_b);
	ft_set_costs(stack_a);
	ft_set_costs(stack_b);
}


t_node *ft_get_lowest_node(t_node *stack_b)
{
	int len;
	int lowest_cost;
	int rel_pos;
	t_node *tmp;

	rel_pos = 1;
	tmp = stack_b->next;
	len = ft_len_list(stack_b);
	lowest_cost = stack_b->cost_change;
	while (--len > 0)
	{
		if (tmp->cost_change < lowest_cost)
		{
			lowest_cost = tmp->cost_change;
			rel_pos = tmp->pos;
		}	
		tmp = tmp->next;
	}
	while(--rel_pos > 0)
		stack_b = stack_b->next;
	return (stack_b);
}

int ft_get_lowest_value(t_node *stack)
{
	int min;
	int pos;
	int len;

	pos = 1;
	min = INT_MAX;
	len  = ft_len_list(stack);
	//ft_printf("\nvalue %d %d %d", stack->value, stack->next->value, stack->pos);
	while (--len >= 0)
	{
		if (stack->value < min)
		{
			min = stack->value;
			pos = stack->pos;
		}
		stack = stack->next;
	}
	//ft_printf("\npos %d\n", pos);
	return (pos);
}

int ft_get_change_cost(t_node *stack, int value, int cost)
{
	int len;
	int change_cost;
	int nearest;

	nearest = INT_MAX;
	change_cost = -1;
	len = ft_len_list(stack);
	while (--len >= 0)
	{
	//ft_printf("s_val: %d near: %d s_pos: %d  val:%d\n", stack->value, nearest, stack->pos, value);
		if (stack->value < nearest && stack->value > value)
		{
			//ft_printf("entro\n");
			nearest = stack->value;
			change_cost = cost + stack->pos;
		}
		stack = stack->next;
	}
	if (change_cost == -1)
		return (ft_get_lowest_value(stack) + cost);
	return (change_cost);
}


t_node *ft_cost_change(t_node *stack_aux, t_node **stack)
{
    int len;
	t_node *tmp;
    
	tmp = *stack;
	len = ft_len_list(*stack);
	while (--len >= 0)
	{
		(*stack)->cost_change = ft_get_change_cost(stack_aux, (*stack)->value, (*stack)->cost);
		(*stack) = (*stack)->next;
	}
	return (ft_get_lowest_node(*stack));
}

void    ft_mvts_a(t_node **stack_a, t_node **stack_b, int flag, t_node *best_index)
{	
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
	
	
    if (!flag)
    {
		while((--best_index->cost_change - best_index->cost) > 0)
        {
            rb(stack_b);
            ft_update_parameters(stack_a, stack_b);
        }
        while(--(best_index->cost) >= 0)
        {
            ra(stack_a);
            ft_update_parameters(stack_a, stack_b);
        }
		pb(stack_a, stack_b);
		ft_update_parameters(stack_a, stack_b);
		ft_update_parameters(stack_a, stack_b);
    }
    else
    { 
		while((--best_index->cost_change - best_index->cost) > 0)
        {
            rb(stack_b);
            ft_update_parameters(stack_a, stack_b);
        }
        while(--(best_index->cost) >= 0)
        {
            rra(stack_a);
            ft_update_parameters(stack_a, stack_b);
        }
	    pb(stack_a, stack_b);
		ft_update_parameters(stack_a, stack_b);
    }
}

void	ft_check_low_index(t_node **stack_a, t_node **stack_b)
{	
	t_node *best_index;

	pb(stack_a, stack_b);
	pb(stack_a, stack_b);
	pb(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
	while (ft_len_list((*stack_a))> 3)
    {

	// int i = -1;
	// int length = ft_len_list((*stack_a));
	// ft_printf("\n|before cost change--------  (*stack_a) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index: %d | cost: %d | cost_change: %d\n",
	// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost, (*stack_b)->cost_change);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");

	
        best_index = ft_cost_change(*stack_b, stack_a);	


	// ft_printf("(best_index) | puntero %p | pos: %d | (best_index) value: %d | index: %d | cost: %d| change_cost: %d\n", (best_index), (best_index)->pos, (best_index)->value, (best_index)->index, (best_index)->cost, (best_index)->cost_change); 
	// i = -1;
	// length = ft_len_list((*stack_a));
	// ft_printf("\n|updated costs-------  (*stack_a) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d| change_cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost, (*stack_a)->cost_change); 
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index: %d | cost: %d| change_cost: %d\n",
	// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost, (*stack_b)->cost_change);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");		

		



		
        if (best_index->pos <= (int)(ft_len_list(*stack_a) / 2) + 1)
            ft_mvts_a(stack_a, stack_b, 0, best_index);
        else
            ft_mvts_a(stack_a, stack_b, 1, best_index);
		ft_update_parameters(stack_a, stack_b);





	// i = -1;
	// length = ft_len_list((*stack_a));
	// ft_printf("\n|after mvts --------  (*stack_a) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index: %d | cost: %d\n",
	// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n|--------------------------|\n");


		
    }

	// int i = -1;
	// int length = ft_len_list((*stack_a));
	// ft_printf("\n|after mvts --------  (*stack_a) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index: %d | cost: %d\n",
	// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost);
	// 	(*stack_b) = (*stack_b)->next;
	// }

	
	ft_update_parameters(stack_a, stack_b);
	if (ft_len_list((*stack_a)) == 3)
		ft_three_nodes(stack_a, stack_b);
	else if (ft_len_list((*stack_a)) == 2)
		ft_two_nodes(stack_a, stack_b, 0);
}

void ft_mvts_0(t_node **stack_a, t_node **stack_b, int cost, int cost_change)
{
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


	
	while((--cost_change - cost) > 0)
	{
		ra(stack_a);
		ft_update_parameters(stack_a, stack_b);
	}
	while(--(cost) >= 0)
	{
		rb(stack_b);
		ft_update_parameters(stack_a, stack_b);
	}
	pa(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
}

void ft_mvts_1(t_node **stack_a, t_node **stack_b, int cost_change, int cost)
{
	int cont;
	int len;

	cont = -1;
	len = ft_len_list(*stack_a);
	while(++cont < len - cost_change + 1 + cost)
	{	
		rra(stack_a);
		ft_update_parameters(stack_a, stack_b);
	}
	cont = -1;
	while(++cont < (cost))
	{
		rb(stack_b);
		ft_update_parameters(stack_a, stack_b);
	}
	pa(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
}

void ft_mvts_2(t_node **stack_a, t_node **stack_b, int cost_change, int cost)
{
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


	
	while((--cost_change - cost) > 0)
	{
		rra(stack_a);
		ft_update_parameters(stack_a, stack_b);
	}
	while(--(cost) >= 0)
	{
		rrb(stack_b);
		ft_update_parameters(stack_a, stack_b);
	}
	pa(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
}

void ft_mvts_3(t_node **stack_a, t_node **stack_b, int cost_change, int cost)
{
	while((--cost_change - cost) > 0)
	{	
		ra(stack_a);
		ft_update_parameters(stack_a, stack_b);
	}
	while(--cost >= 0)
	{
		rrb(stack_b);
		ft_update_parameters(stack_a, stack_b);
	}
	pa(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
}

void    ft_mvts_b(t_node **stack_a, t_node **stack_b, int flag, t_node *best_index)
{	
	if (best_index->cost_change == 1)
		pa(stack_a, stack_b);
	else if (best_index->cost_change == 2 && ft_len_list(*stack_b) == best_index->pos && best_index->pos > 1)
	{
		rrb(stack_b);
		pa(stack_a, stack_b);
	}
    else if (!flag)
    {
        if (best_index->cost_change - best_index->cost <= (int)(ft_len_list(*stack_a) / 2 + 1))
			ft_mvts_0(stack_a, stack_b, best_index->cost, best_index->cost_change);
		else
			ft_mvts_1(stack_a, stack_b, best_index->cost_change, best_index->cost);
    }
    else
    { 
        if (best_index->cost_change - best_index->cost < (int)(ft_len_list(*stack_a) / 2))
			ft_mvts_3(stack_a, stack_b, best_index->cost_change, best_index->cost);
		else
			ft_mvts_2(stack_a, stack_b, best_index->cost_change, best_index->cost);
    }
	ft_update_parameters(stack_a, stack_b);
}


void	ft_push_ordered(t_node **stack_a, t_node **stack_b)
{	
	t_node	*best_index;

    while (ft_len_list((*stack_b))> 0)
    {


	// int i = -1;
	// int length = ft_len_list((*stack_a));
	// ft_printf("\n|before cost change--------  (*stack_a) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index: %d | cost: %d | cost_change: %d\n",
	// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost, (*stack_b)->cost_change);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");

		
        best_index = ft_cost_change(*stack_a, stack_b);



	// ft_printf("(best_index) | puntero %p | pos: %d | (best_index) value: %d | index: %d | cost: %d| change_cost: %d\n", (best_index), (best_index)->pos, (best_index)->value, (best_index)->index, (best_index)->cost, (best_index)->cost_change); 
	// i = -1;
	// length = ft_len_list((*stack_a));
	// ft_printf("\n|updated costs-------  (*stack_a) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d| change_cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost, (*stack_a)->cost_change); 
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index: %d | cost: %d| change_cost: %d\n",
	// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost, (*stack_b)->cost_change);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");




	
        if (best_index->pos <= (int)(ft_len_list(*stack_b) / 2) + 1)
            ft_mvts_b(stack_a, stack_b, 0, best_index);
        else
            ft_mvts_b(stack_a, stack_b, 1, best_index);


	// i = -1;
	// length = ft_len_list((*stack_a));
	// ft_printf("\n|after mvts --------  (*stack_a) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index: %d | cost: %d\n",
	// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n|--------------------------|\n");

	// int	i = -1;
	// int length = ft_len_list((*stack_a));
	// //ft_printf("\n|--------  (*stack_a) ---------|\n\n");
	// ft_printf("\n");
	// while (++i < length)
	// {
	// 	//ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	ft_printf("%d ", (*stack_a)->value);
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// while (++i < length)
	// {
	// 	//ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	ft_printf("%d ", (*stack_b)->value);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n");


    }
}

void	ft_general(t_node **stack_a, t_node **stack_b)
{	
	// int	i = -1;
	// int length = ft_len_list((*stack_a));
	// ft_printf("\n|--------  (*stack_a) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index: %d | cost: %d\n",
	// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");





	ft_check_low_index(stack_a, stack_b);


	// int	i = -1;
	// int length = ft_len_list((*stack_a));
	// //ft_printf("\n|--------  (*stack_a) ---------|\n\n");
	// ft_printf("\n\n");
	// while (++i < length)
	// {
	// 	//ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	ft_printf("%d ", (*stack_a)->value);
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n\n");
	// ft_printf("\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// while (++i < length)
	// {
	// 	//ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	ft_printf("%d ", (*stack_b)->value);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n\n");

	// int i = -1;
	// int length = ft_len_list((*stack_a));
	// ft_printf("\n|after lowest index--------  (*stack_a) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index: %d | cost: %d\n",
	// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n\n\n\n|---------STACK_B------------|\n\n\n\n");






	ft_push_ordered(stack_a, stack_b);
	ft_update_parameters(stack_a, stack_b);
	//ft_printf("\n......................\n");
	if ((*stack_a)->index != 1)
	{
		if ((*stack_a)->index >  ft_len_list(*stack_a) / 2 + 1)
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
	// ft_printf("\n|--------  (*stack_a) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_a) | puntero %p | pos: %d | (*stack_a) value: %d | index: %d | cost: %d\n", (*stack_a), (*stack_a)->pos, (*stack_a)->value, (*stack_a)->index, (*stack_a)->cost); 
	// 	(*stack_a) = (*stack_a)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list((*stack_b));
	// ft_printf("\n|-------- (*stack_b) ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("(*stack_b) | puntero %p | pos: %d | (*stack_b) value: %d | index: %d | cost: %d\n",
	// 		(*stack_b), (*stack_b)->pos, (*stack_b)->value, (*stack_b)->index, (*stack_b)->cost);
	// 	(*stack_b) = (*stack_b)->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");	

