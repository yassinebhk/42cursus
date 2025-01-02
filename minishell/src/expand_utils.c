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

char	*process_str(t_node *tmp, char *str)
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

int	find_dollar(char *str, int pos)
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
