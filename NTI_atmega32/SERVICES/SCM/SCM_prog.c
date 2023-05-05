/**
 * @file SCM_prog.c
 * @author Ahmed Naeem (ahmedaneng@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../LIB/register.h"
#include "../../LIB/bit_math.h"

#include "SCM_cfg.h"
#include "SCM_int.h"

/****************************************************************
 * Tasks Array
 *****************************************************************/
SCM_Task_t SCM_Tasks[TASK_MAX_NO];

/****************************************************************
 * Scheduler Ticks Counter
 *****************************************************************/
u32 SCM_Ticks = 0;

/****************************************************************
 *  SCM APIs
 *****************************************************************/
/**
 * @brief Scheduler initialization
 *
 */
void SCM_vidInit(void)
{

#if (SCM_TICK_TIME <= 16)
    /*	FCPU 16 Mhz to achive 1 msec		*/
    TCNT0 = 256 - (SYSTEM_CLK / 1024ul * 1000ul);
#elif (SCM_TICK_TIME > 16)
    for (u8 i = 1; i <= 16; i++)
    {
        if (SCM_TICK_TIME % i == 0)
            max = i;
    }

#endif
    /*	Enable Timer Overflow Interrupt		*/
    TIMSK = 1;
    /*	Global Interrupt Enable				*/
    GIE_ENABLE();
}

/**
 * @brief Start scheduler
 *
 */
void SCM_vidStart()
{
    /*	Start System Timer	*/
    /* set prescaler to 64*/
    TCCR0 = 0x0D;
}

/**
 * @brief Create a task with priority and periodicity
 *
 * @param copypfPtrTask
 * @param copyofPriority
 * @param copyofPeriodicity
 */
void SCM_vidCreateTask(void (*copypfPtrTask)(void), u8 copyofPriority, u32 copyofPeriodicity, u32 copyofFirstDelay)
{
    SCM_Tasks[copyofPriority].periodicity = copyofPeriodicity;
    SCM_Tasks[copyofPriority].firstDelay = copyofFirstDelay;

    SCM_Tasks[copyofPriority].ptrTask = copypfPtrTask;
    SCM_Tasks[copyofPriority].state = Task_Resumed;
}

/**
 * @brief scheduler handling
 *
 */
void SCM_vidHandler(void)
{
    for (u8 Tcount = 0; Tcount < TASK_MAX_NO; Tcount++)
    {
        if (SCM_Ticks % SCM_Tasks[Tcount].state == Task_Resumed)
        {

            if (SCM_Ticks % SCM_Tasks[Tcount].firstDelay == 0)
            {
                SCM_Tasks[Tcount].firstDelay = SCM_Tasks[Tcount].periodicity - 1;
                if ((SCM_Tasks[Tcount].ptrTask != NULL))
                {
                    SCM_Tasks[Tcount].ptrTask();
                }
            }
            else
            {
                SCM_Tasks[Tcount].firstDelay--;
            }
        }
        else
        {
            // do nothing
        }
    }
}

/**
 * @brief resume task
 *
 * @param priority
 */
void SCM_vidResumeTask(u8 priority)
{
    SCM_Tasks[priority].state = Task_Resumed;
}

/**
 * @brief suspend task
 *
 * @param priority
 */
void SCM_vidSuspendTask(u8 priority)
{
    SCM_Tasks[priority].state = Task_Suspended;
    SCM_Tasks[priority].ptrTask = NULL;
}

/**
 * @brief Delete Task
 *
 * @param priority
 */
void SCM_vidDeleteTask(u8 priority)
{
    SCM_Tasks[priority].state = Task_Suspended;
    SCM_Tasks[priority].ptrTask = NULL;
}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    SCM_Ticks++;
    TCNT0 = 6;
    SCM_vidHandler();
}