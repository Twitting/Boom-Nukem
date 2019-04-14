/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:37:22 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 19:19:46 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_scaler	scaler_init_support5(t_rend *R)
{
	t_scaler temp;

	temp = (t_scaler)
	{R->y1a + (R->beginx - 1 - R->x1) *
		(R->y2a - R->y1a) / (R->x2 - R->x1),
		((R->y2a < R->y1a) ^
		(R->x2 < R->x1)) ? -1 : 1,
		abs(R->y2a - R->y1a),
		abs(R->x2 - R->x1),
		(int)((R->beginx - 1 - R->x1) * abs(R->y2a -
		R->y1a)) % abs(R->x2 - R->x1)};
	return (temp);
}

t_scaler	scaler_init_support6(t_rend *R)
{
	t_scaler temp;

	temp = (t_scaler)
	{R->y1b + (R->beginx - 1 - R->x1) *
		(R->y2b - R->y1b) / (R->x2 - R->x1),
		((R->y2b < R->y1b) ^
		(R->x2 < R->x1)) ? -1 : 1,
		abs(R->y2b - R->y1b),
		abs(R->x2 - R->x1),
		(int)((R->beginx - 1 - R->x1) * abs(R->y2b -
		R->y1b)) % abs(R->x2 - R->x1)};
	return (temp);
}

void	wallstart(t_env *env, t_rend *R, t_now *now)
{
	R->y1a = HWIN / 2 - (int)(YAW(R->yceil, R->t1.y) * R->yscale1);
	R->y1b = HWIN / 2 - (int)(YAW(R->yfloor, R->t1.y) * R->yscale1);
	R->y2a = HWIN / 2 - (int)(YAW(R->yceil, R->t2.y) * R->yscale2);
	R->y2b = HWIN / 2 - (int)(YAW(R->yfloor, R->t2.y) * R->yscale2);
	R->ny1a = HWIN / 2 - (int)(YAW(R->nyceil, R->t1.y) * R->yscale1);
	R->ny1b = HWIN / 2 - (int)(YAW(R->nyfloor, R->t1.y) * R->yscale1);
	R->ny2a = HWIN / 2 - (int)(YAW(R->nyceil, R->t2.y) * R->yscale2);
	R->ny2b = HWIN / 2 - (int)(YAW(R->nyfloor, R->t2.y) * R->yscale2);
	R->beginx = MAX(R->x1, now->sx1);
	R->endx = MIN(R->x2, now->sx2);
	R->x = R->beginx;
	R->ya_int = scaler_init_support5(R);
	R->yb_int = scaler_init_support6(R);
	wallxloop(env, R);
}

void	calc_support(t_env *env, t_rend *R)
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

void	startcalc(t_env *env, t_rend *R, t_now *now)
{
	calc_support(env, R);
	if (R->t1.y <= 0 && R->t2.y <= 0)
		return ;
	R->u0 = 0;
	R->u1 = (ET[0]->w - 1);
	wallintersect(R, env);
	wallscale(env, R);
	if (R->x1 >= R->x2 || R->x2 < now->sx1 || R->x1 > now->sx2)
		return ;
	wallstart(env, R, now);
	if (R->nowsect->neighbors[R->s] >= 0 && R->endx >= R->beginx && (R->head + MAXQUEUE + 1 - R->tail) % MAXQUEUE)
	{
		if (portaledge(env, R) == 0)
			*(R->head) = (t_now){R->nowsect->neighbors[R->s], R->beginx, R->endx};
		else if (portaledge(env, R) == 1)
		{
			if (R->t2.y > 0)
				*(R->head) = (t_now){R->nowsect->neighbors[R->s], 0, R->endx};
			else
				*(R->head) = (t_now){R->nowsect->neighbors[R->s], R->beginx, 0};
		}
		if (++R->head == R->queue + MAXQUEUE)
			R->head = R->queue;
	}
}

void	render_queue(t_env *env, t_rend *R, t_now *now)
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

void	init_wall(t_env *env, t_rend *R)
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

void	render_wall(t_env *env, t_rend *R)
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
