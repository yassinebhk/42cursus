/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:45:21 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/14 17:34:21 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

typedef enum e_builtins
{
	e_echo,
	e_cd, 
	e_pwd, 
	e_export, 
	e_unset, 
	e_env, 
	e_exit
}			t_builtins;


