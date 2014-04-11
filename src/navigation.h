#pragma once

void navigation_window_load(Window *window);

void navigation_window_unload(Window *window);

void set_navigation_dtw(const Tuple* new_tuple);

void set_navigation_btw(const Tuple* new_tuple);

void set_navigation_sog(const Tuple* new_tuple);

void set_navigation_cog(const Tuple* new_tuple);