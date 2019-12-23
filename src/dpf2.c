/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 22:24:48 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 22:24:51 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	clean_flags(void)
{
	t_room *graph;

	graph = g_lst.graph;
	while (graph)
	{
		graph->viz = 0;
		graph = graph->next;
	}
}

static void	set_flags(void)
{
	t_way	*curr;
	t_conn	*way;
	int		i;

	i = 1;
	clean_flags();
	curr = g_lst.ways;
	while (curr)
	{
		way = curr->way;
		while (way)
		{
			way->ptr->viz = i;
			way = way->next;
		}
		curr = curr->next;
		i++;
	}
	g_lst.start->viz = 0;
	g_lst.end->viz = 0;
}

static void	find_ways(void)
{
	t_way	*copy;
	int		prev;
	int		i;

	set_flags();
	while (dpf_search() != 0)
	{
		copy = copy_ways();
		prev = measure_effect();
		add_found_way();
		g_lst.one_way = NULL;
		free_conn(&g_lst.buff);
		while (swap_ways() != 0)
			;
		set_flags();
		i = measure_effect();
		if (prev < i)
		{
			g_lst.copy_flag = 1;
			g_lst.copy = copy;
			return ;
		}
		free_ways(&copy);
	}
}

void		start_dpf(void)
{
	dpf_search();
	if (g_lst.one_way)
	{
		add_found_way();
		count_ways_len();
		if (g_lst.ways->len == 1)
		{
			g_lst.ant = get_ant_struct();
			measure_effect();
			start_ant_walk();
			g_lst.graph_print ? graph_print() : 0;
			g_lst.way_print ? print_ways() : 0;
			exit(0);
		}
		free_conn(&g_lst.buff);
	}
	else
	{
		free_conn(&g_lst.buff);
		error("No Ways In Map");
	}
	g_lst.ant = get_ant_struct();
	find_ways();
}

void		add_found_way(void)
{
	t_way *tmp;
	t_way *head;

	head = g_lst.ways;
	if (!g_lst.ways)
	{
		g_lst.ways = (t_way *)ft_memalloc(sizeof(t_way));
		g_lst.ways->way = g_lst.one_way;
		g_lst.ways->next = NULL;
	}
	else
	{
		tmp = (t_way *)ft_memalloc(sizeof(t_way));
		tmp->way = g_lst.one_way;
		tmp->next = NULL;
		while (g_lst.ways->next != NULL)
			g_lst.ways = g_lst.ways->next;
		g_lst.ways->next = tmp;
		g_lst.ways = head;
	}
	g_lst.ways->len = 0;
	g_lst.ways->use_len = 0;
	g_lst.ways_num += 1;
}
