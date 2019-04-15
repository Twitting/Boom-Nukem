/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:24:41 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 17:03:04 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_scaler	scaler_init_support5(t_rend *rend)
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

t_scaler	scaler_init_support6(t_rend *rend)
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

void		wallstart(t_env *env, t_rend *rend, t_now *now)
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
	R->x = R->beginx - 1;
	R->ya_int = scaler_init_support5(R);
	R->yb_int = scaler_init_support6(R);
	wallxloop(env, R);
}

void		checknextrend(t_env *env, t_rend *rend)
{
	if (portaledge(env, R) == 0)
		*(R->head) = (t_now){R->nowsect->neighbors[
		R->s], R->beginx, R->endx};
	else if (R->bugf == 1)
		*(R->head) = (t_now){R->nowsect->neighbors[R->s], 0, WWIN - 1};
	else if (portaledge(env, R) == 1)
		*(R->head) = R->t2.y > R->t1.y ? (t_now){R->nowsect->neighbors[
			R->s], 0, R->endx} : (t_now){
				R->nowsect->neighbors[R->s], R->beginx, WWIN - 1};
}
