/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 23:50:15 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/06 14:19:24 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

/***************************************
				UTILS
***************************************/

long		ft_atoi(char *str);

/***************************************
				PARSING
***************************************/

/**
 * @brief Checks if the number of arguments are correct and if
 * the format of the arguments are valid
 * @param argc The number of arguments passed to the program when it
 * is executed, including the name of the program itself as the
 *  first argument
 * @param argv The content of each argument
 * @returns 1 if the condition its true, otherwise 0
 */
int			check_args(int argc, char **argv);

#endif
