/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:20:56 by drestles          #+#    #+#             */
/*   Updated: 2019/04/13 19:02:25 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	handle_down(t_env *env, SDL_Event *e)
{
	if (e->button.x >= 72 && e->button.x <= 940 &&
	e->button.y >= 275 && e->button.y <= 445)
		env->b_one = 1;
}

static void	handle_up(t_env *env, SDL_Event *e)
{
	if (env->b_one == 1)
	{
		env->b_one = 0;
		if (e->button.x >= 72 && e->button.x <= 940 &&
	e->button.y >= 275 && e->button.y <= 445)
		{
			env->state = 1;
			env->quit = 1;
		}
	}
}

void		handle_events_game_over(t_env *env, SDL_Event *e)
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

void		game_over(t_env *env, SDL_Event *e)
{
	SDL_Surface	*button;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	button = SDL_LoadBMP("img/game_over_0.bmp");
	/* long long i = 0;
	while (i < WWIN * HWIN)
	{
		long long ran = random() % (WWIN * HWIN - 2) + 1;

		//printf ("%lld\n", ran);
		((int *)(env->surface->pixels))[ran] = ((int *)(button->pixels))[ran];
		SDL_UpdateWindowSurface(env->window);
		i++;
	} */
	int i = 0;
	//int time_o;
	while (i < 48)
	{
		env->head_shot++;
		if (env->head_shot > 30000000)
			env->head_shot = 0;
		//time_o = env->head_shot % 100000;
		//printf ("");
		if (env->head_shot == 0)
		{
			env->head++;
			SDL_BlitScaled(env->game_over[i], NULL, env->surface, NULL);
			SDL_UpdateWindowSurface(env->window);
			i++;
		}
	}

	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	while (env->state == 6)
	{
		if (env->b_one == 1)
		{
			if (env->b_one == 1)
				button = SDL_LoadBMP("img/game_over_1.bmp");
			SDL_BlitScaled(button, NULL, env->surface, NULL);
			SDL_FreeSurface(button);
			SDL_UpdateWindowSurface(env->window);
		}
		handle_events_game_over(env, e);
	}
}
