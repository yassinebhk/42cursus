/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:20:49 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/13 12:54:07 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meals_completed(t_table *table)
{
	int pos;

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
		//printf("hola");
	}
	return (NULL);
}

int	init_monitor(t_table *table)
{
	pthread_t	monitor;

	if (table->n_philo > 1 && pthread_create(&monitor, NULL, monitor_routine,
			table))
	{
		print("\n❌ monitor thread creation failed.\n\n", table); // proteger
		clean(table);
		return (0);
	}
	if (table->n_philo > 1 && pthread_join(monitor, NULL))
	{
		print("\n❌ monitor thread join failed.\n\n", table); // proteger
		clean(table);
		return (0);
	}
	return (1);
}

void	*one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!set_print(get_time_in_ms() - philo->table->start_sim, philo->id,
			"has taken a fork", philo->table))
		return (NULL);
	ft_usleep(philo->table->time_die); // proteger
	if (!set_print(get_time_in_ms() - philo->table->start_sim, philo->id,
			"has died", philo->table))
		return (NULL);
	pthread_mutex_destroy(&philo->table->dead_mutex);
	pthread_mutex_destroy(&philo->philo_mutex);
	pthread_mutex_destroy(philo->left_fork);
	pthread_mutex_destroy(philo->right_fork);
	return (NULL);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->meals_count == philo->table->n_times_eat
		|| philo->table->end_sim == 1 || !set_print(get_time_in_ms()
			- philo->table->start_sim, philo->id, "has taken a fork",
			philo->table))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	if (philo->table->end_sim == 1 || !set_print(get_time_in_ms()
			- philo->table->start_sim, philo->id, "has taken a fork",
			philo->table))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	philo->meals_count++;
	philo->last_meal = get_time_in_ms();
	if (philo->table->end_sim == 1 || !set_print(get_time_in_ms()
			- philo->table->start_sim, philo->id, "is eating", philo->table))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	ft_usleep(philo->table->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (get_end_sim(*philo) != 1)
	{
		if (get_end_sim(*philo) == 1 || !eat(philo))
		{
			if (get_end_sim(*philo) != 1
				&& philo->meals_count != philo->table->n_times_eat)
				set_dead(philo->table, 1, philo->id - 1);
			return (NULL);
		}
		if (philo->meals_count == philo->table->n_times_eat || get_end_sim(*philo) == 1 || !set_print(get_time_in_ms()
				- philo->table->start_sim, philo->id, "is sleeping",
				philo->table))
			return (NULL);
		ft_usleep(philo->table->time_sleep);
		if (philo->meals_count == philo->table->n_times_eat || get_end_sim(*philo) == 1 || !set_print(get_time_in_ms()
				- philo->table->start_sim, philo->id, "is thinking",
				philo->table))
			return (NULL);
	}
	return (NULL);
}

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