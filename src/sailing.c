#include <pebble.h>
#include "sailing.h"
#include "helpers.h"
	
static TextLayer *boat_speed_layer;
static TextLayer *depth_layer;
static TextLayer *wind_speed_layer;
static TextLayer *wind_angle_layer;
static TextLayer *speed_label_layer;
static TextLayer *depth_label_layer;
static TextLayer *wind_label_layer;

void sailing_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);

	  speed_label_layer = text_layer_create(GRect(0, 0, 144, 68));
	  draw_label(speed_label_layer, "Speed");
	  layer_add_child(window_layer, text_layer_get_layer(speed_label_layer));
	
	  boat_speed_layer = text_layer_create(GRect(0, 12, 144, 68));
      text_layer_set_text_color(boat_speed_layer, GColorWhite);
      text_layer_set_background_color(boat_speed_layer, GColorClear);
      text_layer_set_font(boat_speed_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(boat_speed_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(boat_speed_layer));
	
	  depth_label_layer = text_layer_create(GRect(0, 45, 144, 68));
	  draw_label(depth_label_layer, "Depth");
      layer_add_child(window_layer, text_layer_get_layer(depth_label_layer));
	
	  depth_layer = text_layer_create(GRect(0, 57, 144, 68));
      text_layer_set_text_color(depth_layer, GColorWhite);
      text_layer_set_background_color(depth_layer, GColorClear);
      text_layer_set_font(depth_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(depth_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(depth_layer));
	
	  wind_label_layer = text_layer_create(GRect(0, 90, 144, 68));
      draw_label(wind_label_layer, "Wind");
      layer_add_child(window_layer, text_layer_get_layer(wind_label_layer));
	
	  wind_speed_layer = text_layer_create(GRect(0, 102, 144, 68));
      text_layer_set_text_color(wind_speed_layer, GColorWhite);
      text_layer_set_background_color(wind_speed_layer, GColorClear);
      text_layer_set_font(wind_speed_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(wind_speed_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(wind_speed_layer));
	
	  wind_angle_layer = text_layer_create(GRect(0, 132, 144, 68));
      text_layer_set_text_color(wind_angle_layer, GColorWhite);
      text_layer_set_background_color(wind_angle_layer, GColorClear);
      text_layer_set_font(wind_angle_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(wind_angle_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(wind_angle_layer));
	
}

void sailing_window_unload(Window *window) {
	  text_layer_destroy(speed_label_layer);
	  text_layer_destroy(boat_speed_layer);
	  text_layer_destroy(depth_label_layer);
	  text_layer_destroy(depth_layer);
	  text_layer_destroy(wind_label_layer);
	  text_layer_destroy(wind_speed_layer);
	  text_layer_destroy(wind_angle_layer);
}

void set_sailing_boat_speed(const Tuple* new_tuple){
	text_layer_set_text(boat_speed_layer, new_tuple->value->cstring);
}

void set_sailing_depth(const Tuple* new_tuple){
	text_layer_set_text(depth_layer, new_tuple->value->cstring);
}

void set_sailing_wind_speed(const Tuple* new_tuple){
	text_layer_set_text(wind_speed_layer, new_tuple->value->cstring);
}

void set_sailing_wind_angle(const Tuple* new_tuple){
	text_layer_set_text(wind_angle_layer, new_tuple->value->cstring);
}
