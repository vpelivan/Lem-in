/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 21:36:50 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/06 21:36:53 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*next_room(t_room *rm)
{
	t_way	*tmp;
	t_conn	*trav;
	short	i;

	i = 1;
	tmp = g_lst.ways;
	if (rm->viz == 0)
		return (NULL);
	while (i != rm->viz)
	{
		tmp = tmp->next;
		i++;
	}
	trav = tmp->way;
	while (trav->next)
	{
		if (trav->ptr == rm)
			return (trav->next->ptr);
		trav = trav->next;
	}
	return (NULL);
}

static t_room	*previous_room(t_room *rm)
{
	t_way	*tmp;
	t_conn	*trav;
	short	i;

	i = 1;
	tmp = g_lst.ways;
	while (i != rm->viz)
	{
		tmp = tmp->next;
		i++;
	}
	trav = tmp->way;
	while (trav->next)
	{
		if (trav->next->ptr == rm)
			return (trav->ptr);
		trav = trav->next;
	}
	return (NULL);
}

static short	select_flag(t_room *rm, t_conn *trav)
{
	t_conn *head;

	head = g_lst.buff;
	while (head)
	{
		if (head->ptr == rm && head->flags != 1)
			return (-1);
		head = head->next;
	}
	if (trav && trav->flags == 1 && previous_room(trav->ptr) != rm)
		return (-1);
	if (trav && trav->flags == 0 && next_room(trav->ptr) == rm)
		return (-1);
	if (rm->viz)
	{
		if (trav->prev == NULL)
			return (-1);
		if (rm->viz != trav->ptr->viz)
			return (1);
	}
	return (0);
}

static void		operate(void)
{
	find_shortest_way();
	free_conn(&g_lst.buff);
}

short			dpf_search(void)
{
	t_conn	*fast;
	t_conn	*buff;
	t_conn	*tmp;

	connect_add_end(&g_lst.buff, &fast, &g_lst.start, NULL);
	buff = g_lst.buff;
	while (buff != NULL)
	{
		tmp = buff->ptr->conn;
		while (tmp != NULL)
		{
			g_flg = select_flag(tmp->ptr, buff);
			if (g_flg == 0 || g_flg == 1)
				connect_add_end(&g_lst.buff, &fast, &tmp->ptr, buff->ptr);
			if (tmp->ptr == g_lst.end && g_flg != -1)
			{
				operate();
				return (1);
			}
			tmp = tmp->next;
		}
		buff = buff->next;
	}
	free_conn(&g_lst.buff);
	return (0);
}
