/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 22:25:01 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/06 22:25:03 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		get_start_room(void)
{
	if (g_val.start_flag > 0)
		error("Start Command Already Exists!\n");
	get_next_line(0, &g_val.str);
	if (!*g_val.str)
		error("Empty lines in map!\n");
	elm_add_end(&g_lst.map_head, &g_lst.tmp_map_head, g_val.str);
	while (g_val.str[0] == '#')
	{
		(check_hash() != 0) ? error("Only Room Data Or Comments Are Allowed"
		" After ##Start Command!\n") : 0;
		get_next_line(0, &g_val.str);
		if (!*g_val.str)
			error("Empty lines in map!\n");
		elm_add_end(&g_lst.map_head, &g_lst.tmp_map_head, g_val.str);
	}
	check_string();
	g_lst.start = g_lst.tmp_graph;
	g_val.start_flag += 1;
}

void		get_end_room(void)
{
	if (g_val.end_flag > 0)
		error("End Command Already Exists!\n");
	get_next_line(0, &g_val.str);
	if (!*g_val.str)
		error("Empty lines in map!\n");
	elm_add_end(&g_lst.map_head, &g_lst.tmp_map_head, g_val.str);
	while (g_val.str[0] == '#')
	{
		(check_hash() != 0) ? error("Only Room Data Or Comments Are Allowed"
		" After ##End Command!\n") : 0;
		get_next_line(0, &g_val.str);
		if (!*g_val.str)
			error("Empty lines in map!\n");
		elm_add_end(&g_lst.map_head, &g_lst.tmp_map_head, g_val.str);
	}
	check_string();
	g_lst.end = g_lst.tmp_graph;
	g_val.end_flag += 1;
}

void		get_ant_num(void)
{
	if (g_val.str[0] != '#' && !check_ant_str())
		error("Wrong Ant Quantity String Or Forbidden String Above Ant"
		" Quantity!\n");
	while (g_val.str[0] == '#')
	{
		if (check_comment() != 0)
		{
			error("Only Comments And Non Start/End Commands Are Allowed"
			" Before Ant Number!\n");
		}
		get_next_line(0, &g_val.str);
		(!*g_val.str) ? error("Empty lines in map!\n") : 0;
		if (g_val.str[0] != '#' && !check_ant_str())
			error("The Ant Quantity String Is Missing Or Forbidden String"
			" Is In Map Or Wrong Ant Quantity String Format!\n");
		elm_add_end(&g_lst.map_head, &g_lst.tmp_map_head, g_val.str);
	}
	if (!*g_val.str)
		error("Empty lines in map!\n");
	if (!check_ant_str())
		error("The Ant Quantity String Is Missing Or Wrong Format!\n");
	g_lst.ant_num = ft_atoi(g_val.str);
	(g_lst.ant_num < 0) ? error("Ant Quantity Can't Be Negative!\n") : 0;
	(g_lst.ant_num == 0) ? error("Ant Quantity Can't Be Zero!\n") : 0;
	(g_lst.ant_num > 3000000) ? error("Too many ants!\n") : 0;
}

void		get_room(void)
{
	t_room	*rm;

	check_room_str_data();
	create_room(&rm);
	if (!g_lst.graph)
	{
		g_lst.graph = rm;
		g_lst.tmp_graph = g_lst.graph;
	}
	else
	{
		g_lst.tmp_graph->next = rm;
		g_lst.tmp_graph = g_lst.tmp_graph->next;
	}
}

void		get_connection(void)
{
	t_room	*tmp;
	t_room	*room1;
	t_room	*room2;

	room1 = NULL;
	room2 = NULL;
	check_connect_str_data();
	tmp = g_lst.graph;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, g_val.elm[0]) == 0)
			room1 = tmp;
		if (ft_strcmp(tmp->name, g_val.elm[1]) == 0)
			room2 = tmp;
		tmp = tmp->next;
	}
	if (!room1 || !room2)
		error("Room In Connection Doesn't Exist");
	connect_add_end(&(*room1).conn, &(*room1).tmp_conn, &room2, NULL);
	connect_add_end(&(*room2).conn, &(*room2).tmp_conn, &room1, NULL);
	check_same_connect();
	ft_free_tab(g_val.elm);
}
