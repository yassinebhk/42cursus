/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:44:20 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/13 13:50:20 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_print(long time, int id, char *s, t_table *table)
{
	if (pthread_mutex_lock(&table->print_mutex) != 0)
	{
		printf("\n❌ print mutex lock failed.\n\n");
		clean(table);
		return (0);
	}
	if (!strcmp(s, "is thinking"))
		printf("\033[34;1m%ld %d %s\n", time, id, s);
	else if (!strcmp(s, "is sleeping"))
		printf("\033[0;90m%ld %d %s\n", time, id, s);
	else if (!strcmp(s, "is eating"))
		printf("\033[32;1m%ld %d %s\n", time, id, s);
	else if (!strcmp(s, "has died"))
		printf("\033[31;1m%ld %d %s\n", time, id, s);
	else
		printf("\033[37;1m%ld %d %s\n", time, id, s);
	if (pthread_mutex_unlock(&table->print_mutex) != 0)
	{
		printf("\n❌ print mutex unlock failed.\n\n");
		clean(table);
		return (0);
	}
	return (1);
}

int	print(char *s, t_table *table)
{
	if (pthread_mutex_lock(&table->print_mutex) != 0)
	{
		printf("\n❌ print mutex lock failed.\n\n");
		clean(table);
		return (0);
	}
	printf("%s", s);
	if (pthread_mutex_unlock(&table->print_mutex) != 0)
	{
		printf("\n❌ print mutex unlock failed.\n\n");
		clean(table);
		return (0);
	}
	return (1);
}
