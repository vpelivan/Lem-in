/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 22:21:12 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/06 22:21:15 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	check_coords(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+' || !ft_isdigit(str[i]))
			error("Using Forbidden Symbols In Coordinate Numbers!\n");
		i++;
	}
}

void		check_room_str_data(void)
{
	int		i;
	t_room	*graph;

	i = 0;
	graph = g_lst.graph;
	(count_delim(32) != 2) ? error("Wrong Number of spaces!\n") : 0;
	while (g_val.elm[0][i])
	{
		if (g_val.elm[0][i] == 'L' || g_val.elm[0][i] == '-'
			|| g_val.elm[0][i] == '#')
			error("Forbidden Symbols In Room Name!\n");
		i++;
	}
	check_coords(g_val.elm[1]);
	check_coords(g_val.elm[2]);
	while (graph)
	{
		if (!ft_strcmp(graph->name, g_val.elm[0]))
			error("Using Same Names In Different Rooms!\n");
		if (!ft_strcmp(graph->x, g_val.elm[1])
			&& !ft_strcmp(graph->y, g_val.elm[2]))
			error("Using Same Coordinates In Different Rooms!\n");
		graph = graph->next;
	}
}

void		check_connect_str_data(void)
{
	int	i;

	i = 0;
	(count_delim(45) != 1) ? error("Wrong Number of minuses!\n") : 0;
	while (g_val.elm[0][i])
	{
		if (g_val.elm[0][i] == 'L' || g_val.elm[0][i] == '-'
			|| g_val.elm[0][i] == '#')
			error("Forbidden Symbols In Connection Name!\n");
		i++;
	}
}

int			count_delim(char d)
{
	int	i;
	int	delim;

	i = 0;
	delim = 0;
	while (g_val.str[i])
	{
		if (g_val.str[i] == d)
			delim++;
		i++;
	}
	return (delim);
}
