#include "minishell.h"

static t_node	*ft_last_node(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_node_back(t_node **head, t_node *new_node)
{
	t_node	*last;

	if (!new_node)
	{
		print_error("ft_add_back", ENO_MEM);
		return ;
	}
	if (!*head)
		*head = new_node;
	else
	{
		last = ft_last_node(*head);
		if (last)
			last->next = new_node;
	}
}

void	find_pipe(char *line, int *pos)
{
	int	single_quote_open;
	int	double_quote_open;

	single_quote_open = 0;
	double_quote_open = 0;
	while (line[*pos])
	{
		if (line[*pos] == SINGLE_QUOTE && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (line[*pos] == DOUBLE_QUOTE && !single_quote_open)
			double_quote_open = !double_quote_open;
		else if (line[*pos] == PIPE && !single_quote_open && !double_quote_open)
			break ;
		(*pos)++;
	}
	(*pos)++;
}

char	*get_trunc_str(char *line, int init_pos, int end_pos)
{
	int		pos;
	char	*str;

	pos = 0;
	str = (char *)malloc(end_pos - init_pos);
	if (!str)
		return (print_error("new_command malloc", ENO_MEM), NULL);
	while (init_pos < end_pos - 1)
	{
		str[pos] = line[init_pos];
		pos++;
		init_pos++;
	}
	str[pos] = '\0';
	return (str);
}

static int	is_redir(char *str)
{
	return ((*str == '>' && *(str + 1) == '>') || *str == '>' || (*str == '<'
			&& *(str + 1) == '<') || *str == '<');
}

static int	ft_isspecial(char c)
{
	return (c == '*' || c == '?' || c == '!' || c == '$' || c == '&' || c == '#'
		|| c == '<' || c == '>' || c == '\\' || c == '/' || c == '|');
}

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v');
}

static void	num_args(char *str, int *n_args, int *n_redir)
{
	int	word;

	word = 0;
	while (*str <= ' ')
		str++;
	while (*str)
	{
		if (is_redir(str))
		{
			while (is_redir(str))
				str++;
			while (ft_isspace(*str))
				str++;
			while (*str > ' ' && !is_redir(str))
				str++;
			(*n_redir)++;
		}
		while (*str > ' ' && !is_redir(str))
		{
			str++;
			if (!word)
				word = 1;
		}
		while (ft_isspace(*str))
			str++;
		if (word)
			(*n_args)++;
		word = 0;
	}
}

static t_redir	create_redir(char *str)
{
	int		i;
	int		begin;
	int		cp_i;
	t_redir	redir;

	i = 0;
	if (str[i] == '>' && str[i + 1] == '>')
		redir.type = r_append;
	else if (str[i] == '>')
		redir.type = r_output;
	else if (str[i] == '<' && str[i + 1] == '<')
		redir.type = r_heredoc;
	else if (str[i] == '<')
		redir.type = r_input;
	else if (ft_isspecial(str[i + 2]))
		return (print_error("create_redir parse error", PARSING),
			redir.valid = 0, redir);
	while (is_redir(str + i))
		i++;
	while (ft_isspace(str[i]))
		i++;
	begin = i;
	while (str[i] > ' ' && !is_redir(str + i))
	{
		if (ft_isspecial(str[i]))
			return (print_error("create_redir filename", BAD_ASSIGNMENT),
				redir.valid = 0, redir);
		i++;
	}
	redir.filename = (char *)malloc(sizeof(char) * (i - begin + 1));
	if (!redir.filename)
		return (print_error("create_redir malloc", ENO_MEM), redir.valid = 0,
			redir);
	cp_i = 0;
	while (begin < i)
		redir.filename[cp_i++] = str[begin++];
	redir.filename[cp_i] = '\0';
	redir.valid = 1;
	return (redir);
}

static int	create_command(char *str, t_command **command)
{
	int	redir_pos;
	int	args_pos;
	int	cp_i;
	int	word;
	int	comm_word;
	int	i;
	int	begin;
	int	str_i;

	redir_pos = 0;
	args_pos = 0;
	word = 0;
	comm_word = 1;
	i = 0;
	while (str[i] <= ' ')
		i++;
	while (str[i])
	{
		if (is_redir(str + i))
		{
			(*command)->redir[redir_pos] = create_redir(str + i);
			if (!(*command)->redir[redir_pos++].valid)
				return (1);
			while (is_redir(str + i))
				i++;
			while (ft_isspace(str[i]))
				i++;
			while (str[i] > ' ' && !is_redir(str + i))
				i++;
		}
		begin = i;
		while (str[i] > ' ' && !is_redir(str + i))
		{
			i++;
			if (!word)
				word = 1;
		}
		if (word)
		{
			cp_i = 0;
			str_i = begin;
			if (comm_word)
			{
				free((*command)->command);
				(*command)->command = (char *)ft_calloc((i - begin + 1),
						sizeof(char));
				while (begin < i)
					(*command)->command[cp_i++] = str[begin++];
				(*command)->command[cp_i] = '\0';
				comm_word = 0;
				cp_i = 0;
			}
			(*command)->args[args_pos] = (char *)malloc(sizeof(char) * (i
						- str_i + 1));
			while (str_i < i)
				(*command)->args[args_pos][cp_i++] = str[str_i++];
			(*command)->args[args_pos++][cp_i] = '\0';
		}
		while (ft_isspace(str[i]))
			i++;
		word = 0;
	}
	return (0);
}

int	new_command(char *str, t_command **command)
{
	int	n_args;
	int	n_redir;

	n_args = 0;
	n_redir = 0;
	num_args(str, &n_args, &n_redir);
	(*command)->num_args = n_args;
	(*command)->num_redir = n_redir;
	if (n_args)
		(*command)->args = (char **)malloc(sizeof(char *)
				* ((*command)->num_args));
	if (!(*command)->args)
		return (print_error("command args malloc", ENO_MEM), 0);
	if (n_redir)
		(*command)->redir = (t_redir *)malloc(sizeof(t_redir) * n_redir);
	while (*str <= ' ')
		str++;
	if (create_command(str, command))
		return (print_error("error command creation", 0), 0);
	return (1);
}

int	ft_len_node(t_node *head)
{
	int		size;
	t_node	*tmp;

	size = 0;
	tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}
