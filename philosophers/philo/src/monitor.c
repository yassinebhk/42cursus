/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:29:26 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/13 13:50:48 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	meals_completed(t_table *table)
{
	int	pos;

	pos = -1;
	while (++pos < table->n_philo)
	{
		if (table->philosopher[pos].meals_count != table->n_times_eat)
			return (0);
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	int		pos;
	t_table	*table;

	table = (t_table *)arg;
	while (!get_end_sim(*table->philosopher))
	{
		pos = -1;
		while (++pos < table->n_philo)
		{
			if (get_meals_count(table->philosopher[pos]) == table->n_times_eat)
				;
			else if (table->time_die < get_time_in_ms()
				- get_last_meal(table->philosopher[pos]) - table->start_sim)
			{
				set_dead(table, 1, pos);
				break ;
			}
		}
		if (meals_completed(table))
			break ;
	}
	return (NULL);
}

int	init_monitor(t_table *table)
{
	pthread_t	monitor;

	if (table->n_philo > 1 && pthread_create(&monitor, NULL, monitor_routine,
			table))
	{
		print("\n❌ monitor thread creation failed.\n\n", table);
		clean(table);
		return (0);
	}
	if (table->n_philo > 1 && pthread_join(monitor, NULL))
	{
		print("\n❌ monitor thread join failed.\n\n", table);
		clean(table);
		return (0);
	}
	return (1);
}
