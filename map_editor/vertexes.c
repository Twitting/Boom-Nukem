/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertexes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:36:46 by twitting          #+#    #+#             */
/*   Updated: 2019/04/05 22:57:34 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"
#include "kiss_sdl.h"

void	putdot(t_edit *edit, int color, int x, int y)//square on window coords
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

void	showvertex(t_edit *edit, t_sector sect)//prints square on created vertex
{
	unsigned int	k;
	
	k = 0;
	while (k <= sect.npoints)
	{
		putdot(edit, 0xffffff, edit->verts[sect.vertex[k]].x * 25 / 10, edit->verts[sect.vertex[k]].y * 25 / 10);
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

void init_message(t_map_ui *ui)
{
	char *message;
	char *message2;
	char *message3;
	char *message4;

	message = (char*)malloc(sizeof(char) * KISS_MAX_LENGTH);
	message2 = (char*)malloc(sizeof(char) * KISS_MAX_LENGTH);
	message3 = (char*)malloc(sizeof(char) * KISS_MAX_LENGTH);
	message4 = (char*)malloc(sizeof(char) * KISS_MAX_LENGTH);
	ui->message = message;
	ui->message2 = message2;
	ui->message3 = message3;
	ui->message4 = message4;
	strcpy(ui->message, "floor:");
	strcpy(ui->message2, "ceiling:");
	strcpy(ui->message3, "light:");
	strcpy(ui->message4, "texture:");
}

void init_label(t_map_ui *ui, t_edit *edit)
{
	ui->quit = 0;
	ui->draw = 1;
	kiss_array_new(&ui->objects);
	ui->title = ft_strjoin("set sector ", ft_itoa(edit->sectnum));
	ui->renderer = kiss_init(ui->title, &ui->objects, 320, 350);
	kiss_window_new(&ui->window, NULL, 0, 0, 0, kiss_screen_width,
	kiss_screen_height);
	kiss_label_new(&ui->label, &ui->window, ui->message, 8, 10);
	kiss_label_new(&ui->label0, &ui->window, ui->message2, 8, 80);
	kiss_label_new(&ui->label3, &ui->window, ui->message3, 8, 150);
	kiss_label_new(&ui->label4, &ui->window, ui->message4, 8, 220);
	kiss_button_new(&ui->button, &ui->window, "OK", 100, 300);
	ui->window.visible = 1;
	ui->textbox_width =  300;
	kiss_entry_new(&ui->entry0, &ui->window, 1, "0", 0, 35, 320);
	kiss_entry_new(&ui->entry1, &ui->window, 1, "20", 0, 105, 320);
	kiss_entry_new(&ui->entry2, &ui->window, 1, "80", 0, 175, 320);
	kiss_entry_new(&ui->entry3, &ui->window, 1, "1", 0, 250, 320);
}

void ui_draw(t_map_ui *ui)
{
	SDL_RenderClear(ui->renderer);
	kiss_window_draw(&ui->window, ui->renderer);
	kiss_label_draw(&ui->label, ui->renderer);
	kiss_label_draw(&ui->label0, ui->renderer);
	kiss_label_draw(&ui->label3, ui->renderer);
	kiss_label_draw(&ui->label4, ui->renderer);
	kiss_button_draw(&ui->button, ui->renderer);
	kiss_entry_draw(&ui->entry0, ui->renderer);
	kiss_entry_draw(&ui->entry1, ui->renderer);
	kiss_entry_draw(&ui->entry2, ui->renderer);
	kiss_entry_draw(&ui->entry3, ui->renderer);
	SDL_RenderPresent(ui->renderer);
	ui->draw = 0;
}

int	num_to_program(t_edit *edit)
{
	t_map_ui ui;

	init_message(&ui);
	init_label(&ui, edit);
	while (!ui.quit) {
		SDL_Delay(10);
		while (SDL_PollEvent(&ui.e)) {
			if (ui.e.type == SDL_QUIT) ui.quit = 1;
			button_event(&ui.button, &ui.e, &ui.draw, &ui.quit);
			kiss_entry_event(&ui.entry0, &ui.e, &ui.draw);
			kiss_entry_event(&ui.entry1, &ui.e, &ui.draw);
			kiss_entry_event(&ui.entry2, &ui.e, &ui.draw);
			kiss_entry_event(&ui.entry3, &ui.e, &ui.draw);
		}
		if (!ui.draw) continue;
		ui_draw(&ui);
	}
	SECT.floor = ft_atoi(ui.entry0.text) >= 0 ? ft_atoi(ui.entry0.text) : 0;
	SECT.ceiling = ft_atoi(ui.entry1.text) - SECT.floor < 10 ? SECT.floor + 10 : ft_atoi(ui.entry1.text);
	SECT.light = ft_atoi(ui.entry2.text) >= 0 && ft_atoi(ui.entry2.text) <= 100 ? ft_atoi(ui.entry2.text) : 50;
	kiss_clean(&ui.objects);
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