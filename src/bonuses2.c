/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 22:12:53 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/05 22:12:56 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	elm_print(t_elm *head)
{
	while (head != NULL)
	{
		ft_printf("%s\n", head->data);
		head = head->next;
	}
	ft_printf("\n");
}

void	conn_print(t_conn *head)
{
	t_conn *tmp;

	tmp = head;
	if (tmp)
	{
		while (tmp != NULL)
		{
			ft_printf("%s", tmp->ptr->name);
			tmp->next ? ft_printf(", ") : 0;
			tmp = tmp->next;
		}
	}
}

void	comment_print(t_elm *head)
{
	int i;

	i = 1;
	while (i)
	{
		head = head->next;
		i--;
	}
	if (ft_strstr(head->data, "#Here is the number of lines required:"))
		ft_printf("{red}%s{eoc}\n", head->data);
	ft_printf("{red}#My algorithm made it for: %i lines{eoc}\n", g_steps);
	ft_printf("\n");
}
