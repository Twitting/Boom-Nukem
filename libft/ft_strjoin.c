/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:27:25 by twitting          #+#    #+#             */
/*   Updated: 2018/12/12 14:15:45 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	if (!(str = (char *)malloc(i + j + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		*str++ = s1[i++];
	while (s2[j])
		*str++ = s2[j++];
	*str = '\0';
	return (str - i - j);
}
