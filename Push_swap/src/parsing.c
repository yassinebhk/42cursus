/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:31:49 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/27 12:31:51 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

// static  void ft_check_integer(char *str)
// {
//     long    num;
//     int     error;

//     while(*str)
//     {
//         num = ft_atoi_mod(str, &error);
//         ft_printf("%l %l %l\n", num, INT_MIN, num - INT_MIN);
//         if (error == 0 || num > INT_MAX || num < INT_MIN)
//             ft_exit();
//         str++;
//     }
// }

static char *ft_fill_list(int argc, char **argv)
{
    char    **split;
    char    *list;
    int     flag;
    int     tam;
    int     i;

    list = "";
    flag = 0;
    tam = argc;
    while(argc > 1)
    {
        i = -1;
        split = ft_split(argv[tam - argc + 1], ' ');
        if (!split)
            ft_exit_str(list, flag);
        while (split[++i])
        {
            list = ft_strjoin_mod(list, split[i], flag);
            if (!list)
                ft_exit_mtx(split);
            flag = 1;
            free(split[i]);
        }
        free(split);
        argc--;
    }
    return (list);
}

void    ft_check_args(int argc, char **argv)
{
    char    *list;

    list = ft_fill_list(argc, argv);
    //ft_check_integer(argv[argc - 1]);
    ft_printf("%s", list);
    free(list);
}
