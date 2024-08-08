/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:20:49 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/08 14:24:28 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	if (philo->table->n_philo == 1)
	{
		printf("%ld %d has taken a fork\n", get_time_in_ms()
			- philo->table->start_sim, philo->id);
		ft_usleep(philo->table->time_die);
		printf("%ld %d has died\n", get_time_in_ms() - philo->table->start_sim,
			philo->id);
	}
	return (NULL);
}