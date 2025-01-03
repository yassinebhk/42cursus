#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new_str;
	size_t	i;

	len = 0;
	while (s[len] && len < n)
	{
		len++;
	}
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len)
		new_str[i] = s[i];
	new_str[len] = '\0';
	return (new_str);
}

char	*strjoin_char(char *s1, char c, char terminator)
{
	size_t	len1;
	size_t	i;
	char	*new_str;

	len1 = strlen(s1);
	new_str = (char *)malloc(len1 + 2);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len1)
		new_str[i] = s1[i];
	new_str[i] = c;
	new_str[i + 1] = terminator;
	return (free(s1), new_str);
}

static char	*find_var_value(t_env *env_list, char *var_name)
{
	while (env_list)
	{
		if (strcmp(env_list->key, var_name) == 0)
			return (env_list->var);
		env_list = env_list->next;
	}
	return (NULL);
}

static char	*expand_variable(t_node *tmp, char *str, int start, int end)
{
	char	*var_name;
	char	*var_value;
	char	*error_str;
	char	*concat_str;
	char	*final_str;

	if (ft_strlen(str) == 1)
		return (ft_strdup("$"));
	var_name = ft_strndup(str + start + 1, end - start - 1);
	if (!var_name)
		return (NULL);
	if (ft_strncmp(var_name, "?", 1) == 0 || ft_strncmp(var_name, "\\?",
			2) == 0)
	{
		if (ft_strncmp(var_name, "\\?", 2) == 0)
			start += 3;
		else
			start += 2;
		error_str = ft_itoa(tmp->error);
		free(var_name);
		if (str[start] != '\0')
		{
			concat_str = ft_strndup(str + start, ft_strlen(str) - start);
			final_str = ft_strjoin(error_str, concat_str);
			return (free(concat_str), free(error_str), final_str);
		}
		return (error_str);
	}
	var_value = find_var_value(tmp->var_list->env, var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_strdup(""));
}

static int	find_dollar(char *str, int pos)
{
	int	next;

	next = pos + 1;
	while (str[next])
	{
		if (str[next] == DOLLAR && str[next - 1] != BACKSLASH)
			return (next);
		next++;
	}
	return (next);
}

static char	*process_str(t_node *tmp, char *str)
{
	int		pos;
	int		next_dollar;
	char	*new_word;
	char	*var_value;
	size_t	i;

	pos = -1;
	new_word = ft_strdup("");
	while (str[++pos])
	{
		if (str[pos] == DOLLAR && (pos == 0 || str[pos - 1] != BACKSLASH))
		{
			next_dollar = find_dollar(str, pos);
			var_value = expand_variable(tmp, str, pos, next_dollar);
			i = -1;
			while (var_value[++i] != '\0')
				new_word = strjoin_char(new_word, var_value[i], '\0');
			free(var_value);
			pos = next_dollar - 1;
		}
		else
			new_word = strjoin_char(new_word, str[pos], '\0');
	}
	return (new_word);
}

int	expand_commands(t_node **head)
{
	int		i;
	t_node	*tmp;
	char	*expanded;

	tmp = *head;
	while (tmp)
	{
		i = -1;
		while (++i < tmp->content->num_args)
		{
			expanded = process_str(tmp, tmp->content->args[i]);
			free(tmp->content->args[i]);
			tmp->content->args[i] = ft_strdup(expanded);
			if (i == 0)
			{
				free(tmp->content->command);
				tmp->content->command = ft_strdup(expanded);
			}
			free(expanded);
		}
		tmp = tmp->next;
	}
	return (0);
}
