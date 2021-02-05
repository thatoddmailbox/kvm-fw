#ifndef _STM8_CLOCK_H
#define _STM8_CLOCK_H

#include "stm8/registers.h"

inline void clock_init() {
	// [7:5]: reserved, so keep it cleared
	// [4:3]: HSIDIV, set to 0 for divide by 1
	// [2:0]: CPUDIV, set to 0 for divide by 1
	*CLK_CKDIVR = 0;
}

#endif