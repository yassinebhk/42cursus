/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:51:49 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/13 13:27:55 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints an error message for each parsing error
 * @param argc The number of arguments passed to the program when it
 * is executed, including the name of the program itself as the
 *  first argument
 * @param argv The content of each argument
 */
static void	print_parsing_error(int flag, int argc);

/**
 * @brief Checks if in the string there are only numbers
 * @param str The string
 * @returns 1 if the condition its true, otherwise 0
 */
static int	is_digit(char *str);

/**
 * @brief Checks if each argument has one and only one integer number
 * @param argc The number of arguments passed to the program when it
 * is executed, including the name of the program itself as the
 *  first argument
 * @param argv The content of each argument
 * @returns 1 if the condition its true, otherwise 0
 */
static int	valid_format(int argc, char **argv);

static void	print_parsing_error(int flag, int argc)
{
	if (flag == 1)
		printf("\n🚩 -> The number of arguments (%d) is not enough (%d).\n\n",
			argc, 5);
	else if (flag == 2)
		printf("\n🚩\
			-> The number of arguments (%d) exceeds the maximum (%d).\n\n",
			argc, 6);
	else if (flag == 3)
		printf("\n🏁 -> Argument %d contains no numerical characters.\n\n",
			argc);
	else if (flag == 4)
		printf("\n🏁 -> Argument %d exceeds INT_MAX.\n\n", argc);
}

static int	is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

static int	valid_format(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_digit(argv[i]))
		{
			print_parsing_error(3, i);
			return (0);
		}
		if (ft_atoi(argv[i]) > INT_MAX)
		{
			print_parsing_error(4, i);
			return (0);
		}
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			print_parsing_error(1, argc);
		else
			print_parsing_error(2, argc);
		return (0);
	}
	else if (!valid_format(argc, argv))
		return (0);
	return (1);
}
