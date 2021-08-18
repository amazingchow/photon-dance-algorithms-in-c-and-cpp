#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "state_machine.h"

// Motor object structure
typedef struct motor {
    size_t current_speed;
} motor_t;

// Event data structure
typedef struct motor_data {
    size_t speed;
} motor_data_t;

// State machine event functions
EVENT_DECLARE(MTR_SetSpeed, motor_data_t)
EVENT_DECLARE(MTR_Halt, no_event_data)

// Public accessor
GET_DECLARE(MTR_GetSpeed, size_t);

#endif /* __MOTOR_H__ */
