/*
 * main.h
 *
 *  Created on: Jan 3, 2021
 *      Author: jeffr
 */

#ifndef MAIN_H_
#define MAIN_H_

//Tasks
void task1_run(void); // TASK 1
void task2_run(void); // TASK 2
void task3_run(void); // TASK 3
void task4_run(void); // TASK 4

//Systick handler
void init_Systick(uint32_t ticks_hz);

//Stack initializations
__attribute__((naked)) void init_Scheduler_Stack(uint32_t SHED_StackStart);
void init_Tasks_Stack();

//Stack memory calculation
#define task_stack_size 1024U
#define scheduler_stack_size 1024U
#define sram_start  0x20000000
#define sram_size ((128)*(1024))
#define sram_end   sram_start + sram_size

#define t1_stack_start   sram_end
#define t2_stack_start   sram_end - (1*task_stack_size)
#define t3_stack_start   sram_end - (2*task_stack_size)
#define t4_stack_start   sram_end - (3*task_stack_size)
#define sched_stack_start sram_end - (4*task_stack_size)

//Systick clock
#define hsi_clk      16000000U
#define systick_clk  hsi_clk
#define ticks        1000U

//Other Macros
#define Max_tasks   4
//uint32_t psp_of_tasks[Max_tasks]={t1_stack_start,t2_stack_start,t3_stack_start,t4_stack_start};
//uint32_t taskAddress[Max_tasks];

/* This is a task control block carries private information of each task */
typedef struct
{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t  current_state;
	void (*task_handler)(void);
}TCB_t;

/* Each task has its own TCB */
TCB_t user_tasks[Max_tasks];

/* Task States */
#define TASK_RUNNING_STATE 0x00
#define TASK_BLOCKED_STATE 0xff

#define Dummy_xpsr 0x01000000U
uint32_t *SHCSR = (uint32_t*)0xE000ED24;
uint32_t *UFSR = (uint32_t*)0xE000ED2A;
uint8_t current_task=0;//task 1 running

void enable_processor_faults(void);
__attribute__((naked)) void switch_sp_to_psp(void);
uint32_t get_psp(void);
void save_psp(uint32_t current_psp_value);
void update_next_task(void);

#endif /* MAIN_H_ */
