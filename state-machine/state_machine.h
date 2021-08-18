//
// The StateMachine module is a C language implementation of a finite state
// machine (FSM).
//
// All event data must be created dynamically using ALLOC. Use a fixed
// block allocator or the heap as desired.
//
// The standard version (non-EX) supports state and event functions. The
// extended version (EX) supports the additional guard, entry and exit state
// machine features.
//
// Macros are used to assist in creating the state machine machinery.
//

#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include "fault.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#define ALLOC(size) malloc(size)
#define FREE(ptr) free(ptr)

enum { EVENT_IGNORED = 0xFE, CANNOT_HAPPEN = 0xFF };

typedef void no_event_data;

// state machine instance data
typedef struct sm_state_machine {
    const char *name;
    void *instance;
    uint8_t current_state;
    uint8_t new_state;
    void *event_data;
    bool event_generated;
} sm_state_machine_t;

// generic state function signatures
typedef void (*sm_state_func)(sm_state_machine_t *self, void *event_data);
typedef bool (*sm_guard_func)(sm_state_machine_t *self, void *event_data);
typedef void (*sm_entry_func)(sm_state_machine_t *self, void *event_data);
typedef void (*sm_exit_func)(sm_state_machine_t *self);

typedef struct sm_state {
    sm_state_func state_func;
} sm_state_t;

typedef struct sm_state_struct_ex {
    sm_state_func state_func;
    sm_guard_func guard_func;
    sm_entry_func entry_func;
    sm_exit_func exit_func;
} sm_state_struct_ex_t;

// state machine constant data
typedef struct sm_state_machine_const {
    const char *name;
    const uint8_t max_state;
    const sm_state_t *state_map;
    const sm_state_struct_ex_t *state_map_ex;
} sm_state_machine_const_t;

// Public functions
#define SM_Event(_sm_name_, _event_func_, _event_data_) _event_func_(&_sm_name_##Obj, _event_data_)
#define SM_Get(_sm_name_, _get_func_) _get_func_(&_sm_name_##Obj)

// Protected functions
#define SM_InternalEvent(_new_state_, _event_data_) _SM_InternalEvent(self, _new_state_, _event_data_)
#define SM_GetInstance(_instance_) (_instance_ *)(self->instance);

// Private functions
void _SM_ExternalEvent(
  sm_state_machine_t *self, const sm_state_machine_const_t *self_const, uint8_t new_state, void *event_data);
void _SM_InternalEvent(sm_state_machine_t *self, uint8_t new_state, void *event_data);
void _SM_StateEngine(sm_state_machine_t *self, const sm_state_machine_const_t *self_const);
void _SM_StateEngineEx(sm_state_machine_t *self, const sm_state_machine_const_t *self_const);

#define SM_DECLARE(_sm_name_) extern sm_state_machine_t _sm_name_##Obj;
#define SM_DEFINE(_sm_name_, _instance_) sm_state_machine_t _sm_name_##Obj = {#_sm_name_, _instance_, 0, 0, 0, 0};
#define EVENT_DECLARE(_event_func_, _event_data_) void _event_func_(sm_state_machine_t *self, _event_data_ *event_data);
#define EVENT_DEFINE(_event_func_, _event_data_) void _event_func_(sm_state_machine_t *self, _event_data_ *event_data)
#define GET_DECLARE(_get_func_, _get_data_) _get_data_ _get_func_(sm_state_machine_t *self);
#define GET_DEFINE(_get_func_, _get_data_) _get_data_ _get_func_(sm_state_machine_t *self)
#define STATE_DECLARE(_state_, _event_data_)                                                                           \
    static void ST_##_state_(sm_state_machine_t *self, _event_data_ *event_data);
#define STATE_DEFINE(_state_, _event_data_) static void ST_##_state_(sm_state_machine_t *self, _event_data_ *event_data)
#define GUARD_DECLARE(_guard_func_, _event_data_)                                                                      \
    static BOOL GD_##_guard_func_(sm_state_machine_t *self, _event_data_ *event_data);
#define GUARD_DEFINE(_guard_func_, _event_data_)                                                                       \
    static BOOL GD_##_guard_func_(sm_state_machine_t *self, _event_data_ *event_data)
#define ENTRY_DECLARE(_entry_func_, _event_data_)                                                                      \
    static void EN_##_entry_func_(sm_state_machine_t *self, _event_data_ *event_data);
#define ENTRY_DEFINE(_entry_func_, _event_data_)                                                                       \
    static void EN_##_entry_func_(sm_state_machine_t *self, _event_data_ *event_data)
#define EXIT_DECLARE(_exit_func_) static void EX_##_exit_func_(sm_state_machine_t *self);
#define EXIT_DEFINE(_exit_func_) static void EX_##_exit_func_(sm_state_machine_t *self)
#define BEGIN_STATE_MAP(_sm_name_) static const sm_state_t _sm_name_##StateMap[] = {
#define STATE_MAP_ENTRY(_state_func_) {(sm_state_func)_state_func_},
#define END_STATE_MAP(_sm_name_)                                                                                       \
    }                                                                                                                  \
    ;                                                                                                                  \
    static const sm_state_machine_const_t _sm_name_##Const = {                                                         \
      #_sm_name_, (sizeof(_sm_name_##StateMap) / sizeof(_sm_name_##StateMap[0])), _sm_name_##StateMap, NULL};
#define BEGIN_STATE_MAP_EX(_sm_name_) static const sm_state_struct_ex _sm_name_##StateMap[] = {
#define STATE_MAP_ENTRY_EX(_state_func_) {(sm_state_func)_state_func_, NULL, NULL, NULL},
#define STATE_MAP_ENTRY_ALL_EX(_state_func_, _guard_func_, _entry_func_, _exit_func_)                                  \
    {(sm_state_func)_state_func_, (sm_guard_func)_guard_func_, (sm_entry_func)_entry_func_, (sm_exit_func)_exit_func_},
#define END_STATE_MAP_EX(_sm_name_)                                                                                    \
    }                                                                                                                  \
    ;                                                                                                                  \
    static const sm_state_machine_const_t _sm_name_##Const = {                                                         \
      #_sm_name_, (sizeof(_sm_name_##StateMap) / sizeof(_sm_name_##StateMap[0])), NULL, _sm_name_##StateMap};
#define BEGIN_TRANSITION_MAP static const uint8_t TRANSITIONS[] = {
#define TRANSITION_MAP_ENTRY(_entry_) _entry_,
#define END_TRANSITION_MAP(_sm_name_, _event_data_)                                                                    \
    }                                                                                                                  \
    ;                                                                                                                  \
    _SM_ExternalEvent(self, &_sm_name_##Const, TRANSITIONS[self->current_state], _event_data_);                        \
    C_ASSERT((sizeof(TRANSITIONS) / sizeof(uint8_t)) == (sizeof(_sm_name_##StateMap) / sizeof(_sm_name_##StateMap[0])));

#ifdef __cplusplus
}
#endif

#endif /* __STATE_MACHINE_H__ */
