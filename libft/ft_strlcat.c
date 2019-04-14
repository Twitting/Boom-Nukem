/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:21:15 by twitting          #+#    #+#             */
/*   Updated: 2018/12/12 14:16:59 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ret;

	i = 0;
	j = 0;
	if (size >= ft_strlen(dst))
		ret = ft_strlen(dst) + ft_strlen(src);
	else
		ret = size + ft_strlen(src);
	while (dst[i] != '\0')
		i++;
	while (size - 1 > i && src[j] != '\0' && size != 0)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (ret);
}
