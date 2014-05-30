#include <pebble.h>
#include "helpers.h"

	void draw_label(TextLayer *layer, const char *value){
	  text_layer_set_text_color(layer, GColorWhite);
      text_layer_set_background_color(layer, GColorClear);
      text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
      text_layer_set_text_alignment(layer, GTextAlignmentLeft);
	  text_layer_set_text(layer, value);
}

    TextLayer* create_field_layer(int verticalPosition){
	  TextLayer *layer = text_layer_create(GRect(0, verticalPosition, 144, 68));
	  text_layer_set_text_color(layer, GColorWhite);
      text_layer_set_background_color(layer, GColorClear);
      text_layer_set_text_alignment(layer, GTextAlignmentCenter);
	  return layer;
}

	void update_fields(int fields[], TextLayer *fieldLayers[], int numFields, DictionaryIterator *iter){
	  int i;
	  Tuple *tuple;
	  for(i = 0; i < numFields; i++){
  		tuple = dict_find(iter, fields[i]);
		if (tuple){
			text_layer_set_text(fieldLayers[i], tuple->value->cstring);
		}
	  }
    }