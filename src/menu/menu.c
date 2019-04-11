/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 02:45:02 by drestles          #+#    #+#             */
/*   Updated: 2019/04/11 23:03:53 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** STATE 2 PAUSE
*/
void menu_pause(t_env *env, SDL_Event *e)
{
	SDL_Surface *button;
	env->b_one = 0;
	env->b_four = 0;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	button = SDL_LoadBMP("img/pause.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	while (env->state == 2)
	{
		if (env->b_one == 1 || env->b_two == 1 || env->b_three == 1 || env->b_four == 1)
		{
			if (env->b_one == 1)
				button = SDL_LoadBMP("img/pause_1.bmp");
			else if (env->b_two == 1)
				button = SDL_LoadBMP("img/pause_2.bmp");
			else if (env->b_three == 1)
				button = SDL_LoadBMP("img/pause_3.bmp");
			else if (env->b_four == 1)
				button = SDL_LoadBMP("img/pause_4.bmp");
			SDL_BlitScaled(button, NULL, env->surface, NULL);
			SDL_FreeSurface(button);
			SDL_UpdateWindowSurface(env->window);
		}
		handle_events_pause(env, e);
	}
}

/*
** STATE 3 SAVE
*/
void save_game(t_env *env, SDL_Event *e)
{
	SDL_Surface *button;
	button = SDL_LoadBMP("img/save.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env->state == 3)
	{
		if (env->b_one == 1 || env->b_two == 1 || env->b_three == 1 || env->b_four == 1)
		{
			if (env->b_one == 1)
				button = SDL_LoadBMP("img/save_1.bmp");
			else if (env->b_two == 1)
				button = SDL_LoadBMP("img/save_2.bmp");
			else if (env->b_three == 1)
				button = SDL_LoadBMP("img/save_3.bmp");
			else if (env->b_four == 1)
				button = SDL_LoadBMP("img/save_4.bmp");
			SDL_BlitScaled(button, NULL, env->surface, NULL);
			SDL_FreeSurface(button);
			SDL_UpdateWindowSurface(env->window);
		}
		handle_events_save(env, e);
	}
}

/*
** STATE 4 LOAD
*/
void load_game(t_env *env, SDL_Event *e)
{
	SDL_Surface *button;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	button = SDL_LoadBMP("img/load.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	while (env->state == 4)
	{
		if (env->b_one == 1 || env->b_two == 1 || env->b_three == 1 || env->b_four == 1)
		{
			if (env->b_one == 1)
				button = SDL_LoadBMP("img/load_1.bmp");
			else if (env->b_two == 1)
				button = SDL_LoadBMP("img/load_2.bmp");
			else if (env->b_three == 1)
				button = SDL_LoadBMP("img/load_3.bmp");
			else if (env->b_four == 1)
				button = SDL_LoadBMP("img/load_4.bmp");
			SDL_BlitScaled(button, NULL, env->surface, NULL);
			SDL_FreeSurface(button);
			SDL_UpdateWindowSurface(env->window);
		}
		handle_events_load(env, e);
	}
}

/*
** STATE 5 GAME MODE
*/
void game_mode(t_env *env, SDL_Event *e)
{
	SDL_Surface *button = NULL;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	env->b_one = 0;
	env->b_two = 0;
	env->b_three = 0;
	button = SDL_LoadBMP("img/game_mode.bmp");
	SDL_BlitScaled(button, NULL, env->surface, NULL);
	SDL_FreeSurface(button);
	SDL_UpdateWindowSurface(env->window);
	while (env->state == 5)
	{
		if (env->b_one == 1 | env->b_two == 1 | env->b_three == 1)
		{
			if (env->b_one == 1)
				button = SDL_LoadBMP("img/game_mode_1.bmp");
			else if (env->b_two == 1)
				button = SDL_LoadBMP("img/game_mode_2.bmp");
			else if (env->b_three == 1)
				button = SDL_LoadBMP("img/game_mode_3.bmp");
			SDL_BlitScaled(button, NULL, env->surface, NULL);
			SDL_FreeSurface(button);
			SDL_UpdateWindowSurface(env->window);
		}
		handle_events_game_mode(env, e);
	}
}

void	save_game1(t_env *env, int i)
{
	FILE			*outfile;
	char			str[20];

	i == 4 ? i = 0 : i;
	env->save[i] = env->player;
	int j = 0;
	

	while(j < env->sprcount){

			printf("j: %d  x: %f  y:  %f\n", j, env->sprite[j].pos1.x, env->sprite[j].pos1.y);
			strcpy(str, "./save/1/");
			strcat(str, ft_itoa(j));
			strcat(str, "mob.dat");
			printf("str: %s\n", str);
			outfile = fopen(str, "w");
			fwrite(&env->sprite[j], sizeof(t_sprite), 1, outfile);
		j++;
	}
	if (i == 0)
		outfile = fopen("./save/1/player.dat", "w");
	if (i == 1)
		outfile = fopen("./save/2/player.dat", "w");
	if (i == 2)
		outfile = fopen("./save/3/player.dat", "w");
	if (i == 3)
		outfile = fopen("./save/4/player.dat", "w");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit(1);
	}
	fwrite(&env->save[i], sizeof(t_env), 1, outfile);
	if (&fwrite != 0)
		printf("contents to file %d written successfully !\n", i);
	else
		printf("error writing file !\n");
	fclose(outfile);
	i++;
}

void	load_player_init(t_env *env)
{
	env->player = env->save[env->save_number];

	// int j = 0;
	// char			str[20];

	// while(j < env->sprcount){

			
	// 		strcpy(str, "./save/1/");
	// 		strcat(str, ft_itoa(j));
	// 		strcat(str, "mob.dat");
	// 		printf("strL: %s\n", str);
	// 		//outfile = fopen(str, "w");
	// 		fread(&env->sprite[j] , sizeof(t_sprite), 1, fopen(str, "r"));
	// 		printf("j: %d  x: %f  y:  %f\n", j, env->sprite[j].pos1.x, env->sprite[j].pos1.y);
	// 		//fwrite(&env->sprite[j], sizeof(t_sprite), 1, outfile);

	// 	j++;
	// }



}
