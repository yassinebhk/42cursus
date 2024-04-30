/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pos_and_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:57:08 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/30 12:39:50 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_node  *ft_set_pos(t_node *stack)
{
    t_node  *tmp;
    int     len;
    int     pos;

    pos = 1;
    tmp = stack;
    len = ft_len_list(stack);
    if(len == 1)
        stack->pos = pos;
    else if (len > 1)
    {
        while (pos <= len)
        {
            tmp->pos = pos;
            tmp = tmp->next;
            pos++;
        }
    }
    return (stack);
}

t_node  *ft_set_index(t_node *stack)
{
    int     len;
    int     index;
    int     i;
    int     value;
    t_node  *tmp;

    index = 0;
    tmp = stack;
    value = INT_MAX;
    len = ft_len_list(stack);
    while (++index <= len)
    {
        i = -1;
        while (++i < len)
        {
            if (tmp->value <= value)
            {
                tmp->index = index;
                value = tmp->value;
            }
            tmp = tmp->next;
        }               
    }
    return (stack);
}

void    ft_set_pos_and_inex(t_node **stack_a, t_node **stack_b)
{
    *stack_a = ft_set_pos(*stack_b);
    *stack_b = ft_set_pos(*stack_a);
    *stack_a = ft_set_index(*stack_a);
    *stack_b = ft_set_index(*stack_b);
}

