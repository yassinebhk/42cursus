/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:16:42 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/30 11:56:11 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	leaks(void)
{
	system("leaks push_swap");
}

int	main(int argc, char **argv)
{
	int		length;
	int		*list;
	t_node	*stack_a;
	t_node	*stack_b;

	ft_init_stacks(&stack_a, &stack_b);
	if (argc < 2)
		exit(1);
	list = ft_check_args(argc, argv, &length);
	ft_fill_stack_a(&stack_a, list, length);
	ft_set_pos_and_inex(&stack_a, &stack_b);
	if (ft_len_list(stack_a) > 1)
		ft_algorithm(&stack_a, &stack_b);
	/**********************************************
		*                                             *
		*                                             *
		*                  PRUEBAS                    *
		*                                             *
		*                                             *
		* *********************************************/
	// pb(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// rb(&stack_b);
	// pa(&stack_a, &stack_b);
	// pa(&stack_a, &stack_b);
	// sa(&stack_a);
	// pb(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// rrr(&stack_a, &stack_b);
	// ft_set_pos_and_inex(&stack_a, &stack_b);
	int	i = -1;
	length = ft_len_list(stack_a);
	ft_printf("\n|--------  stack_a ---------|\n\n");
	while (++i < length)
	{
		ft_printf("stack_a | pos: %d | stack_a value: %d | index: %d | cost: %d\n", stack_a->pos, stack_a->value, stack_a->index, stack_a->cost); 
		stack_a = stack_a->next;
	}
	ft_printf("\n|------------------------|\n\n");
	i = -1;
	length = ft_len_list(stack_b);
	ft_printf("\n|------- stack_b --------|\n\n");
	while (++i < length)
	{
		ft_printf("stack_b | pos: %d | stack_b value: %d | index: %d | cost: %d\n",
			stack_b->pos, stack_b->value, stack_b->index, stack_b->cost);
		stack_b = stack_b->next;
	}
	ft_printf("\n|------------------------|\n\n");
	// int i = -1;
	// sa(&stack_a);
	// pb(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// pa(&stack_a, &stack_b);
	// sb(&stack_b);
	// pa(&stack_a, &stack_b);
	// pa(&stack_a, &stack_b);
	// ss(&stack_a, &stack_b);
	// ra(&stack_a);
	// rr(&stack_a, &stack_b);
	// rra(&stack_a);
	// rrr(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// ss(&stack_a, &stack_b);
	// rr(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// pb(&stack_a, &stack_b);
	// sa(&stack_a);
	// ra(&stack_a);
	// rra(&stack_a);
	// length = ft_len_list(stack_b);
	// ft_printf("\n|----------------------|\n\n");
	// while (++i < length)
	// {
	//     ft_printf("stack_b value: %d\n", stack_b->value);
	//     stack_b = stack_b->next;
	// }
	// i = -1;
	// length = ft_len_list(stack_a);
	// ft_printf("\n|----------------------|\n\n");
	// while (++i < length)
	// {
	//     ft_printf("stack_a value: %d\n", stack_a->value);
	//     stack_a = stack_a->next;
	// }
	// ft_printf("\n|----------------------|\n\n");
	/***********************************************************/
	ft_free_all(stack_a, stack_b, list);
	atexit(leaks);
	return (0);
}
