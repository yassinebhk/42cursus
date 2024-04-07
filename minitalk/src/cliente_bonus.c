/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cliente_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:20:32 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/07 23:57:18 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cliente.h"

static void	leaks(void)
{
	system("leaks client");
}

static void	ft_exit(int a)
{
	if (a == 0)
		write(1, "Pid inválido\n", 15);
	else if (a == 2 || a == 1)
		write(1, "Faltan argumentos\n", 19);
	else if (a == 3)
		write(1, "Demasiados argumentos\n", 23);
	exit(1);
}

static void	handler(int signo)
{
	if (signo == SIGUSR1)
		write(1, "1", 1);
	else
		write(1, "0", 1);
}

static void	ft_convert_to_binary(char *message, pid_t pid_server)
{
	int	i;
	int	value;
	int	shift;

	i = -1;
	while (++i < ft_strlen(message))
	{
		shift = 8;
		value = (int)message[i];
		while (--shift >= 0)
		{
			if ((value & (1 << shift)) >> shift)
				kill(pid_server, SIGUSR1);
			else
				kill(pid_server, SIGUSR2);
			usleep(300);
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid_server;
	int		i;

	i = -1;
	if (argc != 3)
		ft_exit(argc);
	pid_server = ft_atoi(argv[1]);
	if (pid_server <= 1)
		ft_exit(0);
	write(1, "Mensaje enviado: ", 18);
	ft_putstr_fd(argv[2], 1);
	write(1, "\n", 1);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	ft_convert_to_binary(argv[2], pid_server);
	ft_convert_to_binary("\n", pid_server);
	return (0);
}

	//atexit(leaks);