cabecera

#include "libft.h"

t_list	*ft_lstnew (void *content)
{
	t_list *nodo;

    nodo = (t_list *) malloc (sizeof(t_list));
    if (nodo == NULL)
        return (NULL);
    nodo->content = content;
    nodo->next = NULL;
    return (nodo);
}
