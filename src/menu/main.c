/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 06:00:22 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 17:41:34 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

/*
** STATE 0
*/

void	menu(t_env *env, SDL_Event *e)
{
	SDL_Surface *button;

	env->b_one = 0;
	env->b_three = 0;
	env->b_four = 0;
	button = SDL_LoadBMP("img/menu.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	while (env->state == 0)
	{
		if (env->b_one == 1 | env->b_three == 1 | env->b_four == 1)
		{
			if (env->b_one == 1)
				button = SDL_LoadBMP("img/menu_1.bmp");
			else if (env->b_three == 1)
				button = SDL_LoadBMP("img/menu_2.bmp");
			else if (env->b_four == 1)
				button = SDL_LoadBMP("img/menu_3.bmp");
			SDL_BlitScaled(button, NULL, env->surface, NULL);
			SDL_FreeSurface(button);
			SDL_UpdateWindowSurface(env->window);
		}
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
** STATE 6 GAME OVER
*/

void	start(t_env *env, SDL_Event *e, t_rend *R)
{
	if (env->state == 0)
		menu(env, e);
	else if (env->state == 1)
	{
		if (Mix_PlayingMusic() == 0)
			Mix_PlayMusic(env->music[1], -1);
		if (Mix_PausedMusic())
			Mix_ResumeMusic();
		env->frame = clock();
		start_engine(env, e, R);
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
	else if (env->state == 6)
		game_over(env, e);
}
