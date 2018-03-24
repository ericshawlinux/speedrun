#ifndef SRUN_DEFINED
#define SRUN_DEFINED

void SpeedrunInit();
void SpeedrunEnd();
void SpeedrunRoutine();
void SpeedrunUpdateCurrentSplit();
void SpeedrunInitializeDisplay(int start);
void SpeedrunUpdateSplit(int split, char *timestr);

#endif
