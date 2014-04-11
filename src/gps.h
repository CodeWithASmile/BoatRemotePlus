#pragma once

void gps_window_load(Window *window);

void gps_window_unload(Window *window);

void set_gps_lat(const Tuple* new_tuple);

void set_gps_lon(const Tuple* new_tuple);

void set_gps_sog(const Tuple* new_tuple);

void set_gps_cog(const Tuple* new_tuple);