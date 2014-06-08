#include <pebble.h>
#include <inttypes.h>
#include "message.h"
#include "gps.h"
#include "sailing.h"
#include "navigation.h"
#include "waypoint.h"
#include "log.h"
#include "anchor_watch.h"
#include "lights.h"
#include "view_menu.h"
#include "control_menu.h"
#include "main_menu.h"
#include "keys.h"
	
#define VIEW_WINDOW_COUNT 6
#define CONTROL_WINDOW_COUNT 1
#define MAX_WINDOW_COUNT 6 //Max of two constants above
#define MENU_WINDOW_COUNT 3

Window* message_window;
Window* data_windows[2][MAX_WINDOW_COUNT];
Window* menu_windows[MAX_WINDOW_COUNT];

//int view_windows_enable[VIEW_WINDOW_COUNT] = {1,1,1,1,1,1};
//int control_windows_enable[CONTROL_WINDOW_COUNT] = {1};

int current_screen;
int last_screen;
int current_menu;
int server_error;
int phone_heartbeat;

//Data Keys are now stored in helpers.c

enum ViewScreenKey {
  SCREEN_MESSAGE_KEY = -2,
  SCREEN_MENU_KEY = -1,
  SCREEN_GPS_KEY = 0,
  SCREEN_SAILING_KEY = 1,
  SCREEN_NAVIGATION_KEY = 2,
  SCREEN_WAYPOINT_KEY = 3,
  SCREEN_LOG_KEY = 4,
  SCREEN_ANCHOR_WATCH_KEY = 5
};

enum ControlScreenKey {
  SCREEN_LIGHTS_KEY = 0
};

enum MenuKey {
   VIEW_MENU = 0,
   CONTROL_MENU = 1,
   MAIN_MENU = 2
};

void show_message(char message[]){
	window_stack_pop(true);
	window_stack_push(message_window, true);
	set_message(message);
	last_screen = current_screen;
	current_screen = SCREEN_MESSAGE_KEY;
}

void load_menu(int menu){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Current menu %d", current_menu);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "New menu %d", menu);
	window_stack_pop(true);
	window_stack_push(menu_windows[menu], true);
	current_screen=SCREEN_MENU_KEY;
	switch(menu){
		case VIEW_MENU:
		    APP_LOG(APP_LOG_LEVEL_DEBUG, "Setting view menu selected");
			view_menu_set_selected(last_screen);
			break;
		case CONTROL_MENU:
		    APP_LOG(APP_LOG_LEVEL_DEBUG, "Setting control menu selected");
		    control_menu_set_selected(last_screen);
			break;
		case MAIN_MENU:
			APP_LOG(APP_LOG_LEVEL_DEBUG, "Setting main menu selected");
			main_menu_set_selected(current_menu);
	}
	current_menu = menu;
}

void load_current_menu(){
    load_menu(current_menu);	
}

void change_screen(int nextScreen){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Current_screen %d", current_screen);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Next_screen %d", nextScreen);
	window_stack_pop(true);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushing screen %d", nextScreen);
	window_stack_push(data_windows[current_menu][nextScreen], true);
	current_screen = nextScreen;
	last_screen = current_screen;
}

static void in_received_handler(DictionaryIterator *iter, void *context) {
  phone_heartbeat = 5;
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Received message, current screen: %d", current_screen);
  Tuple *server_error_tuple = dict_find(iter, SERVER_ERROR_KEY); 
  if (server_error_tuple){
	    if (current_screen != SCREEN_MESSAGE_KEY){
		server_error = atoi(server_error_tuple->value->cstring);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Server error received %d", server_error);
		show_message("No connection to Boat Remote Server");
	  } 
	  return;
  }
	
  else{
	  switch(current_menu){
		  case VIEW_MENU:
		  	  switch(current_screen){
				case SCREEN_MESSAGE_KEY:
		  			window_stack_pop(true);
		   		    change_screen(last_screen);
				case SCREEN_GPS_KEY:
		   			update_gps_fields(iter);
		   			break;
				case SCREEN_SAILING_KEY:
				   update_sailing_fields(iter);
				   break;
				case SCREEN_NAVIGATION_KEY:
				   update_navigation_fields(iter);
				   break;
				case SCREEN_WAYPOINT_KEY:
				   update_waypoint_fields(iter);
				   break;
				case SCREEN_LOG_KEY:
				   update_log_fields(iter);
				   break;
				case SCREEN_ANCHOR_WATCH_KEY:
				   update_anchor_watch_fields(iter);
				   break;
			  }
	  }
  }
}

