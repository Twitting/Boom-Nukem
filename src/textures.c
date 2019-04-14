/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:33:20 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 13:10:12 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <render.h>

static void	inittext_keys(t_env *env)
{
	env->text_keys[0] = IMG_Load("img/keys/k1.png");
	env->text_keys[1] = IMG_Load("img/keys/k2.png");
	env->text_keys[2] = IMG_Load("img/keys/k3.png");
	env->text_keys[3] = IMG_Load("img/keys/k4.png");
	env->text_keys[4] = IMG_Load("img/keys/k5.png");
	env->text_keys[5] = IMG_Load("img/keys/k6.png");
	env->text_keys[6] = IMG_Load("img/keys/k7.png");
	env->text_keys[7] = IMG_Load("img/keys/k8.png");
}

static void	inittext_head(t_env *env)
{
	env->text_head[0] = IMG_Load("img/head/1_1.png");
	env->text_head[1] = IMG_Load("img/head/1_2.png");
	env->text_head[2] = IMG_Load("img/head/1_3.png");
	env->text_head[3] = IMG_Load("img/head/2_1.png");
	env->text_head[4] = IMG_Load("img/head/2_2.png");
	env->text_head[5] = IMG_Load("img/head/2_3.png");
	env->text_head[6] = IMG_Load("img/head/3_1.png");
	env->text_head[7] = IMG_Load("img/head/3_2.png");
	env->text_head[8] = IMG_Load("img/head/3_3.png");
	env->text_head[9] = IMG_Load("img/head/4_1.png");
	env->text_head[10] = IMG_Load("img/head/4_2.png");
	env->text_head[11] = IMG_Load("img/head/4_3.png");
	env->text_head[12] = IMG_Load("img/head/5_1.png");
	env->text_head[13] = IMG_Load("img/head/5_2.png");
	env->text_head[14] = IMG_Load("img/head/5_3.png");
	env->text_head[15] = IMG_Load("img/bar_1.png");
	env->text_head[16] = IMG_Load("img/bar_2.png");
	env->text_head[17] = IMG_Load("img/bar_3.png");
	env->text_head[18] = IMG_Load("img/bar_4.png");
	env->text_head[19] = IMG_Load("img/bar_5.png");
	env->text_head[20] = IMG_Load("img/bar_6.png");
	env->text_head[21] = IMG_Load("img/bar_7.png");
	env->text_head[22] = IMG_Load("img/bar_8.png");
	env->text_head[23] = IMG_Load("img/bar_9.png");
	env->text_head[24] = IMG_Load("img/bar_10.png");
}

static void	inittext_game_over_two(t_env *env)
{
	env->game_over[25] = IMG_Load("img/game_over/23.png");
	env->game_over[26] = IMG_Load("img/game_over/22.png");
	env->game_over[27] = IMG_Load("img/game_over/21.png");
	env->game_over[28] = IMG_Load("img/game_over/20.png");
	env->game_over[29] = IMG_Load("img/game_over/19.png");
	env->game_over[30] = IMG_Load("img/game_over/18.png");
	env->game_over[31] = IMG_Load("img/game_over/17.png");
	env->game_over[32] = IMG_Load("img/game_over/16.png");
	env->game_over[33] = IMG_Load("img/game_over/15.png");
	env->game_over[34] = IMG_Load("img/game_over/14.png");
	env->game_over[35] = IMG_Load("img/game_over/13.png");
	env->game_over[36] = IMG_Load("img/game_over/12.png");
	env->game_over[37] = IMG_Load("img/game_over/11.png");
	env->game_over[38] = IMG_Load("img/game_over/10.png");
	env->game_over[39] = IMG_Load("img/game_over/9.png");
	env->game_over[40] = IMG_Load("img/game_over/8.png");
	env->game_over[41] = IMG_Load("img/game_over/7.png");
	env->game_over[42] = IMG_Load("img/game_over/6.png");
	env->game_over[43] = IMG_Load("img/game_over/5.png");
	env->game_over[44] = IMG_Load("img/game_over/4.png");
	env->game_over[45] = IMG_Load("img/game_over/3.png");
	env->game_over[46] = IMG_Load("img/game_over/2.png");
	env->game_over[47] = IMG_Load("img/game_over/1.png");
}

static void	inittext_game_over(t_env *env)
{
	env->game_over[0] = IMG_Load("img/game_over/47.png");
	env->game_over[1] = IMG_Load("img/game_over/46.png");
	env->game_over[2] = IMG_Load("img/game_over/45.png");
	env->game_over[3] = IMG_Load("img/game_over/44.png");
	env->game_over[4] = IMG_Load("img/game_over/43.png");
	env->game_over[5] = IMG_Load("img/game_over/42.png");
	env->game_over[6] = IMG_Load("img/game_over/41.png");
	env->game_over[7] = IMG_Load("img/game_over/40.png");
	env->game_over[8] = IMG_Load("img/game_over/39.png");
	env->game_over[9] = IMG_Load("img/game_over/38.png");
	env->game_over[10] = IMG_Load("img/game_over/37.png");
	env->game_over[11] = IMG_Load("img/game_over/36.png");
	env->game_over[12] = IMG_Load("img/game_over/35.png");
	env->game_over[13] = IMG_Load("img/game_over/34.png");
	env->game_over[14] = IMG_Load("img/game_over/33.png");
	env->game_over[15] = IMG_Load("img/game_over/32.png");
	env->game_over[16] = IMG_Load("img/game_over/31.png");
	env->game_over[17] = IMG_Load("img/game_over/30.png");
	env->game_over[18] = IMG_Load("img/game_over/29.png");
	env->game_over[19] = IMG_Load("img/game_over/28.png");
	env->game_over[21] = IMG_Load("img/game_over/27.png");
	env->game_over[22] = IMG_Load("img/game_over/26.png");
	env->game_over[23] = IMG_Load("img/game_over/25.png");
	env->game_over[24] = IMG_Load("img/game_over/24.png");
	inittext_game_over_two(env);
}

void		inittext(t_env *env)
{
	env->text[0] = IMG_Load("textures/brick.tga");
	env->text[1] = IMG_Load("textures/switch.bmp");
	env->text[2] = IMG_Load("textures/sky.png");
	env->text[7] = IMG_Load("textures/d1.png");
	env->text[6] = IMG_Load("textures/d2.png");
	env->text[5] = IMG_Load("textures/d3.png");
	env->text[4] = IMG_Load("textures/d4.png");
	env->text[3] = IMG_Load("textures/d5.png");
	env->text[8] = IMG_Load("textures/pistol1.png");
	env->text[11] = IMG_Load("textures/pistol2.png");
	env->text[10] = IMG_Load("textures/pistol3.png");
	env->text[9] = IMG_Load("textures/pistol4.png");
	env->text[12] = IMG_Load("textures/sky.png");
	env->text[13] = IMG_Load("textures/shot.png");
	env->text_head[25] = IMG_Load("img/blood.png");
	inittext_head(env);
	inittext_game_over(env);
	inittext_keys(env);
}
