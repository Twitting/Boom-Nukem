/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:57:26 by twitting          #+#    #+#             */
/*   Updated: 2019/03/19 19:29:57 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	putlinelow(t_edit *edit, t_line *l)
{
	int		x;
	int		yi;
	int		dy;
	int		f;
	int		*pix;

	pix = edit->surface->pixels;
	dy = l->y1 - l->y0;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	f = 2 * dy - (l->x1 - l->x0);
	x = l->x0 - 1;
	while (++x <= l->x1)
	{
		if (x >= 0 && x < WWIN && l->y0 >= 0 && l->y0 < HWIN)
			pix[l->y0 * WWIN + x] = l->color;
		if (f > 0)
		{
			l->y0 = l->y0 + yi;
			f = f - 2 * (l->x1 - l->x0);
		}
		f = f + 2 * dy;
	}
}

void	putlinehigh(t_edit *edit, t_line *l)
{
	int		y;
	int		xi;
	int		dx;
	int		f;
	int		*pix;

	pix = edit->surface->pixels;
	dx = l->x1 - l->x0;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	f = 2 * dx - (l->y1 - l->y0);
	y = l->y0 - 1;
	while (++y <= l->y1)
	{
		if (l->x0 >= 0 && l->x0 < WWIN && y >= 0 && y < HWIN)
			pix[y * WWIN + l->x0] = l->color;
		if (f > 0)
		{
			l->x0 = l->x0 + xi;
			f = f - 2 * (l->y1 - l->y0);
		}
		f = f + 2 * dx;
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