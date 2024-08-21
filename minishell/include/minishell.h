/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:45:21 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/21 22:51:23 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

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

typedef struct {
	int		errno;
	char	*message;
} errorMessage;

enum e_errors
{
	ENO_MEM = 12,
	BAD_ASSIGNMENT = 120,
	COMMAND_NOT_FOUND = 127
};

# define NUM_ERRORS 2

typedef struct s_env
{
	char			*key;
	char			*var;
	struct s_env	*next;
}					t_env;

# define	EXPORT_FLAG	1
# define	ENV_FLAG 0

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
* @param flag if flag is 0 return (the environment variables node); otherwise,
		the export node
 * @returns The new node
 */
t_env				*ft_new_node(char *key, char *arg, int flag);

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
 * @param exp The export variables list
 * @param len The len list
 */
void				free_args(t_env *env, t_env *exp);

/***************************************
			environment variables
***************************************/

/**
 * @brief Initializates the list of environment variables in a t_env struct
 * @param environment The environment variables
 * @param flag if flag is 0 return (the environment variables list); otherwise,
	the export list
 * @returns The list of environment variables
 */
t_env				*get_var(char **environment, int flag);

/**
 * @brief Gets the arg of the environment variable key
 * @param env The environment variables list
 * @param key The environment varaible key
 * @returns The argument
 */
char				*get_env(t_env *env, char *key);

/**
 * @brief Gets the arg of the environment variable key
 * @param exp The export variables list
 * @param key The environment varaible key
 * @returns The argument
 */
char				*get_exp(t_env *exp, char *key);

/**
 * @brief Calculates the length of the environment list
 * @param environment The environment variables
 * @returns The len list
 */
int					len_env(char **environment);

/**
 * @brief CHeck if exists the node with the key variable
 * @param key The key variable
 * @returns 1 if exists. Otherwise, 0.
 */
int					find_node(t_env *env, char *key);

/**
 * @brief Calculates the number of "=" in the str
 * @param str The string
 * @returns The numer of character after the "=", included himself
 */
int					find_eq(char *str);

/**
 * @brief Update the current and old dir of both lists
 * @param env The env list
 * @param exp The export list
 * @param curr_dir The current dir
 * @param old_dir The old dir
 * @returns The len list
 */
void				update(t_env *env, t_env *exp, char *old_dir,
						char *new_dir);

/**
 * @brief Gets the parent of the current directory
 * @param dir The current directory
 * @returns The path
 */
char				*get_parent(char *dir);

/**
 * @brief Prints the export list
 * @param exp The export list
 */
void				print_export_list(t_env *exp);

/**
 * @brief Deletes the '=' character of the string
 * @param str The string
 * @returns The modified string
 */
char				*rm_eq(char *str);

/**
 * @brief Checks if exist the str variable
 * @param str The string
 * @param env The len list of env
 * @param exp The export variables list
 * @returns 0
 */
int					exist_var(char *str, t_env *env, t_env *exp);

/***************************************
				builts
***************************************/

/**
 * @brief Find the built in and execute his routine
 * @param str The array of strings splited by spaces
 * @param num_words The number of words of str
 * @param env The len list of env
 * @param exp The export variables list
 * @returns The len list
 */
int					find_built(char **str, int num_words, t_env *env,
						t_env *exp);

/**
 * @brief Execute the echo command
 * @param str The array of strings splited by spaces
 * @param pos The init pos in str
 * @param num_words The number of words of str
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int					echo(char **str, int pos, int num_words);

/**
 * @brief Execute the cd command
 * @param str The array of strings splited by spaces
 * @param num_words The number of words of str
 * @param env The len list of env
 * @param exp The export variables list
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int					cd(char **str, int num_words, t_env *env, t_env *exp);

/**
 * @brief Execute the pwd command
 * @param str The array of strings splited by spaces
 * @param env The len list of env
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int					pwd(t_env *env);

/**
 * @brief Execute the export command
 * @param str The array of strings splited by spaces
 * @param num_words The number of words of str
 * @param env The len list of env
 * @param exp The export variables list
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int					export(char **str, int num_words, t_env *env, t_env *exp);

/**
 * @brief Execute the unset command
 * @param str The array of strings splited by spaces
 * @param num_words The number of words of str
 * @param env The len list of env
 * @param exp The export variables list
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int					unset(char **str, int num_words, t_env *env, t_env *exp);

/**
 * @brief Execute the unset command
 * @param str The array of strings splited by spaces
 * @param env The len list of env
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int					ft_env(t_env *env);

/**
 * @brief Execute the unset exit
 * @returns 42
 */
int					ft_exit(void);

/***************************************
		print_command_not_found
***************************************/

/**
 * @brief Print error caused by command not found
 */

void				print_error(char *command, int errno);

#endif
