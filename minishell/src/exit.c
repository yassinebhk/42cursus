/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/09 16:11:28 by ybouhaik		  #+#	#+#			 */
/*   Updated: 2025/03/22 14:47:05 by maxgarci         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

static int	isnum(char *str)
{
	if (!str || str == (void *) 0)
		return (-1);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

static int	ft_mtxlen(char **str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

int	ft_exit(char **str, t_env **env, t_env **exp, t_node **head)
{
	int	exit_status;

	exit_status = (*head)->last_status;
	if (ft_mtxlen(str) == 2)
	{
		if (!isnum(str[1]))
		{
			printf("%s%s%s", "exit: ", str[1], " numeric argument required\n");
			free_lists(*env, *exp);
			free_list(*head);
			exit(2);
		}
		exit_status = ft_atoi(str[1]);
	}
	else if (ft_mtxlen(str) > 2)
		return (ft_putstr_fd(" too many arguments", 2), 1);
	printf("exit\n");
	free_list(*head);
	free_lists(*env, *exp);
	exit(exit_status);
}
