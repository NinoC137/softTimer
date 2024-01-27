//
// Created by Yoshi on 2024/1/27.
//

#ifndef _SOFTTIMER_H
#define _SOFTTIMER_H

#include "List_Entry.h"

struct softTimer{
    list_t node;

    char* id;
    int count;
    int updateCount;

    void(*callBackFunction)();
};

typedef struct softTimer softTimer_t;

extern softTimer_t timer_1;

extern softTimer_t timer_2;

extern softTimer_t timer_3;

void softTimer_setup(softTimer_t *target, int updateCount);

void softTimer_attach(softTimer_t *target, void(*func)());

void softTimer_delete(softTimer_t *target);

void softTimer_tick();

#endif //SOFTTIMER_SOFTTIMER_H
