#include "minishell.h"

char	*get_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->var);
		env = env->next;
	}
	printf("\n❌ Error: no %s key was found.\n\n", key);
	return (NULL);
}

static int	move_to_path_env(char *new_dir, t_env **env, t_env **exp)
{
	char	*new_rel_dir;
	char	*tmp;
	char	*cwd;
	char	*old_dir;

	old_dir = getcwd(NULL, 0);
	tmp = ft_strjoin("/", new_dir);
	cwd = getcwd(NULL, 0);
	new_rel_dir = ft_strjoin(cwd, tmp);
	if (new_dir && *new_dir == '/' && chdir(new_dir))
	{
		perror("cd absolute ");
		return (free(old_dir), free(new_rel_dir), free(cwd), free(tmp), 1);
	}
	else if (*new_dir != '/' && chdir(new_rel_dir))
	{
		perror("cd relative ");
		return (free(old_dir), free(new_rel_dir), free(cwd), free(tmp), 1);
	}
	if (*new_dir == '/')
		update(env, exp, old_dir, new_dir);
	else
		update(env, exp, old_dir, new_rel_dir);
	return (free(cwd), free(tmp), free(new_rel_dir), 0);
}

static int	change_directory(t_env **env, t_env **exp, char *var, int flag)
{
	char	*old_dir;
	char	*new_dir;

	old_dir = getcwd(NULL, 0);
	if (flag)
	{
		new_dir = get_env(*env, var);
		if (!new_dir)
			return (free(old_dir), 1);
	}
	else
		new_dir = get_parent(old_dir);
	if (chdir(new_dir))
	{
		ft_putstr_fd(old_dir, 2);
		perror(" parent does not exist: ");
		if (!flag)
			free(new_dir);
		return (free(old_dir), 1);
	}
	update(env, exp, old_dir, new_dir);
	if (!flag)
		free(new_dir);
	return (0);
}

int	cd_env(char **str, int num_words, t_lists **list, t_node **head)
{
	if (num_words == 1 || !ft_strcmp(str[1], "~"))
	{
		if (change_directory(&(*list)->env, &(*list)->exp, "HOME\0", 1))
			return (free(NULL), (*head)->error = CANNOT_CHANGE_DIR ,1);
	}
	else if (!ft_strcmp(str[1], "..\0"))
	{
		if (change_directory(&(*list)->env, &(*list)->exp, NULL, 0))
			return (free(NULL), (*head)->error = CANNOT_CHANGE_DIR ,1);
	}
	else if (!ft_strcmp(str[1], "-"))
	{
		if (change_directory(&(*list)->env, &(*list)->exp, "OLDPWD\0", 1))
			return (free(NULL), (*head)->error = CANNOT_CHANGE_DIR ,1);
	}
	else if (ft_strcmp(str[1], "."))
		return (move_to_path_env(str[1], &(*list)->env, &(*list)->exp));
	return (0);
}

int			cd(char **str, int num_words, t_lists **list, t_node **head)
{
	if (cd_env(str, num_words, list, head))
		return (free(NULL), (*head)->error = 1, 1);
	return (free(NULL), (*head)->error = 0, 0);
}
