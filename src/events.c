/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:52:25 by twitting          #+#    #+#             */
/*   Updated: 2019/03/08 23:44:16 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	keyboard_events(t_env *env, SDL_Event *e)
{
	int		on;
	if (e->type == SDL_KEYDOWN)
		on = 1;
	else
		on = 0;
	if (e->key.keysym.sym == SDLK_w)
		env->wsad[0] = on;
	if (e->key.keysym.sym == SDLK_s)
		env->wsad[1] = on;
	if (e->key.keysym.sym == SDLK_a)
		env->wsad[2] = on;
	if (e->key.keysym.sym == SDLK_d)
		env->wsad[3] = on;
}

void	handle_events(t_env *env, SDL_Event *e)
{
	int x;
	int y;

	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			env->quit = 1;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
			env->quit = 1;
		if (e->type == SDL_KEYDOWN || e->type == SDL_KEYUP)
			keyboard_events(env, e);
	}
	SDL_GetRelativeMouseState(&x,&y);
	env->player.angle += x * 3.14159 / 100;
	env->yaw = CLAMP(env->yaw + y * 0.01, -2, 2);
	env->player.yaw = env->yaw;
	movement_calcs(env);
}