/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:49:46 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 18:05:29 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	click(t_env *env)
{
	SDL_Surface *button;

	if (env->b_one == 1)
		button = SDL_LoadBMP("img/game_mode_1.bmp");
	else if (env->b_two == 1)
		button = SDL_LoadBMP("img/game_mode_2.bmp");
	else
		button = SDL_LoadBMP("img/game_mode_3.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
}

void		game_mode(t_env *env, SDL_Event *e)
{
	SDL_Surface *button;

	button = NULL;
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
		if (env->b_one == 1 | env->b_two == 1 | env->b_three == 1)
			click(env);
		handle_events_game_mode(env, e);
	}
}
