/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:47:44 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 21:47:47 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_val_data(void)
{
	g_val.str = NULL;
	g_val.elm = NULL;
	g_val.start_parse_conn = 0;
	g_val.start_flag = 0;
	g_val.end_flag = 0;
}

void	init_data(void)
{
	g_lst.extend_val = 0;
	g_lst.steps = 0;
	g_lst.bfs_flag = 0;
	g_lst.graph_print = 0;
	g_lst.way_print = 0;
	g_lst.ant_num = 0;
	g_lst.room_num = 0;
	g_lst.conn_num = 0;
	g_lst.ways_num = 0;
	g_lst.map_head = NULL;
	g_lst.tmp_map_head = NULL;
	g_lst.start = NULL;
	g_lst.end = NULL;
	g_lst.graph = NULL;
	g_lst.tmp_graph = NULL;
	g_lst.buff = NULL;
	g_lst.buff_end = NULL;
	g_lst.ways = NULL;
	g_lst.copy = NULL;
	g_lst.copy_flag = 0;
	g_lst.trash = NULL;
	g_lst.trash_head = g_lst.trash;
	g_lst.one_way = NULL;
	g_flg = 0;
	g_steps = 0;
}

void	free_conn(t_conn **head)
{
	t_conn *current;
	t_conn *curr_free;

	current = *head;
	while (current)
	{
		curr_free = current;
		current = current->next;
		free(curr_free);
	}
	*head = NULL;
}

void	free_ways(t_way **ways)
{
	t_way *trav;
	t_way *to_free;

	trav = *ways;
	while (trav)
	{
		to_free = trav;
		trav = trav->next;
		free_conn(&to_free->way);
		free(to_free);
	}
	*ways = NULL;
}
