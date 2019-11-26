/*
 * stm32f103_processor.h
 *
 *  Created on: 31 окт. 2019 г.
 *      Author: Ontaelio
 */

#ifndef STM32F103_PROCESSOR_H_
#define STM32F103_PROCESSOR_H_


inline static int _irqDis(void)
{
    __asm volatile ("cpsid i" : : : "memory");
    return 1;
}

inline static int _irqEn(void)
{
    __asm volatile ("cpsie i" : : : "memory");
    return 0;
}

#define ATOMIC_BLOCK_FORCEON \
    for(int flag = _irqDis();\
        flag;\
        flag = _irqEn())

inline static int _iDisGetPrimask(void)
{
    int result;
    __asm volatile ("MRS %0, primask" : "=r" (result) );
    __asm volatile ("cpsid i" : : : "memory");
    return result;
}

inline static int _iSetPrimask(int priMask)
{
    __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
    return 0;
}

#define ATOMIC_BLOCK_RESTORATE \
     for(int mask = _iDisGetPrimask(), flag = 1;\
         flag;\
         flag = _iSetPrimask(mask))


#endif /* STM32F103_PROCESSOR_H_ */
