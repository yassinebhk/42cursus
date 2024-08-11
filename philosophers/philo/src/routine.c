/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:20:49 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/11 16:36:54 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
				break ;
			if (table->time_die < get_time_in_ms()
				- get_last_meal(table->philosopher[pos]) - table->start_sim)
			{
				set_dead(table, 1, pos);
				break ;
			}
			ft_usleep(50);
		}
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
	if (philo->table->end_sim == 1 || !set_print(get_time_in_ms()
			- philo->table->start_sim, philo->id, "has taken a fork",
			philo->table))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	if (philo->table->end_sim == 1 || !set_print(get_time_in_ms()
			- philo->table->start_sim, philo->id, "has taken a fork",
			philo->table))
		return (0);
	philo->meals_count++;                //¿proteger?
	philo->last_meal = get_time_in_ms(); // proteger
	if (philo->table->end_sim == 1 || !set_print(get_time_in_ms()
			- philo->table->start_sim, philo->id, "is eating", philo->table))
		return (0);
	ft_usleep(philo->table->time_eat); // proteger
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
	while (get_end_sim(*philo) != 1) // proteger
	{
		if (get_end_sim(*philo) == 1 || !eat(philo))
		{
			if (get_end_sim(*philo) != 1)
				set_dead(philo->table, 1, philo->id - 1);
			return (NULL);
		}
		if (get_end_sim(*philo) == 1 || !set_print(get_time_in_ms()
				- philo->table->start_sim, philo->id, "is sleeping",
				philo->table))
			return (NULL);
		ft_usleep(philo->table->time_sleep);
		if (get_end_sim(*philo) == 1 || !set_print(get_time_in_ms()
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