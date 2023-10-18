#include <stdio.h>
#include <zephyr.h>
#include <arch/cpu.h>
#include <unity.h>
#include "helper.h"

void setUp(void) {}

void tearDown(void) {}

void busy_busy(char *name)
{
    for (int i = 0; ; i++);
}

void busy_yield(char *name)
{
    for (int i = 0; ; i++) {
        if (!(i & 0xFF)) {
            k_yield();
        }
    }
}

void busy_sleep(char *name)
{
    k_busy_wait(10000);
    k_sleep(K_MSEC(490));
}

void priority_inversion(char *name, struct k_sem *sem)
{
    printk("start priority inversion %s\n", name);
    k_sem_take(sem, K_FOREVER);
    printk("got semaphore %s\n", name);
    for (int i = 0; ; i++);
}

void test_priority_inversion(void)
{
    uint64_t high_stats, low_stats, elapsed_stats;
    struct k_sem sem;
    k_sem_init(&sem, 1, 1);

    thread_analyzer((k_thread_entry_t)priority_inversion, 
                 NULL, &sem, NULL, K_PRIO_PREEMPT(4), K_MSEC(10), &low_stats,
                 (k_thread_entry_t)priority_inversion, 
                 NULL, &sem, NULL, K_PRIO_PREEMPT(3), K_MSEC(12), &high_stats,
                 &elapsed_stats);
                 
    TEST_ASSERT_UINT64_WITHIN(1000, 0, high_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, low_stats);
}

