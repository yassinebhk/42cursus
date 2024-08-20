/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command_not_found.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:10:01 by maxgarci          #+#    #+#             */
/*   Updated: 2024/08/20 13:20:17 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_not_found(char *command)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(command, 2);
	ft_putchar_fd('\n', 2);
}
