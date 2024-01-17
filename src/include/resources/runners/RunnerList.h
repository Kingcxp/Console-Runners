#ifndef RUNNER_LIST
#define RUNNER_LIST


#include "../../elements/Runner.h"
#include "basical.h"

typedef enum RunnerType {
    Basical,
    // TODO: Register more runners.
} RunnerType;

void setRunner(Runner *runner, RunnerType type) {
    if (type == Basical) {
        runner->runningFrames = BR_runningFrames;
        runner->runningColors = BR_runningColors;
        runner->runningCollisionBox = BR_runningCollisionBox;
        runner->runningSeconds = BR_runningSeconds;
        runner->runningFrameCount = BR_runningFrameCount;

        runner->rollingFrames = BR_rollingFrames;
        runner->rollingColors = BR_rollingColors;
        runner->rollingCollisionBox = BR_rollingCollisionBox;
        runner->rollingSeconds = BR_rollingSeconds;
        runner->rollingFrameCount = BR_rollingFrameCount;

        runner->jumpingFrames = BR_jumpingFrames;
        runner->jumpingColors = BR_jumpingColors;
        runner->jumpingCollisionBox = BR_jumpingCollisionBox;
        runner->jumpingFrameCount = BR_jumpingFrameCount;

        runner->deadFrames = BR_deadFrames;
        runner->deadColors = BR_deadColors;
        runner->deadFrameCount = BR_deadFrameCount;

        runner->jumpSpeed = BR_jumpSpeed;
        runner->gravity = BR_gravity;

        runner->switchTrackSpeed = BR_switchTrackSpeed;
        runner->runningSpeed = BR_runningSpeed;
    }
}

#endif // RUNNER_LIST