/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:52:25 by twitting          #+#    #+#             */
/*   Updated: 2019/03/07 22:12:56 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	handle_events(t_env *env, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			env->quit = 1;
		if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_ESCAPE)
			env->quit = 1;
	}
}