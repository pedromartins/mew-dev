#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mouse_encoder.h"

struct mouse_data* vector;

int main(){
  init_mouse_encoder();
  while(1){
    //printf("running\n");
    usleep(500000);
    vector = get_latest_vector();
    printf("left mouse x: %d y: %d *** right mouse x: %d y: %d\n", vector->left_mouse_x_delta, vector->left_mouse_y_delta,
	   vector->right_mouse_x_delta, vector->right_mouse_y_delta);
    free(vector);
  }
}
