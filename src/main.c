/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:46:29 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 21:46:32 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error(char *str)
{
	ft_printf("%s\n", "ERROR");
	(g_lst.extend_val == 1) ? ft_printf("{red}%s{eoc}\n", str) : 0;
	exit(1);
}

void	ways_sort_by_len(t_way *tmp, t_conn *swap_way)
{
	int swap_len;
	int swap_use_len;

	tmp = g_lst.ways;
	g_lst.copy_flag == 1 ? tmp = g_lst.copy : 0;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		if (tmp->len > tmp->next->len)
		{
			swap_way = tmp->way;
			swap_len = tmp->len;
			swap_use_len = tmp->use_len;
			tmp->way = tmp->next->way;
			tmp->len = tmp->next->len;
			tmp->use_len = tmp->next->use_len;
			tmp->next->way = swap_way;
			tmp->next->len = swap_len;
			tmp->next->use_len = swap_use_len;
			tmp = g_lst.ways;
			g_lst.copy_flag == 1 ? tmp = g_lst.copy : 0;
		}
		tmp = tmp->next;
	}
}

int		main(int ac, char **av)
{
	init_data();
	set_bonus_flags(ac, av);
	validate_map();
	elm_print(g_lst.map_head);
	if (g_lst.bfs_flag == 1)
		start_bfs();
	else
		start_dpf();
	count_ways_len();
	ways_sort_by_len(NULL, NULL);
	measure_effect();
	start_ant_walk();
	g_lst.graph_print ? graph_print() : 0;
	g_lst.way_print ? print_ways() : 0;
	return (0);
}
