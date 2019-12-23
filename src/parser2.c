/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 22:29:21 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/06 22:29:23 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_same_connect(void)
{
	t_conn	*tmp;
	t_room	*graph;
	int		i;
	int		j;

	graph = g_lst.graph;
	while (graph)
	{
		i = 0;
		j = 0;
		tmp = graph->conn;
		while (tmp)
		{
			if (!ft_strcmp(g_val.elm[0], tmp->ptr->name))
				i++;
			if (!ft_strcmp(g_val.elm[1], tmp->ptr->name))
				j++;
			tmp = tmp->next;
		}
		if (i > 1 || j > 1)
			error("Same Connections Exist In Map More Than Once!\n");
		graph = graph->next;
	}
}

short	check_ant_str(void)
{
	int i;

	i = 0;
	if (g_val.str[0] == '-' || g_val.str[0] == '+')
		i++;
	while (g_val.str[i])
	{
		if (g_val.str[i] >= 48 && g_val.str[i] <= 57)
			i++;
		else
			return (0);
	}
	return (1);
}

short	check_comment(void)
{
	if (g_val.str[0] != '#' || ft_strcmp(g_val.str, "##start") == 0
		|| ft_strcmp(g_val.str, "##end") == 0)
		return (1);
	if (g_val.str[1] == '#')
	{
		if (!g_val.str[2] && ft_strlen(g_val.str) == 2)
			error("The Name For Command Doesn't Exist");
	}
	return (0);
}

void	create_room(t_room **rm)
{
	*rm = (t_room *)malloc(sizeof(t_room));
	(*rm)->name = g_val.elm[0];
	(*rm)->x = g_val.elm[1];
	(*rm)->y = g_val.elm[2];
	(*rm)->viz = 0;
	(*rm)->conn = NULL;
	(*rm)->tmp_conn = NULL;
	(*rm)->next = NULL;
	free(g_val.elm);
}
