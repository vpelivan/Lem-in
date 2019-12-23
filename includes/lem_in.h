/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 23:06:25 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 23:06:28 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"

typedef struct		s_val
{
	char			*str;
	char			**elm;
	short			start_flag;
	short			start_parse_conn;
	short			end_flag;
}					t_val;

typedef struct		s_elm
{
	char			*data;
	struct s_elm	*next;
}					t_elm;

typedef struct		s_room
{
	char			*name;
	char			*x;
	char			*y;
	short			viz;
	struct s_conn	*conn;
	struct s_conn	*tmp_conn;
	struct s_room	*next;
}					t_room;

typedef struct		s_conn
{
	t_room			*ptr;
	t_room			*parent;
	struct s_conn	*next;
	struct s_conn	*prev;
	short			flags;
}					t_conn;

typedef struct		s_way
{
	t_conn			*way;
	int				len;
	int				use_len;
	struct s_way	*next;
}					t_way;

typedef	struct		s_ant
{
	int				ant;
	int				use_len;
	t_conn			*way;

	struct s_ant	*next;
}					t_ant;

typedef struct		s_data
{
	int				ant_num;
	short			extend_val;
	short			steps;
	short			bfs_flag;
	short			graph_print;
	short			way_print;
	short			copy_flag;
	int				room_num;
	int				conn_num;
	int				ways_num;
	t_room			*start;
	t_room			*end;
	t_room			*graph;
	t_room			*tmp_graph;
	t_elm			*map_head;
	t_elm			*tmp_map_head;
	t_conn			*buff;
	t_conn			*buff_end;
	t_conn			*one_way;
	t_conn			*trash;
	t_conn			*trash_head;
	t_way			*ways;
	t_way			*copy;
	t_ant			*ant;
}					t_data;

t_data				g_lst;
t_val				g_val;
short				g_flg;
int					g_steps;

void				validate_map(void);
void				error(char *str);
void				init_val_data(void);
void				init_data(void);
void				get_start_room(void);
void				get_end_room(void);
void				get_ant_num(void);
void				check_room_str_data(void);
void				check_connect_str_data(void);
void				check_string(void);
int					check_hash(void);
void				get_room(void);
void				get_connection(void);
t_elm				*elm_new(char *str);
t_conn				*conn_new(t_room **adr, t_room *parent);
void				conn_print(t_conn *head);
void				elm_add_end(t_elm **head, t_elm **tmp, char *str);
void				elm_print(t_elm *head);
void				connect_add_end(t_conn **conn, t_conn **tmp_conn,
					t_room **elm, t_room *parent);
void				graph_print(void);
void				connect_add_start(t_conn **conn, t_room **elm);
void				start_bfs(void);
void				free_conn(t_conn **head);
void				add_found_way(void);
void				print_ways(void);
short				swap_ways(void);
void				add_end_start_room(void);
void				ways_sort_by_len(t_way *tmp, t_conn *swap_way);
void				start_ant_walk(void);
void				count_ways_len(void);
t_ant				*get_ant_struct(void);
void				get_ant_ways(void);
t_way				*copy_ways(void);
int					measure_effect(void);
short				dpf_search(void);
void				find_shortest_way(void);
void				comment_print(t_elm *head);
void				free_ways(t_way **ways);
void				set_bonus_flags(int ac, char **av);
void				start_dpf(void);
short				buff_elm_exists(t_conn *elm);
void				check_same_connect(void);
short				check_ant_str(void);
short				check_comment(void);
void				create_room(t_room **rm);
int					count_delim(char d);
#endif
