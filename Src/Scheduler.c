/*
 * Scheduler.c
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#include "Scheduler.h"

static uint32_t scheduledEvents;

uint32_t getScheduledEvents() {
    return scheduledEvents;
}

void addSchedulerEvent(uint32_t event) {
    scheduledEvents |= 1 << event;
}

void removeSchedulerEvent(uint32_t event) {
    scheduledEvents &= ~(1 << event);
}

