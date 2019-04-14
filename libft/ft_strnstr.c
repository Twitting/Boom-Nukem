/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 09:54:40 by twitting          #+#    #+#             */
/*   Updated: 2018/11/25 11:50:51 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	counter;

	counter = 1;
	if (*needle == '\0')
		return ((char*)haystack);
	while (counter <= len && *haystack != '\0')
	{
		i = 0;
		while (haystack[i] == needle[i] && (counter + i) <= len)
		{
			i++;
			if (needle[i] == '\0')
				return ((char*)haystack);
		}
		haystack++;
		counter++;
	}
	return (NULL);
}
