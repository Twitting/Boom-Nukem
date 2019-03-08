/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:37:47 by ebednar           #+#    #+#             */
/*   Updated: 2019/03/08 14:36:55 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

static void	vline(t_env *env, int x, int y1, int y2, int top, int middle, int bottom)
{
	int *pix;

	pix = env->surface->pixels;
	y1 = CLAMP(y1, 0, HWIN - 1);
	y2 = CLAMP(y2, 0, HWIN - 1);
	if (y2 == y1)
		pix[y1 * WWIN + x] = middle;
	else if (y2 > y1)
	{
		pix[y1*WWIN+x] = top;
        for(int y=y1+1; y<y2; ++y) pix[y*WWIN+x] = middle;
        pix[y2*WWIN+x] = bottom;
	}
}

static void	wallintersect(t_rend *rend)
{
	if (rend->t1.y <= 0 || rend->t2.y <= 0)
		{
			rend->nfz.x = 1e-4;
			rend->nfz.y = 5;
			rend->nfside.x = 1e-5;
			rend->nfside.y = 20;
			rend->i1 = intersect(rend->t1, rend->t2, - rend->nfside.x, rend->nfz.x, - rend->nfside.y, rend->nfz.y);
			rend->i2 = intersect(rend->t1, rend->t2, rend->nfside.x, rend->nfz.x, rend->nfside.y, rend->nfz.y);
			if (rend->t1.y < rend->nfz.x)
			{
				if (rend->i1.y > 0)
				{
					rend->t1.x = rend->i1.x;
					rend->t1.y = rend->i1.y;
				}
				else 
				{
					rend->t1.x = rend->i2.x;
					rend->t1.y = rend->i2.y;
				}
			}
			if (rend->t2.y < rend->nfz.x)
			{
				if (rend->i1.y > 0)
				{
					rend->t2.x = rend->i1.x;
					rend->t2.y = rend->i1.y;
				}
				else
				{
					rend->t2.x = rend->i2.x;
					rend->t2.y = rend->i2.y;
				}
			}
		}
}

static void	render_wall(t_env *env)
{
	int			s;
	t_rend		rend;
	t_sector	nowsect;

	// struct {int sectorno, sx1, sx2;} now = {player.sectorno, 0 , WWIN - 1};
	s = -1;
	nowsect = env->sector[env->player.sector];
	while (++s < (int)nowsect.npoints)
	{
		rend.vx1 = env->sector->vertex[s % nowsect.npoints].x - env->player.where.x;
		rend.vy1 = env->sector->vertex[s % nowsect.npoints].y - env->player.where.y;
		rend.vx2 = env->sector->vertex[(s + 1) % nowsect.npoints].x - env->player.where.x;
		rend.vy2 = env->sector->vertex[(s + 1) % nowsect.npoints].y - env->player.where.y;
		rend.t1.x = rend.vx1 * sin(env->player.angle) - rend.vy1 * cos(env->player.angle);
		rend.t1.y = rend.vx1 * cos(env->player.angle) + rend.vy1 * sin(env->player.angle);
		rend.t2.x = rend.vx2 * sin(env->player.angle) - rend.vy2 * cos(env->player.angle);
		rend.t2.y = rend.vx2 * cos(env->player.angle) + rend.vy2 * sin(env->player.angle);
		if (rend.t1.y <= 0 && rend.t2.y <= 0)
			continue ;
		wallintersect(&rend);
		rend.xscale1 = HFOV / rend.t1.y;
		rend.yscale1 = VFOV / rend.t1.y;
		rend.x1 = WWIN / 2 - (int)(rend.t1.x * rend.xscale1);
		rend.xscale2 = HFOV / rend.t2.y;
		rend.yscale2 = VFOV / rend.t2.y;
		rend.x2 = WWIN / 2 - (int)(rend.t2.x * rend.xscale2);
		// if (x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) continue;
		rend.yceil = env->sector->ceiling - env->player.where.z;
		rend.yfloor = env->sector->floor - env->player.where.z;
		//neighbor = env->sector->neighbors[s];
		#define Yaw(y, z) (y + z * env->player.yaw)
		rend.y1a = HWIN / 2 - (int)(Yaw(rend.yceil, rend.t1.y) * rend.yscale1);
		rend.y1b = HWIN / 2 - (int)(Yaw(rend.yfloor, rend.t1.y) * rend.yscale1);
		rend.y2a = HWIN / 2 - (int)(Yaw(rend.yceil, rend.t2.y) * rend.yscale2);
		rend.y2b = HWIN / 2 - (int)(Yaw(rend.yfloor, rend.t2.y) * rend.yscale2);
		rend.beginx = MAX(rend.x1, 0);
		rend.endx = MIN(rend.x2, WWIN - 1);
		rend.x = rend.beginx;
		while (rend.x <= rend.endx)
		{
			rend.ya = (rend.x - rend.x1) * (rend.y2a - rend.y1a) / (rend.x2 - rend.x1) + rend.y1a;
			rend.cya = CLAMP(rend.ya, 0, HWIN - 1);
			rend.yb = (rend.x - rend.x1) * (rend.y2b - rend.y1b) / (rend.x2 - rend.x1) + rend.y1b;
			rend.cyb = CLAMP(rend.yb, 0, HWIN - 1);
			vline(env, rend.x, 0, rend.cya - 1, 0x111111, 0x222222, 0x111111);
			vline(env, rend.x, rend.cyb - 1, HWIN, 0x0000FF, 0x0000AA, 0x0000FF);
			if (env->sector->neighbors[s] >= 0)
				vline(env, rend.x, rend.cya, rend.cyb, 0x00AA00, 0xAA0000, 0x00AA00);
			else
				vline(env, rend.x, rend.cya, rend.cyb, 0, rend.x == rend.x1 || rend.x == rend.x2 ? 0 : 0xAAAAAA, 0);
			rend.x++;
		}
	}
}

int		start_engine(t_env *env, SDL_Event *e)
{
	render_wall(env);
	SDL_UpdateWindowSurface(env->window);
	handle_events(env, e);
	return (0);
}