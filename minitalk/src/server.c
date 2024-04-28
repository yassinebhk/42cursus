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

static void	sig_usr(int signo)
{
	static int	cont_bits = 7;
	static int	number = 0;

	if (signo == SIGUSR1)
		number += (1 << cont_bits);
	cont_bits--;
	if (cont_bits == -1)
	{
		ft_printf("%c", number);
		if (number == 0)
			ft_printf("\n");
		cont_bits = 7;
		number = 0;
	}
}

int	main(void)
{
	int	pid_child;

	ft_printf("\n--------------------\n");
	ft_printf("PID: %d\n", getpid());
	ft_printf("--------------------\n");
	ft_printf("\nReceived messages...\n\n");
	ft_printf("--------------------\n");
	signal(SIGUSR1, sig_usr);
	signal(SIGUSR2, sig_usr);
	while (1)
		pause();
	return (0);
}
