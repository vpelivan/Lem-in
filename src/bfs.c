/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 22:10:08 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 22:10:10 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		bf_search(t_conn *tmp, t_conn *tmp_bf)
{
	connect_add_end(&g_lst.buff, &tmp_bf, &g_lst.start, NULL);
	tmp = g_lst.buff;
	while (tmp != NULL)
	{
		tmp->ptr->tmp_conn = tmp->ptr->conn;
		while (tmp->ptr->tmp_conn != NULL)
		{
			if (buff_elm_exists(tmp->ptr->tmp_conn) == 1)
			{
				tmp->ptr->tmp_conn = tmp->ptr->tmp_conn->next;
				continue ;
			}
			if (tmp->ptr->tmp_conn->ptr->viz == 0)
				connect_add_end(&tmp, &tmp_bf, &tmp->ptr->tmp_conn->ptr, NULL);
			if (tmp->ptr->tmp_conn->ptr == g_lst.end)
			{
				g_lst.buff_end = tmp->ptr->tmp_conn;
				connect_add_end(&tmp, &tmp_bf, &tmp->ptr->tmp_conn->ptr, NULL);
				return ;
			}
			tmp->ptr->tmp_conn = tmp->ptr->tmp_conn->next;
		}
		tmp = tmp->next;
	}
}

static void		find_bfs_way(void)
{
	t_conn *trav;
	t_conn *end;

	trav = g_lst.buff;
	end = g_lst.buff_end;
	!end ? error("No Ways In Map") : 0;
	while (trav->ptr != end->ptr && trav->next != NULL)
	{
		end->ptr->tmp_conn = end->ptr->conn;
		while (end->ptr->tmp_conn != NULL)
		{
			if (end->ptr->tmp_conn->ptr == trav->ptr
				&& end->ptr->tmp_conn->ptr->viz == 0)
			{
				trav->ptr->viz = 1;
				connect_add_start(&g_lst.one_way, &trav->ptr);
				end = trav;
				trav = g_lst.buff;
				break ;
			}
			end->ptr->tmp_conn = end->ptr->tmp_conn->next;
		}
		trav = trav->next;
	}
}

static void		make_start_end_room_way(void)
{
	connect_add_start(&g_lst.one_way, &g_lst.end);
	connect_add_start(&g_lst.one_way, &g_lst.start);
	add_found_way();
	g_lst.ant = get_ant_struct();
}

static short	end_in_start_check(void)
{
	t_conn *tmp;

	tmp = g_lst.start->conn;
	while (tmp)
	{
		if (tmp->ptr == g_lst.end)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void			start_bfs(void)
{
	while (1)
	{
		if (end_in_start_check() == 1)
		{
			make_start_end_room_way();
			return ;
		}
		bf_search(NULL, NULL);
		find_bfs_way();
		if (g_lst.one_way)
			add_found_way();
		else
		{
			if (g_lst.ways)
				break ;
			(!g_lst.ways) ? error("No Ways In Map") : 0;
		}
		g_lst.one_way = NULL;
		free_conn(&g_lst.buff);
	}
	add_end_start_room();
	g_lst.ant = get_ant_struct();
}
