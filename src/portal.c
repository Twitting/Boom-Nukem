/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:08:32 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 16:40:33 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	portaledge_sup1(t_env *env, t_rend *rend, t_xy *p, t_xy *d)
{
	d->x = p->x + 1;
	d->y = p->y + 1;
	rend->butx = 0;
	if (i_b(*p, *d, ESEC[EPS].vertex[rend->s %
	ESEC[EPS].npoints],
	ESEC[EPS].vertex[(rend->s + 1) %
	ESEC[EPS].npoints]) &&
	point_side(d->x, d->y, ESEC[EPS].vertex[rend->s %
	ESEC[EPS].npoints],
	ESEC[EPS].vertex[(rend->s + 1) %
	ESEC[EPS].npoints]) < 0)
		return (1);
	d->x = p->x - 2;
	d->y = p->y - 2;
	rend->butx = 0;
	if (i_b(*p, *d, ESEC[EPS].vertex[rend->s %
	ESEC[EPS].npoints],
	ESEC[EPS].vertex[(rend->s + 1) %
	ESEC[EPS].npoints]) &&
	point_side(d->x, d->y, ESEC[EPS].vertex[rend->s %
	ESEC[EPS].npoints],
	ESEC[EPS].vertex[(rend->s + 1) %
	ESEC[EPS].npoints]) < 0)
		return (1);
	return (0);
}

int	portaledge_sup2(t_env *env, t_rend *rend, t_xy *p, t_xy *d)
{
	d->x = p->x;
	d->y = p->y - 2;
	rend->butx = 0;
	if (i_b(*p, *d, ESEC[EPS].vertex[rend->s %
	ESEC[EPS].npoints],
	ESEC[EPS].vertex[(rend->s + 1) %
	ESEC[EPS].npoints]) &&
	point_side(d->x, d->y, ESEC[EPS].vertex[rend->s %
	ESEC[EPS].npoints],
	ESEC[EPS].vertex[(rend->s + 1) %
	ESEC[EPS].npoints]) < 0)
		return (1);
	d->x = p->x + 2;
	d->y = p->y + 2;
	rend->butx = 0;
	if (i_b(*p, *d, ESEC[EPS].vertex[rend->s %
	ESEC[EPS].npoints],
	ESEC[EPS].vertex[(rend->s + 1) %
	ESEC[EPS].npoints]) &&
	point_side(d->x, d->y, ESEC[EPS].vertex[rend->s %
	ESEC[EPS].npoints],
	ESEC[EPS].vertex[(rend->s + 1) %
	ESEC[EPS].npoints]) < 0)
		return (1);
	return (0);
}

int	portaledge(t_env *env, t_rend *rend)
{
	t_xy	p;
	t_xy	d;
	int		i;

	i = -1;
	while (++i < (int)ESEC[EPS].npoints)
		if (rend->head->sectorno ==
			ESEC[EPS].neighbors[i])
		{
			p.x = EPW.x;
			p.y = EPW.y;
			if (portaledge_sup1(env, rend, &p, &d) ||
				portaledge_sup2(env, rend, &p, &d))
				return (1);
		}
	return (0);
}
