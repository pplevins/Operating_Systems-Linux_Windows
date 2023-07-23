//Pinchas Plevinski 322211558

// dpp.c , The name is: dinning philosophers problem
// Compile: gcc dpp.c -o dpp -pthread

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define NUMBER_OF_PHILOSOPHERS 5

void *philosopher(void *);
void think(int);
void pickUp(int);
void eat(int);
void putDown(int);

pthread_mutex_t chopsticks[NUMBER_OF_PHILOSOPHERS];
pthread_t philosophers[NUMBER_OF_PHILOSOPHERS];
pthread_attr_t attributes[NUMBER_OF_PHILOSOPHERS];

int main() {
	long i;
	srand(time(NULL));
	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
		pthread_mutex_init(&chopsticks[i], NULL);
	}

	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
		pthread_attr_init(&attributes[i]);
	}
	
	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
		pthread_create(&philosophers[i], &attributes[i], philosopher, (void *)i);
	}

	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
		pthread_join(philosophers[i], NULL);
	}
	return 0;
}

void *philosopher(void * philosopherNumber) {
	while (1) {
		think((long)philosopherNumber);
		pickUp((long)philosopherNumber);
		eat((long)philosopherNumber);
		putDown((long)philosopherNumber);
	}
}

void think(int philosopherNumber) {
	int sleepTime = rand() % 3 + 1;
	printf("Philosopher %d will think for %d seconds\n", philosopherNumber, sleepTime);
	sleep(sleepTime);
}

void pickUp(int philosopherNumber) {
	int right = (philosopherNumber + 1) % NUMBER_OF_PHILOSOPHERS;
	int left = (philosopherNumber + NUMBER_OF_PHILOSOPHERS) % NUMBER_OF_PHILOSOPHERS;

	if (philosopherNumber == 0) //the first philosopher is picking the right stick first, and then the left
	{
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, right);
		pthread_mutex_lock(&chopsticks[right]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, right);
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, left);
		sleep(2); //can comment in solution for speed
		pthread_mutex_lock(&chopsticks[left]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, left);
	}
	else {
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, left);
		pthread_mutex_lock(&chopsticks[left]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, left);
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, right);
		sleep(2); //can comment in solution for speed
		pthread_mutex_lock(&chopsticks[right]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, right);
	}
}

void eat(int philosopherNumber) {
	int eatTime = rand() % 3 + 1;
	printf("Philosopher %d will eat for %d seconds\n", philosopherNumber, eatTime);
	sleep(eatTime);
}

void putDown(int philosopherNumber) {
	printf("Philosopher %d will put down his chopsticks\n", philosopherNumber);
	pthread_mutex_unlock(&chopsticks[(philosopherNumber + 1) % NUMBER_OF_PHILOSOPHERS]);
	pthread_mutex_unlock(&chopsticks[(philosopherNumber + NUMBER_OF_PHILOSOPHERS) % NUMBER_OF_PHILOSOPHERS]);
}

//After correcting the code and running the program, it can be seen that all the philosophers were able
//to eat and put down their sticks without interruption even several times, so the deadlock is resolved.

