/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:13:00 by twitting          #+#    #+#             */
/*   Updated: 2018/12/12 14:18:04 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s[j] != c && s[j] != '\0')
		i++;
	while (s[j] != c && s[j] != '\0')
	{
		j++;
		while (s[j] == c)
		{
			j++;
			if (s[j] != c && s[j] != '\0')
				i++;
		}
	}
	return (i);
}

static char	*ft_word(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (*s == c)
		s++;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (!(word = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	ft_wordlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_cleanarr(char **arr, int i)
{
	while (i > 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		wordamount;

	if (s == NULL)
		return (NULL);
	i = -1;
	while (*s == c)
		s++;
	wordamount = ft_countwords(s, c);
	if (!(arr = (char **)malloc(sizeof(char *) * (wordamount + 1))))
		return (NULL);
	while (++i < wordamount)
	{
		if (!(arr[i] = ft_word(s, c)))
		{
			ft_cleanarr(arr, i);
			return (NULL);
		}
		while (*s == c)
			s++;
		s = s + ft_wordlen(arr[i]) + 1;
	}
	arr[i] = 0;
	return (arr);
}
