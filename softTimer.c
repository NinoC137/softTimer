//
// Created by Yoshi on 2024/1/27.
//

#include "softTimer.h"

list_t softTimer_Head = {
        .prev = &softTimer_Head,
        .next = &softTimer_Head
};

softTimer_t timer_1;

softTimer_t timer_2;

softTimer_t timer_3;

void softTimer_setup(softTimer_t *target, int updateCount){
    target->updateCount = updateCount;
    list_add(&target->node, &softTimer_Head);
}

void softTimer_attach(softTimer_t *target, void(*func)()){
    target->callBackFunction = func;
}

void softTimer_delete(softTimer_t *target){
    list_del(&target->node);
}

void softTimer_tick(){
    softTimer_t *softTimer_ptr;

    list_for_each_entry(softTimer_ptr, &softTimer_Head, node){
        softTimer_ptr->count++;
        if(softTimer_ptr->count == softTimer_ptr->updateCount){
            softTimer_ptr->count = 0;
            softTimer_ptr->callBackFunction();
        }
    }
}