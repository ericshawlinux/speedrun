/* srun_split.h
 *  
 * Created by Eric Shaw Jr on 2018-03-25
 * Copyright (c) 2018 Eric Shaw Jr.
 * 
 * This file is part of speedrun. It is subject to the license terms
 * in the LICENSE file found in the top-level directory of this distribution.
 * No part of speedrun, including this file, may be copied, modified, propagated,
 * or distributed except according to the terms contained in the LICENSE file.
 */

#ifndef SRUN_SPLIT_DEFINED
#define SRUN_SPLIT_DEFINED

int SpeedrunSplitLoadFromDisk(const char *);
void SpeedrunSplitStart();
void SpeedrunSplitNext();
void SpeedrunSplitUndo();

void SpeedrunSplitDrawEmpty(int start);
void SpeedrunSplitDraw();

#endif
