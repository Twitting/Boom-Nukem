/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:23:39 by twitting          #+#    #+#             */
/*   Updated: 2018/12/12 14:01:33 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countnum(unsigned int n)
{
	int	i;

	i = 1;
	if (n >= 10)
		i = i + ft_countnum(n / 10);
	return (i);
}

static char	*ft_makestr(unsigned int n, int len, char *str)
{
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = (char)(n % 10) + '0';
		n /= 10;
		len--;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				neg;
	unsigned int	num;

	len = 0;
	neg = 0;
	if (n < 0)
	{
		num = -1 * n;
		len++;
		neg = 1;
	}
	else
		num = n;
	len = len + ft_countnum(num);
	if (!(str = (char *)malloc(len + 1)))
		return (NULL);
	str = ft_makestr(num, len, str);
	if (neg == 1)
		str[0] = '-';
	return (str);
}
