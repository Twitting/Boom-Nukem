/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:46:20 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/05 19:52:39 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void	drawsky(t_env *env, t_rend *rend, int sect)
{
	//int			x;
	int			y;
	t_sprque	now;
	int			*pix;
//	int	txty;
//	int	txtx;

	now = rend->sprq[sect];
	//rend->x = now.sx1;
//	while (rend->x < now.sx2)
	//{
		pix = (int*)env->surface->pixels;
		pix += rend->x; 
		y = now.ytop[rend->x];
		while (y <= rend->cya)
		{
			*pix = ((int *)(env->text[2]->pixels))[(int)(y + 100 * (env->player.yaw + 3)) % env->text[2]->h * env->text[2]->w + + (int)(env->player.angle / 6.2 * env->text[2]->w + rend->x) % env->text[2]->w];
			// *pix = ((int *)(env->text[2]->pixels))[y % env->text[2]->h * env->text[2]->w + (env->skyangle + x) % env->text[2]->w];
			//((int)fabs(1.0 * env->skyangle) + x) % SKYSIZE];
			pix += WWIN;
			y++;
		}
		rend->x++;
	//}
}