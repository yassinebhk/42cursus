/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:10:01 by maxgarci          #+#    #+#             */
/*   Updated: 2024/08/21 23:01:49 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *command, int errno)
{
	if (errno == 12)
		ft_putstr_fd(" allocation failed, no memory available: ", 2);
	if (errno == 120)
		ft_putstr_fd(" bad assignment: ", 2);
	if (errno == 127)
		ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(command, 2);
	ft_putchar_fd('\n', 2);
}
