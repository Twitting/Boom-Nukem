/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movemob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:06:32 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 15:34:44 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	move_mob_support4(t_env *env, int *arr2, t_sector sect)
{
	env->sprite[arr2[3]].sector = sect.neighbors[arr2[0]];
	env->sprite[arr2[3]].movecount = 0;
	env->sprite[arr2[3]].texnum = 0;
	arr2[2] = -1;
	while (++arr2[2] < 7)
		enemylightapply(env, &env->sprite[arr2[3]], arr2[2]);
}

void	move_mob_support3(double *dxdysxsyee, t_xy *opvoppp)
{
	dxdysxsyee[0] = fabs(opvoppp[2].x - opvoppp[0].x);
	dxdysxsyee[1] = fabs(opvoppp[2].y - opvoppp[0].y);
	dxdysxsyee[2] = opvoppp[0].x < opvoppp[2].x ? 0.15 : -0.15;
	dxdysxsyee[3] = opvoppp[0].y < opvoppp[2].y ? 0.15 : -0.15;
	dxdysxsyee[4] = dxdysxsyee[0] - dxdysxsyee[1];
}

void	move_mob_support2(t_env *env, double *dxdysxsyee, t_xy *opvoppp, int i)
{
	dxdysxsyee[5] = dxdysxsyee[4] * 2;
	if (dxdysxsyee[5] > -dxdysxsyee[1])
	{
		dxdysxsyee[4] -= dxdysxsyee[1];
		opvoppp[0].x += dxdysxsyee[2] * 60 * 30 /
			(ESEC[ESPRI.sector].light * env->oldfps);
	}
	if (dxdysxsyee[5] < dxdysxsyee[0])
	{
		dxdysxsyee[4] += dxdysxsyee[0];
		opvoppp[0].y += dxdysxsyee[3] * 60 * 30 /
			(ESEC[ESPRI.sector].light * env->oldfps);
	}
}

void	move_mob_support(t_env *env,
					int *arr2, double *dxdysxsyee, t_xy *opvoppp)
{
	t_sector sect;

	arr2[0] = -1;
	if ((env->sprite[arr2[3]].sector == (int)EPS ||
			env->sprite[arr2[3]].visible) && env->sprite[arr2[3]].type == 1)
	{
		env->sprite[arr2[3]].movecount++;
		sect = ESEC[env->sprite[arr2[3]].sector];
		opvoppp[0] = env->sprite[arr2[3]].pos1;
		opvoppp[1] = env->sprite[arr2[3]].pos1;
		move_mob_support3(dxdysxsyee, opvoppp);
		while (fabs(opvoppp[0].x - opvoppp[2].x) > 2.0 ||
			fabs(opvoppp[0].y - opvoppp[2].y) > 2.0)
		{
			move_mob_support2(env, dxdysxsyee, opvoppp, arr2[3]);
			while (++arr2[0] < (int)sect.NP)
			{
				if (WTF1 >= 0 && i_b(OP[1], OP[0], SV[A1 % SNP], SV[(A1 + 1) %
				SNP]) && PS(OP[0].x, OP[0].y, SV[A1 % SNP], SV[(A2) % SNP]) < 0)
					move_mob_support4(env, arr2, sect);
			}
			env->sprite[arr2[3]].pos1 = opvoppp[0];
			break ;
		}
	}
}

void	move_mob(t_env *env)
{
	int		arr2[4];
	double	dxdysxsyee[6];
	t_xy	opvoppp[3];

	arr2[1] = 0;
	arr2[3] = -1;
	opvoppp[2].x = EPW.x;
	opvoppp[2].y = EPW.y;
	while (++arr2[3] < env->sprcount)
	{
		move_mob_support(env, arr2, dxdysxsyee, opvoppp);
	}
}
