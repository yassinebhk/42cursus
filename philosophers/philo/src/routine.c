/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:20:49 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/09 22:00:30 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_routine(void *arg)
{
	int		pos;
	t_table	*table;

	table = (t_table *)arg;
	while (!table->end_sim)
	{
		pos = -1;
		while (++pos < table->n_philo)
		{
			if (get_meals_count(table->philosopher[pos]) == table->n_times_eat)
				return (NULL); 
			if (table->time_die < get_time_in_ms()
					- get_last_meal(table->philosopher[pos]) - table->start_sim)
			{
				set_dead(table, 0, pos);
				return (NULL);
			}
			ft_usleep(50);
		}
	}
}

int	init_monitor(t_table *table)
{
	pthread_t	monitor;

	if (table->n_philo > 1 && pthread_create(&monitor, NULL, monitor_routine, table))
	{
		printf("\n❌ monitor thread creation failed.\n\n"); //proteger
		clean(table);
		return (0);
	}
	if (table->n_philo > 1 && pthread_join(monitor, NULL))
	{
		printf("\n❌ monitor thread join failed.\n\n"); //proteger
		clean(table);
		return (0);
	}
	return (1);
}

void	*one_philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	printf("%ld %d has taken a fork\n", get_time_in_ms()
		- philo->table->start_sim, philo->id);
	ft_usleep(philo->table->time_die); //proteger
	printf("%ld %d has died\n", get_time_in_ms() - philo->table->start_sim,
		philo->id); //proteger
	pthread_mutex_destroy(&philo->table->dead_mutex);
	pthread_mutex_destroy(&philo[0].philo_mutex);
	pthread_mutex_destroy(philo->left_fork);
	pthread_mutex_destroy(philo->right_fork);
	return (NULL);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("%ld %d has taken a fork\n", get_time_in_ms()
		- philo->table->start_sim, philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%ld %d has taken a fork\n", get_time_in_ms()
		- philo->table->start_sim, philo->id);
	philo->meals_count++; //¿proteger?
	philo->last_meal = get_time_in_ms(); //proteger
	printf("%ld %d is eating\n", get_time_in_ms()
		- philo->table->start_sim, philo->id);
	ft_usleep(philo->table->time_eat); //proteger
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->table->n_philo % 2 == 0)
		ft_usleep(50);
	while(!philo->table->end_sim) //proteger 
	{
		eat(philo);
		printf("%ld %d is sleeping\n", get_time_in_ms()
		- philo->table->start_sim, philo->id); //proteger
		ft_usleep(philo->table->time_sleep); //proteger
		printf("%ld %d is thinking\n", get_time_in_ms()
		- philo->table->start_sim, philo->id); //proteger	
	}
	return (NULL);
}

int	init_dinner(t_table *table)
{
	if (!init_thread_philo(table->philosopher, table))
		return (0);
	if (!init_monitor(table))
		return (0);
	table->start_sim = get_time_in_ms();
	if (!thread_join_philo(table))
		return (0);
	
}