/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:43:20 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/11 19:00:02 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void	drawsprite(t_env *env, t_rend *rend, int j)
{
	int	y;
	int	*pix;
	int	txty;

	pix = (int*)env->surface->pixels;
	pix += rend->csprya * WWIN + rend->sprx;
	y = rend->csprya - 1;
	
	//printf("!!!%d!!!\n", ((int *)(env->sprite[j].texture->pixels))[0]);
	
	while (++y <= rend->cspryb)
	{
		txty = (int)((double)(y - rend->sprya) / (double)(rend->spryb - rend->sprya) * env->sprite[j].texture[0]->h);
		if (y == HWIN / 2 && rend->sprx == WWIN / 2 && env->sprite[j].type == 1 &&
			((int *)(env->sprite[j].texture[0]->pixels))[txty % env->sprite[j].texture[0]->h * env->sprite[j].texture[0]->w + rend->txtx] != 0 &&//-16777216 && 
			((int *)(env->sprite[j].texture[0]->pixels))[txty % env->sprite[j].texture[0]->h * env->sprite[j].texture[0]->w + rend->txtx] != 0)
			env->player.target = j;
		if (((int *)(env->sprite[j].texture[0]->pixels))[txty % env->sprite[j].texture[0]->h * env->sprite[j].texture[0]->w + rend->txtx] != 0 &&//-16777216 && 
			((int *)(env->sprite[j].texture[0]->pixels))[txty % env->sprite[j].texture[0]->h * env->sprite[j].texture[0]->w + rend->txtx] != 0)
			*pix = ((int *)(env->sprite[j].texture[0]->pixels))[txty % env->sprite[j].texture[0]->h * env->sprite[j].texture[0]->w + rend->txtx];
		pix += WWIN;
	}

}

void	spriteplane(t_env *env, t_rend *rend, int j)
{
	t_sprque		now;

	
	now = rend->sprq[env->sprite[j].sector];
	if (now.visible == 0)
		return ;
	//printf("%d\n", j);
	rend->nowsect = &(env->sector[now.sector]);
	rend->vspr.x = env->sprite[j].pos1.x - env->player.where.x;
	rend->vspr.y = env->sprite[j].pos1.y - env->player.where.y;
	rend->tspr.x = rend->vspr.x * env->player.sinang - rend->vspr.y * env->player.cosang;
	rend->tspr1 = rend->tspr.x + env->sprite[j].width / 2;
	rend->tspr2 = rend->tspr.x - env->sprite[j].width / 2;
	rend->tspr.y = rend->vspr.x * env->player.cosang + rend->vspr.y * env->player.sinang;
	if (rend->tspr.y <= 0)
		return ;
	rend->sprxscale = WWIN * HFOV / rend->tspr.y;
	rend->spryscale = HWIN * VFOV / rend->tspr.y;
	rend->sprx1 = WWIN / 2 - (int)((rend->tspr1) * rend->sprxscale);
	rend->sprx2 = WWIN / 2 - (int)((rend->tspr2) * rend->sprxscale);
	if (rend->sprx1 > now.sx2 || rend->sprx2 < now.sx1)
		return ;
	if (rend->sprx1 + (rend->sprx2 - rend->sprx1) / 3 >= now.sx1 && rend->sprx2 - (rend->sprx2 - rend->sprx1) / 3 <= now.sx2)
		env->sprite[j].visible = 1;
	rend->sprceil =  rend->nowsect->floor + env->sprite[j].height - env->player.where.z;
	rend->sprfloor = rend->nowsect->floor - env->player.where.z;
	rend->sprya = HWIN / 2 - (int)(YAW(rend->sprceil, rend->tspr.y) * rend->spryscale);
	rend->spryb = HWIN / 2 - (int)(YAW(rend->sprfloor, rend->tspr.y) * rend->spryscale);
	rend->sprbegx = MAX(rend->sprx1, now.sx1);
	rend->sprendx = MIN(rend->sprx2, now.sx2);
	rend->sprx = rend->sprbegx;
	
	while (rend->sprx < rend->sprendx)
	{
		rend->csprya = CLAMP(rend->sprya, now.ytop[rend->sprx], now.ybottom[rend->sprx]);
		rend->cspryb = CLAMP(rend->spryb, now.ytop[rend->sprx], now.ybottom[rend->sprx]);
		rend->txtx = (int)((double)(rend->sprx - rend->sprx1) / (double)(rend->sprx2 - rend->sprx1) * env->sprite[j].texture[0]->w);
		//printf("%d\n", rend->sprx - rend->sprbegx);
		drawsprite(env, rend, j);
		rend->sprx++;
	}
}

