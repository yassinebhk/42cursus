/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:58:03 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/21 22:43:46 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void check_double_quote(char c, int *double_quote)
{
    if (c == DOUBLE_QUOTE)
        *double_quote = !(*double_quote);
}

static void check_single_quote(char c, int *single_quote)
{
    if (c == SINGLE_QUOTE)
        *single_quote = !(*single_quote);
}

int count_pipes(char *line)
{
    int pos = -1;
    int single_quote = 0;
    int double_quote = 0;
    int num_pipes = 0;

    while (line[++pos])
    {
        check_single_quote(line[pos], &single_quote);
        check_double_quote(line[pos], &double_quote);

        if (line[pos] == PIPE && !single_quote && !double_quote)
            num_pipes++;
    }
    return num_pipes;
}

