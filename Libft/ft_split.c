/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:04:37 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/13 19:04:39 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int num_words(char const *s, char c)
{
    int num;
    int i;

    num = 1;
    i = 0;
    while(s[i])
    {
        if (s[i] == c)
            num++;
        i++;
    }
    return (num);
}


static int size_words(char const *s, char c, int *i)
{
    int num;

    num = 0;
    while(s[*i] != c && s[*i])
    {
        num++;
        (*i)++;
    }
    return (num);
}

static char *fill_word (char *palabra, char *s, int ini, int pos)
{   
    int j;

    j = 0;
    while (ini < pos)
    {
        palabra[j] = s[ini];
        j++;
        ini++;
    }
    palabra[j] = '\0';
    return (palabra);
}

char    **ft_split(char const *s, char c)
{
    int words;
    int i;
    int pos;
    int ini;
    char **palabra;

    i = 0;
    pos = 0;
    words = num_words(s, c);
    palabra = (char **) malloc ((words + 1) * sizeof (char *));
    if (*palabra)
        return (NULL);
    while (i < words)
    {   
        ini = pos;
        palabra[i] = (char *) malloc ((size_words (s, c, &pos) + 1) * sizeof (char));
        palabra[i] = fill_word(palabra[i], (char *)s, ini, pos);
        i++;
        pos++;
    }
    palabra[i] = NULL;
    return (palabra);
}

int main()
{
    char **buffer;
    buffer = ft_split("hccolapacocmijocasas", 'c');
    int i = 0;
    while (i < 7)
    {
        printf("%s\n", buffer[i]);
        i++;
    }
}
