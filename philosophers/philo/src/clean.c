/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:20:13 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/13 13:51:20 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(table->philosopher[i].left_fork);
		pthread_mutex_destroy(table->philosopher[i].right_fork);
		pthread_mutex_destroy(&table->philosopher[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->monitor);
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philosopher);
}
