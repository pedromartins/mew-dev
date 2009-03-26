#ifndef _MOUSE_ENCODER_H
#define _MOUSE_ENCODER_H

struct mouse_data {
  int32_t left_mouse_x_delta;
  int32_t left_mouse_y_delta;
  int32_t right_mouse_x_delta;
  int32_t right_mouse_y_delta;
};

void init_mouse_encoder();
struct mouse_data* get_latest_vector();

#endif
