/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:51:47 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/29 20:38:19 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int ft_len_list(t_node *stack)
{
    int     len;
    t_node  *tmp;

    len = 1;
    if(stack->pos == -1)
        return (0);
    tmp = stack;
    //ft_printf("Value: %d Value_next: %d %p %p %p %p\n", stack->value, stack->next->value, stack->before, stack, stack->next, stack->next->next);
	while (tmp->next != stack)
    {
		tmp = tmp->next;
        len++;
    }
    return (len);
}

t_node  *ft_pop(t_node *stack)
{
    t_node  *tmp1;
    t_node  *tmp2;
    t_node  *last_node;

    tmp1 = stack;
    tmp2 = stack->before;
    if (ft_len_list(stack) == 1)
    {
        free(stack);
        stack->pos = -1;
        return(stack);
    }
    last_node = ft_last_node(stack);
    stack = stack->next;
    stack->before = tmp2;
    last_node->next = stack;
    free(tmp1);
    return (stack);
}

t_node  *ft_add_top(t_node *stack, t_node *new_node)
{
    t_node  *tmp1;
    t_node  *tmp2;
    t_node  *last_node;
    int     length;
    
    length = ft_len_list(stack);
    //ft_printf("\n length: %d\n", length);
    if (length == 0)
    {
        new_node->pos = 0;
        return (new_node);
    }
    tmp1 = stack->before;
    tmp2 = stack;
    last_node = ft_last_node(stack);
    new_node->before = tmp1;
    new_node->next = tmp2;
    stack = new_node;
    stack->pos = length;
    last_node->next = stack;
    return (stack);
    
}
