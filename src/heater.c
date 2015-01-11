#include <pebble.h>
#include "heater.h"
#include "helpers.h"
	
static TextLayer *heater_label_layer;

void heater_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);

	  heater_label_layer = text_layer_create(GRect(0, 0, 144, 68));
      draw_label(heater_label_layer, "Heater");
      layer_add_child(window_layer, text_layer_get_layer(heater_label_layer));
	
}

void heater_window_unload(Window *window) {
	  text_layer_destroy(heater_label_layer);

}

