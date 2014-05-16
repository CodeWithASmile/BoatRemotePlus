#include <pebble.h>
#include <inttypes.h>
#include "message.h"
#include "gps.h"
#include "sailing.h"
#include "navigation.h"
#include "manual.h"
#include "waypoint.h"
#include "log.h"
#include "lights.h"
#include "menu.h"
	
#define VIEW_WINDOW_COUNT 7

Window* message_window;
Window* menu_window;
Window* view_windows [VIEW_WINDOW_COUNT];

int current_screen;
int last_screen;
int current_menu;
int server_error;

enum DataKey {
  BOAT_LAT_KEY = 0x1,
  BOAT_LON_KEY = 0x2,
  BOAT_SOG_KEY = 0x3,
  BOAT_COG_KEY = 0x4,
  BOAT_BOAT_SPEED_KEY = 0x5,
  BOAT_DEPTH_KEY = 0x6,
  BOAT_WIND_SPEED_KEY = 0x7,
  BOAT_WIND_ANGLE_KEY = 0x8,
  BOAT_DTW_KEY = 0x9,
  BOAT_BTW_KEY = 0xA,
  BOAT_XTE_KEY = 0xB,
  BOAT_WAYPOINT_KEY = 0xE,
  BOAT_WPT_LAT_KEY = 0xF,
  BOAT_WPT_LON_KEY = 0x10,
  BOAT_TEMP_KEY = 0x11,
  BOAT_DISTANCE_TOTAL_KEY = 0x12,
  BOAT_DISTANCE_RESET_KEY = 0x13,
};

enum ScreenKey {
  SCREEN_MENU_KEY = -1,
  SCREEN_GPS_KEY = 0,
  SCREEN_SAILING_KEY = 1,
  SCREEN_NAVIGATION_KEY = 2,
  SCREEN_MANUAL_KEY = 3,
  SCREEN_WAYPOINT_KEY = 4,
  SCREEN_LOG_KEY = 5,
  SCREEN_LIGHTS_KEY = 6
};

enum MenuKey {
  MENU_VIEW_KEY = 0x0,
};

int view_windows_enable [VIEW_WINDOW_COUNT] = {1,1,1,1,1,1};

enum OtherKey {
  CURRENT_SCREEN_KEY = 0x0,
  CURRENT_MENU_KEY = 0x16,
  SERVER_ERROR_KEY = 0x14,
  TOGGLE_LIGHTS_KEY = 0x15
};

void show_server_error(){
	set_message("Server Error");
	window_stack_push(message_window, true);	
}

