/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:16:17 by twitting          #+#    #+#             */
/*   Updated: 2019/03/21 11:17:34 by twitting         ###   ########.fr       */
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
				pix[((sect.vertex[k].y * 25 / 10) + j) * WWIN +
					(sect.vertex[k].x * 25 / 10) + i] = 0xffffff;
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

	if (SECT.npoints > 2 && SECT.vertex[0].x == x && SECT.vertex[0].y == y)
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
		if (x == SECT.vertex[i].x && y == SECT.vertex[i].y)
			{
				ft_putstr("wrong vertex\n");

				edit->nowln.x0 = edit->nowln.x1; // strange things because of putline x0-x1 inversions
				edit->nowln.y0 = edit->nowln.y1;
				return (0);
			}
		i++;
	}
	SECT.vertex[edit->vertnum].x = x;
	SECT.vertex[edit->vertnum].y = y;
	showvertex(edit, SECT);
	edit->put = 1;
	SECT.npoints++;
	edit->vertnum++;
	return (1);
}

void	cmp_nulling(t_edit *edit)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		CMP[i] = 0;
		i++;
	}
}

/*RB click on vertex, which belongs to two sectors, then 
RB click on another vertex, which belongs two previous sectors
and is next to first vertex in both sectors*/
int		checkfirst(t_edit *edit, int x, int y)
{
	int		i;
	unsigned int		j;
	int		f;

	f = 0;
	i = 0;
	while (i < edit->sectnum)
	{
		j = 0;
		while (j < edit->sectors[i].npoints)
		{
			if (edit->sectors[i].vertex[j].x == x && edit->sectors[i].vertex[j].y == y && f == 0)
			{
				CMP[0] = x;
				CMP[1] = y;
				CMP[4] = i;
				CMP[5] = j;
				f = 1;
			}
			else if (edit->sectors[i].vertex[j].x == x && edit->sectors[i].vertex[j].y == y && f == 1)
			{
				CMP[2] = x;
				CMP[3] = y;
				CMP[6] = i;
				CMP[7] = j;
			}
			j++;
		}
		i++;
	}
	
	ft_putnbr(CMP[0]);
	ft_putchar(' ');
	ft_putnbr(CMP[1]);
	ft_putchar(' ');
	ft_putnbr(CMP[2]);
	ft_putchar(' ');
	ft_putnbr(CMP[3]);
	ft_putchar('	');
	ft_putnbr(CMP[4]);
	ft_putchar(' ');
	ft_putnbr(CMP[5]);
	ft_putchar(' ');
	ft_putnbr(CMP[6]);
	ft_putchar(' ');
	ft_putnbr(CMP[7]);
	ft_putchar(' ');
	ft_putchar('\n');
	if (CMP[0] == CMP[2] && CMP[1] == CMP[3])
		return (1);
	return (0);
}

int		checksecond(t_edit *edit, int x, int y)
{
	int		i;
	unsigned int		j;
	int		f;

	f = 0;
	i = 0;
	while (i < edit->sectnum)
	{
		j = 0;
		while (j < edit->sectors[i].npoints)
		{
			if (edit->sectors[i].vertex[j].x == x && edit->sectors[i].vertex[j].y == y && f == 0)
			{
				CMP[8] = x;
				CMP[9] = y;
				CMP[12] = i;
				CMP[13] = j;
				f = 1;
			}
			else if (edit->sectors[i].vertex[j].x == x && edit->sectors[i].vertex[j].y == y && f == 1)
			{
				CMP[10] = x;
				CMP[11] = y;
				CMP[14] = i;
				CMP[15] = j;
			}
			j++;
		}
		i++;
	}
	
	ft_putnbr(CMP[8]);
	ft_putchar('.');
	ft_putnbr(CMP[9]);
	ft_putchar('.');
	ft_putnbr(CMP[10]);
	ft_putchar('.');
	ft_putnbr(CMP[11]);
	ft_putchar('	');
	ft_putnbr(CMP[12]);
	ft_putchar('.');
	ft_putnbr(CMP[13]);
	ft_putchar('.');
	ft_putnbr(CMP[14]);
	ft_putchar('.');
	ft_putnbr(CMP[15]);
	ft_putchar('.');
	ft_putchar('\n');
	if (CMP[8] == CMP[10] && CMP[9] == CMP[11])
		return (1);
	return (0);
}

int		checkthird(t_edit *edit)
{
	edit->check1 = 0;
	if (!(CMP[0] == CMP[8] && CMP[1] == CMP[9]) &&
		(CMP[4] == CMP[12] || CMP[4] == CMP[14]) &&
		(CMP[6] == CMP[12] || CMP[6] == CMP[14]) &&
		(abs(CMP[5] - CMP[13]) < 2 || (CMP[5] == 0 && CMP[13] == (int)edit->sectors[CMP[12]].npoints - 1) || (CMP[13] == 0 && CMP[5] == (int)edit->sectors[CMP[12]].npoints - 1)) &&
		(abs(CMP[7] - CMP[15]) < 2 || (CMP[7] == 0 && CMP[15] == (int)edit->sectors[CMP[14]].npoints - 1) || (CMP[15] == 0 && CMP[7] == (int)edit->sectors[CMP[14]].npoints - 1)))
	ft_putstr("all good!\n");
	return (1);
}

void	makeportals2(t_edit *edit)
{
	int x;
	int y;

	SDL_GetMouseState(&x,&y);
	x = (x + 12) / 25 * 25;
	y = (y + 12) / 25 * 25;
	if (checksecond(edit, x / 25 * 10, y / 25 * 10))
	{
		if (checkthird(edit))
			ft_putchar('+');
	}
	else
		edit->check1 = 0;
}

void	makeportals1(t_edit *edit)
{
	int x;
	int y;

	cmp_nulling(edit);
	SDL_GetMouseState(&x,&y);
	x = (x + 12) / 25 * 25;
	y = (y + 12) / 25 * 25;
	if (checkfirst(edit, x / 25 * 10, y / 25 * 10))
	{
		ft_putstr("check1\n");
		edit->check1 = 1;
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
		if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_RIGHT && edit->check1 == 1)
			makeportals2(edit);
		if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_RIGHT && edit->check1 == 0)
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
			printf("v %d: x = %d, y = %d,	neighbor: %d\n", j, edit->sectors[i].vertex[j].x, edit->sectors[i].vertex[j].y, edit->sectors[i].neighbors[j]);
		}
		i++;
	}
	return (0);
}