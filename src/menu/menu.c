/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 02:45:02 by drestles          #+#    #+#             */
/*   Updated: 2019/04/09 22:40:35 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** STATE 2 PAUSE
*/
void menu_pause(t_env *env, SDL_Event *e)
{
	SDL_Surface *button;
	env->b_one = 0;
	env->b_four = 0;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	button = SDL_LoadBMP("img/pause.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	while (env->state == 2)
	{
		if (env->b_one == 1 || env->b_two == 1 || env->b_three == 1 || env->b_four == 1)
		{
			if (env->b_one == 1)
				button = SDL_LoadBMP("img/pause_1.bmp");
			else if (env->b_two == 1)
				button = SDL_LoadBMP("img/pause_2.bmp");
			else if (env->b_three == 1)
				button = SDL_LoadBMP("img/pause_3.bmp");
			else if (env->b_four == 1)
				button = SDL_LoadBMP("img/pause_4.bmp");
			SDL_BlitScaled(button, NULL, env->surface, NULL);
			SDL_FreeSurface(button);
			SDL_UpdateWindowSurface(env->window);
		}
		handle_events_pause(env, e);
	}
}

/*
** STATE 3 SAVE
*/
void save_game(t_env *env, SDL_Event *e)
{
	SDL_Surface *button;
	button = SDL_LoadBMP("img/save.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env->state == 3)
	{
		if (env->b_one == 1 || env->b_two == 1 || env->b_three == 1 || env->b_four == 1)
		{
			if (env->b_one == 1)
				button = SDL_LoadBMP("img/save_1.bmp");
			else if (env->b_two == 1)
				button = SDL_LoadBMP("img/save_2.bmp");
			else if (env->b_three == 1)
				button = SDL_LoadBMP("img/save_3.bmp");
			else if (env->b_four == 1)
				button = SDL_LoadBMP("img/save_4.bmp");
			SDL_BlitScaled(button, NULL, env->surface, NULL);
			SDL_FreeSurface(button);
			SDL_UpdateWindowSurface(env->window);
		}
		handle_events_save(env, e);
	}
}

/*
** STATE 4 LOAD
*/
void load_game(t_env *env, SDL_Event *e)
{
	SDL_Surface *button;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	button = SDL_LoadBMP("img/load.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	while (env->state == 4)
	{
		if (env->b_one == 1 || env->b_two == 1 || env->b_three == 1 || env->b_four == 1)
		{
			if (env->b_one == 1)
				button = SDL_LoadBMP("img/load_1.bmp");
			else if (env->b_two == 1)
				button = SDL_LoadBMP("img/load_2.bmp");
			else if (env->b_three == 1)
				button = SDL_LoadBMP("img/load_3.bmp");
			else if (env->b_four == 1)
				button = SDL_LoadBMP("img/load_4.bmp");
			SDL_BlitScaled(button, NULL, env->surface, NULL);
			SDL_FreeSurface(button);
			SDL_UpdateWindowSurface(env->window);
		}
		handle_events_load(env, e);
	}
}

/*
** STATE 5 GAME MODE
*/
void game_mode(t_env *env, SDL_Event *e)
{
	SDL_Surface *button = NULL;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	env->b_one = 0;
	env->b_two = 0;
	env->b_three = 0;
	button = SDL_LoadBMP("img/game_mode.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	while (env->state == 5)
	{
		//SDL_Surface *button;
		//button = SDL_LoadBMP("img/game_mode.bmp");
		if (env->b_one == 1 | env->b_two == 1 | env->b_three == 1)
		{
			if (env->b_one == 1)
				button = SDL_LoadBMP("img/game_mode_1.bmp");
			else if (env->b_two == 1)
				button = SDL_LoadBMP("img/game_mode_2.bmp");
			else if (env->b_three == 1)
				button = SDL_LoadBMP("img/game_mode_3.bmp");
			SDL_BlitScaled(button, NULL, env->surface, NULL);
			SDL_FreeSurface(button);
			SDL_UpdateWindowSurface(env->window);
		}
		handle_events_game_mode(env, e);
	}
}