static void in_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Dropped!");
}

static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Failed to Send!");
  phone_heartbeat--;
  if (phone_heartbeat == 0)
	  show_message("No connection to Pebble app on phone");
}

static void send_message(int key, int value) {
      Tuplet tuplet = TupletInteger(key, value);
      DictionaryIterator *iter;
      app_message_outbox_begin(&iter);
      if (iter == NULL) {
        return;
      }
      dict_write_tuplet(iter, &tuplet);
      dict_write_end(iter);
      app_message_outbox_send();
}

static void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Tick");
	if (current_menu == VIEW_MENU && current_screen >= 0){
    		send_message(CURRENT_SCREEN_KEY, current_screen);
		}
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Tock");
}

int get_next_screen(int currentScreen) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Leaving %d", currentScreen);
	return (currentScreen + 1) % VIEW_WINDOW_COUNT;
}

int get_previous_screen(int currentScreen) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Leaving %d", currentScreen);
	return (currentScreen - 1 + VIEW_WINDOW_COUNT) % VIEW_WINDOW_COUNT;
}

void navigate_up_handler(ClickRecognizerRef recognizer, void *context){
	int previousScreen = get_previous_screen(current_screen);
	change_screen(previousScreen);
}

void navigate_down_handler(ClickRecognizerRef recognizer, void *context){
	int nextScreen = get_next_screen(current_screen);
	change_screen(nextScreen);
}

void select_handler(ClickRecognizerRef recognizer, void *context){
	switch(current_menu){
		case CONTROL_MENU:
			switch(current_screen){
				case SCREEN_LIGHTS_KEY:
				send_message(TOGGLE_LIGHTS_KEY,1);
				break;
			}
		case VIEW_MENU:
			switch(current_screen){
				case SCREEN_ANCHOR_WATCH_KEY:
				send_message(SET_ANCHOR_WATCH_KEY,1);
				break;
			}
	}
}

void long_select_handler(ClickRecognizerRef recognizer, void *context){
	switch(current_menu){
		/*case CONTROL_MENU:
			switch(current_screen){
				case SCREEN_LIGHTS_KEY:
				send_message(TOGGLE_LIGHTS_KEY,1);
				break;
			}*/
		case VIEW_MENU:
			switch(current_screen){
				case SCREEN_ANCHOR_WATCH_KEY:
				send_message(SET_ANCHOR_WATCH_KEY,0);
				break;
			}
	}
}

void load_main_menu(ClickRecognizerRef recognizer, void *context){
	load_menu(MAIN_MENU);
}

void long_select_handler_release(ClickRecognizerRef recognizer, void *context){
}

void view_window_config_provider(void *context) {
   window_single_click_subscribe(BUTTON_ID_DOWN, navigate_down_handler);
   window_single_click_subscribe(BUTTON_ID_UP, navigate_up_handler);
   window_single_click_subscribe(BUTTON_ID_SELECT, select_handler);
   window_single_click_subscribe(BUTTON_ID_BACK, load_current_menu);
   window_long_click_subscribe(BUTTON_ID_SELECT, 1000, long_select_handler, 
							   long_select_handler_release);
 }

void control_window_config_provider(void *context) {
   window_single_click_subscribe(BUTTON_ID_SELECT, select_handler);
   window_single_click_subscribe(BUTTON_ID_BACK, load_current_menu);
   window_long_click_subscribe(BUTTON_ID_SELECT, 1000, long_select_handler, 
							   long_select_handler_release);
 }

void message_back_handler(ClickRecognizerRef recognizer, void *context){
	window_stack_pop(true);
	window_stack_pop(true);
}

void message_window_config_provider(void *context) {
   window_single_click_subscribe(BUTTON_ID_BACK, message_back_handler);
 }

