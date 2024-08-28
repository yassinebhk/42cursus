#include "minishell.h"

char	*get_path_list(char *command, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(command, env->key))
			return (env->var);
		env = env->next;
	}
	ft_putstr_fd("path variable not found at env.", 2);
	return (NULL);
}

int	is_built_in(char *command)
{
	if (!ft_strcmp(command, "echo\0") || !ft_strcmp(command, "cd\0")
		|| !ft_strcmp(command, "pwd\0") || !ft_strcmp(command, "export\0")
		|| !ft_strcmp(command, "unset\0") || !ft_strcmp(command, "env\0")
		|| !ft_strcmp(command, "exit\0"))
		return (1);
	return (0);
}

int	get_absolute_path(char *path_list, char *command, t_node *head)
{
	int		pos;
	char	*tmp;
	char	**split;
	char	*path;
	char	*absolute_dir;

	pos = -1;
	split = ft_split(path_list, ':');
	tmp = NULL;
	while (split && split[++pos])
	{
		path = split[pos];
		tmp = ft_strjoin(path, "/");
		absolute_dir = ft_strjoin(tmp, command);
		if (!access(absolute_dir, e_X_OK))
		{
			free(head->content->command);
			head->content->command = ft_strdup(absolute_dir);
			return (ft_free(split), free(absolute_dir), 1);
		}
		free(tmp);
		free(absolute_dir);
	}
	ft_putstr_fd("absolute path not found.", 2);
	return (ft_free(split), 0);
}

int	excute_one_command(t_node **head, t_lists *lists)
{
	char	*path_list;

	if (is_built_in((*head)->content->command))
		return (find_built((*head)->content->args, (*head)->content->num_args,
				&(lists->env), &(lists->exp)));
	path_list = get_path_list("PATH\0", lists->env);
	if (!path_list)
		return (VARIABLE_NOT_FOUND);
	if (!get_absolute_path(path_list, (*head)->content->command, (*head)))
		return (COMMAND_NOT_FOUND);
	if (execv((*head)->content->command, (*head)->content->args) == -1)
	{
		perror("execv: ");
		return (1);
	}
	return (0);
}
