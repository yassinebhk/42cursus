/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:40:01 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/13 14:10:16 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_dinner(t_table *table)
{
	table->start_sim = get_time_in_ms();
	if (!init_thread_philo(table->philosopher, table))
		return (0);
	if (!init_monitor(table))
		return (0);
	if (!thread_join_philo(table))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;

	philo = NULL;
	if (!check_args(argc, argv))
		return (1);
	if (!init_table(&table, argc, argv))
		return (1);
	if ((table).n_philo == 0)
		return (free(table.forks), 1);
	if (!init_philo(philo, &table))
		return (1);
	if (!init_dinner(&table))
		return (1);
	clean(&table);
	return (0);
}
