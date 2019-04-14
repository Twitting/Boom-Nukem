/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:55:26 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 16:37:53 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

static void	title_first(SDL_Surface *sur)
{
	SDL_Surface	*new;
	TTF_Font	*bold;
	SDL_Rect	position;
	SDL_Color	color_title;

	color_title.r = 255;
	color_title.g = 0;
	color_title.b = 255;
	bold = TTF_OpenFont("fonts/bold.ttf", 28);
	new = TTF_RenderText_Solid(bold,
	"Welcome to Doom Nukem map editor!", color_title);
	position.x = 10;
	position.y = 10;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);
	SDL_FreeSurface(new);
	TTF_CloseFont(bold);
}

static void	draw_strings_one(SDL_Surface *sur, SDL_Color color)
{
	draw_string("1) All sectors must be set only in clockwise",
	color, 130, sur);
	draw_string("direction, it's mandatory part of creation.",
	color, 150, sur);
	draw_string("2) If ceiling set by negative number, it will be",
	color, 190, sur);
	draw_string("3) Sector can be drawn in game only if you're in",
	color, 250, sur);
	draw_string("it, or if it has active portals to player's sector.",
	color, 270, sur);
	draw_string("4) Player (P button) can be set only in first",
	color, 310, sur);
	draw_string("5) Objects (1 - barrel, 2 - enemy, 3 - medkit,",
	color, 370, sur);
}

void		draw_string(char *text, SDL_Color color, int y, SDL_Surface *sur)
{
	SDL_Surface	*new;
	TTF_Font	*font;
	SDL_Rect	position;

	font = TTF_OpenFont("fonts/droid.ttf", 20);
	new = TTF_RenderText_Solid(font, text, color);
	position.x = 20;
	position.y = y;
	position.h = 20;
	position.w = 50;
	SDL_BlitSurface(new, NULL, sur, &position);
	SDL_FreeSurface(new);
	TTF_CloseFont(font);
}

void		draw_title(SDL_Surface *sur)
{
	SDL_Surface	*new;
	TTF_Font	*bold_mini;
	SDL_Rect	position;
	SDL_Color	color_blue;
	char		*text;

	title_first(sur);
	bold_mini = TTF_OpenFont("fonts/bold.ttf", 21);
	color_blue.r = 0;
	color_blue.g = 255;
	color_blue.b = 255;
	text = "There are some rules of using this program";
	new = TTF_RenderText_Solid(bold_mini, text, color_blue);
	position.x = 10;
	position.y = 45;
	SDL_BlitSurface(new, NULL, sur, &position);
	SDL_FreeSurface(new);
	text = "you MUST follow during map creating process:";
	new = TTF_RenderText_Solid(bold_mini, text, color_blue);
	position.y = 65;
	SDL_BlitSurface(new, NULL, sur, &position);
	SDL_FreeSurface(new);
	TTF_CloseFont(bold_mini);
}

void		draw_strings(SDL_Surface *sur)
{
	SDL_Color color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	draw_strings_one(sur, color);
	draw_string("replaced by sky.", color, 210, sur);
	draw_string("drawn sector.", color, 330, sur);
	draw_string(" 4 - key) can be set only in last drawn sector.",
	color, 390, sur);
	draw_string("6) Buttons (Q button) can be set only on the wall",
	color, 430, sur);
	draw_string("without portal.", color, 450, sur);
	draw_string("8) There are NO reversible actions, if ducked up",
	color, 530, sur);
	draw_string("- do it again.", color, 550, sur);
	draw_string("9) Sectors can be only convex (vignutiy, ponel?).",
	color, 590, sur);
	draw_string("10) Press W while making portal to make",
	color, 630, sur);
	draw_string("metal bar.", color, 650, sur);
}
