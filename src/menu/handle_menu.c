/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 05:31:48 by drestles          #+#    #+#             */
/*   Updated: 2019/04/08 06:05:21 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void handle_down(t_env *env, SDL_Event *e)
{
	if (e->button.x >= 290 && e->button.x <= 735 && 
	e->button.y >= 403 && e->button.y <= 508)
		env->b_one = 1;
	else if (e->button.x >= 390 && e->button.x <= 620 && 
	e->button.y >= 520 && e->button.y <= 630)
		env->b_three = 1;
	else if (e->button.x >= 420 && e->button.x <= 600 && 
	e->button.y >= 650 && e->button.y <= 750)
		env->b_four = 1;
}

static void handle_up(t_env *env, SDL_Event *e)
{
	if (env->b_one == 1)
	{
		env->b_one = 0;
		if (e->button.x >= 290 && e->button.x <= 735 && 
		e->button.y >= 403 && e->button.y <= 508)
			env->state = 5;
	}
	else if (env->b_three == 1)
	{
		env->b_three = 0;
		if (e->button.x >= 390 && e->button.x <= 620 && 
		e->button.y >= 520 && e->button.y <= 630)
			env->state = 4;
	}
	else if (env->b_four == 1)
	{
		env->b_four = 0;
		if (e->button.x >= 420 && e->button.x <= 600 && 
		e->button.y >= 650 && e->button.y <= 750)
			{
				env->state = 1;
				env->quit = 1;
			}
	}
}

void handle_events_menu(t_env *env, SDL_Event *e)
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
