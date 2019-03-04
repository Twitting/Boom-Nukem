/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:24:43 by twitting          #+#    #+#             */
/*   Updated: 2018/11/25 11:52:27 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;

	if (*needle == '\0')
		return ((char*)haystack);
	while (*haystack != '\0')
	{
		i = 0;
		while (haystack[i] == needle[i])
		{
			i++;
			if (needle[i] == '\0')
				return ((char*)haystack);
		}
		haystack++;
	}
	return (NULL);
}
