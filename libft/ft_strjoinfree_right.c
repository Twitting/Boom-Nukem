/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree_right.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:44:38 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 15:48:11 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree_right(char const *s1, char const *s2)
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
	free((char*)s2);
	return (str - i - j);
}
