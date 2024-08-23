#include "minishell.h"

int is_quote(char c) {
    return c == SINGLE_QUOTE || c == DOUBLE_QUOTE;
}

char *translate_str(const char *str)
{
    int pos = 0;
    int quote_open = 0;
    int new_len = 0;
    char *new_str;
    int i = 0;

    // Primera pasada para calcular la longitud de la nueva cadena
    while (str[pos])
    {
        if (is_quote(str[pos]))
            quote_open = !quote_open;
        else if (!quote_open)
            new_len++;
        new_len++;
        pos++;
    }

    new_str = (char *)malloc(new_len + 1);

    pos = 0;
    // Segunda pasada para construir la nueva cadena
    while (str[pos])
    {
        if (is_quote(str[pos]))
            quote_open = !quote_open;
        else if (!quote_open)
            new_str[i++] = '\\';
        new_str[i++] = str[pos];
        pos++;
    }
    new_str[i] = '\0';

    return new_str;
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **environment)
{
	char	*line;
	int		status;

	status = 0;
	while (status != 42)
	{
		line = readline("$ ");
		if (line && line[0])
		{
			add_history(line);
			status = process_command(environment, line);
			//quoted_line = translate_str(line);
			//printf("\n%s <---> %s\n", line, quoted_line);
			//status = split_by_spaces(quoted_line, env, exp);
			//free(quoted_line);

		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
