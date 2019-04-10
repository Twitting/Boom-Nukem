/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:33:20 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/10 20:40:51 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <render.h>

void	inittext(t_env *env)
{
	env->text[0] = IMG_Load("textures/brick.tga");
	env->text[1] = IMG_Load("textures/switch.bmp");
	env->text[2] = IMG_Load("textures/sky.png");
	env->text[7] = IMG_Load("textures/d1.png");
	env->text[6] = IMG_Load("textures/d2.png");
	env->text[5] = IMG_Load("textures/d3.png");
	env->text[4] = IMG_Load("textures/d4.png");
	env->text[3] = IMG_Load("textures/d5.png");
}
