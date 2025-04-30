/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/28 10:00:36 by ybouhaik		  #+#	#+#			 */
/*   Updated: 2025/04/30 11:55:15 by maxgarci         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	sigint_handler(int signal)
{
	(void)signal;
	if (g_signal == 1)
	{
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_signal == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_d(t_lists *lists)
{
	free_lists(lists->env, lists->exp);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void	signal_quit(int signal)
{
	if (signal == SIGQUIT)
		write(2, "Quit (core dumped)\n", 20);
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, SIG_IGN);
	if (g_signal == 0)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, signal_quit);
}
