/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:32:28 by twitting          #+#    #+#             */
/*   Updated: 2018/12/02 11:52:40 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	if (n == 0)
		return (1);
	while (i < n && (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	if (i == n)
		i--;
	if ((unsigned char)s1[i] - (unsigned char)s2[i] == 0)
		return (1);
	else
		return (0);
}
