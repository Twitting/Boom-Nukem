/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertexes_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:05:10 by twitting          #+#    #+#             */
/*   Updated: 2019/04/11 21:09:55 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	putdot(t_edit *edit, int color, int x, int y)
{
	int	i;
	int	j;
	int	*pix;

	pix = edit->surface->pixels;
	i = -6;
	while (++i < 5)
	{
		j = -6;
		while (++j < 5)
		{
			pix[(y + j) * WWIN + x + i] = color;
		}
	}
}

void	showvertex(t_edit *edit, t_sector sect)
{
	unsigned int	k;

	k = 0;
	while (k <= sect.npoints)
	{
		putdot(edit, 0xffffff, edit->verts[sect.vertex[k]].x * 25 / 10,
			edit->verts[sect.vertex[k]].y * 25 / 10);
		k++;
	}
}

int		checknewvertex(t_edit *edit, int x, int y)
{
	unsigned int	i;

	i = 0;
	while (i < SECT.npoints)
	{
		if (x == edit->verts[SECT.vertex[i]].x && y ==
				edit->verts[SECT.vertex[i]].y)
		{
			ft_putstr("wrong vertex\n");
			edit->nowln.x0 = edit->nowln.x1;
			edit->nowln.y0 = edit->nowln.y1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	createornot(t_edit *edit, int x, int y)
{
	int	i;

	i = 0;
	while (i < edit->glvertnum)
	{
		if (edit->verts[i].x == x && edit->verts[i].y == y)
		{
			SECT.vertex[edit->vertnum] = i;
			i = 1000000;
			break ;
		}
		i++;
	}
	if (i != 1000000)
	{
		SECT.vertex[edit->vertnum] = edit->glvertnum;
		edit->verts[edit->glvertnum].x = x;
		edit->verts[edit->glvertnum].y = y;
		edit->glvertnum++;
	}
}
