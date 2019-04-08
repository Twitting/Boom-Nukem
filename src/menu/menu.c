/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 02:45:02 by drestles          #+#    #+#             */
/*   Updated: 2019/04/08 06:03:13 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** STATE 2 PAUSE
*/
void menu_pause(t_env *env, SDL_Event *e)
{
	env->b_one = 0;
	env->b_four = 0;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env->state == 2)
	{
		SDL_Rect rect;
		rect.x = 320;
		rect.y = 200;
		rect.h = 100;
		rect.w = 400;
		SDL_Surface *button;
		button = SDL_LoadBMP("img/pause.bmp");
		if (env->b_one == 1)
			button = SDL_LoadBMP("img/pause_1.bmp");
		if (env->b_two == 1)
			button = SDL_LoadBMP("img/pause_2.bmp");
		if (env->b_three == 1)
			button = SDL_LoadBMP("img/pause_3.bmp");
		if (env->b_four == 1)
			button = SDL_LoadBMP("img/pause_4.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_FreeSurface(button);
		SDL_UpdateWindowSurface(env->window);
		handle_events_pause(env, e);
	}
}

/*
** STATE 3 SAVE
*/
void save_game(t_env *env, SDL_Event *e)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env->state == 3)
	{
		SDL_Rect rect;
		rect.x = 320;
		rect.y = 200;
		rect.h = 100;
		rect.w = 400;
		SDL_Surface *button;
		button = SDL_LoadBMP("img/save.bmp");
		if (env->b_one == 1)
			button = SDL_LoadBMP("img/save_1.bmp");
		if (env->b_two == 1)
			button = SDL_LoadBMP("img/save_2.bmp");
		if (env->b_three == 1)
			button = SDL_LoadBMP("img/save_3.bmp");
		if (env->b_four == 1)
			button = SDL_LoadBMP("img/save_4.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_FreeSurface(button);
		SDL_UpdateWindowSurface(env->window);
		handle_events_save(env, e);
	}
}

/*
** STATE 4 LOAD
*/
void load_game(t_env *env, SDL_Event *e)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env->state == 4)
	{
		SDL_Rect rect;
		rect.x = 320;
		rect.y = 200;
		rect.h = 100;
		rect.w = 400;
		SDL_Surface *button;
		button = SDL_LoadBMP("img/load.bmp");
		if (env->b_one == 1)
			button = SDL_LoadBMP("img/load_1.bmp");
		if (env->b_two == 1)
			button = SDL_LoadBMP("img/load_2.bmp");
		if (env->b_three == 1)
			button = SDL_LoadBMP("img/load_3.bmp");
		if (env->b_four == 1)
			button = SDL_LoadBMP("img/load_4.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_FreeSurface(button);
		SDL_UpdateWindowSurface(env->window);
		handle_events_load(env, e);
	}
}

/*
** STATE 5 GAME MODE
*/
void game_mode(t_env *env, SDL_Event *e)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env->state == 5)
	{
		SDL_Rect rect;
		rect.x = 320;
		rect.y = 200;
		rect.h = 100;
		rect.w = 400;
		SDL_Surface *button;
		button = SDL_LoadBMP("img/game_mode.bmp");
		if (env->b_one == 1)
			button = SDL_LoadBMP("img/game_mode_1.bmp");
		if (env->b_two == 1)
			button = SDL_LoadBMP("img/game_mode_2.bmp");
		if (env->b_three == 1)
			button = SDL_LoadBMP("img/game_mode_3.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_FreeSurface(button);
		SDL_UpdateWindowSurface(env->window);
		handle_events_game_mode(env, e);
	}
}
