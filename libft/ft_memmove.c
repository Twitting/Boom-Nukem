/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:54:31 by twitting          #+#    #+#             */
/*   Updated: 2018/12/12 14:07:28 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	count;

	count = len;
	if (!dst && !src)
		return (NULL);
	while (count > 0)
	{
		count--;
		if (dst > src)
			((unsigned char *)dst)[count] = ((unsigned char *)src)[count];
		else if (dst == src)
			break ;
		else
		{
			i = len - count - 1;
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	}
	return (dst);
}
