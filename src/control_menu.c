#include <pebble.h>
#include "control_menu.h"

#define NUM_CONTROL_MENU_SECTIONS 1
#define NUM_CONTROL_MENU_ICONS 0
#define NUM_CONTROL_MENU_ITEMS 2
	
MenuLayer *control_menu_layer;

ClickConfigProvider control_previous_ccp;

void (*control_menu_change_screen)(int nextScreen); 
void (*control_menu_back_button_handler)(); 

uint16_t control_menu_get_num_sections_callback(MenuLayer *me, void *data) {
  return NUM_CONTROL_MENU_SECTIONS;
}

uint16_t control_menu_get_num_rows_callback(MenuLayer *me, uint16_t section_index, void *data) {
  return NUM_CONTROL_MENU_ITEMS;
}

int16_t control_menu_get_header_height_callback(MenuLayer *me, uint16_t section_index, void *data) {
  // This is a define provided in pebble_os.h that you may use for the default height
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

// Here we draw what each header is
void control_menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Draw Header");
  // Determine which section we're working with
  menu_cell_basic_header_draw(ctx, cell_layer, "Control");
}

// This is the menu item draw callback where you specify what each item should look like
void control_menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in
  switch (cell_index->section) {
    case 0:
      // Use the row to specify which item we'll draw
      switch (cell_index->row) {
        case 0:
          menu_cell_title_draw(ctx, cell_layer, "Lights");
          break;
	  }
	  switch (cell_index->row) {
        case 1:
          menu_cell_title_draw(ctx, cell_layer, "Heater");
          break;
	  }
  }
}

void control_menu_set_selected(int currentScreen){
	MenuIndex last_selected = menu_layer_get_selected_index(control_menu_layer);
	last_selected.row = currentScreen;
	menu_layer_set_selected_index(control_menu_layer, last_selected, MenuRowAlignCenter, false);
}

void control_menu_set_back_button_function(void (*function))
{
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Setting back_button_callback fucntion");
	control_menu_back_button_handler = function;	
}

void control_menu_set_change_screen_function(void (*function)(int nextScreen))
{
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Setting change_screen fucntion");
	control_menu_change_screen = function;	
}

void control_menu_select_callback(MenuLayer *me, MenuIndex *cell_index, void *data) {
	int nextScreen = cell_index->row;
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "menu select callback %d", nextScreen);
	(*control_menu_change_screen)(nextScreen);
}

// This is the new ClickConfigProvider we will set, it just calls the old one and then subscribe
// for back button events.
void control_new_ccp(void *context) {
APP_LOG(APP_LOG_LEVEL_DEBUG, "calling the new control ccp");
control_previous_ccp(context);
window_single_click_subscribe(BUTTON_ID_BACK, control_menu_back_button_handler);
APP_LOG(APP_LOG_LEVEL_DEBUG, "done in the new ccp");
}
 
// Call this from your init function to do the hack
void control_force_back_button(Window *window, MenuLayer *menu_layer) {
control_previous_ccp = window_get_click_config_provider(window);
window_set_click_config_provider_with_context(window, control_new_ccp, menu_layer);
}

// This initializes the menu upon window load
void control_menu_window_load(Window *me) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Loading Control Menu Layer");
  
  Layer *window_layer = window_get_root_layer(me);
	
  // We need the bounds to specify the menu layer's viewport size
  // In this case, it'll be the same as the window's

  // Initialize the menu layer
  GRect bounds = layer_get_bounds(window_layer);
  control_menu_layer = menu_layer_create(bounds);

  // Set all the callbacks for the menu layer
  menu_layer_set_callbacks(control_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = control_menu_get_num_sections_callback,
    .get_num_rows = control_menu_get_num_rows_callback,
    .get_header_height = control_menu_get_header_height_callback,
    .draw_header = control_menu_draw_header_callback,
    .draw_row = control_menu_draw_row_callback,
    .select_click = control_menu_select_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(control_menu_layer, me);

  // Add it to the window for display
  layer_add_child(window_layer, menu_layer_get_layer(control_menu_layer));
  control_force_back_button(me, control_menu_layer);
}

void control_menu_window_unload(Window *me) {
	  menu_layer_destroy(control_menu_layer);
}