static void in_received_handler(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Received message, current screen: %d", current_screen);
  Tuple *server_error_tuple = dict_find(iter, SERVER_ERROR_KEY); 
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Server error received %s", server_error_tuple->value->cstring);
  if (server_error_tuple){
	server_error = atoi(server_error_tuple->value->cstring);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Server error received %d", server_error);
	show_server_error();
  }  
  
  Tuple *lat_tuple = dict_find(iter, BOAT_LAT_KEY);
  Tuple *lon_tuple = dict_find(iter, BOAT_LON_KEY);
  Tuple *sog_tuple = dict_find(iter, BOAT_SOG_KEY);
  Tuple *cog_tuple = dict_find(iter, BOAT_COG_KEY);
  Tuple *boat_speed_tuple = dict_find(iter, BOAT_BOAT_SPEED_KEY);
  Tuple *depth_tuple = dict_find(iter, BOAT_DEPTH_KEY);
  Tuple *wind_speed_tuple = dict_find(iter, BOAT_WIND_SPEED_KEY);
  Tuple *wind_angle_tuple = dict_find(iter, BOAT_WIND_ANGLE_KEY);
  Tuple *dtw_tuple = dict_find(iter, BOAT_DTW_KEY);
  Tuple *btw_tuple = dict_find(iter, BOAT_BTW_KEY);
  Tuple *xte_tuple = dict_find(iter, BOAT_XTE_KEY);
  Tuple *waypoint_tuple = dict_find(iter, BOAT_WAYPOINT_KEY);
  Tuple *wpt_lat_tuple = dict_find(iter, BOAT_WPT_LAT_KEY);
  Tuple *wpt_lon_tuple = dict_find(iter, BOAT_WPT_LON_KEY);
  Tuple *temp_tuple = dict_find(iter, BOAT_TEMP_KEY);
  Tuple *distance_total_tuple = dict_find(iter, BOAT_DISTANCE_TOTAL_KEY);
  Tuple *distance_reset_tuple = dict_find(iter, BOAT_DISTANCE_RESET_KEY);

  if (current_screen == SCREEN_GPS_KEY){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "GPS Screen");
    if (lat_tuple) {
      set_gps_lat(lat_tuple);
    }
	if (lon_tuple) {
      set_gps_lon(lon_tuple);
    }
	if (sog_tuple) {
      set_gps_sog(sog_tuple);
    }
	if (cog_tuple) {
      set_gps_cog(cog_tuple);
    }
  }
  if (current_screen == SCREEN_SAILING_KEY){
    if (boat_speed_tuple) {
      set_sailing_boat_speed(boat_speed_tuple);
    }
	if (depth_tuple) {
      set_sailing_depth(depth_tuple);
    }
	if (wind_speed_tuple) {
      set_sailing_wind_speed(wind_speed_tuple);
    }
	if (wind_angle_tuple) {
      set_sailing_wind_angle(wind_angle_tuple);
    }
  }
  if (current_screen == SCREEN_NAVIGATION_KEY){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Navigation Screen");
    if (dtw_tuple) {
      set_navigation_dtw(dtw_tuple);
    }
	if (btw_tuple) {
      set_navigation_btw(btw_tuple);
    }
	if (sog_tuple) {
      set_navigation_sog(sog_tuple);
    }
	if (cog_tuple) {
      set_navigation_cog(cog_tuple);
    }
  }
  if (current_screen == SCREEN_MANUAL_KEY){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Manual Screen");
    if (dtw_tuple) {
      set_manual_dtw(dtw_tuple);
    }
	if (btw_tuple) {
      set_manual_btw(btw_tuple);
    }
	if (xte_tuple) {
      set_manual_xte(xte_tuple);
    }
  }
  if (current_screen == SCREEN_WAYPOINT_KEY){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Waypoint Screen");
    if (dtw_tuple) {
      set_waypoint_dtw(dtw_tuple);
    }
	if (btw_tuple) {
      set_waypoint_btw(btw_tuple);
    }
	if (waypoint_tuple) {
      set_waypoint_waypoint(waypoint_tuple);
    }
	if (wpt_lat_tuple) {
      set_waypoint_wpt_lat(wpt_lat_tuple);
    }
	if (wpt_lon_tuple) {
      set_waypoint_wpt_lon(wpt_lon_tuple);
    }
  }
  if (current_screen == SCREEN_LOG_KEY){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Log Screen");
    if (temp_tuple) {
      set_log_temp(temp_tuple);
    }
	if (distance_total_tuple) {
      set_log_distance_total(distance_total_tuple);
    }
	if (distance_reset_tuple) {
      set_log_distance_reset(distance_reset_tuple);
    }
  }
}

static void in_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Dropped!");
}

static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Failed to Send!");
}

static void send_current_screen(void) {
	  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Sending key %d", CURRENT_SCREEN_KEY);
	  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Sending value %d", current_screen);
      Tuplet value = TupletInteger(CURRENT_SCREEN_KEY, current_screen);

      DictionaryIterator *iter;
      app_message_outbox_begin(&iter);

      if (iter == NULL) {
        return;
      }

      dict_write_tuplet(iter, &value);
      dict_write_end(iter);

      app_message_outbox_send();
}

static void toggle_lights(void) {
	  APP_LOG(APP_LOG_LEVEL_DEBUG, "Toggling lights");
	  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Sending value %d", current_screen);
      Tuplet value = TupletInteger(TOGGLE_LIGHTS_KEY, 1);

      DictionaryIterator *iter;
      app_message_outbox_begin(&iter);

      if (iter == NULL) {
        return;
      }

      dict_write_tuplet(iter, &value);
      dict_write_end(iter);

      app_message_outbox_send();
}

static void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Tick");
	if (current_screen != SCREEN_LIGHTS_KEY) {
		if (current_screen != SCREEN_MENU_KEY){
    		send_current_screen();
		}
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

void change_screen(int nextScreen){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Current_screen %d", current_screen);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Next_screen %d", nextScreen);
	if(current_screen == SCREEN_MENU_KEY){
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "Popping menu_window");
		window_stack_pop(menu_window);
	}
	else{
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "Popping screen %d", current_screen);
		window_stack_pop(view_windows[current_screen]);
	}
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushing screen %d", nextScreen);
	window_stack_push(view_windows[nextScreen], true);
	current_screen = nextScreen;
	last_screen = current_screen;
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
	if (current_screen == SCREEN_LIGHTS_KEY){
		toggle_lights();
	}
}

