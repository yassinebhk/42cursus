/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:20:49 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/13 14:08:12 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!set_print(get_time_in_ms() - philo->table->start_sim, philo->id,
			"has taken a fork", philo->table))
		return (NULL);
	ft_usleep(philo->table->time_die);
	if (!set_print(get_time_in_ms() - philo->table->start_sim, philo->id,
			"has died", philo->table))
		return (NULL);
	pthread_mutex_destroy(&philo->table->dead_mutex);
	pthread_mutex_destroy(&philo->philo_mutex);
	pthread_mutex_destroy(philo->left_fork);
	pthread_mutex_destroy(philo->right_fork);
	return (NULL);
}

static int	check_end(t_philo *philo, int flag)
{
	if ((philo->meals_count == philo->table->n_times_eat
			|| philo->table->end_sim == 1 || !set_print(get_time_in_ms()
				- philo->table->start_sim, philo->id, "has taken a fork",
				philo->table)) && flag == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	else if ((philo->meals_count == philo->table->n_times_eat
			|| philo->table->end_sim == 1 || !set_print(get_time_in_ms()
				- philo->table->start_sim, philo->id, "has taken a fork",
				philo->table)) && flag == 2)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (1);
}

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!check_end(philo, 1))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	if (!check_end(philo, 2))
		return (0);
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

static int	check_end2(t_philo *philo, char *s)
{
	if (philo->meals_count == philo->table->n_times_eat
		|| get_end_sim(*philo) == 1 || !set_print(get_time_in_ms()
			- philo->table->start_sim, philo->id, s, philo->table))
		return (0);
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
		if (!check_end2(philo, "is sleeping"))
			return (NULL);
		ft_usleep(philo->table->time_sleep);
		if (!check_end2(philo, "is thinking"))
			return (NULL);
	}
	return (NULL);
}
