/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:34:18 by twitting          #+#    #+#             */
/*   Updated: 2018/11/30 15:35:28 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	temp;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	len = i;
	while (i >= (len + 1) / 2)
	{
		temp = str[len - i];
		str[len - i] = str[i];
		str[i] = temp;
		i--;
	}
	return (str);
}
