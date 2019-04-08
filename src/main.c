/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:20:03 by twitting          #+#    #+#             */
/*   Updated: 2019/04/08 03:16:03 by drestles         ###   ########.fr       */
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

/*
** STATE 0 MENU 
** STATE 1 GAME
** STATE 2 PAUSE
** STATE 3 SAVE
** STATE 4 LOAD
*/

void start(t_env *env, SDL_Event *e)
{
	if (env->state == 0)
		menu(env, e);
	else if (env->state == 1)
	{
		env->frame = clock();
		start_engine(env, e);
		fps(env);
	}
	else if (env->state == 2)
		menu_pause(env, e);
	else if (env->state == 3)
		save_game(env, e);
	else if (env->state == 4)
		load_game(env, e);
}

int		main(void)
{
	t_env		*env;
	SDL_Event	e;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		ft_error(2);
	ft_strcpy(env->mapname, "test.map");
	grandparser(env);
	init(env);
	inittext(env);
	env->state = 0;
	while (!(env->quit))
	{
		start(env, &e);
		// env->frame = clock();
		// start_engine(env, &e);
		// fps(env);
	}
	SDL_DestroyWindow(env->window);
	SDL_Quit();
	return (0);
}
