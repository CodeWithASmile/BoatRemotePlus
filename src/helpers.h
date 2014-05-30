#pragma once

void draw_label(TextLayer *layer, const char *value);

TextLayer* create_field_layer(int verticalPosition);

void update_fields(int fields[], TextLayer *fieldLayers[], int numFields, DictionaryIterator *iter);