/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servidor_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:20:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/08 00:00:15 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/servidor.h"

static void	leaks(void)
{
	system("leaks server");
}

static void	sig_usr(int signo, siginfo_t *info, void *other)
{
	static int	cont_bits = 7;
	static int	number = 0;

	(void)other;
	if (signo == SIGUSR1)
		number += (1 << cont_bits);
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
	if (signo == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else
		kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	int					pid_child;
	struct sigaction	sa;

	sa.sa_sigaction = sig_usr;
	sa.sa_flags = SA_SIGINFO;
	write(1, "Mi pid es: ", 12);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\nEsperando mensaje...\n", 23);
	write(1, "--------------------------------\n", 34);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	atexit(leaks);
	return (0);
}
