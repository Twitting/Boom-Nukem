/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 02:45:02 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 18:16:13 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	click(t_env *env)
{
	SDL_Surface *button;

	if (env->b_one == 1)
		button = SDL_LoadBMP("img/load_1.bmp");
	else if (env->b_two == 1)
		button = SDL_LoadBMP("img/load_2.bmp");
	else if (env->b_three == 1)
		button = SDL_LoadBMP("img/load_3.bmp");
	else
		button = SDL_LoadBMP("img/load_4.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
}

void	load_game(t_env *env, SDL_Event *e)
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
			click(env);
		handle_events_load(env, e);
	}
}

void	load_player_init(t_env *env)
{
	env->player = env->save[env->save_number];
}
