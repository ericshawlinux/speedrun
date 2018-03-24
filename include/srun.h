/* srun.h
 *  
 * Created by Eric Shaw Jr on 2018-03-23
 * Copyright (c) 2018 Eric Shaw Jr.
 * 
 * This file is part of speedrun. It is subject to the license terms
 * in the LICENSE file found in the top-level directory of this distribution.
 * No part of speedrun, including this file, may be copied, modified, propagated,
 * or distributed except according to the terms contained in the LICENSE file.
 */

#ifndef SRUN_DEFINED
#define SRUN_DEFINED

void SpeedrunInit();
void SpeedrunEnd();
void SpeedrunRoutine();
void SpeedrunUpdateCurrentSplit();
void SpeedrunInitializeDisplay(int start);
void SpeedrunUpdateSplit(int split, char *timestr);

#endif
