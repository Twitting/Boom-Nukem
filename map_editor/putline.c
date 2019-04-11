/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:57:26 by twitting          #+#    #+#             */
/*   Updated: 2019/04/11 20:23:56 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	putlinelow(t_edit *edit, t_line *l)
{
	int		*pix;
	int		arr[4];

	pix = edit->surface->pixels;
	arr[2] = l->y1 - l->y0;
	arr[1] = 1;
	if (arr[2] < 0)
	{
		arr[1] = -1;
		arr[2] = -arr[2];
	}
	arr[3] = 2 * arr[2] - (l->x1 - l->x0);
	arr[0] = l->x0 - 1;
	while (++arr[0] <= l->x1)
	{
		if (arr[0] >= 0 && arr[0] < WWIN && l->y0 >= 0 && l->y0 < HWIN)
			pix[l->y0 * WWIN + arr[0]] = l->color;
		if (arr[3] > 0)
		{
			l->y0 = l->y0 + arr[1];
			arr[3] = arr[3] - 2 * (l->x1 - l->x0);
		}
		arr[3] = arr[3] + 2 * arr[2];
	}
}

void	putlinehigh(t_edit *edit, t_line *l)
{
	int		*pix;
	int		arr[4];

	pix = edit->surface->pixels;
	arr[2] = l->x1 - l->x0;
	arr[1] = 1;
	if (arr[2] < 0)
	{
		arr[1] = -1;
		arr[2] = -arr[2];
	}
	arr[3] = 2 * arr[2] - (l->y1 - l->y0);
	arr[0] = l->y0 - 1;
	while (++arr[0] <= l->y1)
	{
		if (l->x0 >= 0 && l->x0 < WWIN && arr[0] >= 0 && arr[0] < HWIN)
			pix[arr[0] * WWIN + l->x0] = l->color;
		if (arr[3] > 0)
		{
			l->x0 = l->x0 + arr[1];
			arr[3] = arr[3] - 2 * (l->y1 - l->y0);
		}
		arr[3] = arr[3] + 2 * arr[2];
	}
}

t_line	*revln(t_line *l)
{
	int	tmp;

	tmp = l->x1;
	l->x1 = l->x0;
	l->x0 = tmp;
	tmp = l->y1;
	l->y1 = l->y0;
	l->y0 = tmp;
	return (l);
}

int		putline(t_edit *edit, t_line *l)
{
	if (edit == NULL || l == NULL)
		return (0);
	if ((int)fabs((double)(l->y1 - l->y0)) < (int)fabs((double)(l->x1 - l->x0)))
	{
		if (l->x0 > l->x1)
			putlinelow(edit, revln(l));
		else
			putlinelow(edit, l);
	}
	else
	{
		if (l->y0 > l->y1)
			putlinehigh(edit, revln(l));
		else
			putlinehigh(edit, l);
	}
	return (1);
}