void	sortsprite(t_env *env)
{
	int			f;
	int			i;
	t_sprite	temp;

	f = 1;
	while (f == 1)
	{
		f = 0;
		i = 0;
		while (i < env->sprcount - 1)
		{
			if (env->sprite[i].spritedist < env->sprite[i + 1].spritedist)
			{
				temp = env->sprite[i];
				env->sprite[i] = env->sprite[i + 1];
				env->sprite[i + 1] = temp;
				f = 1;
				break ;
			}
			i++;
		}
	}
}

void	rendersprite(t_env *env, t_rend *rend)
{
	int	i;
	int	x;
	int	y;

	i = -1;

	while (++i < env->sprcount) //
	{
		if (env->sprite[i].type == 2)
		{
			x = (env->sprite[i].pos1.x + env->sprite[i].pos2.x) / 2;
			y = (env->sprite[i].pos1.y + env->sprite[i].pos2.y) / 2;
			env->sprite[i].spritedist = (env->player.where.x - x) *
			(env->player.where.x - x) + (env->player.where.y - y) *
			(env->player.where.y - y);
		}
		else
			env->sprite[i].spritedist = (env->player.where.x - env->sprite[i].pos1.x) *
			(env->player.where.x - env->sprite[i].pos1.x) + (env->player.where.y -
			env->sprite[i].pos1.y) * (env->player.where.y - env->sprite[i].pos1.y);
		env->sprite[i].visible = 0;
	};
	sortsprite(env);
	i = -1;

	env->player.target = -1;
	while (++i < env->sprcount) //
	{
		if (env->sprite[i].spritedist <= 2 && env->sprite[i].type == 3)
		{
			if (env->sprite[i].width > 0)
				env->player.hp += 50;
			env->sprite[i].width = 0;
		}
		if (env->sprite[i].type != 2)
			spriteplane(env, rend, i);
		else
			trplane(env, rend, i);
	}
}

void	spritelightapply(t_env *env, t_sprite *sprite)
{
	int j;
	int k;
	unsigned char *pix;
	
	if (sprite->texture[0] != NULL)
		SDL_FreeSurface(sprite->texture[0]);
	sprite->texture[0] = sprite->type == 0 ? IMG_Load("textures/barrel.png") : IMG_Load("textures/med.png");
	pix = (unsigned char *)sprite->texture[0]->pixels;
	j = -1;
	while (++j < sprite->texture[0]->h)
	{
		k = -1;
		while (++k < sprite->texture[0]->w - 1)
		{
			pix[(j * sprite->texture[0]->w + k) * 4] = (unsigned char)((double)pix[(j * sprite->texture[0]->w + k) * 4] / 100 * env->sector[sprite->sector].light);
			pix[(j * sprite->texture[0]->w + k) * 4 + 1] = (unsigned char)((double)pix[(j * sprite->texture[0]->w + k) * 4 + 1] / 100 * env->sector[sprite->sector].light);
			pix[(j * sprite->texture[0]->w + k) * 4 + 2] = (unsigned char)((double)pix[(j * sprite->texture[0]->w + k) * 4 + 2] / 100 * env->sector[sprite->sector].light);
		}
	}
}