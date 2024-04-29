/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:16:42 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/29 22:08:23 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	leaks(void)
{
	system("leaks push_swap");
}

int	main(int argc, char **argv)
{   
    t_node  *stack_a;
    t_node  *stack_b;
    int     *list;
    int     length;

    ft_init_stacks(&stack_a, &stack_b);
	if (argc < 2)
		exit(1);
	list = ft_check_args(argc, argv, &length);
    ft_fill_stack_a(&stack_a, list, length);
    
    /**********************************************************/
    
    
    int i = -1;
    sa(&stack_a);
    pb(&stack_a, &stack_b);
    pb(&stack_a, &stack_b);
    pb(&stack_a, &stack_b);
    pb(&stack_a, &stack_b);
    pa(&stack_a, &stack_b);
    sb(&stack_b);
    pa(&stack_a, &stack_b);
    length = ft_len_list(stack_b);
    while (++i < length)
    {
        ft_printf("stack_b value: %d\n", stack_b->value);
        stack_b = stack_b->next;
    }

    i = -1;
    length = ft_len_list(stack_a);
    while (++i < length)
    {
        ft_printf("stack_a value: %d\n", stack_a->value);
        stack_a = stack_a->next;
    }

    
    /***********************************************************/

    ft_free_all(stack_a, stack_b, list);
	atexit(leaks);
	return (0);
}
