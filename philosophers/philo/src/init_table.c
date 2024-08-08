/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:32:29 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/08 14:08:39 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_table(t_table *table, int argc, char **argv)
{
	int pos;

	pos = -1;
	table->n_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	table->start_sim = 0;
	table->end_sim = 0;
	if (argc == 6)
		table->n_times_eat = ft_atoi(argv[5]);
	else
		table->n_times_eat = -1;
	table->t_forks = (t_fork *)malloc((table->n_philo)
			* sizeof(t_fork));
	if (!table->t_forks)
	{
		printf("\n❌ Malloc for forks failed.\n\n");
		return (0);
	}
	while(++pos < table->n_philo)
	{
		if (pthread_mutex_init(&table->t_forks[pos].forks, NULL) != 0)
		{
			printf("❌ Error: pthread_mutex_init failed\n\n");
			free(table->t_forks);
			return (1);
		}	
	}
	return (1);
}
