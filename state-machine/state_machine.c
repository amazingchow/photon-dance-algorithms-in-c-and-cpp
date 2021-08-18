#include "state_machine.h"

// Generates an external event.
// Called once per external event to start the state machine executing.
void
_SM_ExternalEvent(
  sm_state_machine_t *self, const sm_state_machine_const_t *self_const, uint8_t new_state, void *event_data) {
    // If we are supposed to ignore this event
    if (new_state == EVENT_IGNORED) {
        // Just delete the event data, if any
        if (event_data) {
            FREE(event_data);
        }
    } else {
        // TODO: acquire software lock here for thread-safe if necessary

        // Generate the event
        _SM_InternalEvent(self, new_state, event_data);
        // Execute state machine based on type of state map defined
        if (self_const->state_map != NULL) {
            _SM_StateEngine(self, self_const);
        } else {
            _SM_StateEngineEx(self, self_const);
        }

        // TODO: release software lock here
    }
}

// Generates an internal event.
// Called from within a state function to transition to a new state.
void
_SM_InternalEvent(sm_state_machine_t *self, uint8_t new_state, void *event_data) {
    ASSERT_TRUE(self);

    self->new_state = new_state;
    self->event_data = event_data;
    self->event_generated = true;
}

// The state engine executes the state machine states.
void
_SM_StateEngine(sm_state_machine_t *self, const sm_state_machine_const_t *self_const) {
    ASSERT_TRUE(self);
    ASSERT_TRUE(self_const);

    void *tmp_data = NULL;

    // While events are being generated, just keep executing states
    while (self->event_generated) {
        // Error check that the new state is valid before proceeding
        ASSERT_TRUE(self->new_state < self_const->max_state);
        // Get the pointers from the state map
        sm_state_func state_func = self_const->state_map[self->new_state].state_func;
        // Copy of event data pointer
        tmp_data = self->event_data;
        // Event data used up, reset the pointer
        self->event_data = NULL;
        // Event used up, reset the flag
        self->event_generated = false;
        // Switch to the new current state
        self->current_state = self->new_state;
        // Execute the state action passing in event data
        ASSERT_TRUE(state_func);
        state_func(self, tmp_data);
        // If event data was used, then delete it
        if (tmp_data) {
            FREE(tmp_data);
            tmp_data = NULL;
        }
    }
}

// The state engine executes the extended state machine states
void
_SM_StateEngineEx(sm_state_machine_t *self, const sm_state_machine_const_t *self_const) {
    ASSERT_TRUE(self);
    ASSERT_TRUE(self_const);

    bool guard_result = true;
    void *tmp_data = NULL;

    // While events are being generated, just keep executing states
    while (self->event_generated) {
        // Error check that the new state is valid before proceeding
        ASSERT_TRUE(self->new_state < self_const->max_state);
        // Get the pointers from the extended state map
        sm_state_func state_func = self_const->state_map_ex[self->new_state].state_func;
        sm_guard_func guard_func = self_const->state_map_ex[self->new_state].guard_func;
        sm_entry_func entry_func = self_const->state_map_ex[self->new_state].entry_func;
        sm_exit_func exit_func = self_const->state_map_ex[self->current_state].exit_func;
        // Copy of event data pointer
        tmp_data = self->event_data;
        // Event data used up, reset the pointer
        self->event_data = NULL;
        // Event used up, reset the flag
        self->event_generated = false;
        // Execute the guard condition
        if (state_func != NULL) {
            guard_result = guard_func(self, tmp_data);
        }
        // If the guard condition succeeds
        if (guard_result) {
            // Transitioning to a new state?
            if (self->new_state != self->current_state) {
                // Execute the state exit action on current state before switching to new state
                if (exit_func != NULL) {
                    exit_func(self);
                }
                // Execute the state entry action on the new state
                if (entry_func != NULL) {
                    entry_func(self, tmp_data);
                }
                // Ensure exit/entry actions didn't call SM_InternalEvent by accident
                ASSERT_TRUE(!self->event_generated);
            }
            // Switch to the new current state
            self->current_state = self->new_state;
            // Execute the state action passing in event data
            ASSERT_TRUE(state_func);
            state_func(self, tmp_data);
        }
        // If event data was used, then delete it
        if (tmp_data) {
            FREE(tmp_data);
            tmp_data = NULL;
        }
    }
}
