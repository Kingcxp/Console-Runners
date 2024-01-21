#ifndef RUNNER_LIST
#define RUNNER_LIST


#include "../../elements/Runner.h"
#include "Basical.h"

typedef enum RunnerType {
    Runner_Basical,
    Runner_Count,
    // TODO: Register more runners.
} RunnerType;

const wchar_t *runnerNames[Runner_Count];
const wchar_t *runnerDescriptions[Runner_Count];
const wchar_t *runnerComments[Runner_Count];
int runnerPrices[Runner_Count];

void setRunner(Runner *runner, RunnerType type) {
    if (type == Runner_Basical) {
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

        runnerNames[Runner_Basical] = BR_name;
        runnerDescriptions[Runner_Basical] = BR_description;
        runnerComments[Runner_Basical] = BR_comment;
        runnerPrices[Runner_Basical] = BR_price;
    }
}

#endif // RUNNER_LIST
