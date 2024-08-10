/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 23:50:15 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/09 22:12:48 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

/***************************************
				STRUCTS
***************************************/

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_fork
{
	int					id;
	pthread_mutex_t		forks;

}						t_fork;

typedef struct s_philo
{
	int					id;
	int					last_meal;
	int					meals_count;
	pthread_t			thread_id;
	pthread_mutex_t		philo_mutex;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					n_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					n_times_eat;
	int					dead;
	int					end_sim;
	long				start_sim;
	t_philo				*philosopher;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		print;
	pthread_mutex_t		monitor;
}						t_table;

/***************************************
				UTILS
***************************************/

long					ft_atoi(char *str);
/**
 * @brief Gives the current time in ms
 * @returns The current time in ms
 */
long					get_time_in_ms(void);

/**
 * @brief Use the usleep function with exact time
 * @param time Time to sleep
 */
void					ft_usleep(int time);

/**
 * @brief Free the table and the philosophers
 * @param table The table
 */
void					clean(t_table *table);
/***************************************
				PARSING
***************************************/

/**
 * @brief Checks if the number of arguments are correct and if
 * the format of the arguments are valid
 * @param argc The number of arguments passed to the program when it
 * is executed, including the name of the program itself as the
 *  first argument
 * @param argv The content of each argument
 * @returns 1 if the condition its true, otherwise 0
 */
int						check_args(int argc, char **argv);

/***************************************
			INITIALIZATION
***************************************/

/**
 * @brief Initializates the table with the argumens passed to the program
 * @param table The table
 * @param argc The number of arguments passed to the program when it
 * is executed, including the name of the program itself as the
 *  first argument
 * @param argv The content of each argument
 * @returns 1 if there is no problem, otherwise 1
 */
int						init_table(t_table *table, int argc, char **argv);

/**
 * @brief Initializates each philosopher thread
 * @param philo The array of philosophers
 * @param table The table
 * @returns 1 if there is no problem, otherwise 1
 */
int						init_thread_philo(t_philo *philo, t_table *table);

/**
 * @brief Initializates each philosopher
 * @param philo The array of philosophers
 * @param table The table
 * @returns 1 if there is no problem, otherwise 1
 */
int						init_philo(t_philo *philo, t_table *table);

/**
 * @brief Joins each thread
 * @param table The table
 * @returns 1 if there is no problem, otherwise 1
 */
int						thread_join_philo(t_table *table);

/**
 * @brief Initializate the monitor
 * @param table The table
 * @returns 1 if there is no problem, otherwise 1
 */
int						init_monitor(t_table *table);

/**
 * @brief Initializate the dinner
 * @param table The table
 * @returns 1 if there is no problem, otherwise 1
 */
int	init_dinner(t_table *table);
/***************************************
				PROTECTION
***************************************/

long					get_last_meal(t_philo philo);
long					get_meals_count(t_philo philo);
long					set_dead(t_table *table, int dead, int pos);

/***************************************
				ROUTINE
***************************************/

/**
 * @brief Sets the routine of each philosopher
 * @param arg Each philosopher
 * @returns NULL
 */
void					*philo_routine(void *arg);

/**
 * @brief Sets the routine if there is only one philosopher
 * @param arg Each philosopher
 * @returns NULL
 */
void					*one_philo_routine(void *arg);

/**
 * @brief Sets the routine of the monitor
 * @param arg The monitor
 * @returns NULL
 */
void					*monitor_routine(void *arg);

#endif