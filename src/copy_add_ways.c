/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_add_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 22:21:48 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 22:21:51 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_conn	*find_par(t_conn *head, t_room *rm)
{
	head = head->prev;
	while (head && head->ptr != rm)
		head = head->prev;
	return (head);
}

static void		get_frist_way_elem(t_conn **head_list, t_conn **head)
{
	(*head_list) = (t_conn *)ft_memalloc(sizeof(t_conn));
	(*head_list)->next = NULL;
	(*head_list)->prev = NULL;
	(*head_list)->ptr = (*head)->ptr;
	(*head) = find_par((*head), (*head)->parent);
}

void			find_shortest_way(void)
{
	t_conn	*head_list;
	t_conn	*buff_list;
	t_conn	*head;

	head_list = NULL;
	head = g_lst.buff;
	while (head->next)
		head = head->next;
	get_frist_way_elem(&head_list, &head);
	while (head)
	{
		buff_list = head_list;
		head_list = (t_conn*)ft_memalloc(sizeof(t_conn));
		head_list->next = buff_list;
		buff_list->prev = head_list;
		head_list->ptr = head->ptr;
		head = find_par(head, head->parent);
	}
	g_lst.one_way = head_list;
}

static t_conn	*copy_single_way(t_conn *way)
{
	t_conn *head;
	t_conn *current;

	head = NULL;
	while (way)
	{
		if (head == NULL)
		{
			head = (t_conn*)ft_memalloc(sizeof(t_conn));
			head->next = NULL;
			head->prev = NULL;
			head->ptr = way->ptr;
			current = head;
			way = way->next;
			continue ;
		}
		current->next = (t_conn*)ft_memalloc(sizeof(t_conn));
		current->prev = current;
		current = current->next;
		current->ptr = way->ptr;
		current->next = NULL;
		way = way->next;
	}
	return (head);
}

t_way			*copy_ways(void)
{
	t_way	*head;
	t_way	*tmp;
	t_way	*current;

	tmp = g_lst.ways;
	head = NULL;
	while (tmp)
	{
		if (head == NULL)
		{
			head = (t_way*)ft_memalloc(sizeof(t_way));
			head->way = copy_single_way(tmp->way);
			head->next = NULL;
			current = head;
			tmp = tmp->next;
			continue ;
		}
		current->next = (t_way*)ft_memalloc(sizeof(t_way));
		current = current->next;
		current->way = copy_single_way(tmp->way);
		current->next = NULL;
		tmp = tmp->next;
	}
	return (head);
}
