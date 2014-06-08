#pragma once

uint16_t control_menu_get_num_sections_callback(MenuLayer *me, void *data); 

uint16_t control_menu_get_num_rows_callback(MenuLayer *me, uint16_t section_index, void *data);

int16_t control_menu_get_header_height_callback(MenuLayer *me, uint16_t section_index, void *data);

void control_menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data);

void control_menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data);

void control_menu_set_change_screen_function(void (*function)(int nextScreen));

void control_menu_set_selected(int currentScreen);

void control_menu_select_callback(MenuLayer *me, MenuIndex *cell_index, void *data);

void control_menu_window_load(Window *me);

void control_menu_window_unload(Window *me);