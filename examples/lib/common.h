#pragma once

#include <time.h>

void get_time(struct timespec *t);
double get_time_diff(struct timespec *before, struct timespec *after);
