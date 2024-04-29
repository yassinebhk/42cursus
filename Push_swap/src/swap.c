/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:48:31 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/29 19:22:33 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void    swap(t_node **stack)
{
    t_node *tmp1;
    t_node *tmp2;
    t_node *last_node;
    
    tmp1 = (*stack);
    tmp2 = (*stack)->before;
    last_node = ft_last_node(*stack);
    (*stack) = (*stack)->next;
    tmp1->next = (*stack)->next;
    tmp1->before = (*stack);
    (*stack)->next = tmp1;
    (*stack)->before = tmp2;
    last_node->next = (*stack);
}

void    sa(t_node **stack_a)
{
    if (ft_len_list(*stack_a) > 1)
    {
        swap(stack_a);
        ft_printf("sa\n");
    }
}

void    sb(t_node **stack_b)
{
    if (ft_len_list(*stack_b) > 1)
    {
        swap(stack_b);
        ft_printf("sb\n");
    }
}

void    ss(t_node **stack_a, t_node **stack_b)
{
    if (ft_len_list(*stack_b) > 1)
    {
        swap(stack_b);
        ft_printf("sb\n");
    }
    if (ft_len_list(*stack_a) > 1)
    {
        swap(stack_a);
        ft_printf("sa\n");
    }
}












