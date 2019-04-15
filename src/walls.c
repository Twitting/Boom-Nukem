/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:37:22 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 16:30:14 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void		calc_support(t_env *env, t_rend *rend)
{
	R->vx1 = R->nowsect->vertex[R->s % R->nowsect->npoints].x - EPW.x;
	R->vy1 = R->nowsect->vertex[R->s % R->nowsect->npoints].y - EPW.y;
	R->vx2 = R->nowsect->vertex[(R->s + 1) % R->nowsect->npoints].x - EPW.x;
	R->vy2 = R->nowsect->vertex[(R->s + 1) % R->nowsect->npoints].y - EPW.y;
	R->t1.x = R->vx1 * EPSIN - R->vy1 * EPCOS;
	R->t1.y = R->vx1 * EPCOS + R->vy1 * EPSIN;
	R->t2.x = R->vx2 * EPSIN - R->vy2 * EPCOS;
	R->t2.y = R->vx2 * EPCOS + R->vy2 * EPSIN;
}

void		startcalc(t_env *env, t_rend *rend, t_now *now)
{
	R->bugf = 0;
	calc_support(env, R);
	if (R->t1.y <= 0 && R->t2.y <= 0)
		return ;
	R->u0 = 0;
	R->u1 = (ET[0]->w - 1);
	wallintersect(R, env);
	wallscale(env, R);
	if (now->sectorno == (int)env->player.sector && portaledge(env, R) == 1
	&& (R->x1 > now->sx2 || R->x2 < now->sx1))
		R->bugf = 1;
	if (R->x1 >= R->x2 || ((R->x2 < now->sx1 || R->x1 > now->sx2) &&
	R->bugf == 0))
		return ;
	wallstart(env, R, now);
	if ((R->endx >= R->beginx && R->bugf == 0) || R->bugf == 1)
		if (R->nowsect->neighbors[R->s] >= 0 && (R->head + MAXQUEUE + 1 -
		R->tail) % MAXQUEUE)
		{
			checknextrend(env, R);
			if (++R->head == R->queue + MAXQUEUE)
				R->head = R->queue;
		}
}

void		render_queue(t_env *env, t_rend *rend, t_now *now)
{
	R->sprq[now->sectorno].sector = now->sectorno;
	if (R->sprq[now->sectorno].visible == 1)
	{
		if (R->sprq[now->sectorno].sx1 > now->sx1)
			R->sprq[now->sectorno].sx1 = now->sx1;
		if (R->sprq[now->sectorno].sx2 < now->sx2)
			R->sprq[now->sectorno].sx2 = now->sx2;
	}
	else
	{
		R->sprq[now->sectorno].sx1 = now->sx1;
		R->sprq[now->sectorno].sx2 = now->sx2;
	}
	R->sprq[now->sectorno].visible = 1;
	R->s = -1;
	while (++R->s < WWIN)
		R->sprq[now->sectorno].ytop[R->s] = R->ytop[R->s];
	R->s = -1;
	while (++R->s < WWIN)
		R->sprq[now->sectorno].ybottom[R->s] = R->ybottom[R->s];
	R->s = -1;
	R->nowsect = &(ESEC[now->sectorno]);
	while (++R->s < (int)R->nowsect->npoints)
		startcalc(env, R, now);
}

void		init_wall(t_env *env, t_rend *rend)
{
	R->head = R->queue;
	R->tail = R->queue;
	R->nyceil = 0;
	R->nyfloor = 0;
	R->s = -1;
	while (++R->s < WWIN)
	{
		R->ytop[R->s] = 0;
		R->ybottom[R->s] = HWIN - 1;
	}
	*(R->head) = (t_now){EPS, 0, WWIN - 1};
}

void		render_wall(t_env *env, t_rend *rend)
{
	t_now		now;
	int			renderedsect[env->nsectors];

	init_wall(env, R);
	R->s = -1;
	while (++R->s < (int)env->nsectors)
		renderedsect[R->s] = 0;
	if (++R->head == R->queue + MAXQUEUE)
		R->head = R->queue;
	while (R->head != R->tail)
	{
		now = *(R->tail);
		if (++R->tail == R->queue + MAXQUEUE)
			R->tail = R->queue;
		if (renderedsect[now.sectorno] & 0x21)
			continue ;
		++renderedsect[now.sectorno];
		render_queue(env, R, &now);
		++renderedsect[now.sectorno];
	}
}
