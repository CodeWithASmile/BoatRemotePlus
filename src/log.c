#include <pebble.h>
#include "log.h"
#include "helpers.h"
#include "keys.h"
	
static TextLayer *temp_label_layer;
static TextLayer *distance_total_label_layer;
static TextLayer *distance_reset_label_layer;

#define LOG_NUM_FIELDS 3

int logFields [LOG_NUM_FIELDS] = {BOAT_TEMP_KEY,BOAT_DISTANCE_TOTAL_KEY,BOAT_DISTANCE_RESET_KEY};
TextLayer* logFieldLayers [LOG_NUM_FIELDS];

void log_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);
	  TextLayer * t;

	  distance_total_label_layer = text_layer_create(GRect(0, 0, 144, 68));
	  draw_label(distance_total_label_layer, "Total Distance");
	  layer_add_child(window_layer, text_layer_get_layer(distance_total_label_layer));
	
	  t = create_field_layer(12);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  logFieldLayers[0] = t;
	
	  distance_reset_label_layer = text_layer_create(GRect(0, 45, 144, 68));
	  draw_label(distance_reset_label_layer, "Distance Since Reset");
      layer_add_child(window_layer, text_layer_get_layer(distance_reset_label_layer));
	
	  t = create_field_layer(57);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  logFieldLayers[1] = t;
	
	  temp_label_layer = text_layer_create(GRect(0, 105, 144, 68));
      draw_label(temp_label_layer, "Water Temp");
      layer_add_child(window_layer, text_layer_get_layer(temp_label_layer));
	
	  t = create_field_layer(117);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  logFieldLayers[2] = t;	
}

void log_window_unload(Window *window) {
	  int i;
	  for (i=0; i < LOG_NUM_FIELDS; i++) {
		text_layer_destroy(logFieldLayers[i]);
	  }
	  text_layer_destroy(temp_label_layer);
	  text_layer_destroy(distance_total_label_layer);
	  text_layer_destroy(distance_reset_label_layer);
}

void update_log_fields(DictionaryIterator *iter){
	update_fields(logFields, logFieldLayers, LOG_NUM_FIELDS, iter);
}