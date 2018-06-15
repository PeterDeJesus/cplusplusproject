/*
 * Peter De Jesus (cssc1096) & Yonas Lemmi (cssc1097)
 * CS 570 - Operating Systems, Summer 2017
 * Assignment #3 - Interruptible clock and timer
 *
 * This program will create 2 threads: one for a running clock
 * and the other for a timer and call an interrupt when the
 * timer runs out. It will also set an alarm if it is set and
 * the time matches the alarm set.
 */

#include "A3.h"

// create a semaphore
sem_t FLAG;

//define methods that will be threads
void *runclock(void *id);
void *countdown(void *id);

// create thread as global so methods can access it
pthread_t thread1;

/*
 * This method will validate user input and create
 * 2 threads for clock and countdown
 */
int main(int argc, char *argv[]) {

	// timer in user input and no alarm set
	if(argc==2) {
		timer = atoi(argv[1]);
	}
	else if(argc==1) {
	// default timer and no alarm set
		timer = 30;
	} 
	else if(argc==5) {
	// timer and alarm set is given by user
		timer = atoi(argv[1]);
		hrs = atoi(argv[2]);
		mins = atoi(argv[3]);
		secs = atoi(argv[4]);
	}
	else if(argc==4) {
	// no timer given and alarm set is given
		timer = 30;
		hrs = atoi(argv[1]);
		mins = atoi(argv[2]);
		secs = atoi(argv[3]);
	} else {
	// invalid user input, print message and exit
		cout << "Invalid Input." << endl;
		return 1;
	}
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
 	// initialize semaphore       
        sem_init(&FLAG, 0, 1);

        pthread_t thread2;

	// create threads
        pthread_create(&thread1, &attr, runclock, (void *) NULL);
        pthread_create(&thread2, &attr, countdown, (void *) NULL);

	// wait for thread to finish before a different
	// thread can run
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        pthread_cancel(thread2);

        

        sem_destroy(&FLAG);
        cout << "Program Finished." << endl;

        return 0;
}

/*
 * This function will display a running clock and
 * will appear every second until it is interrupted
 * It will also check to see if alarm is set and if it is
 * then it will set the alarm off when the time match
 */
void *runclock(void *id) {
        
	// run the clock
        while(timer>=0) {
                sem_wait(&FLAG);
                time_t rawtime;
                tm * timeinfo;
                time (&rawtime);
                timeinfo = localtime (&rawtime);
                hours = timeinfo->tm_hour;
                minutes = timeinfo->tm_min;
                seconds = timeinfo->tm_sec;
		cout << "Clock: ";
                cout << hours << " : " << minutes << " : " << seconds << endl;

                if(hours==hrs && minutes==mins && seconds==secs) {
                        cout << "ALARM!-----ALARM!-----ALARM!-----ALARM!" << endl;
                }

                sem_post(&FLAG);
                sleep(1);
                
        }
       
        pthread_exit(0);
}

/*
 * This function will terminate the clock
 * thread when called
 */
void handle_signal(int sign) {
        //cout << "Interrupting clock" << endl;
        pthread_cancel(thread1);
        sem_destroy(&FLAG);

}

/*
 * This function call handle signal to
 * interrupt the clock thread
 */
void endProg() {
        signal(SIGTERM, handle_signal);
        raise(SIGTERM);
}

/*
 * This function counts down the timer
 * and when timer reaches 0, it calls to
 * interrupt the running clock thread
 */
void *countdown(void *id) {
       
        sem_wait(&FLAG);
        while(timer>=0) {
                cout << "Timer: " << timer << endl;
                timer--;
                sem_post(&FLAG);
                sleep(1);
        }

       
        endProg();
        pthread_exit(0);
        
}
