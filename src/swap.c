/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:45:20 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 21:45:24 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static short	swap_if_coincide(t_conn **head, t_conn **tail)
{
	t_way	*tmp;
	t_conn	*tmp_way;
	t_conn	*swap;

	tmp = g_lst.ways;
	while (tmp)
	{
		tmp_way = tmp->way;
		while (tmp_way->next)
		{
			if ((*tail)->ptr == tmp_way->ptr
			&& (*head)->ptr == tmp_way->next->ptr)
			{
				swap = *tail;
				(*head)->next = tmp_way->next->next;
				tmp_way->next = swap->next;
				(!g_lst.trash) ? (g_lst.trash = swap) :
				(g_lst.trash->next = swap);
				return (1);
			}
			tmp_way = tmp_way->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

static void		connect_chain(t_conn **one, t_conn **trav)
{
	t_conn *tmp;
	t_conn *save;
	t_conn *current;

	tmp = *one;
	save = (*one)->prev;
	while (tmp != *trav)
	{
		current = tmp;
		tmp = tmp->next;
		!g_lst.trash ? (g_lst.trash = current)
		: (g_lst.trash->next = current);
	}
	save->next = *trav;
}

static short	check_same_connections(t_way *tmp_ways)
{
	t_conn	*tmp_one_way;
	t_conn	*trav;
	t_conn	*one;

	while (tmp_ways != NULL)
	{
		tmp_one_way = tmp_ways->way;
		while (tmp_one_way->next != NULL)
		{
			one = tmp_one_way;
			trav = tmp_one_way->next;
			while (trav != NULL)
			{
				if (one->ptr == trav->ptr)
				{
					connect_chain(&one, &trav);
					return (1);
				}
				trav = trav->next;
			}
			tmp_one_way = tmp_one_way->next;
		}
		tmp_ways = tmp_ways->next;
	}
	return (0);
}

short			swap_ways(void)
{
	t_way	*tmp;
	t_conn	*tmp_way;

	tmp = g_lst.ways;
	while (tmp)
	{
		tmp_way = tmp->way;
		while (tmp_way->next)
		{
			if (swap_if_coincide(&tmp_way, &tmp_way->next))
			{
				check_same_connections(g_lst.ways);
				return (1);
			}
			tmp_way = tmp_way->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

void			count_ways_len(void)
{
	t_way	*tmp;
	t_conn	*way;

	tmp = g_lst.ways;
	g_lst.copy_flag == 1 ? tmp = g_lst.copy : 0;
	while (tmp)
	{
		way = tmp->way;
		tmp->len = 0;
		tmp->use_len = tmp->len;
		while (way->next)
		{
			tmp->len += 1;
			tmp->use_len = tmp->len;
			way = way->next;
		}
		tmp = tmp->next;
	}
}
