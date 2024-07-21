/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:31:49 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/20 19:49:39 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	*ft_fill_list(int *list, char **split, int *pos)
{
	long	num;
	int		i;
	int		error;

	i = -1;
	error = 0;
	while (split[++i])
	{
		num = ft_atoi_mod(split[i], &error);
		if (error == 0 || num > INT_MAX || num < INT_MIN
			|| !(ft_strchr_mod(list, *pos, (int)num) - 1))
			ft_exit_str_and_mtx(list, split, i);
		list[*pos] = num;
		(*pos)++;
		free(split[i]);
	}
	return (list);
}

void ft_repeated_numbers(int *list, int length)
{
	int i;
	int j;
	
	i = -1;
	while (++i < length)
	{
		j = i + 1;
		while (j < length)
		{
			if (list[i] == list[j])
				ft_exit();
			j++;
		}
	}
}

static int	*ft_get_args(int argc, char **argv, int length)
{
	char	**split;
	int		*list;
	int		tam;
	int		pos;

	pos = 0;
	tam = argc;
	list = (int *)malloc(length * sizeof(int));
	if (!list)
		ft_exit();
	while (--argc > 0)
	{
		split = ft_split(argv[tam - argc], ' ');
		if (!split)
			ft_exit_str(list);
		list = ft_fill_list(list, split, &pos);
		free(split);
	}
	ft_repeated_numbers(list, length);
	return (list);
}

static int	ft_get_length(int argc, char **argv)
{
	char	**split;
	int		i;
	int		tam;
	int		length;

	tam = argc;
	length = 0;
	while (--argc > 0)
	{
		i = -1;
		if (!ft_is_integer(argv[tam - argc]))
			ft_exit();
		split = ft_split(argv[tam - argc], ' ');
		if (!split)
			exit(1);
		while (split[++i])
		{
			length++;
			free(split[i]);
		}
		free(split);
	}
	return (length);
}

int	*ft_check_args(int argc, char **argv, int *length)
{
	int	*list;

	if (argc == 2 && ft_strlen(argv[1]) == 0)
		ft_exit();
	*length = ft_get_length(argc, argv);
	list = ft_get_args(argc, argv, *length);
	return (list);
}
