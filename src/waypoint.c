#include <pebble.h>
#include "waypoint.h"
#include "helpers.h"
#include "keys.h"	

static TextLayer *pos_label_layer;
static TextLayer *btw_label_layer;
static TextLayer *dtw_label_layer;

#define WAYPOINT_NUM_FIELDS 5

int waypointFields [WAYPOINT_NUM_FIELDS] = {BOAT_WAYPOINT_KEY,BOAT_WPT_LAT_KEY,BOAT_WPT_LON_KEY,
						   BOAT_BTW_KEY, BOAT_DTW_KEY};
TextLayer* waypointFieldLayers [WAYPOINT_NUM_FIELDS];

void waypoint_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);
	  TextLayer * t;
	 
	  t = create_field_layer(0);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  waypointFieldLayers[0] = t;

	  pos_label_layer = text_layer_create(GRect(0, 25, 144, 68));
      draw_label(pos_label_layer, "WP Pos");
      layer_add_child(window_layer, text_layer_get_layer(pos_label_layer));
	
	  t = create_field_layer(37);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  waypointFieldLayers[1] = t;  
	
	  t = create_field_layer(60);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  waypointFieldLayers[2] = t; 
	
	  btw_label_layer = text_layer_create(GRect(0, 88, 144, 68));
      draw_label(btw_label_layer, "BTW (T)");
      layer_add_child(window_layer, text_layer_get_layer(btw_label_layer));
	
	  t = create_field_layer(100);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  waypointFieldLayers[3] = t;
	
	  dtw_label_layer = text_layer_create(GRect(0, 123, 144, 68));
      draw_label(dtw_label_layer, "DTW");
      layer_add_child(window_layer, text_layer_get_layer(dtw_label_layer));
	
	  t = create_field_layer(135);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  waypointFieldLayers[4] = t;
	
}

void waypoint_window_unload(Window *window) {
	  int i;
	  for (i=0; i < WAYPOINT_NUM_FIELDS; i++) {
		text_layer_destroy(waypointFieldLayers[i]);
	  }
	  text_layer_destroy(pos_label_layer);
	  text_layer_destroy(btw_label_layer);
	  text_layer_destroy(dtw_label_layer);
}

void update_waypoint_fields(DictionaryIterator *iter){
	update_fields(waypointFields, waypointFieldLayers, WAYPOINT_NUM_FIELDS, iter);
}
