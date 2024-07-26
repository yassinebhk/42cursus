/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pos_and_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:44:48 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 21:44:49 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_node	*ft_set_pos(t_node *stack)
{
	t_node	*tmp;
	int		len;
	int		pos;

	pos = 1;
	tmp = stack;
	len = ft_len_list(stack);
	if (len == 1)
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

t_node	*ft_set_index(t_node *stack)
{
	t_node	*act;
	t_node	*tmp;
	int		len;
	int		j;
	int		i;

	j = -1;
	act = stack;
	len = ft_len_list(stack);
	while (++j < len)
	{
		i = 0;
		tmp = act->next;
		act->index = 1;
		while (++i < len)
		{
			if (act->value > tmp->value)
				act->index++;
			tmp = tmp->next;
		}
		act = act->next;
	}
	return (stack);
}

void	ft_set_pos_and_inex(t_node **stack_a, t_node **stack_b)
{
	if (*stack_a != NULL)
	{
		*stack_a = ft_set_pos(*stack_a);
		*stack_a = ft_set_index(*stack_a);
	}
	if (*stack_b != NULL)
	{
		*stack_b = ft_set_pos(*stack_b);
		*stack_b = ft_set_index(*stack_b);
	}
}
