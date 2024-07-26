/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:11:02 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 23:13:36 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_free_stack(t_node *stack)
{
	t_node	*tmp;

	tmp = stack;
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

void	ft_free_all(t_node *stack_a, t_node *stack_b, int *list)
{
	ft_free_stack(stack_b);
	ft_free_stack(stack_a);
	free(list);
}
