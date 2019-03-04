/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 11:42:57 by twitting          #+#    #+#             */
/*   Updated: 2018/11/30 14:05:06 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swapptr(void **s1, void **s2)
{
	void *temp;

	if (s1 == NULL && s2 == NULL)
		return ;
	if (s1 == NULL && s2)
		s2 = NULL;
	else if (s2 == NULL && s1)
		s1 = NULL;
	else
	{
		temp = *s1;
		*s1 = *s2;
		*s2 = temp;
	}
	temp = NULL;
}
