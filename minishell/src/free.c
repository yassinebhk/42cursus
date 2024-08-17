/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:14:05 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 12:14:27 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_args(char *line, t_env *env, int len)
{
	int	i;

	i = -1;
	free(line);
	while (++i < len)
	{
		free(env[i].key);
		if (env[i].var)
			free(env[i].var);
	}
	free(env);
}