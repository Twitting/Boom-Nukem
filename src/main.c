/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:20:03 by twitting          #+#    #+#             */
/*   Updated: 2019/04/07 23:28:07 by drestles         ###   ########.fr       */
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

void handle_events_menu(t_env *env, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_g)
			env->state = 1;
		else if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			if (e->button.state == SDL_PRESSED)
			{
				if (e->button.x >= 290 && e->button.x <= 735 && 
					e->button.y >= 403 && e->button.y <= 508)
						env->ng = 1;
				else if (e->button.x >= 390 && e->button.x <= 620 && 
					e->button.y >= 520 && e->button.y <= 630)
						env->load = 1;
				else if (e->button.x >= 420 && e->button.x <= 600 && 
					e->button.y >= 650 && e->button.y <= 750)
						env->q = 1;
			}
		}
		else if (e->type == SDL_MOUSEBUTTONUP)
		{
			if (env->ng == 1)
			{
				env->ng = 0;
				if (e->button.x >= 290 && e->button.x <= 735 && 
					e->button.y >= 403 && e->button.y <= 508)
					env->state = 1;
			}
			else if (env->load == 1)
			{
				env->load = 0;
				if (e->button.x >= 390 && e->button.x <= 620 && 
					e->button.y >= 520 && e->button.y <= 630)
					env->state = 0;
				/////////////////////////    загружаем карту <<<<<<<<<<<<----------------------
			}
			else if (env->q == 1)
			{
				env->q = 0;
				if (e->button.x >= 420 && e->button.x <= 600 && 
					e->button.y >= 650 && e->button.y <= 750)
					{
						env->state = 1;
						env->quit = 1;
					}
			}
		}
	}
}

void menu(t_env *env, SDL_Event *e)
{
	env->ng = 0;
	env->q = 0;
	while (env->state == 0)
	{
		SDL_Rect rect;
		rect.x = 320;
		rect.y = 200;
		rect.h = 100;
		rect.w = 400;
		SDL_Surface *button;
		button = SDL_LoadBMP("img/menu.bmp");
		if (env->ng == 1)
			button = SDL_LoadBMP("img/menu_1.bmp");
		if (env->load == 1)
			button = SDL_LoadBMP("img/menu_2.bmp"); 
		if (env->q == 1)
			button = SDL_LoadBMP("img/menu_3.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_UpdateWindowSurface(env->window);
		handle_events_menu(env, e);
	}
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
			{
				if (e->button.x >= 267 && e->button.x <= 750 && 
					e->button.y >= 40 && e->button.y <= 184)
						env->ng = 1;
				else if (e->button.x >= 360 && e->button.x <= 662 && 
					e->button.y >= 223 && e->button.y <= 366)
						env->save = 1;
				else if (e->button.x >= 363 && e->button.x <= 662 && 
					e->button.y >= 407 && e->button.y <= 549)
						env->load = 1;
				else if (e->button.x >= 385 && e->button.x <= 628 && 
					e->button.y >= 594 && e->button.y <= 735)
						env->q = 1;
			}
		}
		else if (e->type == SDL_MOUSEBUTTONUP)
		{
			if (env->ng == 1)
			{
				env->ng = 0;
				if (e->button.x >= 267 && e->button.x <= 750 && 
					e->button.y >= 40 && e->button.y <= 184)
					env->state = 1;
			}
			else if (env->save == 1)
			{
				env->save = 0;
				if (e->button.x >= 360 && e->button.x <= 662 && 
					e->button.y >= 223 && e->button.y <= 366)
					env->state = 2;
				/////////////////////////    сохраняем карту <<<<<<<<<<<<----------------------
			}
			else if (env->load == 1)
			{
				env->load = 0;
				if (e->button.x >= 363 && e->button.x <= 662 && 
					e->button.y >= 407 && e->button.y <= 549)
					env->state = 2;
				/////////////////////////    загружаем карту <<<<<<<<<<<<----------------------
			}
			else if (env->q == 1)
			{
				env->q = 0;
				if (e->button.x >= 385 && e->button.x <= 628 && 
					e->button.y >= 594 && e->button.y <= 735)
					{
						env->state = 1;
						env->quit = 1;
					}
			}
		}
	}
}

void menu_pause(t_env *env, SDL_Event *e)
{
	env->ng = 0;
	env->q = 0;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env->state == 2)
	{
		SDL_Rect rect;
		rect.x = 320;
		rect.y = 200;
		rect.h = 100;
		rect.w = 400;
		SDL_Surface *button;
		button = SDL_LoadBMP("img/pause.bmp");
		if (env->ng == 1)
			button = SDL_LoadBMP("img/pause_1.bmp");
		if (env->save == 1)
			button = SDL_LoadBMP("img/pause_2.bmp");
		if (env->load == 1)
			button = SDL_LoadBMP("img/pause_3.bmp");
		if (env->q == 1)
			button = SDL_LoadBMP("img/pause_4.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_UpdateWindowSurface(env->window);
		handle_events_pause(env, e);
	}
}

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
