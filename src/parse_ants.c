/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 22:45:14 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 22:45:18 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_ant	*get_ant(t_ant *ant, int i)
{
	ant = (t_ant *)ft_memalloc(sizeof(t_ant));
	ant->next = NULL;
	ant->ant = i;
	ant->way = NULL;
	return (ant);
}

t_ant			*get_ant_struct(void)
{
	t_ant	*ant;
	t_ant	*head;
	int		i;

	i = 1;
	ant = NULL;
	head = NULL;
	while (i <= g_lst.ant_num)
	{
		if (!ant)
		{
			ant = get_ant(ant, i);
			head = ant;
		}
		else
		{
			while (ant->next)
				ant = ant->next;
			ant->next = get_ant(ant, i);
		}
		i++;
	}
	return (head);
}

static t_conn	*choose_ant_way(t_ant *ant)
{
	t_way	*tmp;
	t_way	*choice;
	int		i;

	tmp = g_lst.ways;
	g_lst.copy_flag == 1 ? tmp = g_lst.copy : 0;
	choice = tmp;
	i = choice->use_len;
	tmp = tmp->next;
	while (tmp)
	{
		if (i > tmp->use_len)
			choice = tmp;
		tmp = tmp->next;
	}
	choice->use_len += 1;
	ant->use_len = choice->use_len;
	return (choice->way);
}

void			get_ant_ways(void)
{
	t_ant *tmp;

	tmp = g_lst.ant;
	while (tmp)
	{
		tmp->way = choose_ant_way(tmp);
		tmp = tmp->next;
	}
}
