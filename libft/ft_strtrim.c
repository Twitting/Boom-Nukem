/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:11:59 by twitting          #+#    #+#             */
/*   Updated: 2018/12/12 14:22:28 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	startwsp(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	return (i);
}

static size_t	endwsp(char const *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
		i++;
	i--;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
	{
		j++;
		i--;
	}
	return (j);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	int		j;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (startwsp(s) == ft_strlen(s))
	{
		if (!(str = (char *)malloc(1)))
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (!(str = (char *)malloc(ft_strlen(s) + 1 - endwsp(s) - startwsp(s))))
		return (NULL);
	i = startwsp(s);
	while (i < (ft_strlen(s) - endwsp(s)))
		str[j++] = ((char *)s)[i++];
	str[j] = '\0';
	return (str);
}
