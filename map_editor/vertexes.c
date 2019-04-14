/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertexes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:36:46 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 16:38:22 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"
#include "kiss_sdl.h"

static void	free_all(t_map_ui *ui)
{
	kiss_clean(&(ui->objects));
	free(ui->message);
	free(ui->message2);
	free(ui->message3);
	free(ui->message4);
	free(ui->title);
}

int			num_to_program(t_edit *edit)
{
	t_map_ui ui;

	init_message(&ui);
	init_label(&ui, edit);
	while (!ui.quit)
	{
		SDL_Delay(10);
		while (SDL_PollEvent(&ui.e))
		{
			if (ui.e.type == SDL_QUIT)
				ui.quit = 1;
			button_event(&ui.button, &ui.e, &ui.draw, &ui.quit);
			kiss_entry_event(&ui.entry0, &ui.e, &ui.draw);
			kiss_entry_event(&ui.entry1, &ui.e, &ui.draw);
			kiss_entry_event(&ui.entry2, &ui.e, &ui.draw);
			kiss_entry_event(&ui.entry3, &ui.e, &ui.draw);
		}
		if (!ui.draw)
			continue;
		ui_draw(&ui);
	}
	setsectnums(edit, &ui);
	free_all(&ui);
	return (0);
}

void		boldlinesector(t_edit *edit)
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
				edit->nowln.x1 = edit->verts[SECT.vertex[(i + 1) %
					SECT.npoints]].x * 5 / 2 + j;
				edit->nowln.y1 = edit->verts[SECT.vertex[(i + 1) %
					SECT.npoints]].y * 5 / 2 + k;
				putline(edit, &edit->nowln);
			}
		}
	}
}

int			addvertex(t_edit *edit, int x, int y)
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

void		putsectors(t_edit *edit)
{
	int x;
	int y;

	SDL_GetMouseState(&x, &y);
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
