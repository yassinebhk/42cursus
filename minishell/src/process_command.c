#include "minishell.h"

void	print_list(t_node *head)
{
	int	i;

	while (head)
	{
		if (head->content)
		{
			printf("\n%d|%s|", head->content->num_args, head->content->command);
			if (head->content->args)
			{
				i = -1;
				if (head->content->args[++i])
					printf("%s", head->content->args[i]);
				while (head->content->args[i])
				{
					printf(" %s", head->content->args[i]);
					i++;
				}
			}
			printf("\n");
		}
		head = head->next;
	}
}

int	process_command(char **env, char *line)
{
	t_node *head;

	head = NULL;
	if (!even_quotes(line) || invalid_character(line) || init_nodes(env, line,
			&head))
		return (1);
		// EN init_node.c falta inicialziar la estructura de redir, habria que hacer una funcion que malloquease
	//Ahora seria ir nodo por nodo. Primero, hacer un translate del command (y de los argumentos) para interpretarlo bien
	// luego ver el tema de redirecciones, y luego ya ver si creamos la pipe antes o despues de ejecutar las cosa y almacenar
	// los descriptores de fichero. IMPORTANTE: cuando se vaya a llamar al executor eliminar los \ que hayamos colocado.
	// Leer el .h para ver las estrcuturas que hay y los define
	print_list(head);
	return (free_list(head), 0);
}