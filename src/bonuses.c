/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 22:12:46 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 22:12:49 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			graph_print(void)
{
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = g_lst.graph;
	while (tmp != NULL)
	{
		ft_printf("{cyan}Room number: {eoc}%i, ", ++i);
		ft_printf("{red}Room name:{eoc} %s, {blue}X:{eoc} %s, {green}Y:{eoc} "
		"%s {yellow}Room connections: {eoc}", tmp->name, tmp->x, tmp->y);
		conn_print(tmp->conn);
		ft_printf("\n");
		tmp = tmp->next;
	}
}

void			print_ways(void)
{
	t_way	*tmp;
	int		i;

	i = 0;
	tmp = g_lst.ways;
	g_lst.copy_flag == 1 ? tmp = g_lst.copy : 0;
	while (tmp)
	{
		ft_printf("{green}Way number:{eoc} %d, ", ++i);
		ft_printf("{red}Length:{eoc} %i, ", tmp->len);
		ft_printf("{yellow}Start:{eoc} ");
		conn_print(tmp->way);
		ft_printf("{yellow} End{eoc}\n");
		tmp = tmp->next;
	}
}

static void		print_usage(void)
{
	char *str;

	str = "     ";
	ft_printf("%s\n", "usage: ./lem-in [-flags] < map_file.txt\n");
	ft_printf("%s%s%s\n", "flags:\n", str,
	"-b - \"BFS Algorithm only mode\" launch");
	ft_printf("%s%s\n", str, "-l - Count Step Lines and print");
	ft_printf("%s%s\n", str, "-g - Print parsed graph");
	ft_printf("%s%s\n", str, "-w - Print found ways");
	ft_printf("%s%s\n", str, "-v - Activate extended validator");
	exit(0);
}

static short	check_arg_string(const char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'b' && str[i] != 'l' && str[i] != 'g' && str[i] != 'w'
		&& str[i] != 'v')
			return (0);
		i++;
	}
	return (1);
}

void			set_bonus_flags(int ac, char **av)
{
	if (ac >= 2)
	{
		if (ft_strcmp("--help", av[1]) == 0 || ac > 2)
			print_usage();
		else if (ac == 2)
		{
			if (av[1][0] == '-' && check_arg_string(av[1]) == 1)
			{
				ft_strstr(av[1], "b") ? (g_lst.bfs_flag = 1) : 0;
				ft_strstr(av[1], "l") ? (g_lst.steps = 1) : 0;
				ft_strstr(av[1], "g") ? (g_lst.graph_print = 1) : 0;
				ft_strstr(av[1], "w") ? (g_lst.way_print = 1) : 0;
				ft_strstr(av[1], "v") ? (g_lst.extend_val = 1) : 0;
				if (g_lst.bfs_flag == 0 && g_lst.steps == 0
				&& g_lst.graph_print == 0 && g_lst.way_print == 0
				&& g_lst.extend_val == 0)
					print_usage();
			}
			else
				print_usage();
		}
	}
}
