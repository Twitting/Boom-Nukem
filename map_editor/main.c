/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:16:17 by twitting          #+#    #+#             */
/*   Updated: 2019/03/21 22:13:04 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

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
			edit->portvert1 = i;
			break ;//can be deleted if no vertexes with same x y 
		}
		i++;
	}
	if (edit->portvert1 >= 0)
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
			edit->portvert2 = i;
			break ;//can be deleted if no vertexes with same x y 
		}
		i++;
	}
	if (edit->portvert2 >= 0)
		return (1);
	return (0);
}

void	portalcheck(t_edit *edit)
{
	int i;
	unsigned int j;

	i = 0;
	if (edit->portvert1 == edit->portvert2)
	{
		ft_putstr("Portal can be set by two vertexes\n");
		return;
	}
	while (i < edit->sectnum)
	{
		j = 0;
		while (j < edit->sectors[i].npoints)
		{
			//STOP POINT!!!!!!!!
			j++;
		}
		i++;
	}
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
		ft_putnbr(edit->portvert2);
		ft_putstr(" portvert2\n");
		portalcheck(edit);
	}
}

void	makeportals1(t_edit *edit)
{
	int x;
	int y;

	edit->portvert1 = -1;
	edit->portvert2 = -1;
	SDL_GetMouseState(&x,&y);
	x = (x + 12) / 25 * 25;
	y = (y + 12) / 25 * 25;
	if (getfirstvert(edit, x / 25 * 10, y / 25 * 10))
	{
		ft_putnbr(edit->portvert1);
		ft_putstr(" portvert1\n");
	}
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