/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:16:42 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/27 12:16:44 by ybouhaik         ###   ########.fr       */
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

    int i = -1;
    while (++i < length)
    {
        ft_printf("%d\n", stack_a->value);
        stack_a = stack_a->next;
    }


    ft_free_all(stack_a, stack_b, list);
	atexit(leaks);
	return (0);
}
