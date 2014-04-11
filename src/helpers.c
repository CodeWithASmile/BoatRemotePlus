#include <pebble.h>
#include "helpers.h"

	void draw_label(TextLayer *layer, const char *value){
	  text_layer_set_text_color(layer, GColorWhite);
      text_layer_set_background_color(layer, GColorClear);
      text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
      text_layer_set_text_alignment(layer, GTextAlignmentLeft);
	  text_layer_set_text(layer, value);
}