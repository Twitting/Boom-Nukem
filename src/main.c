/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:20:03 by twitting          #+#    #+#             */
/*   Updated: 2019/04/03 14:13:08 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	fps(t_env *env)
{
	env->fps++;
	env->timer += (clock() - env->frame) / CLOCKS_PER_SEC;
	if (env->timer >= 1.0)
	{
		ft_putstr("fps = ");
		ft_putnbr(env->fps);
		ft_putchar('\n');
		env->oldfps = env->fps;
		env->fps = 0;
		env->timer -= 1;
	}
}

void	ft_error(int errnum)
{
	if (errnum == 1)
		ft_putendl_fd("FFFFFFFFFreeeee", 2);
	if (errnum == 2)
		ft_putendl_fd("Memory allocation error, aborting...", 2);
	if (errnum == 3)
		ft_putendl_fd("Something wrong with map file, aborting...", 2);
	if (errnum == 4)
		ft_putendl_fd("SDL initialization has failed, aborting...", 2);
	exit(errnum);
}

int		main(void)
{
	t_env		*env;
	SDL_Event	e;

	env = structure_init();
	init(env);
	inittext(env);
	SDL_ShowCursor(SDL_DISABLE);
	while (!(env->quit))
	{
		env->frame = clock();
		start_engine(env, &e);
		fps(env);
	}
	SDL_DestroyWindow(env->window);
	SDL_Quit();
	return (0);
}
