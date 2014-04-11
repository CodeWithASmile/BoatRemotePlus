#include <pebble.h>
#include "navigation.h"
#include "helpers.h"
	
static TextLayer *dtw_layer;
static TextLayer *btw_layer;
static TextLayer *cog_layer;
static TextLayer *sog_layer;
static TextLayer *dtw_label_layer;
static TextLayer *btw_label_layer;
static TextLayer *cog_label_layer;
static TextLayer *sog_label_layer;

void navigation_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);

	  dtw_label_layer = text_layer_create(GRect(0, 0, 144, 68));
      draw_label(dtw_label_layer, "DTW");
      layer_add_child(window_layer, text_layer_get_layer(dtw_label_layer));
	
	  dtw_layer = text_layer_create(GRect(0, 12, 144, 68));
      text_layer_set_text_color(dtw_layer, GColorWhite);
      text_layer_set_background_color(dtw_layer, GColorClear);
      text_layer_set_font(dtw_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(dtw_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(dtw_layer));
	
	  btw_label_layer = text_layer_create(GRect(0, 40, 144, 68));
      draw_label(btw_label_layer, "BTW (T)");
      layer_add_child(window_layer, text_layer_get_layer(btw_label_layer));
	
	  btw_layer = text_layer_create(GRect(0, 52, 144, 68));
      text_layer_set_text_color(btw_layer, GColorWhite);
      text_layer_set_background_color(btw_layer, GColorClear);
      text_layer_set_font(btw_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(btw_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(btw_layer));
	
	  cog_label_layer = text_layer_create(GRect(0, 80, 144, 68));
      draw_label(cog_label_layer, "COG (T)");
      layer_add_child(window_layer, text_layer_get_layer(cog_label_layer));
	
	  cog_layer = text_layer_create(GRect(0, 92, 144, 68));
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

void navigation_window_unload(Window *window) {
	  text_layer_destroy(dtw_label_layer);
	  text_layer_destroy(dtw_layer);
	  text_layer_destroy(btw_label_layer);
	  text_layer_destroy(btw_layer);
	  text_layer_destroy(cog_label_layer);
	  text_layer_destroy(cog_layer);
	  text_layer_destroy(sog_label_layer);
	  text_layer_destroy(sog_layer);
}

void set_navigation_dtw(const Tuple* new_tuple){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "DTW: %s",  new_tuple->value->cstring);
	text_layer_set_text(dtw_layer, new_tuple->value->cstring);
}

void set_navigation_btw(const Tuple* new_tuple){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "BTW: %s",  new_tuple->value->cstring);
	text_layer_set_text(btw_layer, new_tuple->value->cstring);
}

void set_navigation_cog(const Tuple* new_tuple){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "COG: %s",  new_tuple->value->cstring);
	text_layer_set_text(cog_layer, new_tuple->value->cstring);
}

void set_navigation_sog(const Tuple* new_tuple){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "SOG: %s",  new_tuple->value->cstring);
	text_layer_set_text(sog_layer, new_tuple->value->cstring);
}

