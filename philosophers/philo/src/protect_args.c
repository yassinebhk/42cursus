/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:21:04 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/11 16:46:03 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_meals_count(t_philo philo)
{
	long	meals_count;

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
	if (meals_count == 0)
		return (-2);
	return (meals_count);
}

long	get_last_meal(t_philo philo)
{
	long	last_meal;

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

long	set_dead(t_table *table, int dead, int pos)
{
	if (!set_print(get_time_in_ms() - table->start_sim,
			table->philosopher[pos].id, "has died", table))
		return (0);
	if (pthread_mutex_lock(&table->dead_mutex) != 0)
	{
		printf("\n❌ last meal mutex lock failed.\n\n");
		return (0);
	}
	table->end_sim = dead;
	if (pthread_mutex_unlock(&table->dead_mutex) != 0)
	{
		printf("\n❌ last meal  mutex unlock failed.\n\n");
		return (0);
	}
	return (1);
}

int	get_end_sim(t_philo philo)
{
	int	end;

	if (pthread_mutex_lock(&philo.table->dead_mutex))
	{
		printf("\n❌ end sim mutex lock failed.\n\n");
		return (-1);
	}
	end = philo.table->end_sim;
	if (pthread_mutex_unlock(&philo.table->dead_mutex))
	{
		printf("\n❌ end sim mutex unlock failed.\n\n");
		return (-1);
	}
	return (end);
}

int	set_print(long time, int id, char *s, t_table *table)
{
	if (pthread_mutex_lock(&table->print_mutex) != 0)
	{
		printf("\n❌ print mutex lock failed.\n\n");
		clean(table);
		return (0);
	}
	if (!strcmp(s, "is thinking"))
		printf("\033[34;1m%ld %d %s\n", time, id, s);
	else if (!strcmp(s, "is sleeping"))
		printf("\033[0;90m%ld %d %s\n", time, id, s);
	else if (!strcmp(s, "is eating"))
		printf("\033[32;1m%ld %d %s\n", time, id, s);
	else if (!strcmp(s, "has died"))
		printf("\033[31;1m%ld %d %s\n", time, id, s);
	else
		printf("\033[37;1m%ld %d %s\n", time, id, s);

	if (pthread_mutex_unlock(&table->print_mutex) != 0)
	{
		printf("\n❌ print mutex unlock failed.\n\n");
		clean(table);
		return (0);
	}
	return (1);
}


int	print(char *s, t_table *table)
{
	if (pthread_mutex_lock(&table->print_mutex) != 0)
	{
		printf("\n❌ print mutex lock failed.\n\n");
		clean(table);
		return (0);
	}
	printf("%s", s);
	if (pthread_mutex_unlock(&table->print_mutex) != 0)
	{
		printf("\n❌ print mutex unlock failed.\n\n");
		clean(table);
		return (0);
	}
	return (1);
}

