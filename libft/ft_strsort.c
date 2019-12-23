/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 22:49:32 by vpelivan          #+#    #+#             */
/*   Updated: 2019/07/06 22:49:35 by vpelivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsort(char *src)
{
	size_t i;

	i = 0;
	if (!src)
		return (NULL);
	if (ft_strlen(src) == 1)
		return (src);
	while (src[i + 1] != '\0')
	{
		if (src[i] > src[i + 1])
		{
			ft_swap(&src[i], &src[i + 1]);
			i = 0;
		}
		i++;
	}
	return (src);
}
