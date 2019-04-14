/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:37:22 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 13:13:46 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	wallstart(t_env *env, t_rend *rend, t_now *now)
{
	rend->y1a = HWIN / 2 - (int)(YAW(rend->yceil, rend->t1.y) * rend->yscale1);
	rend->y1b = HWIN / 2 - (int)(YAW(rend->yfloor, rend->t1.y) * rend->yscale1);
	rend->y2a = HWIN / 2 - (int)(YAW(rend->yceil, rend->t2.y) * rend->yscale2);
	rend->y2b = HWIN / 2 - (int)(YAW(rend->yfloor, rend->t2.y) * rend->yscale2);
	rend->ny1a = HWIN / 2 - (int)(YAW(rend->nyceil, rend->t1.y) * rend->yscale1);
	rend->ny1b = HWIN / 2 - (int)(YAW(rend->nyfloor, rend->t1.y) * rend->yscale1);
	rend->ny2a = HWIN / 2 - (int)(YAW(rend->nyceil, rend->t2.y) * rend->yscale2);
	rend->ny2b = HWIN / 2 - (int)(YAW(rend->nyfloor, rend->t2.y) * rend->yscale2);
	rend->beginx = MAX(rend->x1, now->sx1);
	rend->endx = MIN(rend->x2, now->sx2);
	rend->x = rend->beginx;
	rend->ya_int = (t_scaler)SCALER_INIT(rend->x1, rend->beginx, rend->x2, rend->y1a, rend->y2a);
	rend->yb_int = (t_scaler)SCALER_INIT(rend->x1, rend->beginx, rend->x2, rend->y1b, rend->y2b);
	wallxloop(env, rend);
}

void	calc_support(t_env *env, t_rend *rend)
{
	rend->vx1 = rend->nowsect->vertex[rend->s % rend->nowsect->npoints].x - env->player.where.x;
	rend->vy1 = rend->nowsect->vertex[rend->s % rend->nowsect->npoints].y - env->player.where.y;
	rend->vx2 = rend->nowsect->vertex[(rend->s + 1) % rend->nowsect->npoints].x - env->player.where.x;
	rend->vy2 = rend->nowsect->vertex[(rend->s + 1) % rend->nowsect->npoints].y - env->player.where.y;
	rend->t1.x = rend->vx1 * env->player.sinang - rend->vy1 * env->player.cosang;
	rend->t1.y = rend->vx1 * env->player.cosang + rend->vy1 * env->player.sinang;
	rend->t2.x = rend->vx2 * env->player.sinang - rend->vy2 * env->player.cosang;
	rend->t2.y = rend->vx2 * env->player.cosang + rend->vy2 * env->player.sinang;
}

void	startcalc(t_env *env, t_rend *rend, t_now *now)
{
	calc_support(env, rend);
	if (rend->t1.y <= 0 && rend->t2.y <= 0)
		return ;
	rend->u0 = 0;
	rend->u1 = (env->text[0]->w - 1);
	wallintersect(rend, env);
	wallscale(env, rend);
	if (rend->x1 >= rend->x2 || rend->x2 < now->sx1 || rend->x1 > now->sx2)
		return ;
	wallstart(env, rend, now);
	if (rend->nowsect->neighbors[rend->s] >= 0 && rend->endx >= rend->beginx && (rend->head + MAXQUEUE + 1 - rend->tail) % MAXQUEUE)
	{
		if (portaledge(env, rend) == 0)
			*(rend->head) = (t_now){rend->nowsect->neighbors[rend->s], rend->beginx, rend->endx};
		else if (portaledge(env, rend) == 1)
		{
			if (rend->t2.y > 0)
				*(rend->head) = (t_now){rend->nowsect->neighbors[rend->s], 0, rend->endx};
			else
				*(rend->head) = (t_now){rend->nowsect->neighbors[rend->s], rend->beginx, 0};
		}
		if (++rend->head == rend->queue + MAXQUEUE)
			rend->head = rend->queue;
	}
}

void	render_queue(t_env *env, t_rend *rend, t_now *now)
{
	rend->sprq[now->sectorno].sector = now->sectorno;
	if (rend->sprq[now->sectorno].visible == 1)
	{
		if (rend->sprq[now->sectorno].sx1 > now->sx1)
			rend->sprq[now->sectorno].sx1 = now->sx1;
		if (rend->sprq[now->sectorno].sx2 < now->sx2)
			rend->sprq[now->sectorno].sx2 = now->sx2;
	}
	else
	{
		rend->sprq[now->sectorno].sx1 = now->sx1;
		rend->sprq[now->sectorno].sx2 = now->sx2;
	}
	rend->sprq[now->sectorno].visible = 1;
	rend->s = -1;
	while (++rend->s < WWIN)
		rend->sprq[now->sectorno].ytop[rend->s] = rend->ytop[rend->s];
	rend->s = -1;
	while (++rend->s < WWIN)
		rend->sprq[now->sectorno].ybottom[rend->s] = rend->ybottom[rend->s];
	rend->s = -1;
	rend->nowsect = &(env->sector[now->sectorno]);
	while (++rend->s < (int)rend->nowsect->npoints)
		startcalc(env, rend, now);
}

void	init_wall(t_env *env, t_rend *rend)
{
	rend->head = rend->queue;
	rend->tail = rend->queue;
	rend->nyceil = 0;
	rend->nyfloor = 0;
	rend->s = -1;
	while (++rend->s < WWIN)
	{
		rend->ytop[rend->s] = 0;
		rend->ybottom[rend->s] = HWIN - 1;
	}
	*(rend->head) = (t_now){env->player.sector, 0, WWIN - 1};
}

void	render_wall(t_env *env, t_rend *rend)
{
	t_now		now;
	int			renderedsect[env->nsectors];

	init_wall(env, rend);
	rend->s = -1;
	while (++rend->s < (int)env->nsectors)
		renderedsect[rend->s] = 0;
	if (++rend->head == rend->queue + MAXQUEUE)
		rend->head = rend->queue;
	while (rend->head != rend->tail)
	{
		now = *(rend->tail);
		if (++rend->tail == rend->queue + MAXQUEUE)
			rend->tail = rend->queue;
		if (renderedsect[now.sectorno] & 0x21)
			continue ;
		++renderedsect[now.sectorno];
		render_queue(env, rend, &now);
		++renderedsect[now.sectorno];
	}
}
