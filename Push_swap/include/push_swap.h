/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:16:35 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/27 12:16:37 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

/**********************************************
*                                             * 
*                                             * 
*                  CONSTANTS                  * 
*                                             * 
*                                             * 
* *********************************************/

# ifndef INT_MAX 
# define INT_MAX 2147483647 
# endif
# ifndef INT_MIN 
# define INT_MIN -2147483648
# endif

/**********************************************
*                                             * 
*                                             * 
*                   STRUCTS                   * 
*                                             * 
*                                             * 
* *********************************************/



/**********************************************
*                                             * 
*                                             * 
*                  FUNCTIONS                  * 
*                                             * 
*                                             * 
* *********************************************/

/**
 * @brief Functions to check that args given as parameter are integer numbers
 * @param argc Number of arguments
 * @param argv The arguments given
 * @returns Terminate the program by printing "Error\n"
*/
void    ft_check_args(int argc, char **argv);
/**
 * @brief End the program
 * @returns Terminate the program by printing "Error\n"
*/
void ft_exit();
/**
 * @brief Converts the string into a long number
 * @param str The string to convert
 * @param error The pointer to the flag to check errors
 * @returns The converted integer
 */
long	ft_atoi_mod(const char *nptr, int *error);
/**
 * @brief End the program after free the memory allocated in the string 
 * @param str The string
 * @returns Terminate the program by printing "Error\n"
*/
void ft_exit_str(int *str);
/**
 * @brief End the program after free the memory allocated in the matrix 
 * @param mitx The matrix
 * @returns Terminate the program by printing "Error\n"
*/
void ft_exit_mtx(char **mtx);
/**
 * @brief End the program after free the memory allocated in the string and in the matrix (starting
 * in the position pos)
 * @param str The string
 * @param mtx The matrix
 * @param pos The position in the matrix
 * @returns Terminate the program by printing "Error\n"
*/
void ft_exit_str_and_mtx(int *str, char **mtx, int pos);
/**
 * @brief Locates the first occurrence of c in the string pointed to by s
		`\0', the functions locate the terminating `\0'
 * @param s The string to look into
 * @param pos The length of the string
 * @param c The integer fo look for
 * @returns 1 if it appears. Either 0
*/
int	ft_strchr_mod(int *s, int pos, int c);
/**
 * @brief Check if there is any number in a string
 * @param str The string to look into
 * @returns 1 if it appears. Either 0
*/
int ft_is_integer(char *str);


# endif