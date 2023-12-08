#include <stdio.h>
#include <zephyr.h>
#include <arch/cpu.h>
#include <unity.h>
#include "helper.h"

#define STACKSIZE 2000
extern k_thread_runtime_stats_t threads_runtime_stats;
K_THREAD_STACK_DEFINE(primary_stack, STACKSIZE);
K_THREAD_STACK_DEFINE(secondary_stack, STACKSIZE);
K_THREAD_STACK_DEFINE(supervisor_stack, STACKSIZE);
struct k_thread primary_thread, secondary_thread, super_thread;

void supervisor_entry(struct k_thread *primary, struct k_thread *secondary)
{
    printk("supervisor is suspending threads\n");
    k_thread_suspend(primary);
    k_thread_suspend(secondary);
}

char *primary_name = "primary";
char *secondary_name = "secondary";

void thread_analyzer(   uint32_t time_debounce,
                        k_thread_entry_t pri_thread_entry,
                        void *pri_arg0, void *pri_arg1, void *pri_arg2,
                        int pri_prio,  k_timeout_t pri_delay,
                        uint64_t *pri_duration,

                        k_thread_entry_t sec_thread_entry,
                        void *sec_arg0, void *sec_arg1, void *sec_arg2,
                        int sec_prio,  k_timeout_t sec_delay,
                        uint64_t *sec_duration,

                        uint64_t *total_duration)
{
	uint64_t start, primary, secondary, end, elapsed;
    k_thread_runtime_stats_t pri_stats, sec_stats, start_stats, end_stats;;

    k_thread_runtime_stats_all_get(&start_stats);

    // Meta-IRQ is enabled, forcing this to always preempt.
    int supervisor_prio = -CONFIG_NUM_COOP_PRIORITIES;
    k_thread_create(&super_thread,
                    supervisor_stack,
                    STACKSIZE,
                    (k_thread_entry_t) supervisor_entry,
                    &primary_thread,
                    &secondary_thread,
                    NULL,
                    supervisor_prio,
                    0,
                    K_MSEC(time_debounce));
    printk("\tcreate primary\n");
    k_thread_create(&primary_thread,
                    primary_stack,
                    STACKSIZE,
                    pri_thread_entry,
                    primary_name,
                    pri_arg1,
                    pri_arg2,
                    pri_prio,
                    0,
                    pri_delay);
    printk("\tcreate secondary\n");
    k_thread_create(&secondary_thread,
                    secondary_stack,
                    STACKSIZE,
                    sec_thread_entry,
                    secondary_name,
                    sec_arg1,
                    sec_arg2,
                    sec_prio,
                    0,
                    sec_delay);
    k_thread_join(&super_thread, K_MSEC(5500));
    printk("\tsupervisor joined\n");

    k_thread_runtime_stats_get(&primary_thread, &pri_stats);
    k_thread_runtime_stats_get(&secondary_thread, &sec_stats);
    k_thread_runtime_stats_all_get(&end_stats);

    start = timing_cycles_to_ns(start_stats.execution_cycles) / 1000;
    primary = timing_cycles_to_ns(pri_stats.execution_cycles) / 1000;
    secondary = timing_cycles_to_ns(sec_stats.execution_cycles) / 1000;
    end = timing_cycles_to_ns(end_stats.execution_cycles) / 1000;
    elapsed = end - start;

    printk("primary: %lld\tsecondary: %lld\tstart: %lld\tend: %lld\t elapsed: %lld (us)\n",
           primary, secondary, start, end, elapsed);

    *pri_duration = primary;
    *sec_duration = secondary;
    *total_duration = elapsed;

    k_thread_abort(&primary_thread);
    k_thread_abort(&secondary_thread);
}

