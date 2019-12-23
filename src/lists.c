/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 22:25:33 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 22:25:36 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_elm	*elm_new(char *str)
{
	t_elm *head;

	if (!(head = (t_elm *)malloc(sizeof(t_elm))))
		return (NULL);
	head->data = str;
	head->next = NULL;
	return (head);
}

t_conn	*conn_new(t_room **adr, t_room *prnt)
{
	t_conn *new;

	if (!(new = (t_conn *)ft_memalloc(sizeof(t_conn))))
		return (NULL);
	new->ptr = *adr;
	new->next = NULL;
	new->prev = NULL;
	new->parent = prnt;
	return (new);
}

void	elm_add_end(t_elm **head, t_elm **tmp, char *str)
{
	if (!*head)
	{
		*head = elm_new(str);
		*tmp = *head;
	}
	else
	{
		(*tmp)->next = elm_new(str);
		*tmp = (*tmp)->next;
	}
}

void	connect_add_end(t_conn **conn, t_conn **tmp_conn, t_room **elm,
		t_room *prnt)
{
	if (!*conn)
	{
		*conn = conn_new(&*elm, prnt);
		*tmp_conn = *conn;
	}
	else
	{
		(*tmp_conn)->next = conn_new(&*elm, prnt);
		(*tmp_conn)->next->flags = g_flg;
		(*tmp_conn)->next->prev = *tmp_conn;
		*tmp_conn = (*tmp_conn)->next;
	}
}

void	connect_add_start(t_conn **conn, t_room **elm)
{
	t_conn *tmp;

	if (!*conn)
		*conn = conn_new(&*elm, NULL);
	else
	{
		tmp = conn_new(&*elm, NULL);
		tmp->next = *conn;
		tmp->next->prev = tmp;
		*conn = tmp;
	}
}
