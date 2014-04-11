#pragma once

void waypoint_window_load(Window *window);

void waypoint_window_unload(Window *window);

void set_waypoint_waypoint(const Tuple* new_tuple);

void set_waypoint_wpt_lat(const Tuple* new_tuple);

void set_waypoint_wpt_lon(const Tuple* new_tuple);

void set_waypoint_dtw(const Tuple* new_tuple);

void set_waypoint_btw(const Tuple* new_tuple);