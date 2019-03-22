/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:16:17 by twitting          #+#    #+#             */
/*   Updated: 2019/03/22 17:49:37 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	portalinit(t_edit *edit)
{
	int	i;

	i = -1;
	while (++i < 64)
		edit->portsects[i] = -1;
}

void	showvertex(t_edit *edit, t_sector sect)
{
	int				*pix;
	int				i;
	int				j;
	unsigned int	k;

	pix = edit->surface->pixels;
	k = 0;
	while (k <= sect.npoints)
	{
		i = -5;
		while (i < 5)
		{
			j = -5;
			while (j < 5)
			{
				pix[((edit->verts[sect.vertex[k]].y * 25 / 10) + j) * WWIN +
					(edit->verts[sect.vertex[k]].x * 25 / 10) + i] = 0xffffff;
				j++;
			}
			i++;
		}
		k++;
	}
}

int		addvertex(t_edit *edit, int x, int y)
{
	unsigned int	i;

	if (SECT.npoints > 2 && edit->verts[SECT.vertex[0]].x == x && edit->verts[SECT.vertex[0]].y == y)
		{
			ft_putnbr(edit->sectnum);
			ft_putstr(" sector created\n");
			SECT.finished = 1;
			edit->vertnum = 0;
			edit->sectnum++;
			edit->put = 0;
			return (1);
		}
	i = 0;
	while (i < SECT.npoints)
	{
		if (x == edit->verts[SECT.vertex[i]].x && y == edit->verts[SECT.vertex[i]].y)
			{
				ft_putstr("wrong vertex\n");

				edit->nowln.x0 = edit->nowln.x1; // strange things because of putline x0-x1 inversions
				edit->nowln.y0 = edit->nowln.y1;
				return (0);
			}
		i++;
	}
	i = 0;
	while ((int)i < edit->glvertnum)
	{
		if (edit->verts[i].x == x && edit->verts[i].y == y)
		{
			SECT.vertex[edit->vertnum] = i;
			i = 1000000;
			break;
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
	showvertex(edit, SECT);
	edit->put = 1;
	SECT.npoints++;
	edit->vertnum++;
	return (1);
}

/*RB click on vertex, which belongs to two sectors, then 
RB click on another vertex, which belongs two previous sectors
and is next to first vertex in both sectors*/

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

int		checknearverts2(t_edit *edit, int first)
{
	int	i;
	int	j;

	i = 0;
	while (i < 64 && edit->portsects[i] != -1)
	{
		j = 0;
		while (i != first && j < (int)PSECT.npoints)
		{
			if (PSECT.vertex[j] == PVERT1 &&
				((PSECT.vertex[(j + 1) % PSECT.npoints] == PVERT2) ||
				(j > 0 && PSECT.vertex[j - 1] == PVERT2) ||
				(j == 0 && PSECT.vertex[PSECT.npoints - 1] == PVERT2)))
					return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void	makeneighbors(t_edit *edit, int sect1, int sect2)
{
	int	i;

	i = -1;
	while (++i < (int)PSECT1.npoints)
	{
		if ((PSECT1.vertex[i] == PVERT1 || PSECT1.vertex[i] == PVERT2) &&
			(PSECT1.vertex[(i + 1) % PSECT1.npoints] == PVERT1 ||
			PSECT1.vertex[(i + 1) % PSECT1.npoints] == PVERT2))
			{
				PSECT1.neighbors[i] = sect2;
			}
	}
	i = -1;
	while (++i < (int)PSECT2.npoints)
	{
		if ((PSECT2.vertex[i] == PVERT1 || PSECT2.vertex[i] == PVERT2) &&
			(PSECT2.vertex[(i + 1) % PSECT2.npoints] == PVERT1 ||
			PSECT2.vertex[(i + 1) % PSECT2.npoints] == PVERT2))
			{
				PSECT2.neighbors[i] = sect1;
			}
	}
	printf("PORTAL: Sect1:%d, Sect2:%d, vert1:%d, vert2:%d\n", sect1, sect2, PVERT1, PVERT2);
}

int		checknearverts(t_edit *edit)
{
	int	i;
	int	j;
	int	check2;

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
					if ((check2 = checknearverts2(edit, i)) != -1)
					{
						makeneighbors(edit, edit->portsects[i],
							edit->portsects[check2]);
						return (1);
					}
				}
		}
	}
	return (0);
}

void	portalcheck(t_edit *edit)
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
	if (checknearverts(edit) == 0)
		ft_putstr("Incorrect vertexes\n");
}

void	makeportals2(t_edit *edit)
{
	int x;
	int y;

	SDL_GetMouseState(&x,&y);
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

void	makeportals1(t_edit *edit)
{
	int x;
	int y;

	portalinit(edit);
	PVERT1 = -1;
	PVERT2 = -1;
	SDL_GetMouseState(&x,&y);
	x = (x + 12) / 25 * 25;
	y = (y + 12) / 25 * 25;
	if (!(getfirstvert(edit, x / 25 * 10, y / 25 * 10)))
		ft_putstr("Not a vertex\n");
}

void	putsectors(t_edit *edit)
{
	int x;
	int y;

	SDL_GetMouseState(&x,&y);
	x = (x + 12) / 25 * 25;
	y = (y + 12) / 25 * 25;
	if (edit->put == 1)
	{
		edit->nowln.x1 = x;
		edit->nowln.y1 = y;
		if (edit->put == 1)
			putline(edit, &edit->nowln);
		edit->put = 0;
	}
	if (edit->put == 0)
	{
		edit->nowln.x0 = x;
		edit->nowln.y0 = y;
		edit->put = 1;
		addvertex(edit, x / 25 * 10, y / 25 * 10);
	}
}

void	handle_events(t_edit *edit, SDL_Event *e)
{
	
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			edit->quit = 1;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
			edit->quit = 1;
		if (e->type == SDL_TEXTINPUT)
			ft_putnbr(atoi(e->text.text));
		if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT)
			putsectors(edit);
		if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_RIGHT)
			makeportals2(edit);
		if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_RIGHT)
			makeportals1(edit);
		
		
		//if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
		//	SDL_StartTextInput;
		//if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
		//	SDL_StopTextInput;
	}
	
	//ft_putstr(e->text.text);
}

int		main(void)
{
	t_edit		*edit;
	SDL_Event	e;
	int			i;

	edit = init();
	while (edit->quit == 0)
	{
		SDL_UpdateWindowSurface(edit->window);
		handle_events(edit, &e);
	}
	i = 0;
	while (edit->sectors[i].npoints != 0)
	{
		if (edit->sectors[i].finished == 0)
		{
			i++;
			continue;
		}
		printf("Sector %d: npoints: %d\n", i, edit->sectors[i].npoints);
		for (unsigned int j = 0; j < edit->sectors[i].npoints; j++)
		{
			printf("v %d: x = %d, y = %d,	neighbor: %d\n", edit->sectors[i].vertex[j], edit->verts[edit->sectors[i].vertex[j]].x, edit->verts[edit->sectors[i].vertex[j]].y, edit->sectors[i].neighbors[j]);
		}
		i++;
	}
	return (0);
}