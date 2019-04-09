/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:52:25 by twitting          #+#    #+#             */
/*   Updated: 2019/04/09 22:41:46 by drestles         ###   ########.fr       */
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
	if (e->key.keysym.sym == SDLK_j)
		env->jetpack = 1;
	if (e->key.keysym.sym == SDLK_k)
		env->jetpack = 0;
	if (e->key.keysym.sym == SDLK_w)
		env->wsad[0] = on;
	if (e->key.keysym.sym == SDLK_s)
		env->wsad[1] = on;
	if (e->key.keysym.sym == SDLK_a)
		env->wsad[2] = on;
	if (e->key.keysym.sym == SDLK_d)
		env->wsad[3] = on;
	if (e->key.keysym.sym == SDLK_LCTRL || e->key.keysym.sym == SDLK_RCTRL)
	{
		env->ducking = on;
		env->falling = 1;
	}
	if (e->key.keysym.sym == SDLK_SPACE && on == 1)
		env->spacebar = 1;
	if (e->key.keysym.sym == SDLK_SPACE && on == 0)
		env->spacebar = 0;	
	if (e->key.keysym.sym == SDLK_SPACE && on == 1)
		if (env->ground && !env->jetpack)
		{
			env->player.velocity.z += 1.5;
			env->falling = 1;
		}
	
}

void	handle_events(t_env *env, SDL_Event *e)
{
	int x;
	int y;

	if (env->spacebar && env->jetpack)
	{
		env->player.velocity.z += 0.2;
		env->falling = 1;
	}
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			env->quit = 1;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
			env->state = 2;
		if (e->type == SDL_KEYDOWN || e->type == SDL_KEYUP)
			keyboard_events(env, e);
		/* if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_q)
			env->state = 2; */
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GetRelativeMouseState(&x, &y);
	env->player.angle += x * 3.14159 / 200;
	if (x > 0)
		env->skyangle += env->skyangle == 3840 ? -3808 : 32;
	else
		env->skyangle -= env->skyangle == 0 ? -3808 : 32;	
	env->player.sinang = sin(env->player.angle);
	env->player.cosang = cos(env->player.angle);
	env->yaw = CLAMP(env->yaw + y * 0.01, -3, 3);
	env->player.yaw = env->yaw;
	movement_calcs(env);
}
