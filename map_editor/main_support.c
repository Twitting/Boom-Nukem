/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:20:14 by twitting          #+#    #+#             */
/*   Updated: 2019/04/15 16:32:46 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	ft_error(int errnum)
{
	if (errnum == 1)
		ft_putendl_fd("FFFFFFFFFreeeee", 2);
	if (errnum == 2)
		ft_putendl_fd("Memory allocation error, aborting...", 2);
	if (errnum == 3)
		ft_putendl_fd("Something wrong with map file, aborting...", 2);
	if (errnum == 4)
		ft_putendl_fd("SDL initialization has failed, aborting...", 2);
	exit(errnum);
}

void	putplayer(t_edit *edit)
{
	int x;
	int y;

	SDL_GetMouseState(&x, &y);
	x = x * 2 / 5;
	y = y * 2 / 5;
	edit->player.x = x;
	edit->player.y = y;
	edit->playerangle = 0;
	edit->playersect = 0;
	edit->playersetflag = 1;
	putdot(edit, 0x00ff00, x * 5 / 2, y * 5 / 2);
}

void	putobject(t_edit *edit, int type)
{
	int x;
	int y;
	int	color;

	SDL_GetMouseState(&x, &y);
	x = x * 2 / 5;
	y = y * 2 / 5;
	edit->sprites[edit->sprnum].type = type;
	edit->sprites[edit->sprnum].x = x;
	edit->sprites[edit->sprnum].y = y;
	edit->sprites[edit->sprnum].sector = edit->sectnum - 1;
	color = type == 0 ? 0x0000ff : 0x000000;
	color = type == 1 ? 0xff00ff : color;
	color = type == 3 ? 0x00ffff : color;
	color = type == 5 ? 0xffff00 : color;
	color = type == 6 ? 0xaaaaaa : color;
	putdot(edit, color, x * 5 / 2, y * 5 / 2);
	edit->sprnum++;
}

void	handle_events2(t_edit *edit, SDL_Event *e)
{
	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_3)
		putobject(edit, 3);
	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_4)
		putobject(edit, 5);
	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_5)
		putobject(edit, 6);
	if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_q &&
		edit->buttonflag == 1)
		makebutton2(edit);
	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_q &&
		edit->buttonflag == 0)
		makebutton1(edit);
	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_w)
		edit->barsflag = 1;
	if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_w)
		edit->barsflag = 0;
}

void	handle_events(t_edit *edit, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			edit->quit = 1;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
			edit->quit = 1;
		if (e->type == SDL_MOUSEBUTTONDOWN &&
			e->button.button == SDL_BUTTON_LEFT)
			putsectors(edit);
		if (e->type == SDL_MOUSEBUTTONUP &&
			e->button.button == SDL_BUTTON_RIGHT)
			makeportals2(edit);
		if (e->type == SDL_MOUSEBUTTONDOWN &&
			e->button.button == SDL_BUTTON_RIGHT)
			makeportals1(edit);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_p &&
			edit->playersetflag == 0)
			putplayer(edit);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_1)
			putobject(edit, 0);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_2)
			putobject(edit, 1);
		handle_events2(edit, e);
	}
}
