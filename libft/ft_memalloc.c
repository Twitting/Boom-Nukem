/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14:34:59 by twitting          #+#    #+#             */
/*   Updated: 2018/12/12 14:06:59 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*fresh;

	if (!(fresh = (unsigned char *)malloc(size)) || size == 0)
		return (NULL);
	while (size)
		((unsigned char *)fresh)[size--] = 0;
	((unsigned char *)fresh)[size] = 0;
	return (fresh);
}
