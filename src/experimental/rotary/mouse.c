#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

/*
 * Buildings of a rotary encoder...
 * todo: -make the timing more accurate, rather than relying on usleep
 *	 -add backwards!
 *
 * notes: normal users don't have read permissions for /dev/input/mouse*
 *           by default, at least on ubuntu
 *
 * ian beer
 */

unsigned char e[3];
int mouse_fd;
int forward_steps_total;
int forward_steps_delta;
pthread_mutex_t delta_mutex = PTHREAD_MUTEX_INITIALIZER;

void counting_thread_function(){

	//the third byte of this fd is the movement in the y axis
	if((mouse_fd = open("/dev/input/mouse2", O_RDONLY)) < 0){
		perror("opening file");
		return;
	}

	while(1){
		read(mouse_fd, e, 3);
		if(e[2] < 128){ //we only want forwards
			pthread_mutex_lock(&delta_mutex);
			forward_steps_delta += e[2];
			pthread_mutex_unlock(&delta_mutex);
		}
	}
}

void calculating_thread_function(){
	while(1){
		usleep(100000);
		forward_steps_total += forward_steps_delta;
		printf("total distance: %d units, speed(units/s): %d\n",
			forward_steps_total,
			forward_steps_delta * 10);
		pthread_mutex_lock(&delta_mutex);
		forward_steps_delta = 0;
		pthread_mutex_unlock(&delta_mutex);
	}
}

int main(){
	pthread_t counting_thread, calculating_thread;

	if((mouse_fd = open("/dev/input/mouse1", O_RDONLY)) < 0){
		perror("opening file");
		exit(1);
	}

	pthread_create(&counting_thread, NULL, counting_thread_function, NULL);
	pthread_create(&calculating_thread, NULL, calculating_thread_function, NULL);

	pthread_join(counting_thread, NULL);
	pthread_join(calculating_thread, NULL);
}
