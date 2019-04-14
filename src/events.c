/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:52:25 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 18:45:25 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	keyboard_events3(t_env *env, SDL_Event *e)
{
	if (e->type == SDL_KEYUP && e->key.keysym.sym ==
		1073741901 && env->volume > 0)
	{
		env->volume -= 15;
		if (env->volume < 0)
			env->volume = 0;
		Mix_VolumeMusic(env->volume);
	}
	if (e->type == SDL_KEYUP && e->key.keysym.sym ==
		1073741898 && env->volume < 128)
	{
		env->volume += 15;
		if (env->volume > 128)
			env->volume = 128;
		Mix_VolumeMusic(env->volume);
	}
	if (e->type == SDL_KEYUP && e->key.keysym.sym == 127)
	{
		if (env->help)
			env->help = 0;
		else
			env->help = 1;
	}
}

void	keyboard_events2(t_env *env, SDL_Event *e, int on)
{
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
			Mix_PlayChannel(-1, env->sound[10], 0);
			env->player.velocity.z += 1.5;
			env->falling = 1;
		}
	keyboard_events3(env, e);
}

void	keyboard_events(t_env *env, SDL_Event *e)
{
	int		on;

	on = e->type == SDL_KEYDOWN ? 1 : 0;
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
	if (e->key.keysym.sym == SDLK_e && !on && checkswitch(env) &&
	env->button[env->player.sector].visible == 1)
	{
		Mix_PlayChannel(-1, env->sound[5], 0);
		env->player.pushingbutton = 1;
	}
	if (e->key.keysym.sym == SDLK_e && !on && env->player.keys > 0)
	{
		if (openbars(env))
			env->player.keys--;
		//Mix_PlayChannel(-1, env->sound[5], 0);
		//env->player.pushingbutton = 1;
	}
	keyboard_events2(env, e, on);
}

void	handle_events2(t_env *env, int x, int y)
{
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
		if (e->type == SDL_MOUSEBUTTONDOWN)
			shoot(env, e);
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GetRelativeMouseState(&x, &y);
	handle_events2(env, x, y);
}
