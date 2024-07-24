/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:16:42 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/24 19:51:19 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_close_ordered(int *str, t_node **stack_a)
{
	free(str);
	free(*stack_a);
	exit(1);
}

int ft_is_ordered(int *list, int length)
{
	int i = -1;

	while (++i < length - 1)
	{
		if (list[i] > list[i + 1])
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		length;
	int		*list;
	t_node	*stack_a;
	t_node	*stack_b;

	if (argc < 2)
		exit(1);
	else if (argc == 2 && ft_strlen(argv[1]) == 0)
		ft_exit();
	ft_init_stacks(&stack_a, &stack_b);
	list = ft_check_args(argc, argv, &length);
	if (!ft_is_ordered(list, length))
		ft_close_ordered(list, &stack_a);
	ft_fill_stack_a(&stack_a, list, length);
	ft_set_pos_and_inex(&stack_a, &stack_b);
	
	// int	i = -1;
	// length = ft_len_list(stack_a);
	// //ft_printf("\n|--------  stack_a ---------|\n\n");
	// while (++i < length)
	// {
	// 	//ft_printf("stack_a | puntero %p | pos: %d | stack_a value: %d | index: %d | cost: %d\n", stack_a, stack_a->pos, stack_a->value, stack_a->index, stack_a->cost); 
	// 	ft_printf("%d ", stack_a->value);
	// 	stack_a = stack_a->next;
	// }
	//ft_printf("\n|--------------------------|\n\n");

	if (ft_len_list(stack_a) > 1)
		ft_algorithm(&stack_a, &stack_b);

		
	/**********************************************
		*                                             *
		*                                             *
		*                  PRUEBAS                    *
		*                                             *
		*                                             *
		* *********************************************/

	// int i = -1;
	// length = ft_len_list(stack_a);
	// ft_printf("\n|--------  stack_a ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("stack_a | puntero %p | pos: %d | stack_a value: %d | index: %d | cost: %d\n", stack_a, stack_a->pos, stack_a->value, stack_a->index, stack_a->cost); 
	// 	stack_a = stack_a->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	// i = -1;
	// length = ft_len_list(stack_b);
	// ft_printf("\n|-------- stack_b ---------|\n\n");
	// while (++i < length)
	// {
	// 	ft_printf("stack_b | puntero %p | pos: %d | stack_b value: %d | index: %d | cost: %d\n",
	// 		stack_b, stack_b->pos, stack_b->value, stack_b->index, stack_b->cost);
	// 	stack_b = stack_b->next;
	// }
	// ft_printf("\n|--------------------------|\n\n");
	/***********************************************************/


	// int	i = -1;
	// length = ft_len_list(stack_a);
	// //ft_printf("\n|--------  stack_a ---------|\n\n");
	// ft_printf("\n");
	// while (++i < length)
	// {
	// 	//ft_printf("stack_a | puntero %p | pos: %d | stack_a value: %d | index: %d | cost: %d\n", stack_a, stack_a->pos, stack_a->value, stack_a->index, stack_a->cost); 
	// 	ft_printf("%d ", stack_a->value);
	// 	stack_a = stack_a->next;
	// }
	// ft_printf("\n");
	ft_free_all(stack_a, stack_b, list);
	return (0);
}
