#include <pebble.h>
#include "anchor_watch.h"
#include "helpers.h"
#include "keys.h"
	
static TextLayer *drift_label_layer;
static TextLayer *instruction_label_layer;

#define ANCHOR_WATCH_NUM_FIELDS 1

int anchorWatchFields [ANCHOR_WATCH_NUM_FIELDS] = {BOAT_DRIFT_KEY};
TextLayer* anchorWatchFieldLayers [ANCHOR_WATCH_NUM_FIELDS];

void anchor_watch_window_load(Window *window) {
      Layer *window_layer = window_get_root_layer(window);
	  TextLayer *t;

	  drift_label_layer = text_layer_create(GRect(0, 0, 144, 68));
      draw_label(drift_label_layer, "Distance Drifted");
      layer_add_child(window_layer, text_layer_get_layer(drift_label_layer));
	
	  t = create_field_layer(15);
      text_layer_set_font(t, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      layer_add_child(window_layer, text_layer_get_layer(t));
	  anchorWatchFieldLayers[0] = t;
	
	  instruction_label_layer = text_layer_create(GRect(0, 75, 144, 68));
      draw_label(instruction_label_layer, "Click Centre Button To Set Position");
      layer_add_child(window_layer, text_layer_get_layer(instruction_label_layer));
}

void anchor_watch_window_unload(Window *window) {
	  int i;
	for (i=0; i <ANCHOR_WATCH_NUM_FIELDS; i++) {
		text_layer_destroy(anchorWatchFieldLayers[i]);
	}
	  text_layer_destroy(drift_label_layer);
	  text_layer_destroy(instruction_label_layer);
}

void update_anchor_watch_fields(DictionaryIterator *iter){
	update_fields(anchorWatchFields, anchorWatchFieldLayers, ANCHOR_WATCH_NUM_FIELDS, iter);
}
