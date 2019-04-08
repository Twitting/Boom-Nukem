/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 02:45:02 by drestles          #+#    #+#             */
/*   Updated: 2019/04/08 03:18:18 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

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
		}
		else if (e->type == SDL_MOUSEBUTTONUP)
		{
			if (env->b_one == 1)
			{
				env->b_one = 0;
				if (e->button.x >= 267 && e->button.x <= 750 && 
					e->button.y >= 40 && e->button.y <= 184)
					env->state = 1;
			}
			else if (env->b_two == 1)
			{
				env->b_two = 0;
				if (e->button.x >= 360 && e->button.x <= 662 && 
					e->button.y >= 223 && e->button.y <= 366)
					env->state = 3;
			}
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
	}
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
						env->b_one = 1;
				else if (e->button.x >= 390 && e->button.x <= 620 && 
					e->button.y >= 520 && e->button.y <= 630)
						env->b_three = 1;
				else if (e->button.x >= 420 && e->button.x <= 600 && 
					e->button.y >= 650 && e->button.y <= 750)
						env->b_four = 1;
			}
		}
		else if (e->type == SDL_MOUSEBUTTONUP)
		{
			if (env->b_one == 1)
			{
				env->b_one = 0;
				if (e->button.x >= 290 && e->button.x <= 735 && 
					e->button.y >= 403 && e->button.y <= 508)
					env->state = 1;
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
	}
}

void handle_events_save(t_env *env, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_g)
			env->state = 1;
		else if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			if (e->button.state == SDL_PRESSED)
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
		}
		else if (e->type == SDL_MOUSEBUTTONUP)
		{
			if (env->b_one == 1)
			{
				env->b_one = 0;
				if (e->button.x >= 93 && e->button.x <= 345 && 
					e->button.y >= 178 && e->button.y <= 415)
					env->state = 1;
				/////////////////////////    сохраняем карту в 1 файл <<<<<<<<<<<<----------------------
			}
			else if (env->b_two == 1)
			{
				env->b_two = 0;
				if (e->button.x >= 680 && e->button.x <= 934 && 
					e->button.y >= 178 && e->button.y <= 411)
					env->state = 1;
				/////////////////////////    сохраняем карту во 2 файл<<<<<<<<<<<<----------------------
			}
			else if (env->b_three == 1)
			{
				env->b_three = 0;
				if (e->button.x >= 186 && e->button.x <= 442 && 
					e->button.y >= 500 && e->button.y <= 735)
					env->state = 1;
				/////////////////////////     сохраняем карту в 3 файл<<<<<<<<<<<<----------------------
			}
			else if (env->b_four == 1)
			{
				env->b_four = 0;
				if (e->button.x >= 580 && e->button.x <= 833 && 
					e->button.y >= 500 && e->button.y <= 734)
					{
						env->state = 1;
						/////////////////////////     сохраняем карту в 4 файл<<<<<<<<<<<<----------------------
					}
			}
		}
	}
}

void handle_events_load(t_env *env, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_g)
			env->state = 1;
		else if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			if (e->button.state == SDL_PRESSED)
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
		}
		else if (e->type == SDL_MOUSEBUTTONUP)
		{
			if (env->b_one == 1)
			{
				env->b_one = 0;
				if (e->button.x >= 93 && e->button.x <= 345 && 
					e->button.y >= 178 && e->button.y <= 415)
					env->state = 1;
				/////////////////////////    загружаем карту из 1 файла <<<<<<<<<<<<----------------------
			}
			else if (env->b_two == 1)
			{
				env->b_two = 0;
				if (e->button.x >= 680 && e->button.x <= 934 && 
					e->button.y >= 178 && e->button.y <= 411)
					env->state = 1;
				/////////////////////////    загружаем карту из 2 файла<<<<<<<<<<<<----------------------
			}
			else if (env->b_three == 1)
			{
				env->b_three = 0;
				if (e->button.x >= 186 && e->button.x <= 442 && 
					e->button.y >= 500 && e->button.y <= 735)
					env->state = 1;
				/////////////////////////     загружаем карту из 3 файла<<<<<<<<<<<<----------------------
			}
			else if (env->b_four == 1)
			{
				env->b_four = 0;
				if (e->button.x >= 580 && e->button.x <= 833 && 
					e->button.y >= 500 && e->button.y <= 734)
					{
						env->state = 1;
						/////////////////////////     загружаем карту из 4 файла<<<<<<<<<<<<----------------------
					}
			}
		}
	}
}

void menu(t_env *env, SDL_Event *e)
{
	env->b_one = 0;
	env->b_four = 0;
	while (env->state == 0)
	{
		SDL_Rect rect;
		rect.x = 320;
		rect.y = 200;
		rect.h = 100;
		rect.w = 400;
		SDL_Surface *button;
		button = SDL_LoadBMP("img/menu.bmp");
		if (env->b_one == 1)
			button = SDL_LoadBMP("img/menu_1.bmp");
		if (env->b_three == 1)
			button = SDL_LoadBMP("img/menu_2.bmp"); 
		if (env->b_four == 1)
			button = SDL_LoadBMP("img/menu_3.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_FreeSurface(button);
		SDL_UpdateWindowSurface(env->window);
		handle_events_menu(env, e);
	}
}

void menu_pause(t_env *env, SDL_Event *e)
{
	env->b_one = 0;
	env->b_four = 0;
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
		if (env->b_one == 1)
			button = SDL_LoadBMP("img/pause_1.bmp");
		if (env->b_two == 1)
			button = SDL_LoadBMP("img/pause_2.bmp");
		if (env->b_three == 1)
			button = SDL_LoadBMP("img/pause_3.bmp");
		if (env->b_four == 1)
			button = SDL_LoadBMP("img/pause_4.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_FreeSurface(button);
		SDL_UpdateWindowSurface(env->window);
		handle_events_pause(env, e);
	}
}

void save_game(t_env *env, SDL_Event *e)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env->state == 3)
	{
		SDL_Rect rect;
		rect.x = 320;
		rect.y = 200;
		rect.h = 100;
		rect.w = 400;
		SDL_Surface *button;
		button = SDL_LoadBMP("img/save.bmp");
		if (env->b_one == 1)
			button = SDL_LoadBMP("img/save_1.bmp");
		if (env->b_two == 1)
			button = SDL_LoadBMP("img/save_2.bmp");
		if (env->b_three == 1)
			button = SDL_LoadBMP("img/save_3.bmp");
		if (env->b_four == 1)
			button = SDL_LoadBMP("img/save_4.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_FreeSurface(button);
		SDL_UpdateWindowSurface(env->window);
		handle_events_save(env, e);
	}
}

void load_game(t_env *env, SDL_Event *e)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env->state == 4)
	{
		SDL_Rect rect;
		rect.x = 320;
		rect.y = 200;
		rect.h = 100;
		rect.w = 400;
		SDL_Surface *button;
		button = SDL_LoadBMP("img/load.bmp");
		if (env->b_one == 1)
			button = SDL_LoadBMP("img/load_1.bmp");
		if (env->b_two == 1)
			button = SDL_LoadBMP("img/load_2.bmp");
		if (env->b_three == 1)
			button = SDL_LoadBMP("img/load_3.bmp");
		if (env->b_four == 1)
			button = SDL_LoadBMP("img/load_4.bmp");
		SDL_BlitScaled(button, NULL, env->surface, NULL);
		SDL_FreeSurface(button);
		SDL_UpdateWindowSurface(env->window);
		handle_events_load(env, e);
	}
}