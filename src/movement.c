/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:10:46 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/05 18:30:39 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int		can_i_go(t_env *env, t_xy *p, double x, double y);


int can_i_go2(t_env *env, t_xy *p, double x, double y)
{
	double			oldx = x;
	double			oldy = y;
	double			a, b, c, s;
	double			hh[env->sector[env->sprite[0].sector].npoints];
	unsigned int	i = 0;
	unsigned int	ii = i % env->sector[env->sprite[0].sector].npoints;
	unsigned int	ii1 = (i + 1) % env->sector[env->sprite[0].sector].npoints;

	while (i < env->sector[env->sprite[0].sector].npoints)
	{
		a = sqrt(pow(p[i].x - oldx, 2) + pow(p[i].y - oldy, 2));
		b = sqrt(pow(p[ii1].x - oldx, 2) + pow(p[ii1].y - oldy, 2));
		c = sqrt(pow(p[i].x - p[ii1].x, 2) + pow(p[i].y - p[ii1].y, 2));
		s = 0.25 * sqrt(pow(pow(a, 2) + pow(b, 2) + pow(c, 2), 2) \
			- 2 * (pow(a, 4) + pow(b, 4) + pow(c, 4)));
		hh[i] = (2 * s) / c;
		printf("%f \n", hh[0]);
		if (hh[ii] < 5.0 && (env->sector[env->sprite[0].sector].neighbors[ii] != -1))
			return (0);
		i++;
	}
	return (1);
}

void move_mob(t_env *env) {

	t_xy oldPos;
	t_xy playerPos;
	t_sector		sect;
	int			arr2[2];
	
	
	arr2[0] = -1;
	arr2[1] = 0;
	oldPos.x = env->sprite[0].pos.x;
	oldPos.y = env->sprite[0].pos.y;
	playerPos.x = env->player.where.x;
	playerPos.y = env->player.where.y;
	sect = env->sector[env->sprite[0].sector];
	double deltaX = fabs(playerPos.x - oldPos.x);
    double deltaY = fabs(playerPos.y - oldPos.y);
    double signX = oldPos.x < playerPos.x  ? 1 : -1;
    double signY = oldPos.y < playerPos.y ? 1 : -1;
    double error = deltaX - deltaY;
	t_xy			points[env->sector[env->sprite[0].sector].npoints];


    while ((unsigned int)arr2[1]++ < env->sector[env->player.sector].npoints)
	{
		points[arr2[1]].x = sect.vertex[arr2[1]].x;
		points[arr2[1]].y = sect.vertex[arr2[1]].y;
	}

	

    while(fabs(oldPos.x - playerPos.x) > 5.0 || fabs(oldPos.y - playerPos.y) > 5.0) 
   {
        double error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            oldPos.x += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            oldPos.y += signY;
        }
		if(can_i_go2(env,points,env->sprite[0].pos.x, env->sprite[0].pos.y))
		{
			env->sprite[0].pos.x = oldPos.x;
			env->sprite[0].pos.y = oldPos.y;
			printf("STOP\n");
		}
		else
		{
			if(error2 > -deltaY) 
        	{
            	error += deltaY;
            	oldPos.x -= signX;
        	}
        	if(error2 < deltaX) 
        	{
           		error -= deltaX;
          		oldPos.y -= signY;
       		}
		}
		
		
			
		//printf("secS: %d  secP: %d\n", env->sprite[0].sector, env->player.sector);
		while (++arr2[0] < (int)sect.npoints)
			if (sect.neighbors[arr2[0]] >= 0 && intersect_box(oldPos, env->sprite[0].pos, sect.vertex[arr2[0] % sect.npoints], sect.vertex[(arr2[0] + 1) % sect.npoints]))
			{	
				env->sprite[0].sector = sect.neighbors[arr2[0]];
				break;
			}
		break ;
    }
}

void	v_collision_support(t_env *env)
{
	double	nz;

	env->player.velocity.z -= (0.05 * 60.0 / (double)env->oldfps);
	nz = env->player.where.z + env->player.velocity.z;
	if (env->player.velocity.z < 0 && nz <
			env->sector[env->player.sector].floor + env->player.eye)
	{
		env->player.where.z = env->sector[env->player.sector].floor
			+ env->player.eye;
		env->player.velocity.z = 0;
		env->falling = 0;
		env->ground = 1;
	}
	else if (env->player.velocity.z > 0 &&
			nz > env->sector[env->player.sector].ceiling)
	{
		env->player.velocity.z = 0;
		env->falling = 1;
	}
	if (env->falling)
	{
		env->player.where.z += env->player.velocity.z;
		env->moving = 1;
	}
}

