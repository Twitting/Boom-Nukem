/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_game_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 05:53:07 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 17:35:42 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void handle_down(t_env *env, SDL_Event *e)
{
	if (e->button.x >= 384 && e->button.x <= 640 && 
	e->button.y >= 305 && e->button.y <= 420)
		env->b_one = 1;
	else if (e->button.x >= 316 && e->button.x <= 708 && 
	e->button.y >= 448 && e->button.y <= 567)
		env->b_two = 1;
	else if (e->button.x >= 385 && e->button.x <= 638 && 
	e->button.y >= 595 && e->button.y <= 714)
		env->b_three = 1;
}

static void button_one(t_env *env, SDL_Event *e)
{
	env->b_one = 0;
	if (e->button.x >= 384 && e->button.x <= 640 && 
	e->button.y >= 305 && e->button.y <= 420)
	{
		env->state = 1;
		env->mode = 1;
	}
}

static void handle_up(t_env *env, SDL_Event *e)
{
	if (env->b_one == 1)
		button_one(env, e);
	else if (env->b_two == 1)
	{
		env->b_two = 0;
		if (e->button.x >= 316 && e->button.x <= 708 && 
		e->button.y >= 448 && e->button.y <= 567)
		{
			env->state = 1;
			env->mode = 2;
		}
	}
	else if (env->b_three == 1)
	{
		env->b_three = 0;
		if (e->button.x >= 385 && e->button.x <= 638 && 
		e->button.y >= 595 && e->button.y <= 714)
		{
			env->state = 1;
			env->mode = 3;
		}
	}
}

void handle_events_game_mode(t_env *env, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			if (e->button.state == SDL_PRESSED)
				handle_down(env, e);
		}
		else if (e->type == SDL_MOUSEBUTTONUP)
			handle_up(env, e);
	}
}
