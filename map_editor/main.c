/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:16:17 by twitting          #+#    #+#             */
/*   Updated: 2019/04/07 01:27:34 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"
#include "SDL_ttf.h"

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
	color = type == 0 ? 0x00ffff : 0xff00ff;
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

void	rules(void)
{
	TTF_Init();
	SDL_Window *win;
	SDL_Rect position;
	win = SDL_CreateWindow("RULES", 1795, 336, 435, 770, SDL_WINDOW_SHOWN);
	SDL_Surface *sur;
	sur = SDL_GetWindowSurface(win);
	SDL_FillRect(sur, NULL, 0x000000);
	TTF_Font* bold= TTF_OpenFont("bold.ttf", 28);
	TTF_Font* bold_mini= TTF_OpenFont("bold.ttf", 21);
	TTF_Font* font= TTF_OpenFont("droid.ttf", 20);
	 if (bold == NULL)
        printf("Unable to load font \n");
	SDL_Color color_title={0,255,0};
	SDL_Color color={255,255,255};
	SDL_Color color_bold={255,0,255};
	SDL_Color color_blue={0,255,255};
	SDL_Surface *new = NULL;

	new = TTF_RenderText_Solid(bold, "Welcome to Doom Nukem map editor!", color_bold);
	position.x = 10;
	position.y = 10;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	char *text;
	text = "There are some rules of using this program";

	new = TTF_RenderText_Solid(bold_mini, text, color_blue);
	position.x = 10;
	position.y = 45;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	text = "you MUST follow during map creating process:";

	new = TTF_RenderText_Solid(bold_mini, text, color_blue);
	position.x = 10;
	position.y = 65;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

/////////////////////////////////////////////////////////////////////////////////////////

	text = "1) All sectors must be set only in clockwise";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 130;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	text = "direction, it's mandatory part of creation.";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 150;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

/////////////////////////////

	text = "2) If ceiling set by negative number, it will be";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 190;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	text = "replaced by sky.";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 210;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

//////////////////////////////

	text = "3) Sector can be drawn in game only if you're in";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 250;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	text = "it, or if it has active portals to player's sector.";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 270;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

//////////////////////////////

	text = "4) Player (P button) can be set only in first";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 310;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	text = "drawn sector.";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 330;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

//////////////////////////////

	text = "5) Objects (1, 2 buttons) can be set only in last";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 370;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	text = "drawn sector.";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 390;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

//////////////////////////////

	text = "6) Buttons (Q button) can be set only on the wall";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 430;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	text = "without portal.";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 450;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

//////////////////////////////

	text = "7) Rate of this project can be only above 100.";

	new = TTF_RenderText_Solid(font, text, color_title);
	position.x = 20;
	position.y = 490;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	//////////////////////////////

	text = "8) There are NO reversible actions, if ducked up";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 530;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	text = "- do it again.";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 550;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);

	//////////////////////////////

	text = "9) Sectors can be only convex (vignutiy, ponel?).";

	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = 590;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);


	TTF_CloseFont(bold);
	SDL_UpdateWindowSurface(win);
}

int		main(void)
{
	t_edit		*edit;
	SDL_Event	e;
	int			i;

	edit = init();
	rules();
	
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
