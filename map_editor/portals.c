/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:33:33 by twitting          #+#    #+#             */
/*   Updated: 2019/04/03 17:18:14 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

int		getsecondvert(t_edit *edit, int x, int y)
{
	int		i;

	i = 0;
	while (i < edit->glvertnum)
	{
		if (edit->verts[i].x == x && edit->verts[i].y == y)
		{
			PVERT2 = i;
			break ;
		}
		i++;
	}
	if (PVERT2 >= 0)
		return (1);
	return (0);
}

void	makeportals2(t_edit *edit)
{
	int x;
	int y;

	SDL_GetMouseState(&x, &y);
	x = (x + 12) / 25 * 25;
	y = (y + 12) / 25 * 25;
	if (getsecondvert(edit, x / 25 * 10, y / 25 * 10))
	{
		if (PVERT1 == PVERT2)
			ft_putstr("Portal cannot be set by one vertex\n");
		else
			portalcheck(edit);
	}
	else
		ft_putstr("Not a vertex\n");
}

int		getfirstvert(t_edit *edit, int x, int y)
{
	int		i;

	i = 0;
	while (i < edit->glvertnum)
	{
		if (edit->verts[i].x == x && edit->verts[i].y == y)
		{
			PVERT1 = i;
			break ;
		}
		i++;
	}
	if (PVERT1 >= 0)
		return (1);
	return (0);
}

void	makeportals1(t_edit *edit)
{
	int x;
	int y;

	portalinit(edit);
	PVERT1 = -1;
	PVERT2 = -1;
	SDL_GetMouseState(&x, &y);
	x = (x + 12) / 25 * 25;
	y = (y + 12) / 25 * 25;
	if (!(getfirstvert(edit, x / 25 * 10, y / 25 * 10)))
		ft_putstr("Not a vertex\n");
}
