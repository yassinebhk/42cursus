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
		number |= (1 << cont_bits);
	cont_bits--;
	if (cont_bits == -1)
	{
		ft_printf("%c", number);
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
	sa.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	ft_printf("\n--------------------\n");
	ft_printf("PID: %d\n", getpid());
	ft_printf("--------------------\n");
	ft_printf("\nMensajes recibidos...\n\n");
	ft_printf("--------------------\n");
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}

// atexit(leaks);