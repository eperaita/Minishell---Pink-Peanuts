/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/19 11:40:07 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//GET_CHILD_INFO -> Madre hace todas las siguientes funciones para pasar a ada hijo su t_ch (array de order y infiles y outfiles)

//COUNT_PIQUITOS -> Numero de infiles y oufiles para hacer malloc de cada t_piquito
//CHOP_ORDER + CHOP_FILE_INFO -> Substrae del order los infiles
//GET_REAL_COMMAND -> Se queda con los comandos LIMPIOS en un array. 

#include "../include/minishell.h"

void    count_piquitos(int *nbr_file, char c, t_piquito **file_t, char *order) 
{
	int i;
	char **file;
  
   	file = ft_split_2(order, c, nbr_file);
	i = -1;
	free_double(file, 2);
	(*file_t) = (t_piquito *)ft_calloc(sizeof(t_piquito), (*nbr_file + 1));
	if (!(*file_t))
		status_error(strerror(errno), errno);
	i = -1;
	while (++i < *nbr_file)
		(*file_t)[i].type = 1;
}


void	chop_files(t_ch *ch, char c, char no_c, int *i, char *order) //sobra 1 
{
	int type;
	int start;

	start = 0;
	if  (order[++*i] && order[*i] ==  c)
	{
		type = 2;
		*i += 1;
	}
	while (order[*i] && order[*i] == 32)
		*i += 1;
	start = *i;
	while (order[*i] && order[*i] != 32 && order[*i] != no_c) 
		*i = *i +1;
	if (c == '<')
	{
		ch->infile_t[ch->index_in].file_name
			= ft_substr(order, start, *i - start); 
		ch->infile_t[ch->index_in++].type = type;
	}
	else
	{
		ch->outfile_t[ch->index_out].file_name
			= ft_substr(order, start, *i - start);
		ch->outfile_t[ch->index_out++].type = type;
	}
}

char	*chop_command(t_ch *ch, int *i, char *order)
{
	int		start;
	char	*temp;
	char	*real_temp;

	start = *i;
	real_temp = NULL;
	while (order[*i] && order[*i] != '<' && order[*i] != '>')
	{
		check_quotes(order, i);
		*i += 1;
	}
	temp = ft_substr(order, start, *i - start);
	if (!ch->command_group)
		real_temp  = ft_strdup(temp);
	else
		real_temp = ft_strjoin(ch->command_group,temp);

	free(temp);
	return (real_temp);
}

void	classify_order(t_ch *ch, char *order)
{
    int i;

	i = 0;
	if (!order)
		return ;
    while (order[i])
    {
		while (order[i] && order[i] == 32)
			i++;
        if (order[i] && order[i] ==  '<')// INFILES
			chop_files(ch, '<', '>', &i, order);
		else if (order[i] && order[i] == '>') //OUTFILES
			chop_files(ch, '>', '<', &i, order);
        else //COMMAND
			ch->command_group = chop_command(ch, &i, order);
    }
}

void	get_child_info(t_shell *shell) 
{
	int i;

	i = -1;
    shell->my_pro->child = (t_ch *)ft_calloc(sizeof(t_ch),
			shell->my_pro->nbr_process);
	if (!shell->my_pro->child)
		status_error(strerror(errno), errno);
    while (++i < shell->my_pro->nbr_process)
	{
		count_piquitos( &shell->my_pro->child[i].nbr_infile, '<',
				&shell->my_pro->child[i].infile_t, shell->my_pro->orders[i]);
    	count_piquitos(&shell->my_pro->child[i].nbr_outfile, '>',
				&shell->my_pro->child[i].outfile_t, shell->my_pro->orders[i]);
		classify_order(&shell->my_pro->child[i], shell->my_pro->orders[i]);
		shell->my_pro->child[i].command_split
			= ft_split_2(shell->my_pro->child[i].command_group,
					' ', &shell->my_pro->child[i].nbr_command); 
		count_nbr_commands(&shell->my_pro->child[i]);
		clean_commands(shell, &shell->my_pro->child[i]);
		if (shell->my_pro->child[i].command_split
				&& shell->my_pro->nbr_process == 1)
			check_builtins_mother(&shell, i);	
	}	
}
