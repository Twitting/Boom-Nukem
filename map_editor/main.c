/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:16:17 by twitting          #+#    #+#             */
/*   Updated: 2019/04/06 20:18:03 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

/*
INPUT
*/
//void	getfloorceilingheights(t_edit *edit)

void	putplayer(t_edit *edit)
{
	int x;
	int y;

	SDL_GetMouseState(&x,&y);
	x = x * 2 / 5;
	y = y * 2 / 5;
	edit->player.x = x;
	edit->player.y = y;
	edit->playerangle = 0;
	edit->playersect = 0;
	edit->playersetflag = 1;
	printf("player set on x - %d	y - %d\n", x, y);
	putdot(edit, 0x00ff00, x * 5 / 2, y * 5 / 2);
}

void	putobject(t_edit *edit, int type)
{
	int x;
	int y;
	int	color;

	SDL_GetMouseState(&x,&y);
	x = x * 2 / 5;
	y = y * 2 / 5;
	edit->sprites[edit->sprnum].type = type;
	edit->sprites[edit->sprnum].x = x;
	edit->sprites[edit->sprnum].y = y;
	edit->sprites[edit->sprnum].sector = edit->sectnum - 1;
	color = type == 0 ? 0x996600 : 0xff00ff;
	putdot(edit, color, x * 5 / 2, y * 5 / 2);
	edit->sprnum++;
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
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_p && edit->playersetflag == 0)
			putplayer(edit);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_1)
			putobject(edit, 0);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_2)
			putobject(edit, 1);
		if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_q && edit->buttonflag == 1)
			makebutton2(edit);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_q && edit->buttonflag == 0)
			makebutton1(edit);
	}
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
	savemap(edit);
	// while (edit->sectors[i].npoints != 0)//this part just print things in stdout
	// {
	// 	if (edit->sectors[i].finished == 0)
	// 	{
	// 		i++;
	// 		continue;
	// 	}
	// 	printf("Sector %d: 	npoints:%d 	floor:%d 	ceiling:%d    light:%u\n", i, edit->sectors[i].npoints, edit->sectors[i].floor,
	// 	edit->sectors[i].ceiling, edit->sectors[i].light);
	// 	for (unsigned int j = 0; j < edit->sectors[i].npoints; j++)
	// 	{
	// 		printf("v %d: x = %d, y = %d,	neighbor: %d\n", edit->sectors[i].vertex[j], edit->verts[edit->sectors[i].vertex[j]].x, 
	// 		edit->verts[edit->sectors[i].vertex[j]].y, edit->sectors[i].neighbors[j]);
	// 	}
	// 	i++;
	// }
	return (0);
}
