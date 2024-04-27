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
 * @param flag The flag that indicates if there is memory allocated
 * @returns Terminate the program by printing "Error\n"
*/
void ft_exit_str(char *str, int flag);
/**
 * @brief End the program after free the memory allocated in the matrix 
 * @param mitx The matrix
 * @returns Terminate the program by printing "Error\n"
*/
void ft_exit_mtx(char **mtx);
/**
 * @brief Using malloc, creates an array of strings made up by separating
		the string s in subtrings using the character 'c' as delimiter. It also
        free the memory of the string s1 if it's allocated
		The array has to finish with a NULL pointer
 * @param s The string to separe
 * @param c The character using as dellimiter
 * @returns The array of strings resulting from the separation. Other
		-wise, returns NULL if malloc fails
*/
char	*ft_strjoin_mod(char const *s1, char const *s2, int mlc);


# endif