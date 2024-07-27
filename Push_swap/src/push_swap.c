/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:44:02 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 23:12:50 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_close_ordered(int *str, t_node **stack_a)
{
	free(str);
	free(*stack_a);
	exit(0);
}

int	ft_is_ordered(int *list, int length)
{
	int	i;

	i = -1;
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
	if (ft_len_list(stack_a) > 1)
		ft_algorithm(&stack_a, &stack_b);
	ft_free_all(stack_a, stack_b, list);
	return (0);
}
