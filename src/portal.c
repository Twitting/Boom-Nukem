/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:08:32 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 13:02:28 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	portaledge_sup1(t_env *env, t_rend *rend, t_xy *p, t_xy *d)
{
	d->x = p->x + 1;
	d->y = p->y + 1;
	rend->butx = 0;
	if (intersect_box(*p, *d, env->sector[env->player.sector].vertex[rend->s %
	env->sector[env->player.sector].npoints],
	env->sector[env->player.sector].vertex[(rend->s + 1) %
	env->sector[env->player.sector].npoints]) &&
	point_side(d->x, d->y, env->sector[env->player.sector].vertex[rend->s %
	env->sector[env->player.sector].npoints],
	env->sector[env->player.sector].vertex[(rend->s + 1) %
	env->sector[env->player.sector].npoints]) < 0)
		return (1);
	d->x = p->x - 2;
	d->y = p->y - 2;
	rend->butx = 0;
	if (intersect_box(*p, *d, env->sector[env->player.sector].vertex[rend->s %
	env->sector[env->player.sector].npoints],
	env->sector[env->player.sector].vertex[(rend->s + 1) %
	env->sector[env->player.sector].npoints]) &&
	point_side(d->x, d->y, env->sector[env->player.sector].vertex[rend->s %
	env->sector[env->player.sector].npoints],
	env->sector[env->player.sector].vertex[(rend->s + 1) %
	env->sector[env->player.sector].npoints]) < 0)
		return (1);
	return (0);
}

int	portaledge_sup2(t_env *env, t_rend *rend, t_xy *p, t_xy *d)
{
	d->x = p->x;
	d->y = p->y - 2;
	rend->butx = 0;
	if (intersect_box(*p, *d, env->sector[env->player.sector].vertex[rend->s %
	env->sector[env->player.sector].npoints],
	env->sector[env->player.sector].vertex[(rend->s + 1) %
	env->sector[env->player.sector].npoints]) &&
	point_side(d->x, d->y, env->sector[env->player.sector].vertex[rend->s %
	env->sector[env->player.sector].npoints],
	env->sector[env->player.sector].vertex[(rend->s + 1) %
	env->sector[env->player.sector].npoints]) < 0)
		return (1);
	d->x = p->x + 2;
	d->y = p->y + 2;
	rend->butx = 0;
	if (intersect_box(*p, *d, env->sector[env->player.sector].vertex[rend->s %
	env->sector[env->player.sector].npoints],
	env->sector[env->player.sector].vertex[(rend->s + 1) %
	env->sector[env->player.sector].npoints]) &&
	point_side(d->x, d->y, env->sector[env->player.sector].vertex[rend->s %
	env->sector[env->player.sector].npoints],
	env->sector[env->player.sector].vertex[(rend->s + 1) %
	env->sector[env->player.sector].npoints]) < 0)
		return (1);
	return (0);
}

int	portaledge(t_env *env, t_rend *rend)
{
	t_xy	p;
	t_xy	d;
	int		i;

	i = -1;
	while (++i < (int)env->sector[env->player.sector].npoints)
		if (rend->head->sectorno ==
			env->sector[env->player.sector].neighbors[i])
		{
			p.x = env->player.where.x;
			p.y = env->player.where.y;
			if (portaledge_sup1(env, rend, &p, &d) ||
				portaledge_sup2(env, rend, &p, &d))
				return (1);
		}
	return (0);
}
