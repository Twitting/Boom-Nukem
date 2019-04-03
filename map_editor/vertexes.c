/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertexes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:36:46 by twitting          #+#    #+#             */
/*   Updated: 2019/04/03 17:31:26 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"
#include "kiss_sdl.h"

void	showvertex(t_edit *edit, t_sector sect)//prints square on created vertex
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

int		checknewvertex(t_edit *edit, int x, int y)//checks if clicked vertex is previous or new
{
	unsigned int	i;

	i = 0;
	while (i < SECT.npoints)
	{
		if (x == edit->verts[SECT.vertex[i]].x && y ==
				edit->verts[SECT.vertex[i]].y)
			{
				ft_putstr("wrong vertex\n");
				edit->nowln.x0 = edit->nowln.x1; // strange things because of putline x0-x1 inversions
				edit->nowln.y0 = edit->nowln.y1;
				return (0);
			}
		i++;
	}
	return (1);
}

void	createornot(t_edit *edit, int x, int y)//creates new vertex or makes a link to present
{
	int	i;

	i = 0;
	while (i < edit->glvertnum)
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
}
/*
MAKING VERTEXES
*/

void	button_event(kiss_button *button, SDL_Event *e, int *draw,
		int *quit)
{
if (kiss_button_event(button, e, draw)) *quit = 1;
}

int	num_to_program(t_edit *edit)
{
	SDL_Renderer *renderer;
	SDL_Event e;
	kiss_array objects;
	kiss_window window;
	kiss_label label = {0};
	kiss_button button = {0};
	char message[KISS_MAX_LENGTH];
	int draw, quit;
	quit = 0;
	draw = 1;
	kiss_array_new(&objects);
	char *title = ft_strjoin("set sector ", ft_itoa(edit->sectnum));
	renderer = kiss_init(title, &objects, 320, 300);
	if (!renderer) return 1;
	kiss_window_new(&window, NULL, 0, 0, 0, kiss_screen_width,
	kiss_screen_height);
	strcpy(message, "floor:");
	char message2[KISS_MAX_LENGTH];
	strcpy(message2, "ceiling:");
	kiss_label_new(&label, &window, message, 8, 10);
	kiss_label label0 = {0};
	kiss_label_new(&label0, &window, message2, 8, 80);
	kiss_label label01 = {0};
	char message3[KISS_MAX_LENGTH];
	strcpy(message3, "light:");
	kiss_label_new(&label01, &window, message3, 8, 150);
	//label.textcolor.r = 255;
	kiss_button_new(&button, &window, "OK", 100, 250);
	window.visible = 1;
	kiss_textbox textbox1 = {0};
	kiss_entry entry = {0};kiss_entry entry0 = {0};kiss_entry entry01 = {0};
	kiss_label label1 = {0}, label2 = {0};
	int textbox_width =  300;
	kiss_entry_new(&entry, &window, 1, "0", 0, 35, 320);
	kiss_entry_new(&entry0, &window, 1, "20", 0, 105, 320);
	kiss_entry_new(&entry01, &window, 1, "1", 0, 175, 320);

	while (!quit) {
		SDL_Delay(10);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = 1;
			button_event(&button, &e, &draw, &quit);
			kiss_entry_event(&entry, &e, &draw);
			kiss_entry_event(&entry0, &e, &draw);
			kiss_entry_event(&entry01, &e, &draw);
		}
		if (!draw) continue;
		SDL_RenderClear(renderer);
		kiss_window_draw(&window, renderer);
		kiss_label_draw(&label, renderer);
		kiss_label_draw(&label0, renderer);
		kiss_label_draw(&label01, renderer);
		kiss_button_draw(&button, renderer);
		kiss_entry_draw(&entry, renderer);
		kiss_entry_draw(&entry0, renderer);
		kiss_entry_draw(&entry01, renderer);
		SDL_RenderPresent(renderer);
		draw = 0;
	}
	SECT.floor = ft_atoi(entry.text);
	SECT.ceiling = ft_atoi(entry0.text);
	SECT.light = ft_atoi(entry01.text);
	//printf("%s\n", entry.text);
	kiss_clean(&objects);
	return (0);
}

void	boldlinesector(t_edit *edit)
{
	int	i;
	int j;
	int k;

	i = -1;
	while (++i < (int)SECT.npoints)
	{
		j = -2;
		while (++j < 2)
		{

			k = -2;
			while (++k < 2)
			{
				edit->nowln.x0 = edit->verts[SECT.vertex[i]].x * 5 / 2 + j;
				edit->nowln.y0 = edit->verts[SECT.vertex[i]].y * 5 / 2 + k;
				edit->nowln.x1 = edit->verts[SECT.vertex[(i + 1) % SECT.npoints]].x * 5 / 2 + j;
				edit->nowln.y1 = edit->verts[SECT.vertex[(i + 1) % SECT.npoints]].y * 5 / 2 + k;
				putline(edit, &edit->nowln);
			}
		}
	}
}

int		addvertex(t_edit *edit, int x, int y)//eats mouse position and makes main creating magic
{	
	if (SECT.npoints > 2 && edit->verts[SECT.vertex[0]].x == x &&
		edit->verts[SECT.vertex[0]].y == y)
		{
			ft_putnbr(edit->sectnum);
			ft_putstr(" sector created\n");
			boldlinesector(edit);
			num_to_program(edit);
			SECT.finished = 1;
			edit->vertnum = 0;
			edit->sectnum++;
			edit->put = 0;
			return (1);
		}
	if (checknewvertex(edit, x, y) == 0)
		return (0);
	createornot(edit, x, y);
	showvertex(edit, SECT);
	edit->put = 1;
	SECT.npoints++;
	edit->vertnum++;
	return (1);
}

/*RB click on vertex, which belongs to two sectors, then 
RB click on another vertex, which belongs two previous sectors
and is next to first vertex in both sectors*/


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