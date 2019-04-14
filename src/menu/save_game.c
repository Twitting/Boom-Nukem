/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 18:09:01 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 18:20:52 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	click(t_env *env)
{
	SDL_Surface *button;

	if (env->b_one == 1)
		button = SDL_LoadBMP("img/save_1.bmp");
	else if (env->b_two == 1)
		button = SDL_LoadBMP("img/save_2.bmp");
	else if (env->b_three == 1)
		button = SDL_LoadBMP("img/save_3.bmp");
	else
		button = SDL_LoadBMP("img/save_4.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
}

void		save_game1(t_env *env, int i)
{
	i == 4 ? i = 0 : i;
	env->save[i] = env->player;
	i++;
}

void		save_game(t_env *env, SDL_Event *e)
{
	SDL_Surface *button;

	button = SDL_LoadBMP("img/save.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env->state == 3)
	{
		if (env->b_one == 1 || env->b_two == 1
			|| env->b_three == 1 || env->b_four == 1)
			click(env);
		handle_events_save(env, e);
	}
}
