/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 06:00:22 by drestles          #+#    #+#             */
/*   Updated: 2019/04/08 06:04:36 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** STATE 0
*/
void menu(t_env *env, SDL_Event *e)
{
	env->b_one = 0;
	env->b_four = 0;
	while (env->state == 0)
	{
		SDL_Rect rect;
		rect.x = 320;
		rect.y = 200;
		rect.h = 100;
		rect.w = 400;
		SDL_Surface *button;
		button = SDL_LoadBMP("img/menu.bmp");
		if (env->b_one == 1)
			button = SDL_LoadBMP("img/menu_1.bmp");
		if (env->b_three == 1)
			button = SDL_LoadBMP("img/menu_2.bmp"); 
		if (env->b_four == 1)
			button = SDL_LoadBMP("img/menu_3.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_FreeSurface(button);
		SDL_UpdateWindowSurface(env->window);
		handle_events_menu(env, e);
	}
}
/*
** STATE 0 MENU 
** STATE 1 GAME
** STATE 2 PAUSE
** STATE 3 SAVE
** STATE 4 LOAD
** STATE 5 GAME MODE
*/
void start(t_env *env, SDL_Event *e)
{
	if (env->state == 0)
		menu(env, e);
	else if (env->state == 1)
	{
		env->frame = clock();
		start_engine(env, e);
		fps(env);
	}
	else if (env->state == 2)
		menu_pause(env, e);
	else if (env->state == 3)
		save_game(env, e);
	else if (env->state == 4)
		load_game(env, e);
	else if (env->state == 5)
		game_mode(env, e);
}