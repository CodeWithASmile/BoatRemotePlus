#include <pebble.h>
#include "log.h"
#include "helpers.h"
	
static TextLayer *temp_layer;
static TextLayer *distance_total_layer;
static TextLayer *distance_reset_layer;
static TextLayer *temp_label_layer;
static TextLayer *distance_total_label_layer;
static TextLayer *distance_reset_label_layer;

void log_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);

	  distance_total_label_layer = text_layer_create(GRect(0, 0, 144, 68));
	  draw_label(distance_total_label_layer, "Total Distance");
	  layer_add_child(window_layer, text_layer_get_layer(distance_total_label_layer));
	
	  distance_total_layer = text_layer_create(GRect(0, 12, 144, 68));
      text_layer_set_text_color(distance_total_layer, GColorWhite);
      text_layer_set_background_color(distance_total_layer, GColorClear);
      text_layer_set_font(distance_total_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(distance_total_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(distance_total_layer));
	
	  distance_reset_label_layer = text_layer_create(GRect(0, 45, 144, 68));
	  draw_label(distance_reset_label_layer, "Distance Since Reset");
      layer_add_child(window_layer, text_layer_get_layer(distance_reset_label_layer));
	
	  distance_reset_layer = text_layer_create(GRect(0, 57, 144, 68));
      text_layer_set_text_color(distance_reset_layer, GColorWhite);
      text_layer_set_background_color(distance_reset_layer, GColorClear);
      text_layer_set_font(distance_reset_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(distance_reset_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(distance_reset_layer));
	
	  temp_label_layer = text_layer_create(GRect(0, 105, 144, 68));
      draw_label(temp_label_layer, "Water Temp");
      layer_add_child(window_layer, text_layer_get_layer(temp_label_layer));
	
	  temp_layer = text_layer_create(GRect(0, 117, 144, 68));
      text_layer_set_text_color(temp_layer, GColorWhite);
      text_layer_set_background_color(temp_layer, GColorClear);
      text_layer_set_font(temp_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(temp_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(temp_layer));	
}

void log_window_unload(Window *window) {
	  text_layer_destroy(temp_label_layer);
	  text_layer_destroy(temp_layer);
	  text_layer_destroy(distance_total_label_layer);
	  text_layer_destroy(distance_total_layer);
	  text_layer_destroy(distance_reset_label_layer);
	  text_layer_destroy(distance_reset_layer);
}

void set_log_temp(const Tuple* new_tuple){
	text_layer_set_text(temp_layer, new_tuple->value->cstring);
}

void set_log_distance_total(const Tuple* new_tuple){
	text_layer_set_text(distance_total_layer, new_tuple->value->cstring);
}

void set_log_distance_reset(const Tuple* new_tuple){
	text_layer_set_text(distance_reset_layer, new_tuple->value->cstring);
}