void	v_collision(t_env *env)
{
	env->ground = !env->falling;
	env->player.eye = env->ducking ? DUCKHEIGHT : EYEHEIGHT;
	if (env->falling)
		v_collision_support(env);
}

void	h_collision(t_env *env, t_xy *p, t_xy *d, t_xy *dd)
{
	int			s;
	double		arr[3]; //temp low hight
	t_xy		b_pd[2];

	b_pd[1].x = p->x + dd->x;
	b_pd[1].y = p->y + dd->y;
	s = -1;
	while (++s < (int)env->sector[env->player.sector].npoints)
		if (intersect_box(*p, b_pd[1], env->sector[env->player.sector].vertex[s % env->sector[env->player.sector].npoints], env->sector[env->player.sector].vertex[(s + 1) % env->sector[env->player.sector].npoints]) && point_side(b_pd[1].x, b_pd[1].y, env->sector[env->player.sector].vertex[s % env->sector[env->player.sector].npoints], env->sector[env->player.sector].vertex[(s + 1) % env->sector[env->player.sector].npoints]) < 0)
		{
			arr[1] = env->sector[env->player.sector].neighbors[s] < 0 ? 9e9 : MAX(env->sector[env->player.sector].floor, env->sector[env->sector[env->player.sector].neighbors[s]].floor);
			arr[2] = env->sector[env->player.sector].neighbors[s] < 0 ? 9e9 : MIN(env->sector[env->player.sector].ceiling, env->sector[env->sector[env->player.sector].neighbors[s]].ceiling);
			if (arr[2] < env->player.where.z + HEADMARGIN || arr[1] > env->player.where.z - (env->ducking ? DUCKHEIGHT : EYEHEIGHT) + KNEEHEIGHT)
			{
				b_pd[0].x = env->sector[env->player.sector].vertex[(s + 1) % env->sector[env->player.sector].npoints].x - env->sector[env->player.sector].vertex[s % env->sector[env->player.sector].npoints].x;
				b_pd[0].y = env->sector[env->player.sector].vertex[(s + 1) % env->sector[env->player.sector].npoints].y - env->sector[env->player.sector].vertex[s % env->sector[env->player.sector].npoints].y;
				arr[0] = d->x;
				d->x = b_pd[0].x * (d->x * b_pd[0].x + b_pd[0].y * d->y) / (b_pd[0].x * b_pd[0].x + b_pd[0].y * b_pd[0].y);
				d->y = b_pd[0].y * (arr[0] * b_pd[0].x + b_pd[0].y * d->y) / (b_pd[0].x * b_pd[0].x + b_pd[0].y * b_pd[0].y);
				env->moving = -1;
			}
		}
	env->falling = 1;
}

int		can_i_go(t_env *env, t_xy *p, double x, double y)
{
	double			hh[env->sector[env->player.sector].npoints];
	unsigned int	i;
	unsigned int	ii1;
	double			arr[6];// 0x 1y 2a 3b 4c 5s

	i = 0;
	ii1 = (i + 1) % env->sector[env->player.sector].npoints;
	arr[0] = x;
	arr[1] = y;
	while (i < env->sector[env->player.sector].npoints)
	{
		arr[2] = sqrt(pow(p[i].x - arr[0], 2) + pow(p[i].y - arr[1], 2));
		arr[3] = sqrt(pow(p[ii1].x - arr[0], 2) + pow(p[ii1].y - arr[1], 2));
		arr[4] = sqrt(pow(p[i].x - p[ii1].x, 2) + pow(p[i].y - p[ii1].y, 2));
		arr[5] = 0.25 * sqrt(pow(pow(arr[2], 2) + pow(arr[3], 2) + pow(arr[4], 2), 2) - 2 * (pow(arr[2], 4) + pow(arr[3], 4) + pow(arr[4], 4)));
		hh[i] = (2 * arr[5]) / arr[4];
		if (arr[2] < 0.7 || arr[3] < 0.7)
			return (0);// нет зависимости от высоты
		i++;
	}
	return (1);
}

