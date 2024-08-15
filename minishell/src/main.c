/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:50:55 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/15 14:42:55 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *str, int *pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	env(char *str, int *pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	unset(char *str, int *pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	export(char *str, int *pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	pwd(char *str, int *pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	cd(char *str, int *pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	is_valid_arg(char *str)
{
	int	pos;

	pos = 0;
	if (str[pos] != '-')
		return (0);
	while (str[++pos])
	{
		if (str[pos] != 'n')
			return (0);
	}
	return (1);
}

int	echo(char **str, int *pos, int num_words)
{
	int	flag;

	flag = 0;
	while (++(*pos) < num_words && is_valid_arg(str[*pos]))
		flag = 1;
	if (flag)
	{
		if ((*pos) < num_words)
			printf("%s", str[*pos]);
		while (++(*pos) < num_words)
			printf(" %s", str[*pos]);
	}
	else
	{
		if ((*pos) < num_words)
			printf("%s", str[*pos]);
		while (++(*pos) < num_words)
			printf(" %s", str[*pos]);
		printf("\n");
	}
	return (1);
}

int	find_built(char **str, int num_words)
{
	int	pos;

	pos = -1;
	while (++pos < num_words)
	{
		if (!ft_strcmp(str[pos], "echo"))
			return (echo(str, &pos, num_words));
		else if (!ft_strcmp(str[pos], "cd"))
			return (cd(str[pos], &pos));
		else if (!ft_strcmp(str[pos], "pwd"))
			return (pwd(str[pos], &pos));
		else if (!ft_strcmp(str[pos], "export"))
			return (export(str[pos], &pos));
		else if (!ft_strcmp(str[pos], "unset"))
			return (unset(str[pos], &pos));
		else if (!ft_strcmp(str[pos], "env"))
			return (env(str[pos], &pos));
		else if (!ft_strcmp(str[pos], "exit"))
			return (ft_exit(str[pos], &pos));
	}
	return (1);
}

int	set_built(char **split, int num_words)
{
	// int	built;
	return (find_built(split, num_words));
}

int	main(int argc, char **argv, char **environment)
{
	char	*line;
	char	**split;

	(void)argc;
	(void)argv;
	(void)environment;
	// int		status;
	// char	**env;
	while (1)
	{
		line = readline("$ ");
		if (!line)
			;
		else
		{
			split = ft_split(line, ' ');
			set_built(split, num_words(line, ' '));
			free(split);
		}
	}
	free(line);
	return (0);
}
