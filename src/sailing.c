#include <pebble.h>
#include "sailing.h"
#include "helpers.h"
#include "keys.h"

static TextLayer *speed_label_layer;
static TextLayer *depth_label_layer;
static TextLayer *wind_label_layer;

#define SAILING_NUM_FIELDS 4

int sailingFields [SAILING_NUM_FIELDS] = {BOAT_BOAT_SPEED_KEY,BOAT_DEPTH_KEY,BOAT_WIND_SPEED_KEY,BOAT_WIND_ANGLE_KEY};
TextLayer* sailingFieldLayers [SAILING_NUM_FIELDS];

void sailing_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);
	  TextLayer * t;

	  speed_label_layer = text_layer_create(GRect(0, 0, 144, 68));
	  draw_label(speed_label_layer, "Speed");
	  layer_add_child(window_layer, text_layer_get_layer(speed_label_layer));
	
	  t = create_field_layer(12);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  sailingFieldLayers[0] = t;
	
	  depth_label_layer = text_layer_create(GRect(0, 45, 144, 68));
	  draw_label(depth_label_layer, "Depth");
      layer_add_child(window_layer, text_layer_get_layer(depth_label_layer));
	
	  t = create_field_layer(57);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  sailingFieldLayers[1] = t;
	
	  wind_label_layer = text_layer_create(GRect(0, 90, 144, 68));
      draw_label(wind_label_layer, "Wind");
      layer_add_child(window_layer, text_layer_get_layer(wind_label_layer));
	
	  t = create_field_layer(102);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  sailingFieldLayers[2] = t;
	
	  t = create_field_layer(132);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  sailingFieldLayers[3] = t;
	
}

void sailing_window_unload(Window *window) {
	  int i;
	  for (i=0; i < SAILING_NUM_FIELDS; i++) {
		text_layer_destroy(sailingFieldLayers[i]);
	  }
	  text_layer_destroy(speed_label_layer);
	  text_layer_destroy(depth_label_layer);
	  text_layer_destroy(wind_label_layer);
}

void update_sailing_fields(DictionaryIterator *iter){
	update_fields(sailingFields, sailingFieldLayers, SAILING_NUM_FIELDS, iter);
}