void	movement_support(t_env *env, float dx, float dy)
{
	env->player.where.x += dx;
	env->player.where.y += dy;
}

void	movement(t_env *env, float dx, float dy)
{
	t_sector		sect;
	int				arr2[2];//s i
	t_xy			points[env->sector[env->player.sector].npoints];
	t_xy			arr[2];//p dp
	arr2[0] = -1;
	arr2[1] = 0;
	arr[0].x = env->player.where.x;
	arr[0].y = env->player.where.y;
	arr[1].x = arr[0].x + dx;
	arr[1].y = arr[0].y + dy;
	sect = env->sector[env->player.sector];
	
	while (++arr2[0] < (int)sect.npoints)
		if (sect.neighbors[arr2[0]] >= 0 && intersect_box(arr[0], arr[1], sect.vertex[arr2[0] % sect.npoints], sect.vertex[(arr2[0] + 1) % sect.npoints]) && point_side(arr[1].x, arr[1].y, sect.vertex[arr2[0] % sect.npoints], sect.vertex[(arr2[0] + 1) % sect.npoints]) < 0)
		{
			env->player.sector = sect.neighbors[arr2[0]];
			break ;
		}
	while ((unsigned int)arr2[1]++ < env->sector[env->player.sector].npoints)
	{
		points[arr2[1]].x = sect.vertex[arr2[1]].x;
		points[arr2[1]].y = sect.vertex[arr2[1]].y;
	}
	if (can_i_go(env, points, env->player.where.x + dx, env->player.where.y + dy))
		movement_support(env, dx, dy);
}

t_xy	wsad_read_support(t_env *env, t_xy mv)
{
	if (env->wsad[0])
	{
		mv.x += cos(env->player.angle) * 0.4;
		mv.y += sin(env->player.angle) * 0.4;
	}
	if (env->wsad[1])
	{
		mv.x -= cos(env->player.angle) * 0.4;
		mv.y -= sin(env->player.angle) * 0.4;
	}
	if (env->wsad[2])
	{
		mv.x += sin(env->player.angle) * 0.4;
		mv.y -= cos(env->player.angle) * 0.4;
	}
	if (env->wsad[3])
	{
		mv.x -= sin(env->player.angle) * 0.4;
		mv.y += cos(env->player.angle) * 0.4;
	}
	return (mv);
}

t_xy	wsad_read_support2(t_env *env, t_xy dmv)
{
	if (env->wsad[0])
	{
		dmv.x += cos(env->player.angle) * 1;
		dmv.y += sin(env->player.angle) * 1;
	}
	if (env->wsad[1])
	{
		dmv.x -= cos(env->player.angle) * 1;
		dmv.y -= sin(env->player.angle) * 1;
	}
	if (env->wsad[2])
	{
		dmv.x += sin(env->player.angle) * 1;
		dmv.y -= cos(env->player.angle) * 1;
	}
	if (env->wsad[3])
	{
		dmv.x -= sin(env->player.angle) * 1;
		dmv.y += cos(env->player.angle) * 1;
	}
	return (dmv);
}

void	wsad_read(t_env *env)
{
	t_xy	mv;
	t_xy	dmv;

	mv.x = 0;
	mv.y = 0;
	mv = wsad_read_support(env, mv);
	dmv.x = 0;
	dmv.y = 0;
	dmv = wsad_read_support2(env, dmv);
	env->player.velocity.x = mv.x * 60.0 / (double)env->oldfps;
	env->player.velocity.y = mv.y * 60.0 / (double)env->oldfps;
	env->player.dvelocity.x = dmv.x * 60.0 / (double)env->oldfps;
	env->player.dvelocity.y = dmv.y * 60.0 / (double)env->oldfps;
	env->moving = (mv.x != 0 || mv.y != 0 || env->falling) ? 1 : 0;
}

void	movement_calcs(t_env *env)
{
	t_xy		p;
	t_xy		d;
	t_xy		dd;

	wsad_read(env);
	if (env->moving)
	{
		p.x = env->player.where.x;
		p.y = env->player.where.y;
		d.x = env->player.velocity.x;
		d.y = env->player.velocity.y;
		dd.x = env->player.dvelocity.x;
		dd.y = env->player.dvelocity.y;
		v_collision(env);
		h_collision(env, &p, &d, &dd);
		movement(env, d.x, d.y);
	}
	movement(env, 0, 0);
}
