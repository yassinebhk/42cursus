/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:11:02 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/29 20:38:23 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void    ft_free_stack(t_node *stack)
{
    t_node *tmp;

    tmp = stack;
    //ft_printf("\n\n len %d\n\n", ft_len_list(stack));
    if (stack == NULL)
        return ;
    if (ft_len_list(stack) == 1)
    {
        free(stack);
        return ;
    }
	while (stack->next != tmp)
    {
        free(stack);
		stack = stack->next;
    }
    free(stack);
}

void    ft_free_all(t_node *stack_a, t_node *stack_b, int *list)
{
    ft_free_stack(stack_b);
    ft_printf("Entro a liberar stack_a\n");
    ft_free_stack(stack_a);
    free(list);
}