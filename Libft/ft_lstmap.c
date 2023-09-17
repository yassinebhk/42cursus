/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:09:44 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/17 12:09:45 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;

	new = (t_list *)malloc(ft_lstsize(lst) * sizeof(t_list));
	if (new)
		return (NULL);
	while (lst)
	{
		if ((*f)(lst->content))
		{
			new->content = (*f)(lst->content);
			new = new->next;
		}
		else
			(*del)(lst->content);
		lst = lst->next;
	}
	return (new);
}
