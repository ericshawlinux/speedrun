/* srun_timer.h
 *  
 * Created by Eric Shaw Jr on 2018-03-23
 * Copyright (c) 2018 Eric Shaw Jr.
 * 
 * This file is part of speedrun. It is subject to the license terms
 * in the LICENSE file found in the top-level directory of this distribution.
 * No part of speedrun, including this file, may be copied, modified, propagated,
 * or distributed except according to the terms contained in the LICENSE file.
 */

#ifndef SRUN_TIMER_DEFINED
#define SRUN_TIMER_DEFINED

void SpeedrunSetTimerStart();
void SpeedrunGetTimeString(char *, size_t);
void SpeedrunSimplestFormFromTimespec(struct timespec, int *h, int *m, int *s, int *ms);

#endif
