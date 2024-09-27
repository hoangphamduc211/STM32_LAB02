/*
 * time_set.h
 *
 *  Created on: Sep 14, 2024
 *      Author: ADMIN
 */

#ifndef INC_TIME_SET_H_
#define INC_TIME_SET_H_

extern int timer1_flag;
extern int timer2_flag;
void setTimer1(int duration);
void setTimer2(int duration);
void timerRun();

#endif /* INC_TIME_SET_H_ */
