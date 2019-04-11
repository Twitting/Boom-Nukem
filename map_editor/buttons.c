/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:33:33 by twitting          #+#    #+#             */
/*   Updated: 2019/04/11 21:01:29 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

int		makeneighbutton(t_edit *edit, int sect1)
{
	int	i;
	int nobutton;

	i = -1;
	nobutton = 1;
	while (++i < (int)PSECT1.npoints)
		if (PSECT1.neighbors[i] == -2)
		{
			nobutton = 0;
			break ;
		}
	i = -1;
	while (++i < (int)PSECT1.npoints)
	{
		if ((PSECT1.vertex[i] == PVERT1 || PSECT1.vertex[i] == PVERT2) &&
			(PSECT1.vertex[(i + 1) % PSECT1.npoints] == PVERT1 ||
			PSECT1.vertex[(i + 1) % PSECT1.npoints] == PVERT2) &&
			PSECT1.neighbors[i] == -1 && nobutton)
		{
			PSECT1.neighbors[i] = -2;
			putportalline(edit, 0xffff00);
			return (1);
		}
	}
	return (0);
}

int		checkbuttonverts(t_edit *edit)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 64 && edit->portsects[i] != -1)
	{
		j = -1;
		while (++j < (int)PSECT.npoints)
		{
			if (PSECT.vertex[j] == PVERT1 && ((PSECT.vertex[(j + 1) %
			PSECT.npoints] == PVERT2) || (j > 0 && PSECT.vertex[j - 1] ==
			PVERT2) || (j == 0 && PSECT.vertex[PSECT.npoints - 1] == PVERT2)))
			{
				if (makeneighbutton(edit, edit->portsects[i]))
					return (1);
			}
		}
	}
	return (0);
}

void	buttoncheck(t_edit *edit)
{
	int	i;
	int	j;
	int	counter;
	int	sectcounter;

	i = -1;
	sectcounter = 0;
	while (++i < edit->sectnum)
	{
		j = -1;
		counter = 0;
		while (++j < (int)edit->sectors[i].npoints)
			if (edit->sectors[i].vertex[j] == PVERT1 ||
				edit->sectors[i].vertex[j] == PVERT2)
				counter++;
		if (counter == 2)
			edit->portsects[sectcounter++] = i;
	}
	if (checkbuttonverts(edit) == 0)
		ft_putstr("Incorrect vertexes\n");
}

void	makebutton2(t_edit *edit)
{
	int x;
	int y;

	edit->buttonflag = 0;
	SDL_GetMouseState(&x, &y);
	x = (x + 12) / 25 * 25;
	y = (y + 12) / 25 * 25;
	if (getsecondvert(edit, x / 25 * 10, y / 25 * 10))
	{
		if (PVERT1 == PVERT2)
			ft_putstr("Button cannot be set by one vertex\n");
		else
			buttoncheck(edit);
	}
	else
		ft_putstr("Not a vertex\n");
}

void	makebutton1(t_edit *edit)
{
	int x;
	int y;

	edit->buttonflag = 1;
	portalinit(edit);
	PVERT1 = -1;
	PVERT2 = -1;
	SDL_GetMouseState(&x, &y);
	x = (x + 12) / 25 * 25;
	y = (y + 12) / 25 * 25;
	if (!(getfirstvert(edit, x / 25 * 10, y / 25 * 10)))
		ft_putstr("Not a vertex\n");
}
