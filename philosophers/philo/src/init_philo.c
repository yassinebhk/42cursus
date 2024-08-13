/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:44:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/13 13:49:26 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_thread_philo(t_philo *philo, t_table *table)
{
	int		pos;
	void	*func;

	pos = -1;
	func = philo_routine;
	while (++pos < table->n_philo)
	{
		if (table->n_philo == 1)
			func = one_philo_routine;
		if (pthread_create(&philo[pos].thread_id, NULL, func,
				(void *)&philo[pos]))
		{
			print("\n❌ pthread_create failed.\n\n", table);
			clean(table);
			return (0);
		}
	}
	return (1);
}

int	thread_join_philo(t_table *table)
{
	int	pos;

	pos = -1;
	while (++pos < table->n_philo)
	{
		if (pthread_join(table->philosopher[pos].thread_id, NULL))
		{
			print("\n❌ pthread_join failed.\n\n", table);
			clean(table);
			return (0);
		}
	}
	return (1);
}

static int	init_args(t_philo *philo, t_table *table, int pos)
{
	philo->id = pos + 1;
	philo->meals_count = 0;
	philo->last_meal = 0;
	philo->table = table;
	philo->left_fork = &table->forks[pos];
	philo->right_fork = &table->forks[(pos + 1) % table->n_philo];
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &table->forks[pos];
		philo->left_fork = &table->forks[(pos + 1) % table->n_philo];
	}
	if (pthread_mutex_init(&philo->philo_mutex, NULL))
	{
		print("\n❌ philo mutex init failed.\n\n", table);
		clean(table);
		return (0);
	}
	return (1);
}

void	print_philo(t_philo *philo)
{
	int	pos;

	pos = -1;
	while (++pos < philo->table->n_philo)
	{
		printf("Philo: %d %ld %d\n", philo[pos].id, philo[pos].last_meal,
			philo[pos].meals_count);
	}
}

int	init_philo(t_philo *philo, t_table *table)
{
	int	pos;

	pos = -1;
	philo = (t_philo *)malloc((table->n_philo) * sizeof(t_philo));
	if (!philo)
	{
		print("\n❌ Malloc failed.\n\n", table);
		return (0);
	}
	while (++pos < table->n_philo)
	{
		if (!init_args(&philo[pos], table, pos))
			return (0);
	}
	table->philosopher = philo;
	return (1);
}
