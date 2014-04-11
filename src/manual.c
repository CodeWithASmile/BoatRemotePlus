#include <pebble.h>
#include "manual.h"
#include "helpers.h"
	
static TextLayer *dtw_layer;
static TextLayer *btw_layer;
static TextLayer *xte_layer;
static TextLayer *heading_to_steer_layer;
static TextLayer *heading_to_steer_type_layer;
static TextLayer *dtw_label_layer;
static TextLayer *btw_label_layer;
static TextLayer *xte_label_layer;
static TextLayer *steer_label_layer;


void manual_window_load(Window *window) {
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
	
	  xte_label_layer = text_layer_create(GRect(0, 80, 144, 68));
      draw_label(xte_label_layer, "XTE");
      layer_add_child(window_layer, text_layer_get_layer(xte_label_layer));
	
	  xte_layer = text_layer_create(GRect(0, 92, 144, 68));
      text_layer_set_text_color(xte_layer, GColorWhite);
      text_layer_set_background_color(xte_layer, GColorClear);
      text_layer_set_font(xte_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(xte_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(xte_layer));
	
	  steer_label_layer = text_layer_create(GRect(0, 120, 144, 68));
      draw_label(steer_label_layer, "Steer");
      layer_add_child(window_layer, text_layer_get_layer(steer_label_layer));
	
	  heading_to_steer_type_layer = text_layer_create(GRect(35, 120, 144, 68));
	  draw_label(heading_to_steer_type_layer, "(?)");
      layer_add_child(window_layer, text_layer_get_layer(heading_to_steer_type_layer));
	
	  heading_to_steer_layer = text_layer_create(GRect(0, 132, 144, 68));
      text_layer_set_text_color(heading_to_steer_layer, GColorWhite);
      text_layer_set_background_color(heading_to_steer_layer, GColorClear);
      text_layer_set_font(heading_to_steer_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      text_layer_set_text_alignment(heading_to_steer_layer, GTextAlignmentCenter);
      layer_add_child(window_layer, text_layer_get_layer(heading_to_steer_layer));
	
}

void manual_window_unload(Window *window) {
	  text_layer_destroy(dtw_label_layer);
	  text_layer_destroy(dtw_layer);
	  text_layer_destroy(btw_label_layer);
	  text_layer_destroy(btw_layer);
	  text_layer_destroy(xte_label_layer);
	  text_layer_destroy(xte_layer);
	  text_layer_destroy(steer_label_layer);
	  text_layer_destroy(heading_to_steer_layer);
	  text_layer_destroy(heading_to_steer_type_layer);
}

void set_manual_dtw(const Tuple* new_tuple){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "DTW: %s",  new_tuple->value->cstring);
	text_layer_set_text(dtw_layer, new_tuple->value->cstring);
}

void set_manual_btw(const Tuple* new_tuple){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "BTW: %s",  new_tuple->value->cstring);
	text_layer_set_text(btw_layer, new_tuple->value->cstring);
}

void set_manual_xte(const Tuple* new_tuple){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "XTE: %s",  new_tuple->value->cstring);
	text_layer_set_text(xte_layer, new_tuple->value->cstring);
}

void set_manual_heading_to_steer(const Tuple* new_tuple){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Heading To Steer: %s",  new_tuple->value->cstring);
	text_layer_set_text(heading_to_steer_layer, new_tuple->value->cstring);
}

void set_manual_heading_to_steer_type(const Tuple* new_tuple){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Heading To Steer Type: %s",  new_tuple->value->cstring);
	text_layer_set_text(heading_to_steer_type_layer, new_tuple->value->cstring);
}

