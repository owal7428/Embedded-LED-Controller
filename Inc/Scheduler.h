/*
 * Scheduler.h
 *
 *  Created on: Sep 7, 2023
 *      Author: owenallison
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

#define LED_TOGGLE_EVENT 0
#define DELAY_EVENT 1
#define BUTTON_POLL 2

#define accessToggleEvent (1 << LED_TOGGLE_EVENT)
#define accessDelayEvent (1 << DELAY_EVENT)
#define AccessPollEvent (1 << BUTTON_POLL)

uint32_t getScheduledEvents();

void addSchedulerEvent(uint32_t event);
void removeSchedulerEvent(uint32_t event);

#endif /* SCHEDULER_H_ */
