/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_costs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:59:52 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/21 16:01:00 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int  ft_cost(t_node *head, t_node *act, int direcction)
{
    int cost;

    cost = 0;
    if (!direcction)
    {   
        while(act != head)
        {
            act = act->before;
            cost++;
        }
        return (cost);
    }
    else
    {
        while(act != head)
        {
            act = act->next;
            cost++;
        }
        return (cost);
    }
}

void	ft_set_costs(t_node **stack)
{
	t_node	*act;
	int		length;
	int		i;

	i = -1;
	act = *stack;
	length = ft_len_list(*stack);

	while (++i < length)
	{
	    //ft_printf(" length: %d pos: %d\n", length, act->pos);
		if (act->pos <= (int)(length / 2) + 1)
			act->cost = ft_cost(*stack, act, 0);
		else
			act->cost = ft_cost(*stack, act, 1);
		act = act->next;
	}
}
