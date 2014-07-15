#include <pebble.h>
#include "popup.h"
	
static TextLayer *popup_layer;

void popup_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);
	
	  popup_layer = text_layer_create(layer_get_bounds(window_layer));
      text_layer_set_text_color(popup_layer, GColorWhite);
      text_layer_set_background_color(popup_layer, GColorClear);
      text_layer_set_font(popup_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
      text_layer_set_text_alignment(popup_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(popup_layer));
}

void popup_window_unload(Window *window) {
	  text_layer_destroy(popup_layer);
}

void set_popup(char *popup){
	text_layer_set_text(popup_layer, popup);
}