/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:40:01 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/08 14:28:26 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main (int argc, char **argv)
{
	t_table table;
	t_philo *philo;
	
	if (!check_args(argc, argv))
		return (1);
	if (!init_table(&table, argc, argv))
		return (1);
	if ((table).n_philo == 0)
		return (0);
	if (!init_philo(philo, &table))
		return (1);
	//free(philo);
	free(table.t_forks);
	return (0);
}
