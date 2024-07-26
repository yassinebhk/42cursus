/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:16:35 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/26 23:20:22 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
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
#  define INT_MAX 2147483647
# endif
# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif

/**********************************************
 *                                             *
 *                                             *
 *                   STRUCTS                   *
 *                                             *
 *                                             *
 * *********************************************/

/**
 * @brief Node struct
 * @param value The value of the node
 * @param cost The cost to reach the top of the list
 * @param pos The relative position of the node in the list
 * @param index Index that should take based on his value
 * @param next The next node
 * @param before The previous node
 */
typedef struct s_node
{
	int				value;
	int				cost;
	int				cost_change;
	int				pos;
	int				index;
	struct s_node	*next;
	struct s_node	*before;
}					t_node;

/**********************************************
 *                                             *
 *                                             *
 *                  PARSING                    *
 *                                             *
 *                                             *
 * *********************************************/

/**
 * @brief Functions to check that args given as parameter are integer numbers
 * @param argc Number of arguments
 * @param argv The arguments given
 * @param length The length of the string of integers
 * @returns The string of integer numbers given as parameter
 */
int					*ft_check_args(int argc, char **argv, int *length);
/**
 * @brief End the program and free the stack_a
 * @param The linked list A
 */
void				ft_exit_node(t_node **stack_a);
/**
 * @brief End the program
 */
void				ft_exit(void);
/**
 * @brief Converts the string into a long number
 * @param str The string to convert
 * @param error The pointer to the flag to check errors
 * @returns The converted integer
 */
long				ft_atoi_mod(const char *nptr, int *error);
/**
 * @brief End the program after free the memory allocated in the string
 * @param str The string
 */
void				ft_exit_str(int *str);
/**
 * @brief End the program after free the memory allocated in the matrix
 * @param mitx The matrix
 */
void				ft_exit_mtx(char **mtx);
/**

* @brief End the program after free the memory allocated in the string
		and in the matrix (starting in the position pos)
 * @param str The string
 * @param mtx The matrix
 * @param pos The position in the matrix
 */
void				ft_exit_str_and_mtx(int *str, char **mtx, int pos);
/**
 * @brief Locates the first occurrence of c in the string pointed to by s
		`\0', the functions locate the terminating `\0'
 * @param s The string to look into
 * @param pos The length of the string
 * @param c The integer fo look for
 * @returns 1 if it appears. Either 0
*/
int					ft_strchr_mod(int *s, int pos, int c);
/**
 * @brief Check if there is any number in a string
 * @param str The string to look into
 * @returns 1 if it appears. Either 0
 */
int					ft_is_integer(char *str);
/**
 * @brief Inizializate both stacks
 * @param stack_a Stack_a
 * @param stack_b Stack_b
 */

/**********************************************
 *                                             *
 *                                             *
 *                   STACKS                    *
 *                                             *
 *                                             *
 * *********************************************/

void				ft_init_stacks(t_node **stack_a, t_node **stack_b);
/**
 * @brief Free the node
 * @param stack The stack
 */
void				ft_free_stack(t_node *stack);
/**
 * @brief Free both nodes
 * @param stack_a Stack_a
 * @param stack_b Stack_b
 */
void				ft_free_all(t_node *stack_a, t_node *stack_b, int *list);
/**
 * @brief Inizializate a stack with a value
 * @param value The value
 * @returns The new node
 */
t_node				*ft_new_node(int value);
/**
 * @brief Gives the last node of the linked list
 * @param stack_a The head of the linked list
 * @returns The last node
 */
t_node				*ft_last_node(t_node *stack_a);
/**
 * @brief Fill the stack_a
 * @param stack_a Stack_a
 * @param list The list of integer numbers
 * @param length The length of the list
 */
void				ft_fill_stack_a(t_node **stack_a, int *list, int length);
/**
 * @brief Calculates the length of a linked list
 * @param stack The head of the linked list
 * @returns The length of the list
 */
int					ft_len_list(t_node *stack);
/**
 * @brief Removes the first element of the list
 * @param stack The head of the linked list
 * @returns The new list
 */
t_node				*ft_pop(t_node *stack);
/**
 * @brief Adds one node at the top of the linked list
 * @param stack The head of the linked list
 * @param new_node The new node
 * @returns The new list
 */
t_node				*ft_add_top(t_node *stack, t_node *new_node);

/**********************************************
 *                                             *
 *                                             *
 *                  MOVEMENTS                  *
 *                                             *
 *                                             *
 * *********************************************/

/**
 * @brief Exchange the first two positions of the stack_a
 * @param stack_a The linked list a
 */
