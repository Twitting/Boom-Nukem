/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 05:19:27 by drestles          #+#    #+#             */
/*   Updated: 2019/04/08 05:30:52 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void button_two(t_env *env, SDL_Event *e)
{
	env->b_two = 0;
	if (e->button.x >= 360 && e->button.x <= 662 && 
	e->button.y >= 223 && e->button.y <= 366)
		env->state = 3;
}

static void button_one(t_env *env, SDL_Event *e)
{
	env->b_one = 0;
	if (e->button.x >= 267 && e->button.x <= 750 && 
	e->button.y >= 40 && e->button.y <= 184)
		env->state = 1;
}

static void handle_up(t_env *env, SDL_Event *e)
{
	if (env->b_one == 1)
		button_one(env, e);
	else if (env->b_two == 1)
		button_two(env, e);
	else if (env->b_three == 1)
	{
		env->b_three = 0;
		if (e->button.x >= 363 && e->button.x <= 662 && 
		e->button.y >= 407 && e->button.y <= 549)
			env->state = 4;
	}
	else if (env->b_four == 1)
	{
		env->b_four = 0;
		if (e->button.x >= 385 && e->button.x <= 628 && 
		e->button.y >= 594 && e->button.y <= 735)
		{
			env->state = 1;
			env->quit = 1;
		}
	}
}

static void handle_down(t_env *env, SDL_Event *e)
{
	if (e->button.x >= 267 && e->button.x <= 750 && 
	e->button.y >= 40 && e->button.y <= 184)
			env->b_one = 1;
	else if (e->button.x >= 360 && e->button.x <= 662 && 
	e->button.y >= 223 && e->button.y <= 366)
		env->b_two = 1;
	else if (e->button.x >= 363 && e->button.x <= 662 && 
	e->button.y >= 407 && e->button.y <= 549)
		env->b_three = 1;
	else if (e->button.x >= 385 && e->button.x <= 628 && 
	e->button.y >= 594 && e->button.y <= 735)
		env->b_four = 1;
}
void handle_events_pause(t_env *env, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_g)
			env->state = 1;
		else if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			if (e->button.state == SDL_PRESSED)
				handle_down(env, e);
		}
		else if (e->type == SDL_MOUSEBUTTONUP)
			handle_up(env, e);
	}
}
