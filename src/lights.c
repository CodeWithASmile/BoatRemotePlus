#include <pebble.h>
#include "lights.h"
#include "helpers.h"
	
static TextLayer *lights_label_layer;

void lights_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);

	  lights_label_layer = text_layer_create(GRect(0, 0, 144, 68));
      draw_label(lights_label_layer, "Lights!");
      layer_add_child(window_layer, text_layer_get_layer(lights_label_layer));
	
}

void lights_window_unload(Window *window) {
	  text_layer_destroy(lights_label_layer);

}


