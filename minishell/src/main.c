/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:50:55 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/15 20:49:04 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_words(char const *s, char c)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			num++;
			while (s[i] != c && s[i + 1])
				i++;
		}
		i++;
	}
	return (num);
}

int	ft_exit(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	ft_env(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	unset(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	export(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (0);
}

// int	pwd(char **str, int pos, int num_words, char **env)
// {

// 	return (0);
// }

int	cd(char **str, int pos, int num_words, t_env *env)
{
	char	cwd[1024];

	// char	*current_dir;
	// char	*new_dir;
	(void)env;
	if (num_words == 1 || !ft_strcmp(str[pos + 1], "~"))
		chdir("/home/ybouhaik");
	else if (!ft_strcmp(str[pos + 1], "..\0"))
	{
		if (!getcwd(cwd, sizeof(cwd)))
		{
			printf("Error in getcwd function\n");
			return (1);
		}
		chdir(cwd);
	}
	else if (!ft_strcmp(str[pos + 1], "."))
		;
	else
	{
		if (chdir(str[pos + 1]))
		{
			perror("cd: ");
			return (1);
		}
	}
	return (0);
}

static int	is_valid_arg(char *str)
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

int	echo(char **str, int pos, int num_words)
{
	int	flag;

	flag = 0;
	while (++(pos) < num_words && is_valid_arg(str[pos]))
		flag = 1;
	if (flag)
	{
		if ((pos) < num_words)
			printf("%s", str[pos]);
		while (++(pos) < num_words)
			printf(" %s", str[pos]);
	}
	else
	{
		if ((pos) < num_words)
			printf("%s", str[pos]);
		while (++(pos) < num_words)
			printf(" %s", str[pos]);
		printf("\n");
	}
	return (0);
}

int	find_built(char **str, int num_words, t_env *env)
{
	if (!ft_strcmp(str[0], "echo"))
		return (echo(str, 0, num_words));
	else if (!ft_strcmp(str[0], "cd"))
		return (cd(str, 0, num_words, env));
	// else if (!ft_strcmp(str[0], "pwd"))
	// 	return (pwd(str, 0, num_words, env));
	else if (!ft_strcmp(str[0], "export"))
		return (export(str[0], 0));
	else if (!ft_strcmp(str[0], "unset"))
		return (unset(str[0], 0));
	else if (!ft_strcmp(str[0], "env"))
		return (ft_env(str[0], 0));
	else if (!ft_strcmp(str[0], "exit"))
		return (ft_exit(str[0], 0));
	return (0);
}

int	set_built(char **split, int num_words, t_env *env)
{
	// int	built;
	return (find_built(split, num_words, env));
}

int	len_env(char **environment)
{
	int	len;

	len = 0;
	while (environment[len])
		len++;
	return (len);
}

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

t_env	*get_var(char **environment)
{
	int		pos;
	t_env	*env;
	char	**split;

	pos = -1;
	env = (t_env *)malloc(sizeof(t_env) * len_env(environment));
	if (!env)
	{
		printf("Error: environment variables malloc failed.\n");
		return (NULL);
	}
	while (++pos < len_env(environment))
	{
		split = ft_split(environment[pos], '=');
		env[pos].key = ft_strdup(split[0]);
		if (!split[1])
			env[pos].var = NULL;
		else
			env[pos].var = ft_strdup(split[1]);
		ft_free(split);
	}
	return (env);
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

int	main(int argc, char **argv, char **environment)
{
	t_env	*env;
	char	*line;
	char	**split;

	(void)argc;
	(void)argv;
	env = get_var(environment);
	while (1)
	{
		line = readline("$ ");
		if (!line)
			;
		else
		{
			split = ft_split(line, ' ');
			set_built(split, num_words(line, ' '), env);
			free(split);
		}
	}
	free_args(line, env, len_env(environment));
	return (0);
}
