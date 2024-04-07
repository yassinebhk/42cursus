/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servidor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:20:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/08 00:02:21 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/servidor.h"

static void	leaks(void)
{
	system("leaks server");
}

static void	sig_usr(int signo)
{
	static int	cont_bits = 7;
	static int	number = 0;

	if (signo == SIGUSR1)
	{
		number += (1 << cont_bits);
		cont_bits--;
	}
	else
		cont_bits--;
	if (cont_bits == -1)
	{
		if (!ft_putchar_fd((char)number, 1))
			exit(1);
		if (number == 0)
		{
			write(1, "\n", 1);
			exit(0);
		}
		cont_bits = 7;
		number = 0;
	}
}

int	main(void)
{
	int	pid_child;

	write(1, "Mi pid es: ", 12);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\nEsperando mensaje...\n", 23);
	write(1, "--------------------------------\n", 34);
	signal(SIGUSR1, sig_usr);
	signal(SIGUSR2, sig_usr);
	while (1)
	{
		pause();
	}
	return (0);
}
	// atexit(leaks);
