/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 23:50:15 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/13 14:07:50 by ybouhaik         ###   ########.fr       */
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

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	long				last_meal;
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
	int					end_sim;
	long				start_sim;
	t_philo				*philosopher;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		print_mutex;
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
 * @brief Free the table and the philosophers and destroy the mutexs
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
int						init_dinner(t_table *table);
/***************************************
				PROTECTION
***************************************/

/**
 * @brief Gets the last meal of the philosopher
 * @param philo The philosopher
 * @returns The last meal
 */
long					get_last_meal(t_philo philo);

/**
 * @brief Gets the meals_count of the philosopher
 * @param philo The philosopher
 * @returns The meals_count
 */
long					get_meals_count(t_philo philo);

/**
 * @brief Sets the dead flag of the table
 * @param table The table
 * @param dead The dead status
 * @param pos The philosopher position
 * @returns 1 if there is no problem, otherwise 1
 */
long					set_dead(t_table *table, int dead, int pos);

/**
 * @brief Gets the end sim flag of the philosopher
 * @param philo The philosopher
 * @returns 1 if there is no problem, otherwise 1
 */
int						get_end_sim(t_philo philo);

/**
 * @brief Prints the status message of each philospher 
 * @param time The current time
 * @param id The philosopher id
 * @param s The message status
 * @param table The table
 * @returns 1 if there is no problem, otherwise 1
 */
int						set_print(long time, int id, char *s, t_table *table);

/**
 * @brief Prints a message safely 
 * @param s The message
 * @param table The table
 * @returns 1 if there is no problem, otherwise 1
 */
int						print(char *s, t_table *table);

/***************************************
					PHILO
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

/***************************************
					MONITORR
***************************************/

/**
 * @brief Sets the routine of the monitor
 * @param arg The monitor
 * @returns NULL
 */
void					*monitor_routine(void *arg);

/**
 * @brief Creates the monitor's pthread
 * @param arg The table
 * @returns 1 if there is no problem, otherwise 1
 */
int						init_monitor(t_table *table);

#endif
