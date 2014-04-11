#include <pebble.h>
#include "gps.h"
#include "helpers.h"
	
static TextLayer *lat_layer;
static TextLayer *lon_layer;
static TextLayer *cog_layer;
static TextLayer *sog_layer;
static TextLayer *pos_label_layer;
static TextLayer *cog_label_layer;
static TextLayer *sog_label_layer;

void gps_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);

	  pos_label_layer = text_layer_create(GRect(0, 0, 144, 68));
      draw_label(pos_label_layer, "Pos");
      layer_add_child(window_layer, text_layer_get_layer(pos_label_layer));
	
	  lat_layer = text_layer_create(GRect(0, 15, 144, 68));
      text_layer_set_text_color(lat_layer, GColorWhite);
      text_layer_set_background_color(lat_layer, GColorClear);
      text_layer_set_font(lat_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      text_layer_set_text_alignment(lat_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(lat_layer));
	
	  lon_layer = text_layer_create(GRect(0, 40, 144, 68));
      text_layer_set_text_color(lon_layer, GColorWhite);
      text_layer_set_background_color(lon_layer, GColorClear);
      text_layer_set_font(lon_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      text_layer_set_text_alignment(lon_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(lon_layer));
	
	  cog_label_layer = text_layer_create(GRect(0, 75, 144, 68));
      draw_label(cog_label_layer, "COG (T)");
      layer_add_child(window_layer, text_layer_get_layer(cog_label_layer));
	
	  cog_layer = text_layer_create(GRect(0, 87, 144, 68));
      text_layer_set_text_color(cog_layer, GColorWhite);
      text_layer_set_background_color(cog_layer, GColorClear);
      text_layer_set_font(cog_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(cog_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(cog_layer));
	
	  sog_label_layer = text_layer_create(GRect(0, 120, 144, 68));
      draw_label(sog_label_layer, "SOG");
      layer_add_child(window_layer, text_layer_get_layer(sog_label_layer));
	
	  sog_layer = text_layer_create(GRect(0, 132, 144, 68));
      text_layer_set_text_color(sog_layer, GColorWhite);
      text_layer_set_background_color(sog_layer, GColorClear);
      text_layer_set_font(sog_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(sog_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(sog_layer));
	
}

void gps_window_unload(Window *window) {
	  text_layer_destroy(pos_label_layer);
	  text_layer_destroy(lat_layer);
	  text_layer_destroy(lon_layer);
	  text_layer_destroy(cog_label_layer);
	  text_layer_destroy(cog_layer);
	  text_layer_destroy(sog_label_layer);
	  text_layer_destroy(sog_layer);
}

void set_gps_lat(const Tuple* new_tuple){
	text_layer_set_text(lat_layer, new_tuple->value->cstring);
}

void set_gps_lon(const Tuple* new_tuple){
	text_layer_set_text(lon_layer, new_tuple->value->cstring);
}

void set_gps_cog(const Tuple* new_tuple){
	text_layer_set_text(cog_layer, new_tuple->value->cstring);
}

void set_gps_sog(const Tuple* new_tuple){
	text_layer_set_text(sog_layer, new_tuple->value->cstring);
}

