/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:16:17 by twitting          #+#    #+#             */
/*   Updated: 2019/04/11 21:20:57 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"
#include "SDL_ttf.h"

void	draw_string(char *text, SDL_Color color, int y, SDL_Surface *sur)
{
	SDL_Surface	*new;
	TTF_Font	*font;
	SDL_Rect	position;

	font = TTF_OpenFont("droid.ttf", 20);
	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = y;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);
	SDL_FreeSurface(new);
	TTF_CloseFont(font);
}

void	draw_title(SDL_Surface *sur)
{
	SDL_Surface *new;
	TTF_Font* bold= TTF_OpenFont("bold.ttf", 28);
	TTF_Font* bold_mini= TTF_OpenFont("bold.ttf", 21);
	SDL_Rect position;
	SDL_Color color_title={255,0,255};
	SDL_Color color_blue={0,255,255};
	char *text;

	new = TTF_RenderText_Solid(bold, "Welcome to Doom Nukem map editor!", color_title);
	position.x = 10;
	position.y = 10;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);
	SDL_FreeSurface(new);
	text = "There are some rules of using this program";
	new = TTF_RenderText_Solid(bold_mini, text, color_blue);
	position.y = 45;
	SDL_BlitSurface(new, NULL, sur, &position);
	SDL_FreeSurface(new);
	text = "you MUST follow during map creating process:";
	new = TTF_RenderText_Solid(bold_mini, text, color_blue);
	position.y = 65;
	SDL_BlitSurface(new, NULL, sur, &position);
	SDL_FreeSurface(new);
	TTF_CloseFont(bold);
	TTF_CloseFont(bold_mini);
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
	 /* if (bold == NULL)
        printf("Unable to load font \n"); */
	SDL_Color color_bold={0,255,0};
	SDL_Color color={255,255,255};

	draw_title(sur);
	draw_string("1) All sectors must be set only in clockwise", color, 130, sur);
	draw_string("direction, it's mandatory part of creation.", color, 150, sur);
	draw_string("2) If ceiling set by negative number, it will be", color, 190, sur);
	draw_string("replaced by sky.", color, 210, sur);
	draw_string("3) Sector can be drawn in game only if you're in", color, 250, sur);
	draw_string("it, or if it has active portals to player's sector.", color, 270, sur);
	draw_string("4) Player (P button) can be set only in first", color, 310, sur);
	draw_string("drawn sector.", color, 330, sur);
	draw_string("5) Objects (1, 2 buttons) can be set only in last", color, 370, sur);
	draw_string("drawn sector.", color, 390, sur);
	draw_string("6) Buttons (Q button) can be set only on the wall", color, 430, sur);
	draw_string("without portal.", color, 450, sur);
	draw_string("7) Rate of this project can be only above 100.", color_bold, 490, sur);
	draw_string("8) There are NO reversible actions, if ducked up", color, 530, sur);
	draw_string("- do it again.", color, 550, sur);
	draw_string("9) Sectors can be only convex (vignutiy, ponel?).", color, 590, sur);
	draw_string("10) Press W while making portal to make", color, 630, sur);
	draw_string("metal bar.", color, 650, sur);
	SDL_UpdateWindowSurface(win);
	TTF_Quit();
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
	SDL_Quit();
	exit(1);
	return (0);
}
