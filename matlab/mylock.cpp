#include "mylock.h"
#include <omp.h>

static bool init_flag = false;
static omp_nest_lock_t lockVar;

void mylock_initialize() {
    if(init_flag) return;
    omp_init_nest_lock(&lockVar);
    init_flag = true;
}

void mylock() {
    omp_set_nest_lock(&lockVar);
}

void myunlock() {
    omp_unset_nest_lock(&lockVar);
}