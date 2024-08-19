/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:10:15 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/19 23:29:50 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var(char *str, t_env *env, t_env *exp)
{
	char	*tmp;

	while (env)
	{
		if (!ft_strcmp(env->key, str))
			return (1);
		env = env->next;
	}
	while (exp)
	{
		tmp = ft_strjoin("declare -x ", str);
		if (!ft_strcmp(exp->key, tmp))
			return (free(tmp), 2);
		exp = exp->next;
		free(tmp);
	}
	return (0);
}
/*
void	delete_var(char *str, t_env **env, t_env **exp, int flag)
{
	t_env	*tmp;
	char	*aux;

	if (!flag)
	{
		while (ft_strcmp((*env)->next->key, str))
			(*env) = (*env)->next;
		tmp = (*env)->next;
		(*env)->next = (*env)->next->next;
		free(tmp->key);
		if (tmp->var)
			free(tmp->var);
		free(tmp);
	}
	aux = ft_strjoin("declare -x ", str);
	while (ft_strcmp((*exp)->next->key, aux))
	{
		printf("\nAntes:   %s|%s|%s|%s", aux, (*exp)->key, (*exp)->next->key, (*exp)->next->next->key);
		(*exp) = (*exp)->next;
		printf("\nDespues: %s|%s|%s", aux, (*exp)->key, (*exp)->next->key);
	}
	tmp = (*exp)->next;
	(*exp)->next = (*exp)->next->next;
	free(tmp->key);
	if (tmp->var)
		free(tmp->var);
	free(tmp);
	free(aux);
}
*/

void	delete_var(char *str, t_env **env, t_env **exp, int flag)
{
	t_env	tmp;
	t_env	*aux;
	t_env	*curr;
	
	char	*key;

	tmp.next = *env;
	curr = &tmp;
	if (!flag)
	{
		while (curr->next)
		{
			if (ft_strcmp(curr->next->key, str) == 0)
			{
				free(curr->next->key);
				free(curr->next->var);
				aux = curr->next->next;
				free(curr->next);
				curr->next = aux;
				break;
			}
			curr = curr->next;
		}
	}
	*env = tmp.next;
	tmp.next = *exp;
	curr = &tmp;
	key = ft_strjoin("declare -x ", str);
	while (curr->next)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			free(curr->next->key);
			free(curr->next->var);
			aux = curr->next->next;
			free(curr->next);
			curr->next = aux;
			break;
		}
		curr = curr->next;
	}
	free(key);
	*exp = tmp.next;
}

//Arreglar leaks cuando reasigno valores a la vbles y reescribir la funcion anteior

/*
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode temp;
    temp->next = head;

    struct ListNode *curr = temp;
    while(curr->next != NULL){
        if(curr->next->val == val)
            curr->next = curr->next->next;
            free();
            return;
        curr = curr->next;
    }
    return temp->next;
}
*/

char	*add_eq(char *str)
{
	int		pos;
	char	*rmv;

	pos = -1;
	rmv = (char *)malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!rmv)
		return (NULL);
	while (++pos < ((int)ft_strlen(str)))
		rmv[pos] = str[pos];
	rmv[pos] = '=';
	rmv[pos + 1] = '\0';
	free(str);
	return (rmv);
}

int	unset(char **str, int num_words, t_env *env, t_env *exp)
{
	int	pos;
	int	result;

	result = 0;
	pos = 0;
	if (num_words > 1)
	{
		while (++pos < num_words)
		{
			if (check_var(str[pos], env, exp) == 1)
				delete_var(str[pos], &env, &exp, 0);
			else if (check_var(str[pos], env, exp) == 2)
				delete_var(str[pos], &env, &exp, 1);
		}
	}
	return (result);
}
