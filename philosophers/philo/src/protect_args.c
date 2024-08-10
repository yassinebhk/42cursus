/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:21:04 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/09 21:57:06 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_meals_count (t_philo philo)
{
	long meals_count;
	
	if (pthread_mutex_lock(&philo.philo_mutex))
	{
		printf("\n❌ meals count mutex lock failed.\n\n");
		return (-1);
	}
	meals_count = philo.meals_count;
	if (pthread_mutex_unlock(&philo.philo_mutex))
	{
		printf("\n❌ meals count mutex unlock failed.\n\n");
		return (-1);
	}
	return (meals_count);
}

long	get_last_meal (t_philo philo)
{
	long last_meal;
	
	if (pthread_mutex_lock(&philo.philo_mutex))
	{
		printf("\n❌ last meal mutex lock failed.\n\n");
		return (-1);
	}
	last_meal = philo.last_meal;
	if (pthread_mutex_unlock(&philo.philo_mutex))
	{
		printf("\n❌ last meal  mutex unlock failed.\n\n");
		return (-1);
	}
	return (last_meal);
}

long	set_dead (t_table *table, int dead, int pos)
{
	printf("%ld %d has died\n", get_time_in_ms() - table->start_sim,
		table->philosopher[pos].id);
	if (pthread_mutex_lock(&table->dead_mutex) != 0)
	{
		printf("\n❌ last meal mutex lock failed.\n\n");
		return (-1);
	}	
	table->dead = dead;
	if (pthread_mutex_unlock(&table->dead_mutex) != 0)
	{
		printf("\n❌ last meal  mutex unlock failed.\n\n");
		return (-1);
	}
}
