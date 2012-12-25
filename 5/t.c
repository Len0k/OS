#include <stdio.h>
#include <ucontext.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdarg.h>

int kbthread_create(void(*)(), int, ...);
void kbthread_exit();
void kbthread_join(int);
void kbthread_sleep(int);

#define KBTHREAD_MAX_COUNT 100
#define KBTHREAD_STACK_SIZE 1024 * 1024
//#define DEBUG 0

struct kbthread {
    int id;
    char status;
    char stack[KBTHREAD_STACK_SIZE];
    ucontext_t context;
    char exit_stack[KBTHREAD_STACK_SIZE];
    ucontext_t exit_context;
    int sleep;
};

static ucontext_t main_context;
static struct kbthread kbthreads[KBTHREAD_MAX_COUNT];
static int current_context = -1;

void f(void) {
    int i;
    for (i = 0; i != 20; ++i) {
        printf("f!\n");
        kbthread_sleep(1000);
    }
    return;
}

void f2(void) {
    int i;
    for (i = 0; i != 10; ++i) {
        printf("f2!\n");
        kbthread_sleep(2000);
    }
    return;
}

void scheduler(int signal) {
    int tid, next_tid = -1;
    // Sleep.
    for (tid = 0; tid != KBTHREAD_MAX_COUNT - 1; ++tid) {
        if (kbthreads[tid].status == 'S') {
            if (signal == SIGALRM) {
                kbthreads[tid].sleep -= 250;
                if (kbthreads[tid].sleep <= 0)
                    kbthreads[tid].status = 'R';
            }
        }
    }
    // Select next running thread.
    for (tid = current_context + 1; tid != KBTHREAD_MAX_COUNT -1; ++tid) {
        if (kbthreads[tid].status == 'R') {
            next_tid = tid;
            break;
        }
    }
    // Swith to new running thread.
    int old_context = current_context;
    current_context = next_tid;
    #ifdef DEBUG
    printf("S: %d -> %d\n", old_context, current_context);
    #endif
    if (current_context == -1 && old_context == -1) {
        return;
    }
    if (old_context == -1) {
        if (swapcontext(&main_context, &kbthreads[current_context].context) == -1) {
            perror("Can't swapcontext");
            exit(13);
        }
    } else if (current_context == -1) {
        if (swapcontext(&kbthreads[old_context].context, &main_context) == -1) {
            perror("Can't swapcontext");
            exit(13);
        }
    } else {
        if (swapcontext(&kbthreads[old_context].context, &kbthreads[current_context].context) == -1) {
            perror("Can't swapcontext");
            exit(13);
        }
    }
}

int kbthread_create(void(*func)(), int argc, ...) {
    int tid;
    // Select empty kbthread structure.
    for(tid = 0; tid != KBTHREAD_MAX_COUNT - 1; ++tid) {
        if (kbthreads[tid].status == 'Z') {
            kbthreads[tid].status = 'R';
            kbthreads[tid].id = tid;
            break;
        }
    }
    // Set callbacks.
    if (getcontext(&kbthreads[tid].exit_context) == -1) {
        perror("Can't getcontext");
        exit(13);
    }
    kbthreads[tid].exit_context.uc_stack.ss_sp = kbthreads[tid].exit_stack;
    kbthreads[tid].exit_context.uc_stack.ss_size = sizeof(kbthreads[tid].exit_stack);
    kbthreads[tid].exit_context.uc_link = &main_context;
    makecontext(&kbthreads[tid].exit_context, kbthread_exit, 0);
    if (getcontext(&kbthreads[tid].context) == -1) {
        perror("Can't getcontext");
        exit(13);
    }
    kbthreads[tid].context.uc_stack.ss_sp = kbthreads[tid].stack;
    kbthreads[tid].context.uc_stack.ss_size = sizeof(kbthreads[tid].stack);
    kbthreads[tid].context.uc_link = &kbthreads[tid].exit_context;

    //va_list argp;
    //va_start(argp, argc);
    makecontext(&kbthreads[tid].context, func, 0);
    //va_end(argp);
    return tid;
}

void kbthread_exit() {
    #ifdef DEBUG
    printf("E: %d\n", current_context);
    #endif
    kbthreads[current_context].status = 'Z';
    return;
}

void kbthread_join(int tid) {
    struct timespec t;
    t.tv_sec = 0;
    t.tv_nsec = 100000000;
    // Block main thread while thread tid do not stop.
    while (kbthreads[tid].status != 'Z') {
        nanosleep(&t, NULL);
    }
}

void kbthread_sleep(int millisec) {
    kbthreads[current_context].status = 'S';
    kbthreads[current_context].sleep = millisec;
    scheduler(SIGUSR1);
    return;
}

int main() {
    // Init scheduler.
    int i;
    for (i = 0; i != KBTHREAD_MAX_COUNT - 1; ++i) {
        kbthreads[i].status = 'Z';
    }

    // Call scheduler every 1/4 sec.
    signal(SIGALRM, scheduler);
    struct itimerval alarm_interval;
    alarm_interval.it_interval.tv_sec = 0;
    alarm_interval.it_interval.tv_usec = 250000;
    alarm_interval.it_value.tv_sec = 0;
    alarm_interval.it_value.tv_usec = 250000;
    setitimer(ITIMER_REAL, &alarm_interval, NULL);

    int tid1 = kbthread_create(f2, 1, 13);
    printf("Create thread: %d\n", tid1);
    int tid2 = kbthread_create(f, 0);
    printf("Create thread: %d\n", tid2);
    kbthread_join(tid1);
    printf("Thread %d stop\n", tid1);
    kbthread_join(tid2);
    printf("Thread %d stop\n", tid2);
    return 0;
}
