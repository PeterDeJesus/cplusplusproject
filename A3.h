/*
 * Peter De Jesus (cssc1096) & Yonas Lemmi (cssc1097)
 * CS 570 - Operating Systems, Summer 2017
 * Assignment #3 - Interruptible clock and timer
 *
 * This is the header file that the A3.cpp will use
 */

#ifndef A3_H
#define A3_H

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

// default value for timer
int timer = 30;

/*
 * value holder for alarm set
 * default set to -1 to represent no alarm is set yet
 */
int hrs = -1;
int mins = -1;
int secs = -1;

// real time value holder
int hours = 0;
int minutes = 0;
int seconds = 0;


#endif