void test_coop_same_priority_busy(void)
{
    uint64_t first_stats, second_stats, elapsed_stats;

    thread_analyzer((k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_COOP(3), K_MSEC(10), &first_stats,
                 (k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_COOP(3), K_MSEC(12), &second_stats,
                 &elapsed_stats);
                 
    TEST_ASSERT_EQUAL_UINT64(0, second_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, first_stats);
}

void test_coop_same_priority_yield(void)
{
    uint64_t first_stats, second_stats, elapsed_stats;
    
    thread_analyzer((k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_COOP(3), K_MSEC(10), &first_stats,
                 (k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_COOP(3), K_MSEC(10), &second_stats,
                 &elapsed_stats);
                 
    TEST_ASSERT_UINT64_WITHIN(100000, 2500000, first_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 2500000, second_stats);
}

void test_preempt_same_priority_busy(void)
{
    uint64_t first_stats, second_stats, elapsed_stats;
    thread_analyzer((k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(3), K_MSEC(10), &first_stats,
                 (k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(3), K_MSEC(12), &second_stats,
                 &elapsed_stats);

    TEST_ASSERT_EQUAL_UINT64(0, second_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, first_stats);
}

void test_preempt_same_priority_yield(void)
{
    uint64_t first_stats, second_stats, elapsed_stats;

    thread_analyzer((k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(3), K_MSEC(10), &first_stats,
                 (k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(3), K_MSEC(10), &second_stats,
                 &elapsed_stats);
                 
    TEST_ASSERT_UINT64_WITHIN(100000, 2500000, first_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 2500000, second_stats);
}

void test_coop_priority_high_first_busy(void)
{
    uint64_t high_stats, low_stats, elapsed_stats;
    thread_analyzer((k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_COOP(2), K_MSEC(10), &high_stats,
                 (k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_COOP(3), K_MSEC(12), &low_stats,
                 &elapsed_stats);
                 
    TEST_ASSERT_EQUAL_UINT64(0, low_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, high_stats);
}

void test_coop_priority_low_first_busy(void)
{
    uint64_t high_stats, low_stats, elapsed_stats;

    thread_analyzer((k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_COOP(3), K_MSEC(10), &low_stats,
                 (k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_COOP(2), K_MSEC(12), &high_stats,
                 &elapsed_stats);

    TEST_ASSERT_EQUAL_UINT64(0, high_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, low_stats);
}

void test_coop_priority_high_first_yield(void)
{
    uint64_t low_stats, high_stats, elapsed_stats;
    thread_analyzer((k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_COOP(2), K_MSEC(12), &high_stats,
                 (k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_COOP(3), K_MSEC(10), &low_stats,
                 &elapsed_stats);

    TEST_ASSERT_UINT64_WITHIN(5000, 0, high_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, low_stats);
}

void test_coop_priority_low_first_yield(void)
{
    uint64_t low_stats, high_stats, elapsed_stats;
    thread_analyzer((k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_COOP(3), K_MSEC(10), &low_stats,
                 (k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_COOP(2), K_MSEC(12), &high_stats,
                 &elapsed_stats);
                 
    TEST_ASSERT_UINT64_WITHIN(5000, 0, low_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, high_stats);
}



void test_preempt_priority_high_first_busy(void)
{
    uint64_t low_stats, high_stats, elapsed_stats;

    thread_analyzer((k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(2), K_MSEC(10), &high_stats,
                 (k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(3), K_MSEC(10), &low_stats,
                 &elapsed_stats);

    TEST_ASSERT_UINT64_WITHIN(5000, 0, low_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, high_stats);
}

void test_preempt_priority_low_first_busy(void)
{
    uint64_t low_stats, high_stats, elapsed_stats;

    thread_analyzer((k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(3), K_MSEC(10), &low_stats,
                 (k_thread_entry_t)busy_busy, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(2), K_MSEC(10), &high_stats,
                 &elapsed_stats);

    TEST_ASSERT_UINT64_WITHIN(5000, 0, low_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, high_stats);
}

void test_preempt_priority_high_first_yield(void)
{
    uint64_t low_stats, high_stats, elapsed_stats;

    thread_analyzer((k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(2), K_MSEC(10), &high_stats,
                 (k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(3), K_MSEC(10), &low_stats,
                 &elapsed_stats);

    TEST_ASSERT_UINT64_WITHIN(5000, 0, low_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, high_stats);
}

void test_preempt_priority_low_first_yield(void)
{
    uint64_t low_stats, high_stats, elapsed_stats;

    thread_analyzer((k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(3), K_MSEC(10), &low_stats,
                 (k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(2), K_MSEC(10), &high_stats,
                 &elapsed_stats);

    TEST_ASSERT_UINT64_WITHIN(5000, 0, low_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, high_stats);
}

// Write tests for two threads: one should run busy_sleep and the other busy_yield 
void test_preempt_priority_mix(void)
{
    uint64_t low_stats, high_stats, elapsed_stats;

    thread_analyzer((k_thread_entry_t)busy_sleep, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(3), K_MSEC(10), &low_stats,
                 (k_thread_entry_t)busy_yield, 
                 NULL, NULL, NULL, K_PRIO_PREEMPT(2), K_MSEC(10), &high_stats,
                 &elapsed_stats);

    TEST_ASSERT_UINT64_WITHIN(1000, 10000, high_stats);
    TEST_ASSERT_UINT64_WITHIN(100000, 5000000, low_stats);
}

int main (void)
{
    UNITY_BEGIN();
    RUN_TEST(test_priority_inversion);

    RUN_TEST(test_coop_same_priority_busy);
    RUN_TEST(test_coop_same_priority_yield);

    RUN_TEST(test_preempt_same_priority_busy);
    RUN_TEST(test_preempt_same_priority_yield);

    RUN_TEST(test_coop_priority_high_first_busy);
    RUN_TEST(test_coop_priority_low_first_busy);
   
    RUN_TEST(test_coop_priority_high_first_yield);
    RUN_TEST(test_coop_priority_low_first_yield);
    
    RUN_TEST(test_preempt_priority_high_first_busy);
    RUN_TEST(test_preempt_priority_low_first_busy);

    RUN_TEST(test_preempt_priority_high_first_yield);
    RUN_TEST(test_preempt_priority_low_first_yield);

    RUN_TEST(test_preempt_priority_mix);

    return UNITY_END();
}