/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:00:37 by twitting          #+#    #+#             */
/*   Updated: 2018/12/12 14:18:18 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = ((char *)s)[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
