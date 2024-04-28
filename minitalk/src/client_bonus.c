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

static void	ft_exit(int a)
{
	if (a == 0)
		ft_printf("Invalid PID\n");
	else if (a == 2 || a == 1)
		ft_printf("Insufficient arguments\n");
	else if (a > 3)
		ft_printf("Too much arguments: [PID_SERVER] [MESSAGE]\n");
	exit(1);
}

static void	handler(int signo)
{
	if (signo == SIGUSR1)
		ft_printf("1");
	else
		ft_printf("0");
}

static void	ft_convert_to_binary(char *message, pid_t pid_server)
{
	int				i;
	unsigned char	value;
	int				shift;

	i = -1;
	while (++i < ft_strlen(message))
	{
		shift = 8;
		value = message[i];
		while (--shift >= 0)
		{
			if ((value & (1 << shift)) >> shift)
				kill(pid_server, SIGUSR1);
			else
				kill(pid_server, SIGUSR2);
			usleep(50);
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
	ft_printf("\n--------------------\n");
	ft_printf("\n[Sent message]\n\n%s\n", argv[2]);
	ft_printf("--------------------\n\n");
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	ft_convert_to_binary(argv[2], pid_server);
	return (0);
}
