/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:33:20 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/03 19:41:15 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <render.h>

void	inittext(t_env *env)
{
	env->text[0] = IMG_Load("textures/brick.tga");
	env->text[1] = IMG_Load("textures/barrel.png");
	/*env->text[2] = IMG_Load("textures/3.tga");
	env->text[3] = IMG_Load("textures/4.tga");
	env->text[4] = IMG_Load("textures/5.tga");
	env->text[5] = IMG_Load("textures/6.tga");
	env->text[6] = IMG_Load("textures/7.tga");
	env->text[7] = IMG_Load("textures/8.tga");
	env->text[8] = IMG_Load("textures/9.tga");
	env->text[9] = IMG_Load("textures/10.tga");*/
}
