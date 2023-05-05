/**
 * @file SCM_int.h
 * @author Ahmed Naeem (ahmedaneng@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SCM_INT_H
#define SCM_INT_H

#include "../../LIB/std_types.h"

/******************************************************************
 *          SCM Types
 ******************************************************************/
typedef enum
{
    Task_Resumed,
    Task_Suspended
} Task_state_t;

typedef struct task
{
    u32 periodicity;
    u32 firstDelay;
    u8 priority;
    void (*ptrTask)(void);
    Task_state_t state;

} SCM_Task_t;

/*********************************************************************
 *                      SCM APIs
 *********************************************************************/
/**
 * @brief Scheduler initialization
 *
 */
void SCM_vidInit(void);

/**
 * @brief Start scheduler
 *
 */
void SCM_vidStart();

/**
 * @brief Create a task with priority and periodicity
 *
 * @param copypfPtrTask
 * @param copyofPriority
 * @param copyofPeriodicity
 */
void SCM_vidCreateTask(void (*copypfPtrTask)(void), u8 copyofPriority, u32 copyofPeriodicity, u32 copyofFirstDelay);

/**
 * @brief scheduler handling
 *
 */
void SCM_vidHandler(void);

/**
 * @brief resume task
 *
 * @param priority
 */
void SCM_vidResumeTask(u8 priority);

/**
 * @brief suspend task
 *
 * @param priority
 */
void SCM_vidSuspendTask(u8 priority);

/**
 * @brief Delete Task
 *
 * @param priority
 */
void SCM_vidDeleteTask(u8 priority);

#endif