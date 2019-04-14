/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 06:58:32 by drestles          #+#    #+#             */
/*   Updated: 2019/04/14 15:21:08 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void put_bar(t_env *env)
{
	if (env->help)
		help(env);
	put_hp(env);
	if (env->player.keys > 0)
		keys(env);
}
