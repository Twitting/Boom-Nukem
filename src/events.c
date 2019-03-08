/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:52:25 by twitting          #+#    #+#             */
/*   Updated: 2019/03/08 18:58:28 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	handle_events(t_env *env, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			env->quit = 1;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
			env->quit = 1;
		if (e->type == SDL_KEYDOWN)
		{
			if (e->key.keysym.sym == SDLK_w)
				movement(env, 1, 0);
			if (e->key.keysym.sym == SDLK_s)
				movement(env, -1, 0);
			if (e->key.keysym.sym == SDLK_a)
				movement(env, 0, -1);
			if (e->key.keysym.sym == SDLK_d)
				movement(env, 0, 1);
		}
	}
	int x,y;
	SDL_GetRelativeMouseState(&x,&y);
	env->player.angle += x * 0.03;
		
		//if (e->type == SDL_MOUSEMOTION)
		//{
		//}
}