void				sa(t_node **stack_a);
/**
 * @brief Exchange the first two positions of the stack_b
 * @param stack_b The linked list b
 */
void				sb(t_node **stack_b);
/**
 * @brief Exchanges the first two positions of both stacks
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				ss(t_node **stack_a, t_node **stack_b);
/**
 * @brief Carry out the action of swap
 * @param stack The linked list
 */
void				swap(t_node **stack);
/**
 * @brief Moves the first element of stack_b to stack_a
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				pa(t_node **stack_a, t_node **stack_b);
/**
 * @brief Moves the first element of stack_a to stack_b
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				pb(t_node **stack_a, t_node **stack_b);
/**
 * @brief Carriy out the action of push
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				push(t_node **stack_a, t_node **stack_b, char c);
/**
 * @brief Scroll up the elements of the stack_a
 * @param stack_a The linked list a
 */
void				ra(t_node **stack_a);
/**
 * @brief Scroll up the elements of the stack_b
 * @param stack_b The linked list b
 */
void				rb(t_node **stack_b);
/**
 * @brief Scroll up the elements of both stacks
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				rr(t_node **stack_a, t_node **stack_b);
/**
 * @brief Carry out the action of rotate
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				rotate(t_node **stack);
/**
 * @brief Scroll down the elements of the stack_a
 * @param stack_a The linked list a
 */
void				rra(t_node **stack_a);
/**
 * @brief Scroll down the elements of the stack_b
 * @param stack_b The linked list
 */
void				rrb(t_node **stack_b);
/**
 * @brief Scroll down the elements of both stacks
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				rrr(t_node **stack_a, t_node **stack_b);
/**
 * @brief Carry out the action of rotate reverse
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				rotate_reverse(t_node **stack);

/**********************************************
 *                                             *
 *                                             *
 *            Position and index               *
 *                                             *
 *                                             *
 * *********************************************/

/**
 * @brief Calculates the pos and index of both lists
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				ft_set_pos_and_inex(t_node **stack_a, t_node **stack_b);
/**
 * @brief Carry out the calculation of the positions
 * @param stack The head of the linked list
 * @returns The updated head of the list
 */
t_node				*ft_set_pos(t_node *stack);
/**
 * @brief Carry out the calculation of the indexs
 * @param stack The head of the linked list
 * @param new_node The new node
 * @returns The updated head of the list
 */
t_node				*ft_set_index(t_node *stack);

/**********************************************
 *                                             *
 *                                             *
 *                 Algorithm                   *
 *                                             *
 *                                             *
 * *********************************************/

/**
 * @brief Algorithm that sorts the list
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				ft_algorithm(t_node **stack_a, t_node **stack_b);
/**
 * @brief Algorithm that sorts two nodes
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 * @param flag If flag its 0, we sort the stack_a; otherwise, stack_b
 */
void				ft_two_nodes(t_node **stack_a, t_node **stack_b, int flag);
/**
 * @brief Algorithm that sorts three nodes
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				ft_three_nodes(t_node **stack, t_node **stack_aux);
/**
 * @brief Algorithm that sorts less than 6 nodes
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				ft_general(t_node **stack_a, t_node **stack_b);
/**

	* @brief Push to the stack_b the nodes 
	that have an index lower than half of the list
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				ft_check_low_index(t_node **stack, t_node **stack_b);
/**

	* @brief Calculates the costs to reach the top of 
	the list of each node of the linked list
 * @param stack The linked list
 */
void				ft_set_costs(t_node **stack);
/**
 * @brief Makes the mvts to sort the stack_b
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 * @param flag If flag its 0, we make rb mvts; otherwise, rrb mvts
 * @param best_index The best index to move
 */
void				ft_mvts_b(t_node **stack_a, t_node **stack_b, int flag,
						t_node *best_index);
/**
 * @brief Makes the mvts to sort the stack_a
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 * @param flag If flag its 0, we make ra mvts; otherwise, rra mvts
 * @param best_index The best index to move
 */
void				ft_mvts_a(t_node **stack_a, t_node **stack_b, int flag,
						t_node *best_index);
/**
 * @brief Calculates the cost change from one node to another
 * @param stack_aux The destination list
 * @param stack The source list
 * @return
 */
t_node				*ft_cost_change(t_node *stack_aux, t_node **stack);
/**
 * @brief Updates the parameters of the nodes
 * @param stack_a The linked list a
 * @param stack_b The linked list b
 */
void				ft_update_parameters(t_node **stack_a, t_node **stack_b);

#endif