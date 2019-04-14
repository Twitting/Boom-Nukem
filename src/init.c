/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:10:22 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 12:29:22 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	texnulling(t_env *env)
{
	int i;
	int	j;

	i = -1;
	while (++i < env->sprcount && env->sprite[i].type != 2)
	{
		j = -1;
		while (++j < 8 && env->sprite[i].type != 2)
			env->sprite[i].texture[j] = NULL;
	}
	i = -1;
	while (++i < (int)env->nsectors)
	{
		j = -1;
		while (++j < 3)
			env->sector[i].text[j] = NULL;
	}
}

void	init_support(t_env *env)
{
	if (!(env->window = SDL_CreateWindow("Doom Nukem 2,5D",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WWIN, HWIN, SDL_WINDOW_OPENGL + SDL_WINDOW_ALLOW_HIGHDPI)))
		ft_error(4);
	env->surface = SDL_GetWindowSurface(env->window);
	initspritelight(env);
	findbutton(env);
}

void	init_music(t_env *env)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	env->volume = Mix_VolumeMusic(-1);
	env->music[0] = Mix_LoadMUS("music/2.mp3");
	env->music[1] = Mix_LoadMUS("music/1.mp3");
	env->sound[0] = Mix_LoadWAV("music/pistol_1.wav");
	Mix_VolumeChunk(env->sound[0], MIX_MAX_VOLUME / 4);
	env->sound[2] = Mix_LoadWAV("music/pistol_pere.wav");
	env->sound[3] = Mix_LoadWAV("music/oy_1.wav");
	env->sound[4] = Mix_LoadWAV("music/oy_2.wav");
	env->sound[5] = Mix_LoadWAV("music/pik.wav");
	env->sound[6] = Mix_LoadWAV("music/mob_2.wav");
	env->sound[7] = Mix_LoadWAV("music/mob_3.wav");
	env->sound[8] = Mix_LoadWAV("music/jump_1.wav");
	env->sound[9] = Mix_LoadWAV("music/jump_2.wav");
	env->sound[10] = Mix_LoadWAV("music/up_and_down.wav");
}

void	init_fonts(t_env *env)
{
	TTF_Init();
	env->fonts[0] = TTF_OpenFont("fonts/Pasajero.otf", 40);
	env->fonts[1] = TTF_OpenFont("fonts/Pasajero.otf", 50);
	env->fonts[2] = TTF_OpenFont("fonts/Pasajero.otf", 30);
}

void	init(t_env *env)
{
	int		i;

	i = 0;
	env->yaw = 0;
	env->quit = 0;
	env->shooting = 0;
	env->ground = 0;
	env->falling = 1;
	env->ducking = 0;
	env->fps = 0;
	env->oldfps = 60;
	env->timer = 0;
	env->jetpack = 0;
	ft_bzero(env->wsad, 16);
	while (i++ < 4)
		save_game1(env, i);
	sectorlightapply(env);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_error(4);
	else
		init_support(env);
	init_music(env);
	init_fonts(env);
}
