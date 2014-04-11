#include <pebble.h>
#include "waypoint.h"
#include "helpers.h"
	
static TextLayer *waypoint_layer;
static TextLayer *lat_layer;
static TextLayer *lon_layer;
static TextLayer *btw_layer;
static TextLayer *dtw_layer;
static TextLayer *pos_label_layer;
static TextLayer *btw_label_layer;
static TextLayer *dtw_label_layer;

void waypoint_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);
	
	  waypoint_layer = text_layer_create(GRect(0, 0, 144, 68));
      text_layer_set_text_color(waypoint_layer, GColorWhite);
      text_layer_set_background_color(waypoint_layer, GColorClear);
      text_layer_set_font(waypoint_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      text_layer_set_text_alignment(waypoint_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(waypoint_layer));

	  pos_label_layer = text_layer_create(GRect(0, 25, 144, 68));
      draw_label(pos_label_layer, "WP Pos");
      layer_add_child(window_layer, text_layer_get_layer(pos_label_layer));
	
	  lat_layer = text_layer_create(GRect(0, 37, 144, 68));
      text_layer_set_text_color(lat_layer, GColorWhite);
      text_layer_set_background_color(lat_layer, GColorClear);
      text_layer_set_font(lat_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      text_layer_set_text_alignment(lat_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(lat_layer));
	
	  lon_layer = text_layer_create(GRect(0, 60, 144, 68));
      text_layer_set_text_color(lon_layer, GColorWhite);
      text_layer_set_background_color(lon_layer, GColorClear);
      text_layer_set_font(lon_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      text_layer_set_text_alignment(lon_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(lon_layer));
	
	  btw_label_layer = text_layer_create(GRect(0, 88, 144, 68));
      draw_label(btw_label_layer, "BTW (T)");
      layer_add_child(window_layer, text_layer_get_layer(btw_label_layer));
	
	  btw_layer = text_layer_create(GRect(0, 100, 144, 68));
      text_layer_set_text_color(btw_layer, GColorWhite);
      text_layer_set_background_color(btw_layer, GColorClear);
      text_layer_set_font(btw_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(btw_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(btw_layer));
	
	  dtw_label_layer = text_layer_create(GRect(0, 123, 144, 68));
      draw_label(dtw_label_layer, "DTW");
      layer_add_child(window_layer, text_layer_get_layer(dtw_label_layer));
	
	  dtw_layer = text_layer_create(GRect(0, 135, 144, 68));
      text_layer_set_text_color(dtw_layer, GColorWhite);
      text_layer_set_background_color(dtw_layer, GColorClear);
      text_layer_set_font(dtw_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(dtw_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(dtw_layer));
	
}

void waypoint_window_unload(Window *window) {
	  text_layer_destroy(waypoint_layer);
	  text_layer_destroy(pos_label_layer);
	  text_layer_destroy(lat_layer);
	  text_layer_destroy(lon_layer);
	  text_layer_destroy(btw_label_layer);
	  text_layer_destroy(btw_layer);
	  text_layer_destroy(dtw_label_layer);
	  text_layer_destroy(dtw_layer);
}

void set_waypoint_waypoint(const Tuple* new_tuple){
	text_layer_set_text(waypoint_layer, new_tuple->value->cstring);
}

void set_waypoint_wpt_lat(const Tuple* new_tuple){
	text_layer_set_text(lat_layer, new_tuple->value->cstring);
}

void set_waypoint_wpt_lon(const Tuple* new_tuple){
	text_layer_set_text(lon_layer, new_tuple->value->cstring);
}

void set_waypoint_btw(const Tuple* new_tuple){
	text_layer_set_text(btw_layer, new_tuple->value->cstring);
}

void set_waypoint_dtw(const Tuple* new_tuple){
	text_layer_set_text(dtw_layer, new_tuple->value->cstring);
}

