/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_pause.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:42:36 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 17:47:06 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

static void click_buttons(t_env *env)
{
    SDL_Surface *button;

    if (env->b_one == 1)
		button = SDL_LoadBMP("img/pause_1.bmp");
	else if (env->b_two == 1)
		button = SDL_LoadBMP("img/pause_2.bmp");
	else if (env->b_three == 1)
		button = SDL_LoadBMP("img/pause_3.bmp");
	else
		button = SDL_LoadBMP("img/pause_4.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
}

void	menu_pause(t_env *env, SDL_Event *e)
{
	SDL_Surface *button;

	Mix_PauseMusic();
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
            click_buttons(env);
		handle_events_pause(env, e);
	}
}
