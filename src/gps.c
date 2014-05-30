#include <pebble.h>
#include "gps.h"
#include "helpers.h"
#include "keys.h"
	
static TextLayer *pos_label_layer;
static TextLayer *cog_label_layer;
static TextLayer *sog_label_layer;

#define GPS_NUM_FIELDS 4

int gpsFields [GPS_NUM_FIELDS] = {BOAT_LAT_KEY,BOAT_LON_KEY,BOAT_COG_KEY,BOAT_SOG_KEY};
TextLayer* gpsFieldLayers [GPS_NUM_FIELDS];

void gps_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);
	  TextLayer *t;

	  pos_label_layer = text_layer_create(GRect(0, 0, 144, 68));
      draw_label(pos_label_layer, "Pos");
      layer_add_child(window_layer, text_layer_get_layer(pos_label_layer));
	
	  t = create_field_layer(15);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  gpsFieldLayers[0] = t;
	
	  t = create_field_layer(40);;
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  gpsFieldLayers[1] = t;
	
	  cog_label_layer = text_layer_create(GRect(0, 75, 144, 68));
      draw_label(cog_label_layer, "COG (T)");
      layer_add_child(window_layer, text_layer_get_layer(cog_label_layer));
	
	  t = create_field_layer(87);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  gpsFieldLayers[2] = t;
	
	  sog_label_layer = text_layer_create(GRect(0, 120, 144, 68));
      draw_label(sog_label_layer, "SOG");
      layer_add_child(window_layer, text_layer_get_layer(sog_label_layer));
	
	  t = create_field_layer(132);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  gpsFieldLayers[3] = t;
	
}

void gps_window_unload(Window *window) {
	  int i;
	for (i=0; i < GPS_NUM_FIELDS; i++) {
		text_layer_destroy(gpsFieldLayers[i]);
	}
	  text_layer_destroy(pos_label_layer);
	  text_layer_destroy(cog_label_layer);
	  text_layer_destroy(sog_label_layer);
}

void update_gps_fields(DictionaryIterator *iter){
	update_fields(gpsFields, gpsFieldLayers, GPS_NUM_FIELDS, iter);
}


