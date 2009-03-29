#include "mew_i2c.h"
#include "drive_motor.h"

void set_drive_motor_power(int left_power_level, int right_power_level){
  write_byte_to_register(WHEEL_MOTOR_CONTROLLER, WHEEL_MOTOR_CONTROLLER_LEFT_SPEED, left_power_level);
  write_byte_to_register(WHEEL_MOTOR_CONTROLLER, WHEEL_MOTOR_CONTROLLER_RIGHT_SPEED, right_power_level);
}
void right_motor_power(int power_level){
  write_byte_to_register(WHEEL_MOTOR_CONTROLLER, WHEEL_MOTOR_CONTROLLER_RIGHT_SPEED, power_level);
}

void init_drive_motor(){
  init_comms(MOTOR_DEVICE_NODE);
}
void destroy_drive_motor(){
  end_comms();
}

