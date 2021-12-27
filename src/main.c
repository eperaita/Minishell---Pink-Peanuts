/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:50:16 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/27 17:07:47 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

/*
 * 1. PASO = INIT -> 
 * 		-crear la estructura
 * 		-inicializarla a 0 
 * 		-crear el environment (GET_ENVIRONMENT)
 * 2. PASO = CREATE_TERMINAL ->
 * 		-crear la terminal
 * 		2. 1 ->Dentro de CREAT_TERMINAL -> analizar el comando que nos han pasado
 * 		*/

int main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	(void)argc;
	(void)argv;
	if (init(&shell, env))
		return (1);
	create_terminal(shell);
	return (0);
}