static void init(void) {
	  Window* w;
	  tick_timer_service_subscribe(SECOND_UNIT, handle_tick);
	
      //APP_LOG(APP_LOG_LEVEL_DEBUG, "Creating GPS window");
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = gps_window_load,
        .unload = gps_window_unload
      });
	  window_set_click_config_provider(w, view_window_config_provider);
	  data_windows[VIEW_MENU][SCREEN_GPS_KEY] = w;
	
	  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Creating sailing window");  
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = sailing_window_load,
        .unload = sailing_window_unload
      });
	  window_set_click_config_provider(w, view_window_config_provider);
	  data_windows[VIEW_MENU][SCREEN_SAILING_KEY] = w;
	
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = navigation_window_load,
        .unload = navigation_window_unload
      });
	  window_set_click_config_provider(w, view_window_config_provider);
	  data_windows[VIEW_MENU][SCREEN_NAVIGATION_KEY] = w;
	
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = waypoint_window_load,
        .unload = waypoint_window_unload
      });
	  window_set_click_config_provider(w, view_window_config_provider);
	  data_windows[VIEW_MENU][SCREEN_WAYPOINT_KEY] = w;
	
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = log_window_load,
        .unload = log_window_unload
      });
	  window_set_click_config_provider(w, view_window_config_provider);
	  data_windows[VIEW_MENU][SCREEN_LOG_KEY] = w;
	
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = anchor_watch_window_load,
        .unload = anchor_watch_window_unload
      });
	  window_set_click_config_provider(w, view_window_config_provider);
	  data_windows[VIEW_MENU][SCREEN_ANCHOR_WATCH_KEY] = w;
	
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = lights_window_load,
        .unload = lights_window_unload
      });
	  window_set_click_config_provider(w, control_window_config_provider);
	  data_windows[CONTROL_MENU][SCREEN_LIGHTS_KEY] = w;
	
	
	  message_window = window_create();
      window_set_background_color(message_window, GColorBlack);
      window_set_fullscreen(message_window, true);
      window_set_window_handlers(message_window, (WindowHandlers) {
        .load = message_window_load,
        .unload = message_window_unload
      });
	  window_set_click_config_provider(message_window, message_window_config_provider);
	  	
	  w = window_create();
      // Setup the window handlers
	  window_set_window_handlers(w, (WindowHandlers){
    	.load = view_menu_window_load,
		.unload = view_menu_window_unload
      });
	  view_menu_set_change_screen_function(change_screen);
	  //view_menu_set_back_button_function(load_main_menu);
	  menu_windows[VIEW_MENU] = w;
	 
	  w = window_create();
      // Setup the window handlers
	  window_set_window_handlers(w, (WindowHandlers){
    	.load = control_menu_window_load,
		.unload = control_menu_window_unload
      });
	  control_menu_set_change_screen_function(change_screen);
	  menu_windows[CONTROL_MENU] = w;
	  
	  w = window_create();
      // Setup the window handlers
	  window_set_window_handlers(w, (WindowHandlers){
    	.load = main_menu_window_load,
		.unload = main_menu_window_unload
      });
	  main_menu_set_change_screen_function(load_menu);
	  menu_windows[MAIN_MENU] = w;
	
	  app_message_register_inbox_received(in_received_handler);
      app_message_register_inbox_dropped(in_dropped_handler);
      app_message_register_outbox_failed(out_failed_handler);
	
	  const int inbound_size = 128;
      const int outbound_size = 128;
      app_message_open(inbound_size, outbound_size);

	  const bool animated = true;
	  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushing screen %d", current_screen);
      //window_stack_push(view_windows[current_screen], animated);
	  phone_heartbeat = 5;
	  if (persist_exists(54322)){
		  current_menu = persist_read_int(54322);  
		  if (persist_exists(54321)){ 
			  current_screen = persist_read_int(54321);
			  window_stack_push(data_windows[current_menu][current_screen], animated);
		  }
		  else{
			  current_screen = SCREEN_MENU_KEY;
		      window_stack_push(menu_windows[current_menu], animated); 
		  }
	  }
	  else{
		  current_menu = MAIN_MENU;
		  current_screen = SCREEN_MENU_KEY;
		  window_stack_push(menu_windows[current_menu], animated);
	  }
}

static void deinit(void) {
	  int i, check;
	  tick_timer_service_unsubscribe();
	  window_destroy(message_window);
	  
	  for (i=0; i < VIEW_WINDOW_COUNT; i++) 
		  window_destroy(data_windows[VIEW_MENU][i]); 
	  for (i=0; i < CONTROL_WINDOW_COUNT; i++) 
		  window_destroy(data_windows[CONTROL_MENU][i]); 
	  for (i=0; i < MENU_WINDOW_COUNT; i++) 
	  	  window_destroy(menu_windows[i]); 
	  check = persist_write_int(54321, last_screen);
	  APP_LOG(APP_LOG_LEVEL_DEBUG, "Persisting %d=%d, status %d", 54321,
			  last_screen, check);
      check = persist_write_int(54322, current_menu);
	  APP_LOG(APP_LOG_LEVEL_DEBUG, "Persisting %d=%d, status %d", 54322,
	  		  current_menu, check);
}

int main(void) {
      init();
      app_event_loop();
      deinit();
}

