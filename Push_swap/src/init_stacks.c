/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:25:03 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/28 20:25:04 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_node *ft_new_node(int value)
{
    t_node *stack;

    stack = (t_node *)malloc (sizeof(t_node));
    stack->before = stack;
    stack->next = stack;
    stack->cost = -1;
    stack->index = -1;
    stack->pos = -1;
    stack->value = value;
    return (stack);
}

void    ft_init_stacks(t_node **stack_a, t_node **stack_b)
{
    *stack_a = ft_new_node(0);
    *stack_b = NULL;
}
