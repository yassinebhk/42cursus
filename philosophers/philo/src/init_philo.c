/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:44:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/08 14:15:40 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_thread_philo(t_philo *philo, t_table *table)
{
	int	pos;

	pos = -1;
	while (++pos < table->n_philo)
	{
		if (pthread_create(&philo[pos].thread_id, NULL, &philo_routine,
				(void *)&philo[pos]))
		{
			printf("\n❌ pthread_create failed.\n\n");
			free(philo);
			return (0);
		}
		pthread_join(philo[pos].thread_id, NULL);
	}

	// while (++pos < table->n_philo)
	// {
	// 	philo = philo + pos;
	// 	if (pthread_create(&philo->thread_id, NULL, &philo_routine,
	// 			(void *)&philo))
	// 	{
	// 		printf("\n❌ pthread_create failed.\n\n");
	// 		free(philo);
	// 		return (0);
	// 	}
	// 	pthread_join(philo->thread_id, NULL);
	// }
	
	// while (++pos < table->n_philo)
	// {
	// 	printf("hola... %p\n", philo[pos].thread_id);
	// 	if(pthread_join(philo[pos].thread_id, NULL))
	// 	{
	// 		printf("hola..\n");
	// 		printf("\n❌ pthread_join failed.\n\n");
	// 		free(philo);
	// 		return (0);
	// 	}
	// }
	return (1);
}

int	init_philo(t_philo *philo, t_table *table)
{
	int	pos;

	pos = -1;
	philo = (t_philo *)malloc((table->n_philo) * sizeof(t_philo));
	if (!philo)
	{
		printf("\n❌ Malloc failed.\n\n");
		return (0);
	}
	while (++pos < table->n_philo)
	{
		philo[pos].id = pos + 1;
		philo[pos].times_eat = 0;
		philo[pos].died = 0;
		philo[pos].thinking = 0;
		philo[pos].eating = 0;
		philo[pos].table = table;
		philo->left_fork = &table->t_forks[pos].forks;
		philo->right_fork = &table->t_forks[(pos + 1) % table->n_philo].forks;
		if (philo->id % 2 == 0)
		{
			philo->right_fork = &table->t_forks[pos].forks;
			philo->left_fork = &table->t_forks[(pos + 1) % table->n_philo].forks;
		}
	}
	table->start_sim = get_time_in_ms();
	if (!init_thread_philo(philo, table))
		return (0);
	table->philosopher = philo;
	return (1);
}
