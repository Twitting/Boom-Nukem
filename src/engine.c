/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:37:47 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 16:31:54 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	termtex(t_env *env, t_sprite *sprite)
{
	int	px;
	int	py;

	px = EPW.x - sprite->pos1.x;
	py = EPW.y - sprite->pos1.y;
	if (px >= 0 && px >= -py && py <= 0)
		sprite->texnum = 0;
	else if (px >= 0 && px >= py && py >= 0)
		sprite->texnum = 1;
	else if (px >= 0 && px < py && py >= 0)
		sprite->texnum = 2;
	else if (px <= 0 && py > -px && py >= 0)
		sprite->texnum = 3;
	else if (px <= 0 && py <= -px && py >= 0)
		sprite->texnum = 4;
	else if (px <= 0 && -py <= -px && py <= 0)
		sprite->texnum = 5;
	else if (px <= 0 && -py > -px && py <= 0)
		sprite->texnum = 6;
	else
		sprite->texnum = 7;
}

void	animation_support(t_env *env, int i)
{
	ESPRI.movecount++;
	if (ESPRI.movecount == 5)
	{
		ESPRI.movecount = 0;
		ESPRI.texnum = ESPRI.texnum == 7 ? 0 : ESPRI.texnum + 1;
		mixkeytex(&ESPRI);
	}
}

void	animation(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->sprcount)
	{
		if (ESPRI.movecount >= 5 && ESPRI.type != 5 && ESPRI.type != 6)
		{
			ESPRI.movecount = 0;
			ESPRI.texnum = ESPRI.texnum == 6 ? 0 : ESPRI.texnum + 1;
			mixtex(env, &ESPRI);
		}
		if (ESPRI.type == 4 && ESPRI.hp != 665)
			mixtex(env, &ESPRI);
		if (ESPRI.type == 5)
			animation_support(env, i);
		if (ESPRI.type == 6)
		{
			termtex(env, &ESPRI);
			applytermtex(env, &ESPRI);
		}
	}
}

void	pistolrender(t_env *env)
{
	int *pix;
	int	xyab[4];

	pix = (int *)(env->surface->pixels);
	xyab[1] = 460;
	xyab[0] = WWIN / 3 * 2;
	xyab[2] = 0;
	xyab[3] = 0;
	while (++xyab[1] < HWIN)
	{
		xyab[0] = WWIN / 3 * 2;
		while (++xyab[0] < WWIN / 3 * 2 + 263)
		{
			if (((int *)(ET[8 + ESHOOT / 3]->pixels))
			[xyab[2] % ET[8 + ESHOOT / 3]->h * (ET[8 + ESHOOT / 3]->w) +
			xyab[3] % ET[8 + ESHOOT / 3]->w] != -1)
				pix[xyab[1] * WWIN + xyab[0]] = ((int *)(ET[8 + ESHOOT
				/ 3]->pixels))[xyab[2] % ET[8 + ESHOOT / 3]->h *
			(ET[8 + ESHOOT / 3]->w) + xyab[3] % ET[8 + ESHOOT / 3]->w];
			xyab[3]++;
		}
		xyab[2]++;
	}
	if (ESHOOT > 0)
		ESHOOT--;
}

int		start_engine(t_env *env, SDL_Event *e, t_rend *rend)
{
	int	i;

	i = -1;
	while (++i < (int)env->nsectors)
		R->sprq[i].visible = 0;
	SDL_LockSurface(env->surface);
	render_wall(env, R);
	renderbutton(env, R);
	rendersprite(env, R);
	cross(env);
	animation(env);
	pistolrender(env);
	pushswitch(env);
	SDL_UnlockSurface(env->surface);
	if (env->blood-- > 0)
		SDL_BlitScaled(env->text_head[25], NULL, env->surface, NULL);
	put_bar(env);
	SDL_UpdateWindowSurface(env->window);
	handle_events(env, e);
	return (0);
}