/*part of Run sample:
Philosopher 2 will think for 1 seconds
Philosopher 3 will think for 1 seconds
Philosopher 0 will think for 1 seconds
Philosopher 1 will think for 1 seconds
Philosopher 4 will think for 3 seconds
Philosopher 3 is waiting to pick up chopstick 3
Philosopher 3 picked up chopstick 3
Philosopher 3 is waiting to pick up chopstick 4
Philosopher 2 is waiting to pick up chopstick 2
Philosopher 2 picked up chopstick 2
Philosopher 2 is waiting to pick up chopstick 3
Philosopher 0 is waiting to pick up chopstick 1
Philosopher 0 picked up chopstick 1
Philosopher 0 is waiting to pick up chopstick 0
Philosopher 1 is waiting to pick up chopstick 1
Philosopher 4 is waiting to pick up chopstick 4
Philosopher 4 picked up chopstick 4
Philosopher 4 is waiting to pick up chopstick 0
Philosopher 0 picked up chopstick 0
Philosopher 0 will eat for 2 seconds
Philosopher 0 will put down his chopsticks
Philosopher 0 will think for 1 seconds
Philosopher 4 picked up chopstick 0
Philosopher 4 will eat for 3 seconds
Philosopher 1 picked up chopstick 1
Philosopher 1 is waiting to pick up chopstick 2
Philosopher 0 is waiting to pick up chopstick 1
Philosopher 4 will put down his chopsticks
Philosopher 4 will think for 2 seconds
Philosopher 3 picked up chopstick 4
Philosopher 3 will eat for 2 seconds
Philosopher 3 will put down his chopsticks
Philosopher 3 will think for 2 seconds
Philosopher 4 is waiting to pick up chopstick 4
Philosopher 4 picked up chopstick 4
Philosopher 4 is waiting to pick up chopstick 0
Philosopher 2 picked up chopstick 3
Philosopher 2 will eat for 1 seconds
Philosopher 2 will put down his chopsticks
Philosopher 2 will think for 3 seconds
Philosopher 1 picked up chopstick 2
Philosopher 1 will eat for 1 seconds
Philosopher 3 is waiting to pick up chopstick 3
Philosopher 3 picked up chopstick 3
Philosopher 3 is waiting to pick up chopstick 4
Philosopher 4 picked up chopstick 0
Philosopher 4 will eat for 3 seconds
Philosopher 1 will put down his chopsticks
Philosopher 1 will think for 1 seconds
Philosopher 0 picked up chopstick 1
Philosopher 0 is waiting to pick up chopstick 0
Philosopher 1 is waiting to pick up chopstick 1
Philosopher 2 is waiting to pick up chopstick 2
Philosopher 2 picked up chopstick 2
Philosopher 2 is waiting to pick up chopstick 3
Philosopher 4 will put down his chopsticks
Philosopher 4 will think for 1 seconds
Philosopher 3 picked up chopstick 4
Philosopher 3 will eat for 2 seconds
Philosopher 0 picked up chopstick 0
Philosopher 0 will eat for 2 seconds
Philosopher 4 is waiting to pick up chopstick 4
Philosopher 3 will put down his chopsticks
Philosopher 3 will think for 1 seconds
Philosopher 0 will put down his chopsticks
Philosopher 0 will think for 3 seconds
Philosopher 2 picked up chopstick 3
Philosopher 2 will eat for 1 seconds
Philosopher 4 picked up chopstick 4
Philosopher 4 is waiting to pick up chopstick 0
Philosopher 1 picked up chopstick 1
Philosopher 1 is waiting to pick up chopstick 2
Philosopher 2 will put down his chopsticks
Philosopher 2 will think for 2 seconds
Philosopher 3 is waiting to pick up chopstick 3
Philosopher 3 picked up chopstick 3
Philosopher 3 is waiting to pick up chopstick 4
Philosopher 4 picked up chopstick 0
Philosopher 4 will eat for 2 seconds
Philosopher 1 picked up chopstick 2
Philosopher 1 will eat for 2 seconds
Philosopher 0 is waiting to pick up chopstick 1
Philosopher 2 is waiting to pick up chopstick 2
Philosopher 4 will put down his chopsticks
Philosopher 4 will think for 3 seconds
Philosopher 3 picked up chopstick 4
Philosopher 3 will eat for 1 seconds
Philosopher 1 will put down his chopsticks
Philosopher 1 will think for 3 seconds
Philosopher 0 picked up chopstick 1
Philosopher 0 is waiting to pick up chopstick 0
Philosopher 2 picked up chopstick 2
Philosopher 2 is waiting to pick up chopstick 3
Philosopher 3 will put down his chopsticks
Philosopher 3 will think for 2 seconds
Philosopher 0 picked up chopstick 0
Philosopher 0 will eat for 1 seconds
Philosopher 2 picked up chopstick 3
Philosopher 2 will eat for 3 seconds
Philosopher 4 is waiting to pick up chopstick 4
Philosopher 4 picked up chopstick 4
Philosopher 4 is waiting to pick up chopstick 0
Philosopher 1 is waiting to pick up chopstick 1
Philosopher 0 will put down his chopsticks
Philosopher 0 will think for 1 seconds
Philosopher 1 picked up chopstick 1
Philosopher 1 is waiting to pick up chopstick 2
Philosopher 3 is waiting to pick up chopstick 3
Philosopher 0 is waiting to pick up chopstick 1
Philosopher 4 picked up chopstick 0
Philosopher 4 will eat for 1 seconds
Philosopher 2 will put down his chopsticks
Philosopher 2 will think for 1 seconds
Philosopher 1 picked up chopstick 2
Philosopher 1 will eat for 3 seconds
Philosopher 3 picked up chopstick 3
Philosopher 3 is waiting to pick up chopstick 4
Philosopher 2 is waiting to pick up chopstick 2
Philosopher 4 will put down his chopsticks
Philosopher 4 will think for 2 seconds
Philosopher 3 picked up chopstick 4
Philosopher 3 will eat for 3 seconds
Philosopher 1 will put down his chopsticks
Philosopher 1 will think for 1 seconds
Philosopher 0 picked up chopstick 1
Philosopher 0 is waiting to pick up chopstick 0
Philosopher 2 picked up chopstick 2
Philosopher 2 is waiting to pick up chopstick 3
Philosopher 4 is waiting to pick up chopstick 4
Philosopher 1 is waiting to pick up chopstick 1
Philosopher 3 will put down his chopsticks
Philosopher 3 will think for 1 seconds
Philosopher 4 picked up chopstick 4
Philosopher 4 is waiting to pick up chopstick 0
Philosopher 0 picked up chopstick 0
Philosopher 0 will eat for 1 seconds
Philosopher 2 picked up chopstick 3
Philosopher 2 will eat for 3 seconds
Philosopher 3 is waiting to pick up chopstick 3
Philosopher 0 will put down his chopsticks
Philosopher 0 will think for 3 seconds
Philosopher 1 picked up chopstick 1
Philosopher 1 is waiting to pick up chopstick 2
Philosopher 4 picked up chopstick 0
Philosopher 4 will eat for 2 seconds
Philosopher 2 will put down his chopsticks
Philosopher 3 picked up chopstick 3
Philosopher 3 is waiting to pick up chopstick 4
Philosopher 1 picked up chopstick 2
Philosopher 1 will eat for 3 seconds
Philosopher 2 will think for 1 seconds
Philosopher 4 will put down his chopsticks
Philosopher 4 will think for 2 seconds
Philosopher 0 is waiting to pick up chopstick 1
Philosopher 2 is waiting to pick up chopstick 2
Philosopher 3 picked up chopstick 4
Philosopher 3 will eat for 1 seconds
Philosopher 4 is waiting to pick up chopstick 4
Philosopher 1 will put down his chopsticks
Philosopher 1 will think for 2 seconds
Philosopher 0 picked up chopstick 1
Philosopher 0 is waiting to pick up chopstick 0
Philosopher 2 picked up chopstick 2
Philosopher 2 is waiting to pick up chopstick 3
Philosopher 3 will put down his chopsticks
Philosopher 3 will think for 1 seconds
Philosopher 4 picked up chopstick 4
Philosopher 4 is waiting to pick up chopstick 0
Philosopher 3 is waiting to pick up chopstick 3
Philosopher 3 picked up chopstick 3
Philosopher 3 is waiting to pick up chopstick 4
Philosopher 0 picked up chopstick 0
Philosopher 0 will eat for 2 seconds
Philosopher 1 is waiting to pick up chopstick 1
Philosopher 0 will put down his chopsticks
Philosopher 0 will think for 3 seconds
Philosopher 1 picked up chopstick 1
Philosopher 1 is waiting to pick up chopstick 2
Philosopher 4 picked up chopstick 0
Philosopher 4 will eat for 3 seconds
Philosopher 0 is waiting to pick up chopstick 1
Philosopher 4 will put down his chopsticks
Philosopher 4 will think for 2 seconds
Philosopher 3 picked up chopstick 4
Philosopher 3 will eat for 2 seconds
Philosopher 3 will put down his chopsticks
Philosopher 3 will think for 2 seconds
Philosopher 2 picked up chopstick 3
Philosopher 2 will eat for 1 seconds
Philosopher 4 is waiting to pick up chopstick 4
Philosopher 4 picked up chopstick 4
Philosopher 4 is waiting to pick up chopstick 0
Philosopher 2 will put down his chopsticks
Philosopher 2 will think for 2 seconds
Philosopher 1 picked up chopstick 2
Philosopher 1 will eat for 3 seconds
Philosopher 3 is waiting to pick up chopstick 3
Philosopher 3 picked up chopstick 3
Philosopher 3 is waiting to pick up chopstick 4
Philosopher 4 picked up chopstick 0
Philosopher 4 will eat for 1 seconds
Philosopher 2 is waiting to pick up chopstick 2
Philosopher 4 will put down his chopsticks
Philosopher 4 will think for 1 seconds
Philosopher 1 will put down his chopsticks
Philosopher 1 will think for 3 seconds
Philosopher 0 picked up chopstick 1
Philosopher 0 is waiting to pick up chopstick 0
Philosopher 2 picked up chopstick 2
Philosopher 2 is waiting to pick up chopstick 3
Philosopher 3 picked up chopstick 4
Philosopher 3 will eat for 1 seconds
Philosopher 4 is waiting to pick up chopstick 4
Philosopher 3 will put down his chopsticks
Philosopher 3 will think for 1 seconds
Philosopher 4 picked up chopstick 4
Philosopher 4 is waiting to pick up chopstick 0
Philosopher 0 picked up chopstick 0
Philosopher 0 will eat for 1 seconds
Philosopher 2 picked up chopstick 3
Philosopher 2 will eat for 2 seconds
Philosopher 3 is waiting to pick up chopstick 3
Philosopher 1 is waiting to pick up chopstick 1
Philosopher 0 will put down his chopsticks
Philosopher 0 will think for 1 seconds
Philosopher 1 picked up chopstick 1
Philosopher 1 is waiting to pick up chopstick 2
Philosopher 4 picked up chopstick 0
Philosopher 4 will eat for 1 seconds
Philosopher 2 will put down his chopsticks
Philosopher 0 is waiting to pick up chopstick 1
Philosopher 2 will think for 1 seconds
Philosopher 3 picked up chopstick 3
Philosopher 3 is waiting to pick up chopstick 4
Philosopher 4 will put down his chopsticks
Philosopher 4 will think for 2 seconds
Philosopher 1 picked up chopstick 2
Philosopher 1 will eat for 1 seconds
Philosopher 2 is waiting to pick up chopstick 2
Philosopher 3 picked up chopstick 4
Philosopher 3 will eat for 2 seconds
Philosopher 1 will put down his chopsticks
Philosopher 0 picked up chopstick 1
Philosopher 0 is waiting to pick up chopstick 0
Philosopher 2 picked up chopstick 2
Philosopher 2 is waiting to pick up chopstick 3
Philosopher 1 will think for 2 seconds
Philosopher 4 is waiting to pick up chopstick 4
Philosopher 3 will put down his chopsticks
Philosopher 3 will think for 1 seconds
Philosopher 4 picked up chopstick 4
Philosopher 4 is waiting to pick up chopstick 0
Philosopher 0 picked up chopstick 0
Philosopher 0 will eat for 1 seconds
Philosopher 2 picked up chopstick 3
Philosopher 2 will eat for 1 seconds
Philosopher 1 is waiting to pick up chopstick 1
Philosopher 3 is waiting to pick up chopstick 3
Philosopher 0 will put down his chopsticks
Philosopher 0 will think for 2 seconds
Philosopher 2 will put down his chopsticks
Philosopher 2 will think for 3 seconds
Philosopher 1 picked up chopstick 1
Philosopher 1 is waiting to pick up chopstick 2
Philosopher 3 picked up chopstick 3
Philosopher 3 is waiting to pick up chopstick 4
Philosopher 4 picked up chopstick 0
Philosopher 4 will eat for 2 seconds
Philosopher 0 is waiting to pick up chopstick 1
Philosopher 1 picked up chopstick 2
Philosopher 1 will eat for 1 seconds
Philosopher 4 will put down his chopsticks
Philosopher 4 will think for 3 seconds
Philosopher 3 picked up chopstick 4
Philosopher 3 will eat for 1 seconds
Philosopher 2 is waiting to pick up chopstick 2
Philosopher 1 will put down his chopsticks
Philosopher 2 picked up chopstick 2
Philosopher 2 is waiting to pick up chopstick 3
Philosopher 1 will think for 1 seconds
Philosopher 0 picked up chopstick 1
Philosopher 0 is waiting to pick up chopstick 0
Philosopher 3 will put down his chopsticks
Philosopher 3 will think for 3 seconds
Philosopher 1 is waiting to pick up chopstick 1*/