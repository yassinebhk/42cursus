/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:45:21 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 14:35:02 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

typedef enum e_builtins
{
	e_echo,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit
}					t_builtins;

typedef struct s_env
{
	char			*key;
	char			*var;
	struct s_env	*next;
}					t_env;

/***************************************
				list utils
***************************************/

/**
 * @brief Initializates the list of environment variables in a t_env struct
 * @param env The environment variables list
 * @returns The len list
 */
int					ft_lst_size(t_env *env);

/**
 * @brief Create a new node
 * @param key The key of the new node
 * @param arg The arg of the new node
 * @returns The new node
 */
t_env				*ft_new_node(char *key, char *arg);

/**
 * @brief Add a new node to the environment variables list
 * @param lst The environment variables list
 * @param new The new node
 * @returns The updated list
 */
void				ft_add_back(t_env **lst, t_env *new);

/**
 * @brief Gets the last node of the list
 * @param lst The environment variables list
 * @returns The last node
 */
t_env				*ft_last(t_env *lst);

/***************************************
					free
***************************************/

/**
 * @brief Free the str
 * @param str The string
 */
void				ft_free(char **str);

/**
 * @brief Free the params of the program
 * @param line The line
 * @param env The environment variables list
 * @param len The len list
 */
void				free_args(char *line, t_env *env, int len);

/***************************************
			environment variables
***************************************/

/**
 * @brief Initializates the list of environment variables in a t_env struct
 * @param environment The environment variables
 * @returns The list of environment variables
 */
t_env				*get_var(char **environment);

/**
 * @brief Calculates the lent of the environment list
 * @param environment The environment variables
 * @returns The len list
 */
int					len_env(char **environment);

/**
 * @brief Update the current and old dir
 * @param env The environment list
 * @returns The len list
 */
void				set_dirs(t_env **env, char *curr_dir, char *old_dir);

/***************************************
				builts
***************************************/

/**
 * @brief Find the built in and execute his routine
 * @param str The array of strings splited by spaces
 * @param num_words The number of words of str
 * @param env The len list of env
 * @returns The len list
 */
int					find_built(char **str, int num_words, t_env *env);

/**
 * @brief Execute the echo function
 * @param str The array of strings splited by spaces
 * @param pos The init pos in str
 * @param num_words The number of words of str
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int					echo(char **str, int pos, int num_words);

/**
 * @brief Execute the cd function
 * @param str The array of strings splited by spaces
 * @param pos The init pos in str
 * @param num_words The number of words of str
 * @param env The len list of env
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int					cd(char **str, int pos, int num_words, t_env *env);
