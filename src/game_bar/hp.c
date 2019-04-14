/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 07:26:44 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 19:41:41 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void	good_frame_for_head(t_env *env)
{
	int frame;

	env->head_shot++;
	if (env->head_shot > 100000)
		env->head_shot = 0;
	frame = env->head_shot % 25;
	if (frame == 0)
	{
		env->head++;
		env->head %= 4;
	}
}

void	put_hp(t_env *env)
{
	if (env->player.hp > 80)
		head_one(env);
	else if (env->player.hp > 60)
		head_two(env);
	else if (env->player.hp > 40)
		head_three(env);
	else if (env->player.hp > 20)
		head_four(env);
	else
		head_five(env);
}
