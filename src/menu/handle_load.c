/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 05:38:44 by drestles          #+#    #+#             */
/*   Updated: 2019/04/10 14:47:45 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void handle_down(t_env *env, SDL_Event *e)
{
	if (e->button.x >= 93 && e->button.x <= 345 && 
	e->button.y >= 178 && e->button.y <= 415)
		env->b_one = 1;
	else if (e->button.x >= 680 && e->button.x <= 934 && 
	e->button.y >= 178 && e->button.y <= 411)
		env->b_two = 1;
	else if (e->button.x >= 186 && e->button.x <= 442 && 
	e->button.y >= 500 && e->button.y <= 735)
		env->b_three = 1;
	else if (e->button.x >= 580 && e->button.x <= 833 && 
	e->button.y >= 500 && e->button.y <= 734)
		env->b_four = 1;
}

static void button_one(t_env *env, SDL_Event *e)
{
	env->b_one = 0;
	if (e->button.x >= 93 && e->button.x <= 345 && 
	e->button.y >= 178 && e->button.y <= 415)
		env->state = 1;
		env->save_number = 0;
		load_player_init(env);
	/////////////////////////    загружаем карту из 1 файла <<<<<<<<<<<<----------------------
}

static void button_two(t_env *env, SDL_Event *e)
{
	env->b_two = 0;
	if (e->button.x >= 680 && e->button.x <= 934 && 
	e->button.y >= 178 && e->button.y <= 411)
		env->state = 1;
		env->save_number = 1;
		load_player_init(env);
	/////////////////////////    загружаем карту из 2 файла<<<<<<<<<<<<----------------------
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
		if (e->button.x >= 186 && e->button.x <= 442 && 
		e->button.y >= 500 && e->button.y <= 735)
			env->state = 1;
			env->save_number = 2;
			load_player_init(env);
			/////////////////////////     загружаем карту из 3 файла<<<<<<<<<<<<----------------------
	}
	else if (env->b_four == 1)
	{
		env->b_four = 0;
		if (e->button.x >= 580 && e->button.x <= 833 && 
		e->button.y >= 500 && e->button.y <= 734)
		{
			env->state = 1;
			env->save_number = 3;
			load_player_init(env);
			/////////////////////////     загружаем карту из 4 файла<<<<<<<<<<<<----------------------
		}
	}
}

void handle_events_load(t_env *env, SDL_Event *e)
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