void load_menu(){
	window_stack_pop(view_windows[current_screen]);
	window_stack_push(menu_window, true);
	current_screen=SCREEN_MENU_KEY;
	menu_set_selected(last_screen);
}


void config_provider(void *context) {
   window_single_click_subscribe(BUTTON_ID_DOWN, navigate_down_handler);
   window_single_click_subscribe(BUTTON_ID_UP, navigate_up_handler);
   window_single_click_subscribe(BUTTON_ID_SELECT, select_handler);
   window_single_click_subscribe(BUTTON_ID_BACK, load_menu);
 }

static void init(void) {
	  Window* w;
	  tick_timer_service_subscribe(SECOND_UNIT, handle_tick);
	
	  message_window = window_create();
      window_set_background_color(message_window, GColorBlack);
      window_set_fullscreen(message_window, true);
      window_set_window_handlers(message_window, (WindowHandlers) {
        .load = message_window_load,
        .unload = message_window_unload
      });
	
      //APP_LOG(APP_LOG_LEVEL_DEBUG, "Creating GPS window");
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = gps_window_load,
        .unload = gps_window_unload
      });
	  window_set_click_config_provider(w, config_provider);
	  view_windows[SCREEN_GPS_KEY] = w;
	
	  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Creating sailing window");  
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = sailing_window_load,
        .unload = sailing_window_unload
      });
	  window_set_click_config_provider(w, config_provider);
	  view_windows[SCREEN_SAILING_KEY] = w;
	
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = navigation_window_load,
        .unload = navigation_window_unload
      });
	  window_set_click_config_provider(w, config_provider);
	  view_windows[SCREEN_NAVIGATION_KEY] = w;
	
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = manual_window_load,
        .unload = manual_window_unload
      });
	  window_set_click_config_provider(w, config_provider);
	  view_windows[SCREEN_MANUAL_KEY] = w;
	
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = waypoint_window_load,
        .unload = waypoint_window_unload
      });
	  window_set_click_config_provider(w, config_provider);
	  view_windows[SCREEN_WAYPOINT_KEY] = w;
	
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = log_window_load,
        .unload = log_window_unload
      });
	  window_set_click_config_provider(w, config_provider);
	  view_windows[SCREEN_LOG_KEY] = w;
	
	  w = window_create();
      window_set_background_color(w, GColorBlack);
      window_set_fullscreen(w, true);
      window_set_window_handlers(w, (WindowHandlers) {
        .load = lights_window_load,
        .unload = lights_window_unload
      });
	  window_set_click_config_provider(w, config_provider);
	  view_windows[SCREEN_LIGHTS_KEY] = w;
	
	  menu_window = window_create();
      // Setup the window handlers
	  window_set_window_handlers(menu_window, (WindowHandlers){
    	.load = menu_window_load,
		.unload = menu_window_unload
      });
	  menu_set_change_screen_function(change_screen);

	  app_message_register_inbox_received(in_received_handler);
      app_message_register_inbox_dropped(in_dropped_handler);
      app_message_register_outbox_failed(out_failed_handler);
	
	  const int inbound_size = 128;
      const int outbound_size = 128;
      app_message_open(inbound_size, outbound_size);

	  const bool animated = true;
	  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushing screen %d", current_screen);
      //window_stack_push(view_windows[current_screen], animated);
	  window_stack_push(menu_window, animated); 
	  current_screen = SCREEN_MENU_KEY;
	  last_screen = persist_exists(54321) ? persist_read_int(54321) : SCREEN_GPS_KEY;
	  current_menu = persist_exists(54322) ? persist_read_int(54322) : MENU_VIEW_KEY;	
	  APP_LOG(APP_LOG_LEVEL_DEBUG, "Persistent Read %d=%d", 54321,
			  last_screen);
	  menu_set_selected(last_screen);
}

static void deinit(void) {
	  int i, check;
	  tick_timer_service_unsubscribe();
	  window_destroy(message_window);
	  window_destroy(menu_window);
	  
	  for (i=0; i < VIEW_WINDOW_COUNT; i++) 
		  window_destroy(view_windows[i]); 
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

