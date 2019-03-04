/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:27:40 by twitting          #+#    #+#             */
/*   Updated: 2018/12/12 14:17:21 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*mapped;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (!(mapped = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapped[i] = f(s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
