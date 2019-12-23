/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 22:10:54 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 22:10:57 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_end_start_room(void)
{
	t_way	*tmp_ways;
	t_conn	*tmp;

	tmp_ways = g_lst.ways;
	while (tmp_ways)
	{
		connect_add_start(&tmp_ways->way, &g_lst.start);
		tmp = tmp_ways->way;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = conn_new(&g_lst.end, NULL);
		tmp->next->prev = tmp;
		tmp_ways = tmp_ways->next;
	}
}

short	buff_elm_exists(t_conn *elm)
{
	t_conn *buff_tmp;

	buff_tmp = g_lst.buff;
	if (!elm)
		return (0);
	while (buff_tmp != NULL)
	{
		if (buff_tmp->ptr == elm->ptr)
			return (1);
		buff_tmp = buff_tmp->next;
	}
	return (0);
}
