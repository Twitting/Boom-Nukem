/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:38:09 by twitting          #+#    #+#             */
/*   Updated: 2019/04/11 15:46:21 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	findbutton(t_env *env)
{
	unsigned int	s;
	unsigned int	i;
	double			x;
	double			y;

	i = 0;
	while (i < env->nsectors)
	{
		s = -1;
		while (++s < env->sector[i].npoints)
		{
			if (env->sector[i].neighbors[s] == -2)
			{
				env->button[i].x1 = (env->sector[i].vertex[s % env->sector[i].npoints].x + env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x) / 2;
				env->button[i].y1 = (env->sector[i].vertex[s % env->sector[i].npoints].y + env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y) / 2;
				if (env->sector[i].vertex[s % env->sector[i].npoints].x == env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x)
				{
					x = env->button[i].x1;
					if (env->sector[i].vertex[s % env->sector[i].npoints].y < env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y)
						y = env->button[i].y1 + BUTTONWIDTH;
					else
						y = env->button[i].y1 - BUTTONWIDTH;
				}
				else if (env->sector[i].vertex[s % env->sector[i].npoints].y == env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y)
				{
					y = env->button[i].y1;
					if (env->sector[i].vertex[s % env->sector[i].npoints].x < env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x)
						x = env->button[i].x1 + BUTTONWIDTH;
					else
						x = env->button[i].x1 - BUTTONWIDTH;
				}
				else
				{
					if (env->sector[i].vertex[s % env->sector[i].npoints].x < env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x)
						x = env->button[i].x1 + 0.1;
					else
						x = env->button[i].x1 - 0.1;
					y = (x - env->sector[i].vertex[s % env->sector[i].npoints].x) *
					(env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y -
					env->sector[i].vertex[s % env->sector[i].npoints].y) / (env->sector[i].vertex[(s + 1) %
					env->sector[i].npoints].x - env->sector[i].vertex[s % env->sector[i].npoints].x) +
					env->sector[i].vertex[s % env->sector[i].npoints].y;
					while (((x - env->button[i].x1) * (x - env->button[i].x1) + (y - env->button[i].y1) * (y - env->button[i].y1)) < BUTTONWIDTH)
					{
						y = (x - env->sector[i].vertex[s % env->sector[i].npoints].x) *
						(env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y -
						env->sector[i].vertex[s % env->sector[i].npoints].y) / (env->sector[i].vertex[(s + 1) %
						env->sector[i].npoints].x - env->sector[i].vertex[s % env->sector[i].npoints].x) +
						env->sector[i].vertex[s % env->sector[i].npoints].y;
						if (env->sector[i].vertex[s % env->sector[i].npoints].x < env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x)
							x += 0.1;
						else
							x -= 0.1;
					}
				}
				env->button[i].x2 = x;
				env->button[i].y2 = y;
			}
		}
		i++;
	}
}

char	*gettex(t_env *env, int secnum, int tex)
{
	if (((TEXP == 0 || TEXP == 4) && tex == 0) || (TEXP == 5 && tex == 2))
		return ("textures/asphalt.tga");
	if ((TEXP == 0 && tex == 1) || (TEXP == 1 && tex == 1))
		return ("textures/brick.tga");
	if (((TEXP == 0 || TEXP == 1 || TEXP == 2) && tex == 2) || TEXP == 2)
		return ("textures/metal.tga");
	if (((TEXP == 1 || TEXP == 5) && tex == 0) || (TEXP == 3 && tex == 1))
		return ("textures/stone.tga");
	return ("textures/wood.tga");
}

void	sectorlightapply(t_env *env)
{
	int				i;
	int				j;
	int				k;
	int				tex;
	unsigned char	*pix;

	tex = -1;
	while (++tex < 3)
	{
		i = -1;
		while (++i < (int)env->nsectors)
		{
			if (env->sector[i].sky == 1)
				env->sector[i].light = 100;
			if (env->sector[i].text[tex] != NULL)
				SDL_FreeSurface(env->sector[i].text[tex]);
			env->sector[i].text[tex] = IMG_Load(gettex(env, i, tex));
			pix = (unsigned char *)env->sector[i].text[tex]->pixels;
			j = -1;
			while (++j < env->sector[i].text[tex]->h)
			{
				k = -1;
				while (++k < env->sector[i].text[tex]->w)
				{
					pix[(j * env->sector[i].text[tex]->w + k) * 4] = (unsigned char)((double)pix[(j * env->sector[i].text[tex]->w + k) * 4] / 100 * env->sector[i].light);
					pix[(j * env->sector[i].text[tex]->w + k) * 4 + 1] = (unsigned char)((double)pix[(j * env->sector[i].text[tex]->w + k) * 4 + 1] / 100 * env->sector[i].light);
					pix[(j * env->sector[i].text[tex]->w + k) * 4 + 2] = (unsigned char)((double)pix[(j * env->sector[i].text[tex]->w + k) * 4 + 2] / 100 * env->sector[i].light);
				}
			}
		}
	}
}

char	*gettexenemy(int tex)
{
	if (tex == 0)
		return ("textures/1.png");
	else if (tex == 1)
		return ("textures/2.png");
	else if (tex == 2)
		return ("textures/3.png");
	else if (tex == 3)
		return ("textures/4.png");
	else if (tex == 4)
		return ("textures/5.png");
	else if (tex == 5)
		return ("textures/6.png");
	else if (tex == 6)
		return ("textures/7.png");
	return ("textures/dead.png");
}

void	enemylightapply(t_env *env, t_sprite *sprite, int tex)
{
	int				j;
	int				k;
	unsigned char	*pix;

	sprite->hp = 100;
	sprite->movecount = 0;
	sprite->texnum = 0;
	env->sprite->mobtimer = 0;
	if (sprite->texture[tex] != NULL)
		SDL_FreeSurface(sprite->texture[tex]);
	sprite->texture[tex] = IMG_Load(gettexenemy(tex));
	pix = (unsigned char *)sprite->texture[tex]->pixels;
	j = -1;
	while (++j < sprite->texture[tex]->h)
	{
		k = -1;
		while (++k < sprite->texture[tex]->w - 1)
		{
			pix[(j * sprite->texture[tex]->w + k) * 4] = (unsigned char)((double)pix[(j * sprite->texture[tex]->w + k) * 4] / 100 * env->sector[sprite->sector].light);
			pix[(j * sprite->texture[tex]->w + k) * 4 + 1] = (unsigned char)((double)pix[(j * sprite->texture[tex]->w + k) * 4 + 1] / 100 * env->sector[sprite->sector].light);
			pix[(j * sprite->texture[tex]->w + k) * 4 + 2] = (unsigned char)((double)pix[(j * sprite->texture[tex]->w + k) * 4 + 2] / 100 * env->sector[sprite->sector].light);
		}
	}
	env->fps++;
}

void	initspritelight(t_env *env)
{
	int	i;
	int	j;

	i = -1;
	while (++i < env->sprcount)
	{
		j = -1;
		if (env->sprite[i].type == 0)
			spritelightapply(env, &env->sprite[i]);
		if (env->sprite[i].type == 1)
			while (++j < 8)
				enemylightapply(env, &env->sprite[i], j);
	}
}

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

void	init(t_env *env)
{
	FILE	*input_file;
	int		i;

	i = 0;
	env->yaw = 0;
	env->player.hp = 100;
	env->quit = 0;
	env->shooting = 0;
	env->ground = 0;
	env->falling = 1;
	env->ducking = 0;
	env->player.eye = EYEHEIGHT;
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
	{
		if (!(env->window = SDL_CreateWindow("Doom Nukem 2,5D",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WWIN, HWIN, SDL_WINDOW_OPENGL + SDL_WINDOW_ALLOW_HIGHDPI)))
			ft_error(4);
		env->surface = SDL_GetWindowSurface(env->window);
		initspritelight(env);
		findbutton(env);
	}
	if ((input_file = fopen("./save/1/player.dat", "r")))
		fread(&env->save[0], sizeof(t_player), 1, input_file);
	if ((input_file = fopen("./save/2/player.dat", "r")))
		fread(&env->save[1], sizeof(t_player), 1, input_file);
	if ((input_file = fopen("./save/3/player.dat", "r")))
		fread(&env->save[2], sizeof(t_player), 1, input_file);
	if ((input_file = fopen("./save/4/player.dat", "r")))
		fread(&env->save[3], sizeof(t_player), 1, input_file);
}
