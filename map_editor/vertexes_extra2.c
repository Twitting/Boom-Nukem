/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertexes_extra2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:10:24 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 16:06:21 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	init_message(t_map_ui *ui)
{
	char *message;
	char *message2;
	char *message3;
	char *message4;

	message = (char*)malloc(sizeof(char) * KISS_MAX_LENGTH);
	message2 = (char*)malloc(sizeof(char) * KISS_MAX_LENGTH);
	message3 = (char*)malloc(sizeof(char) * KISS_MAX_LENGTH);
	message4 = (char*)malloc(sizeof(char) * KISS_MAX_LENGTH);
	ui->message = message;
	ui->message2 = message2;
	ui->message3 = message3;
	ui->message4 = message4;
	strcpy(ui->message, "floor:");
	strcpy(ui->message2, "ceiling (neg - sky):");
	strcpy(ui->message3, "light (0-100):");
	strcpy(ui->message4, "texture (0-5):");
}

void	init_label(t_map_ui *ui, t_edit *edit)
{
	ui->quit = 0;
	ui->draw = 1;
	kiss_array_new(&ui->objects);
	ui->title = ft_strjoinfree_right("set sector ", ft_itoa(edit->sectnum));
	ui->renderer = kiss_init(ui->title, &ui->objects, 320, 350);
	kiss_window_new(&ui->window, NULL, 0, 0, 0, kiss_screen_width,
	kiss_screen_height);
	kiss_label_new(&ui->label, &ui->window, ui->message, 8, 10);
	kiss_label_new(&ui->label0, &ui->window, ui->message2, 8, 80);
	kiss_label_new(&ui->label3, &ui->window, ui->message3, 8, 150);
	kiss_label_new(&ui->label4, &ui->window, ui->message4, 8, 220);
	kiss_button_new(&ui->button, &ui->window, "OK", 100, 300);
	ui->window.visible = 1;
	ui->textbox_width = 300;
	kiss_entry_new(&ui->entry0, &ui->window, 1, "0", 0, 35, 320);
	kiss_entry_new(&ui->entry1, &ui->window, 1, "20", 0, 105, 320);
	kiss_entry_new(&ui->entry2, &ui->window, 1, "80", 0, 175, 320);
	kiss_entry_new(&ui->entry3, &ui->window, 1, "0", 0, 250, 320);
}

void	ui_draw(t_map_ui *ui)
{
	SDL_RenderClear(ui->renderer);
	kiss_window_draw(&ui->window, ui->renderer);
	kiss_label_draw(&ui->label, ui->renderer);
	kiss_label_draw(&ui->label0, ui->renderer);
	kiss_label_draw(&ui->label3, ui->renderer);
	kiss_label_draw(&ui->label4, ui->renderer);
	kiss_button_draw(&ui->button, ui->renderer);
	kiss_entry_draw(&ui->entry0, ui->renderer);
	kiss_entry_draw(&ui->entry1, ui->renderer);
	kiss_entry_draw(&ui->entry2, ui->renderer);
	kiss_entry_draw(&ui->entry3, ui->renderer);
	SDL_RenderPresent(ui->renderer);
	ui->draw = 0;
}

void	setsectnums(t_edit *edit, t_map_ui *ui)
{
	SECT.floor = ft_atoi(ui->entry0.text) >= 0 ? ft_atoi(ui->entry0.text) : 0;
	SECT.ceiling = abs(ft_atoi(ui->entry1.text)) - SECT.floor < 10 ?
		SECT.floor + 10 : ft_atoi(ui->entry1.text);
	SECT.light = ft_atoi(ui->entry2.text) >= 0 && ft_atoi(ui->entry2.text)
		<= 100 ? ft_atoi(ui->entry2.text) : 80;
	SECT.texture = ft_atoi(ui->entry3.text) >= 0 && ft_atoi(ui->entry3.text)
		<= 5 ? ft_atoi(ui->entry3.text) : 0;
}
