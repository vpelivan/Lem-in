/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antwalk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 22:45:26 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 22:45:29 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				measure_effect(void)
{
	int		i;
	t_ant	*ants;

	i = 0;
	count_ways_len();
	ways_sort_by_len(NULL, NULL);
	get_ant_ways();
	ants = g_lst.ant;
	while (ants)
	{
		if (ants->use_len > i)
			i = ants->use_len;
		ants = ants->next;
	}
	return (i);
}

static int		check_room_free(t_room *rm)
{
	t_ant *tmp;

	tmp = g_lst.ant;
	while (tmp)
	{
		if (tmp->way->ptr == rm && rm != g_lst.end)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void			start_ant_walk(void)
{
	t_ant	*tmp;
	int		i;

	while (1)
	{
		i = 0;
		tmp = g_lst.ant;
		while (tmp)
		{
			if (tmp->way->next && check_room_free(tmp->way->next->ptr))
			{
				tmp->way = tmp->way->next;
				i++ != 0 ? ft_printf(" L%i-%s", tmp->ant, tmp->way->ptr->name)
				: ft_printf("L%i-%s", tmp->ant, tmp->way->ptr->name);
			}
			tmp = tmp->next;
		}
		if (!i)
			break ;
		ft_printf("\n");
		g_steps++;
	}
	g_lst.steps == 1 ? comment_print(g_lst.map_head) : 0;
}
