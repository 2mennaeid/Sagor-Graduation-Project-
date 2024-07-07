/*****************                     *****************************************/
/***************** Name : Menna Eid    ****************************************/
/***************** Date: 8/18/2023     ***************************************/
/***************** Version: 1.0        **************************************/
/***************** SWC: Bit math       *************************************/
#ifndef BIT_MATH_h
#define BIT_MATH_h

#define SET_BIT(PORT,PIT)          (PORT |= (1<<PIT))
#define CLEAR_BIT(PORT,PIT)        (PORT &= ~(1<<PIT))
#define READ_BIT(PORT,PIT)         ((PORT>>PIT)&1)
#define TOOGLE_BIT(PORT,PIT)       (PORT ^= (1<<PIT))
#define MASKING_BIT(PORT,PIT)      (PORT &= ~(1<<PIT))
#endif
