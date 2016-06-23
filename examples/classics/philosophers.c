#define _GNU_SOURCE

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define PHIL_COUNT (4)
#define MAX_MEAL (10)

typedef struct meal_s
{
    unsigned            count_phil;
    unsigned            count_stick;
    unsigned            started;
    pthread_mutex_t     *sticks;
} meal_t;

typedef struct phil_s
{
    meal_t      *meal;
    pthread_t   thread;
    char        *name;
    unsigned    stick_idx;
    unsigned    meal_count;
} phil_t;


void *philosopher(void *arg)
{
    phil_t *self = (phil_t *)arg;
    meal_t *meal = self->meal;
    unsigned left, right;


    /* Seting up initial state */
    self->meal_count = 0;
    right = self->stick_idx;
    left = (self->stick_idx + 1) % meal->count_stick;
    pthread_mutex_lock(meal->sticks + right);
    printf("%s got chopstick %u\n", self->name, right);

    /* Waiting for the meal to start */
    while(!meal->started)
        sleep(1);

    while(self->meal_count < MAX_MEAL)
    {
        pthread_mutex_lock(meal->sticks + left);
        printf("%s got chopstick %u and eats\n", self->name, left);
        self->meal_count++;
        usleep(100000);
        printf("%s release chopstick %u\n", self->name, right);
        pthread_mutex_unlock(meal->sticks + right);
        right = left;
        left = (left + 1) % meal->count_stick;
    }

    return (void *)0;
}

int     main(int ac, char **av) {
    pthread_mutex_t     sticks[PHIL_COUNT + 1];
    meal_t              meal;
    phil_t              philz[PHIL_COUNT];

    meal.count_phil = PHIL_COUNT;
    meal.count_stick = PHIL_COUNT + 1;
    meal.started = 0;
    meal.sticks = sticks;

    for(unsigned i = 0; i < PHIL_COUNT + 1; i++)
        pthread_mutex_init(&sticks[i], 0);

    for(unsigned i = 0; i < PHIL_COUNT; i++)
    {
        philz[i].meal = &meal;
        asprintf(&philz[i].name, "Philosopher %u", i);
        philz[i].stick_idx = i;
        pthread_create(&philz[i].thread, NULL, &philosopher, (void *)&philz[i]);
    }

    meal.started = 1;
    pthread_join(philz[0].thread, NULL);
    return (0);
}
