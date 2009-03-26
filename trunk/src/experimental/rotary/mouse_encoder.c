#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include "mouse_encoder.h"

/*
 * Buildings of a rotary encoder...
 * 
 * ian beer
 */

pthread_t left_mouse_thread, right_mouse_thread;
struct mouse_data* working_data;

pthread_mutex_t working_data_mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned char left_data[3];
unsigned char right_data[3];
int left_mouse_fd;
int right_mouse_fd;

void left_mouse_counter(void * blah){
  while(1){
    read(left_mouse_fd, left_data, 3);

    pthread_mutex_lock(&working_data_mutex);

    if(left_data[2] < 128){ //y axis forwards
      working_data->left_mouse_y_delta += left_data[2];
    }
    if(left_data[2] > 128){ 
      working_data->left_mouse_y_delta -= (255 - left_data[2]);
    }
    if(left_data[1] < 128){
      working_data->left_mouse_x_delta += left_data[1];
    }
    if(left_data[1] > 128){
      working_data->left_mouse_x_delta -= (255 - left_data[1]);
    }

     pthread_mutex_unlock(&working_data_mutex);
  }
}

void right_mouse_counter(void * blah){
  while(1){
    
    read(right_mouse_fd, right_data, 3);
    pthread_mutex_lock(&working_data_mutex);
    
    if(right_data[2] < 128){ //y axis forwards
      working_data->right_mouse_y_delta += right_data[2];
    }
    if(right_data[2] > 128){ 
      working_data->right_mouse_y_delta -= (255 - right_data[2]);
    }
    if(right_data[1] < 128){
      working_data->right_mouse_x_delta += right_data[1];
    }
    if(right_data[1] > 128){
      working_data->right_mouse_x_delta -= (255 - right_data[1]);
    }
    
    pthread_mutex_unlock(&working_data_mutex);
  }
}

struct mouse_data* get_latest_vector(){
  struct mouse_data* r = malloc(sizeof( struct mouse_data)); 
  pthread_mutex_lock(&working_data_mutex);
  memcpy(r, working_data, sizeof( struct mouse_data));
  memset(working_data, 0, sizeof( struct mouse_data));
  pthread_mutex_unlock(&working_data_mutex);
  return r;
}

/*
void calculating_thread_function(){
  while(1){
    usleep(100000);
    pthread_mutex_lock(&working_data_mutex);
    forward_steps_total += forward_steps_delta;
    printf("total distance: %d units, speed(units/s): %d\n",
	   forward_steps_total,
	   forward_steps_delta * 10);
    pthread_mutex_lock(&delta_mutex);
    forward_steps_delta = 0;
    pthread_mutex_unlock(&delta_mutex);
  }
}
*/

void init_mouse_encoder(){

  working_data = malloc(sizeof( struct mouse_data ));
  
  //the third byte of this fd is the movement in the y axis
  if((left_mouse_fd = open("/dev/input/mouse2", O_RDONLY)) < 0){
    perror("opening left mouse file");
    return;
  }

  if((right_mouse_fd = open("/dev/input/mouse1", O_RDONLY)) < 0){
    perror("opening right mouse file");
    return;
  }
  
  //start a thread, but don't join it
  //we assume this is being called in some kind of while loop
  pthread_create(&left_mouse_thread, NULL, left_mouse_counter, (void *) NULL);
  pthread_create(&right_mouse_thread, NULL, right_mouse_counter,(void *) NULL);
}
