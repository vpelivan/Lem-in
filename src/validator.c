/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 22:15:46 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/06 22:15:58 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	check_command(void)
{
	if (!g_val.str[2] && ft_strlen(g_val.str) == 2)
		error("The Name For Command Doesn't Exist");
}

static int	count_elm_str(void)
{
	int i;

	i = 0;
	while (g_val.elm[i] && g_val.elm[i][0])
		i++;
	return (i);
}

void		check_string(void)
{
	int i;

	if (g_val.start_parse_conn == 0)
	{
		g_val.elm = ft_strsplit(g_val.str, 32);
		i = count_elm_str();
		if (i == 3)
			get_room();
		else
		{
			ft_free_tab(g_val.elm);
			g_val.start_parse_conn = 1;
		}
	}
	if (g_val.start_parse_conn == 1)
	{
		g_val.elm = ft_strsplit(g_val.str, 45);
		i = count_elm_str();
		if (i == 2)
			get_connection();
		else
			error("Wrong Format! Check spaces or Hashes!\n");
	}
}

int			check_hash(void)
{
	if (ft_strcmp(g_val.str, "##start") == 0)
	{
		get_start_room();
		return (1);
	}
	else if (ft_strcmp(g_val.str, "##end") == 0)
	{
		get_end_room();
		return (2);
	}
	else if (g_val.str[1] == '#' && g_val.str[2] != '#')
	{
		check_command();
		return (3);
	}
	return (0);
}

void		validate_map(void)
{
	init_val_data();
	while (get_next_line(0, &g_val.str) > 0)
	{
		elm_add_end(&g_lst.map_head, &g_lst.tmp_map_head, g_val.str);
		if (g_lst.ant_num == 0)
			get_ant_num();
		else if (!*g_val.str)
			error("Empty lines in map!\n");
		else if (g_val.str[0] == '#')
			check_hash();
		else
			check_string();
	}
	if (g_val.end_flag == 0)
		error("No End Room In Map!\n");
	if (g_val.start_flag == 0)
		error("No Start Room In Map!\n");
}
