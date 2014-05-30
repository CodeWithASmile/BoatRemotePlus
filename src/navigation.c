#include <pebble.h>
#include "navigation.h"
#include "helpers.h"
#include "keys.h"
	

static TextLayer *dtw_label_layer;
static TextLayer *btw_label_layer;
static TextLayer *cog_label_layer;
static TextLayer *sog_label_layer;

#define NAVIGATION_NUM_FIELDS 4

int navigationFields [NAVIGATION_NUM_FIELDS] = {BOAT_DTW_KEY,BOAT_BTW_KEY,BOAT_COG_KEY,BOAT_SOG_KEY};
TextLayer* navigationFieldLayers [NAVIGATION_NUM_FIELDS];

void navigation_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);
	  TextLayer * t;

	  dtw_label_layer = text_layer_create(GRect(0, 0, 144, 68));
      draw_label(dtw_label_layer, "DTW");
      layer_add_child(window_layer, text_layer_get_layer(dtw_label_layer));
	
	  t = create_field_layer(12);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  navigationFieldLayers[0] = t;  
	
	  btw_label_layer = text_layer_create(GRect(0, 40, 144, 68));
      draw_label(btw_label_layer, "BTW (T)");
      layer_add_child(window_layer, text_layer_get_layer(btw_label_layer));
	
	  t = create_field_layer(52);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  navigationFieldLayers[1] = t;  
	
	  cog_label_layer = text_layer_create(GRect(0, 80, 144, 68));
      draw_label(cog_label_layer, "COG (T)");
      layer_add_child(window_layer, text_layer_get_layer(cog_label_layer));
	
	  t = create_field_layer(92);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  navigationFieldLayers[2] = t;  
	
	  sog_label_layer = text_layer_create(GRect(0, 120, 144, 68));
      draw_label(sog_label_layer, "SOG");
      layer_add_child(window_layer, text_layer_get_layer(sog_label_layer));
	
	  t = create_field_layer(132);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  navigationFieldLayers[3] = t;  	
}

void navigation_window_unload(Window *window) {
	  int i;
	  for (i=0; i < NAVIGATION_NUM_FIELDS; i++) {
		text_layer_destroy(navigationFieldLayers[i]);
	  }
	  text_layer_destroy(dtw_label_layer);
	  text_layer_destroy(btw_label_layer);
	  text_layer_destroy(cog_label_layer);
	  text_layer_destroy(sog_label_layer);
}

void update_navigation_fields(DictionaryIterator *iter){
	update_fields(navigationFields, navigationFieldLayers, NAVIGATION_NUM_FIELDS, iter);
}

