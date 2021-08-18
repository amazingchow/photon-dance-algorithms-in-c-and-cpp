#include "motor.h"

// State enumeration order must match the order of state
// method entries in the state map
enum States { ST_IDLE, ST_STOP, ST_START, ST_CHANGE_SPEED, ST_MAX_STATE };

// State machine state functions
STATE_DECLARE(Idle, no_event_data)
STATE_DECLARE(Stop, no_event_data)
STATE_DECLARE(Start, motor_data_t)
STATE_DECLARE(ChangeSpeed, motor_data_t)

// State map to define state function order
// clang-format off
BEGIN_STATE_MAP(motor_t)
    STATE_MAP_ENTRY(ST_Idle)
    STATE_MAP_ENTRY(ST_Stop)
    STATE_MAP_ENTRY(ST_Start)
    STATE_MAP_ENTRY(ST_ChangeSpeed)
END_STATE_MAP(motor_t)
// clang-format on

// Set motor speed external event
// clang-format off
EVENT_DEFINE(MTR_SetSpeed, motor_data_t)
{
    BEGIN_TRANSITION_MAP
        TRANSITION_MAP_ENTRY(ST_START)
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)
        TRANSITION_MAP_ENTRY(ST_CHANGE_SPEED)
        TRANSITION_MAP_ENTRY(ST_CHANGE_SPEED)
    END_TRANSITION_MAP(motor_t, event_data)
}  // clang-format on

// Halt motor external event
// clang-format off
EVENT_DEFINE(MTR_Halt, no_event_data)
{
    BEGIN_TRANSITION_MAP
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)
        TRANSITION_MAP_ENTRY(ST_STOP)
        TRANSITION_MAP_ENTRY(ST_STOP)
    END_TRANSITION_MAP(motor_t, event_data)
}
// clang-format on

// State machine sits here when motor is not running
STATE_DEFINE(Idle, no_event_data) {
    printf("%s ST_Idle\n", self->name);
}

// Stop the motor
STATE_DEFINE(Stop, no_event_data) {
    // Get pointer to the instance data and update current_speed
    motor_t *pInstance = SM_GetInstance(motor_t);
    pInstance->current_speed = 0;
    // Perform the stop motor processing here
    printf("%s ST_Stop: %ld\n", self->name, pInstance->current_speed);
    // Transition to ST_Idle via an internal event
    SM_InternalEvent(ST_IDLE, NULL);
}

// Start the motor going
STATE_DEFINE(Start, motor_data_t) {
    ASSERT_TRUE(event_data);
    // Get pointer to the instance data and update current_speed
    motor_t *inst = SM_GetInstance(motor_t);
    inst->current_speed = event_data->speed;
    // Set initial motor speed processing here
    printf("%s ST_Start: %ld\n", self->name, inst->current_speed);
}

// Changes the motor speed once the motor is moving
STATE_DEFINE(ChangeSpeed, motor_data_t) {
    ASSERT_TRUE(event_data);
    // Get pointer to the instance data and update current_speed
    motor_t *inst = SM_GetInstance(motor_t);
    inst->current_speed = event_data->speed;
    // Perform the change motor speed here
    printf("%s ST_ChangeSpeed: %ld\n", self->name, inst->current_speed);
}

// Get current speed
GET_DEFINE(MTR_GetSpeed, size_t) {
    motor_t *inst = SM_GetInstance(motor_t);
    return inst->current_speed;
}
