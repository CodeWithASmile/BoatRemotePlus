#include <pebble.h>
#include "message.h"
	
static TextLayer *message_layer;

void message_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);
	
	  message_layer = text_layer_create(layer_get_bounds(window_layer));
      text_layer_set_text_color(message_layer, GColorWhite);
      text_layer_set_background_color(message_layer, GColorClear);
      text_layer_set_font(message_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
      text_layer_set_text_alignment(message_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(message_layer));
}

void message_window_unload(Window *window) {
	  text_layer_destroy(message_layer);
}

void set_message(char *message){
	text_layer_set_text(message_layer, message);
}