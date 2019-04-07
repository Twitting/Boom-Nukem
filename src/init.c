/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:38:09 by twitting          #+#    #+#             */
/*   Updated: 2019/04/07 18:33:03 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	findbutton(t_env *env)
{
	unsigned int	s;
	unsigned int	i;
	double			x;
	double			y;
	
	i = 0;
	
	while (i < env->butcount)
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
						y = env->button[i].y1 + env->button[i].width;
					else
						y = env->button[i].y1 - env->button[i].width;
				}
				else if (env->sector[i].vertex[s % env->sector[i].npoints].y == env->sector[i].vertex[(s + 1) % env->sector[i].npoints].y)
				{
					y = env->button[i].y1;
					if (env->sector[i].vertex[s % env->sector[i].npoints].x < env->sector[i].vertex[(s + 1) % env->sector[i].npoints].x)
						x = env->button[i].x1 + env->button[i].width;
					else
						x = env->button[i].x1 - env->button[i].width;			
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
					while (((x - env->button[i].x1) * (x - env->button[i].x1) + (y -  env->button[i].y1) * (y -  env->button[i].y1)) < env->button[i].width)
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
	// printf("%f %f\n", env->button[0].x1, env->button[0].y1);
	// printf("%f %f\n", env->button[0].x2, env->button[0].y2);
	// printf("%f %f\n", env->button[1].x1, env->button[1].y1);
	// printf("%f %f\n", env->button[1].x2, env->button[1].y2);
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
	int	i;
	int j;
	int k;
	int	tex;
	unsigned char *pix;
	
	tex = -1;
	while (++tex < 3)
	{
		i = -1;
		while (++i < (int)env->nsectors)
		{
			if (env->sector[i].sky == 1)
				env->sector[i].light = 100;
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

void	initspritelight(t_env *env)
{
	int	i;

	i = -1;
	
	while (++i < env->sprcount)
	{
		spritelightapply(env, &env->sprite[i]);
	}
}

void	init(t_env *env)
{
	env->yaw = 0;
	env->quit = 0;
	env->ground = 0;
	env->falling = 1;
	env->ducking = 0;
	env->player.eye = EYEHEIGHT;
	env->fps = 0;
	env->oldfps = 60;
	env->timer = 0;
	env->butcount = 2;//!!!!!!!!!!!!MAKE IT IN PARSER
	// env->sector[0].ceiling *= -1;
	// env->sector[0].sky = 1;
	// env->sector[1].sky = 1;
	// env->sector[2].sky = 0;
	// env->sector[3].sky = 0;
	// env->sector[4].sky = 0;
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
	 env->button = (t_button *)malloc(sizeof(t_button) * env->butcount);
	env->button[0].width = 2;
	env->button[0].height = 4;
	env->button[0].sector = 0;
	env->button[1].width = 2;
	env->button[1].height = 4;
	env->button[1].sector = 1;
	findbutton(env);
	// if (!(env->sprite = (t_sprite *)malloc(sizeof(t_sprite) * env->sprcount)))
	// 	ft_error(2);
	printf("%d\n", env->butcount);
	env->sprite[3].pos1.x = env->vertex[6].x;
	env->sprite[3].pos1.y = env->vertex[6].y;
	env->sprite[3].pos2.x = env->vertex[9].x;
	env->sprite[3].pos2.y = env->vertex[9].y;
	env->sprite[3].height = 30;
	env->sprite[3].floor = 0;
	env->sprite[3].type = 2;
	env->sprite[3].sector = 0;
	// env->sprite[0].x = 24;
	// env->sprite[0].y = 40;
	// env->sprite[0].height = 12;
	// env->sprite[0].width = 4;
	// env->sprite[0].sector = 0;
	// env->sprite[1].x = 35;
	// env->sprite[1].y = 48;
	// env->sprite[1].height = 12;
	// env->sprite[1].width = 4;
	// env->sprite[1].sector = 1;
	// env->sprite[2].x = 19;
	// env->sprite[2].y = 45;
	// env->sprite[2].height = 12;
	// env->sprite[2].width = 4;
	// env->sprite[2].sector = 0;
	}
}
