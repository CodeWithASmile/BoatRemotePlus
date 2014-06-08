#include <pebble.h>
#include "main_menu.h"

#define NUM_MAIN_MENU_SECTIONS 1
#define NUM_MAIN_MENU_ICONS 0
#define NUM_MAIN_MENU_ITEMS 2
	
MenuLayer *main_menu_layer;

void (*main_menu_change_screen)(int menu); 

uint16_t main_menu_get_num_sections_callback(MenuLayer *me, void *data) {
  return NUM_MAIN_MENU_SECTIONS;
}

uint16_t main_menu_get_num_rows_callback(MenuLayer *me, uint16_t section_index, void *data) {
  return NUM_MAIN_MENU_ITEMS;
}

int16_t main_menu_get_header_height_callback(MenuLayer *me, uint16_t section_index, void *data) {
  // This is a define provided in pebble_os.h that you may use for the default height
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

// Here we draw what each header is
void main_menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Draw Header");
  // Determine which section we're working with
  menu_cell_basic_header_draw(ctx, cell_layer, "View");
}

// This is the menu item draw callback where you specify what each item should look like
void main_menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in
  switch (cell_index->section) {
    case 0:
      // Use the row to specify which item we'll draw
      switch (cell_index->row) {
        case 0:
          menu_cell_title_draw(ctx, cell_layer, "View");
          break;
		case 1:
          menu_cell_title_draw(ctx, cell_layer, "Control");
          break;
	  }
  }
}

void main_menu_set_selected(int current_menu){
	MenuIndex last_selected = menu_layer_get_selected_index(main_menu_layer);
	last_selected.row = current_menu;
	menu_layer_set_selected_index(main_menu_layer, last_selected, MenuRowAlignCenter, false);
}

void main_menu_set_change_screen_function(void (*function)(int menu))
{
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Setting change_screen fucntion");
	main_menu_change_screen = function;	
}

void main_menu_select_callback(MenuLayer *me, MenuIndex *cell_index, void *data) {
	int menu = cell_index->row;
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "menu select callback %d", nextScreen);
	(*main_menu_change_screen)(menu);
}

// This initializes the menu upon window load
void main_menu_window_load(Window *me) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Loading View Menu Layer");
  
  Layer *window_layer = window_get_root_layer(me);
	
  // We need the bounds to specify the menu layer's viewport size
  // In this case, it'll be the same as the window's

  // Initialize the menu layer
  GRect bounds = layer_get_bounds(window_layer);
  main_menu_layer = menu_layer_create(bounds);

  // Set all the callbacks for the menu layer
  menu_layer_set_callbacks(main_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = main_menu_get_num_sections_callback,
    .get_num_rows = main_menu_get_num_rows_callback,
    .get_header_height = main_menu_get_header_height_callback,
    .draw_header = main_menu_draw_header_callback,
    .draw_row = main_menu_draw_row_callback,
    .select_click = main_menu_select_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(main_menu_layer, me);

  // Add it to the window for display
  layer_add_child(window_layer, menu_layer_get_layer(main_menu_layer));
}

void main_menu_window_unload(Window *me) {
	  menu_layer_destroy(main_menu_layer);
}