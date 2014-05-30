#include <pebble.h>
#include "menu.h"

#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ICONS 0
#define NUM_FIRST_MENU_ITEMS 5
#define NUM_SECOND_MENU_ITEMS 0
	
MenuLayer *menu_layer;

void (*menu_change_screen)(int nextScreen); 

uint16_t menu_get_num_sections_callback(MenuLayer *me, void *data) {
  return NUM_MENU_SECTIONS;
}

uint16_t menu_get_num_rows_callback(MenuLayer *me, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      return NUM_FIRST_MENU_ITEMS;

    case 1:
      return NUM_SECOND_MENU_ITEMS;

    default:
      return 0;
  }
}

int16_t menu_get_header_height_callback(MenuLayer *me, uint16_t section_index, void *data) {
  // This is a define provided in pebble_os.h that you may use for the default height
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

// Here we draw what each header is
void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Draw Header");
  // Determine which section we're working with
  switch (section_index) {
    case 0:
	  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Draw Header 0");
      // Draw title text in the section header
      menu_cell_basic_header_draw(ctx, cell_layer, "Data");
      break;
  }
}

// This is the menu item draw callback where you specify what each item should look like
void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in
  switch (cell_index->section) {
    case 0:
      // Use the row to specify which item we'll draw
      switch (cell_index->row) {
        case 0:
          menu_cell_title_draw(ctx, cell_layer, "GPS");
          break;
        case 1:
          menu_cell_title_draw(ctx, cell_layer, "Sailing");
          break;
		case 2:
          menu_cell_title_draw(ctx, cell_layer, "Navigation");
          break;
		case 3:
          menu_cell_title_draw(ctx, cell_layer, "Waypoint");
          break;
		case 4:
          menu_cell_title_draw(ctx, cell_layer, "Log");
          break;
	  }
  }
}

void menu_set_selected(int currentScreen){
	MenuIndex last_selected = menu_layer_get_selected_index(menu_layer);
	last_selected.row = currentScreen;
	menu_layer_set_selected_index(menu_layer, last_selected, MenuRowAlignCenter, false);
}

void menu_set_change_screen_function(void (*function)(int nextScreen))
{
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Setting change_screen fucntion");
	menu_change_screen = function;	
}

void menu_select_callback(MenuLayer *me, MenuIndex *cell_index, void *data) {
	int nextScreen = cell_index->row;
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "menu select callback %d", nextScreen);
	(*menu_change_screen)(nextScreen);
}

// This initializes the menu upon window load
void menu_window_load(Window *me) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Loading Menu Layer");
  
  Layer *window_layer = window_get_root_layer(me);
	
  // We need the bounds to specify the menu layer's viewport size
  // In this case, it'll be the same as the window's

  // Initialize the menu layer
  GRect bounds = layer_get_bounds(window_layer);
  menu_layer = menu_layer_create(bounds);

  // Set all the callbacks for the menu layer
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(menu_layer, me);

  // Add it to the window for display
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
}

void menu_window_unload(Window *me) {
	  menu_layer_destroy(menu_layer);
}