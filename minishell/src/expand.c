#include "minishell.h"

// static int	find_dollar(char *str, int pos)
// {
// 	int next;

// 	next = pos + 1;
// 	while(str[next])
// 	{
// 		if (str[next] == DOLLAR && str[next - 1] != BACKSLASH)
// 			return (next);
// 		next++;
// 	}
// 	return (next);
// }

// static int	process_str(t_node *tmp, char *str)
// {
// 	int	pos;
// 	int	next_dollar;
// 	char	*new_word;

// 	pos = -1;
// 	while(str[++pos])
// 	{
// 		if (str[pos] == DOLLAR && !pos)
// 		{
// 			next_dollar = find_dollar(str, pos);
// 			//construyo una palabra que vaya desde str[pos] hasta str[next_dollar - 1]
// 			//esa es la variable a expandir, luego busco en tmp->var_list->env si existe
// 			//esa variable y en caso de existir, retorno su valor
// 			// Si encuentro la variable, la concateno a new_word
// 			// Si no existe, no concateno nada a new_word
// 		}
// 		else if (str[pos] == DOLLAR && str[pos - 1] != BACKSLASH)
// 		{
// 			//hago lo mismo que en el if
// 		}
// 		else
// 		{
// 			//concateno el caracter a new_word
// 		}
// 	}
// 	return (new_word);
// }

// int	expand_commands(t_node **head)
// {
// 	int		i;
// 	t_node	*tmp;

// 	tmp = head;
// 	while(tmp)
// 	{
// 		i = -1;
// 		while(++i < tmp->content->num_args)
// 			tmp->content->args[i] = process_str(tmp, tmp->content->args[i]);
// 		tmp = tmp->next;
// 	}
// }

char *strndup(const char *s, size_t n)
{
    size_t len;
    char *new_str;

    len = 0;
    while (s[len] && len < n)
        len++;
    new_str = (char *)malloc(len + 1);
    if (!new_str)
        return (NULL);
    for (size_t i = 0; i < len; i++)
        new_str[i] = s[i];
    new_str[len] = '\0';
    return (new_str);
}

char *strjoin_char(const char *s1, const char *s2, char c)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *new_str = (char *)malloc(len1 + len2 + 2); // +2 for the char and null terminator

    if (!new_str)
        return (NULL);

    strcpy(new_str, s1);
    new_str[len1] = c;  // Insert the character
    strcpy(new_str + len1 + 1, s2); // Copy second string

    return (new_str);
}

static char *find_var_value(t_env *env_list, char *var_name)
{
	while (env_list)
	{
		if (strcmp(env_list->key, var_name) == 0)
			return (env_list->var);
		env_list = env_list->next;
	}
	return (NULL);
}

static char *expand_variable(t_env *env_list, char *str, int start, int end)
{
	char *var_name;
	char *var_value;

	var_name = strndup(str + start + 1, end - start - 1); // Extract variable name after $
	if (!var_name)
		return (NULL); // handle allocation error
	var_value = find_var_value(env_list, var_name);
	free(var_name);
	return (var_value ? strdup(var_value) : strdup("")); // If variable found, return value, else return empty string
}

static int find_dollar(char *str, int pos)
{
	int next;

	next = pos + 1;
	while (str[next])
	{
		if (str[next] == DOLLAR && str[next - 1] != BACKSLASH)
			return (next);
		next++;
	}
	return (next);
}

static char *process_str(t_node *tmp, char *str)
{
	int pos = 0, next_dollar;
	char *new_word = strdup(""); // Start with an empty string
	char *var_value;
	char *temp;

	while (str[pos])
	{
		if (str[pos] == DOLLAR && (pos == 0 || str[pos - 1] != BACKSLASH))
		{
			next_dollar = find_dollar(str, pos);
			var_value = expand_variable(tmp->var_list->env, str, pos, next_dollar);
			temp = new_word;
			new_word = ft_strjoin(new_word, var_value); // Append the variable's value
			free(temp);
			free(var_value);
			pos = next_dollar - 1; // Move past the expanded variable
		}
		else
		{
			temp = new_word;
			new_word = strjoin_char(new_word, temp, str[pos]); // Append regular character
			free(temp);
		}
		pos++;
	}
	return (new_word); // Return the expanded string
}

int expand_commands(t_node **head)
{
	t_node *tmp = *head;
	int i;

	while (tmp)
	{
		for (i = 0; i < tmp->content->num_args; i++)
		{
			char *expanded = process_str(tmp, tmp->content->args[i]);
			free(tmp->content->args[i]);  // Free original argument
			tmp->content->args[i] = expanded;  // Replace with expanded version
		}
		tmp = tmp->next;
	}
	return (0);
}
