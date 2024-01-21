#ifndef RUNNER_LIST
#define RUNNER_LIST


#include "../../elements/Runner.h"
#include "Basical.h"
#include "Rainbow.h"
#include "Kid.h"
#include "Hat.h"
#include "Steel.h"
#include "Triangle.h"
#include "Final.h"

typedef enum RunnerType {
    Runner_Basical,
    Runner_Rainbow,
    Runner_Kid,
    Runner_Hat,
    Runner_Triangle,
    Runner_Steel,
    Runner_Final,
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
    } else if (type == Runner_Rainbow) {
        runner->runningFrames = RR_runningFrames;
        runner->runningColors = RR_runningColors;
        runner->runningCollisionBox = RR_runningCollisionBox;
        runner->runningSeconds = RR_runningSeconds;
        runner->runningFrameCount = RR_runningFrameCount;

        runner->rollingFrames = RR_rollingFrames;
        runner->rollingColors = RR_rollingColors;
        runner->rollingCollisionBox = RR_rollingCollisionBox;
        runner->rollingSeconds = RR_rollingSeconds;
        runner->rollingFrameCount = RR_rollingFrameCount;

        runner->jumpingFrames = RR_jumpingFrames;
        runner->jumpingColors = RR_jumpingColors;
        runner->jumpingCollisionBox = RR_jumpingCollisionBox;
        runner->jumpingFrameCount = RR_jumpingFrameCount;

        runner->deadFrames = RR_deadFrames;
        runner->deadColors = RR_deadColors;
        runner->deadFrameCount = RR_deadFrameCount;

        runner->jumpSpeed = RR_jumpSpeed;
        runner->gravity = RR_gravity;

        runner->switchTrackSpeed = RR_switchTrackSpeed;
        runner->runningSpeed = RR_runningSpeed;

        runnerNames[Runner_Rainbow] = RR_name;
        runnerDescriptions[Runner_Rainbow] = RR_description;
        runnerComments[Runner_Rainbow] = RR_comment;
        runnerPrices[Runner_Rainbow] = RR_price;
    } else if (type == Runner_Kid) {
        runner->runningFrames = Kid_runningFrames;
        runner->runningColors = Kid_runningColors;
        runner->runningCollisionBox = Kid_runningCollisionBox;
        runner->runningSeconds = Kid_runningSeconds;
        runner->runningFrameCount = Kid_runningFrameCount;

        runner->rollingFrames = Kid_rollingFrames;
        runner->rollingColors = Kid_rollingColors;
        runner->rollingCollisionBox = Kid_rollingCollisionBox;
        runner->rollingSeconds = Kid_rollingSeconds;
        runner->rollingFrameCount = Kid_rollingFrameCount;

        runner->jumpingFrames = Kid_jumpingFrames;
        runner->jumpingColors = Kid_jumpingColors;
        runner->jumpingCollisionBox = Kid_jumpingCollisionBox;
        runner->jumpingFrameCount = Kid_jumpingFrameCount;

        runner->deadFrames = Kid_deadFrames;
        runner->deadColors = Kid_deadColors;
        runner->deadFrameCount = Kid_deadFrameCount;

        runner->jumpSpeed = Kid_jumpSpeed;
        runner->gravity = Kid_gravity;

        runner->switchTrackSpeed = Kid_switchTrackSpeed;
        runner->runningSpeed = Kid_runningSpeed;

        runnerNames[Runner_Kid] = Kid_name;
        runnerDescriptions[Runner_Kid] = Kid_description;
        runnerComments[Runner_Kid] = Kid_comment;
        runnerPrices[Runner_Kid] = Kid_price;
    } else if (type == Runner_Hat) {
        runner->runningFrames = Hat_runningFrames;
        runner->runningColors = Hat_runningColors;
        runner->runningCollisionBox = Hat_runningCollisionBox;
        runner->runningSeconds = Hat_runningSeconds;
        runner->runningFrameCount = Hat_runningFrameCount;

        runner->rollingFrames = Hat_rollingFrames;
        runner->rollingColors = Hat_rollingColors;
        runner->rollingCollisionBox = Hat_rollingCollisionBox;
        runner->rollingSeconds = Hat_rollingSeconds;
        runner->rollingFrameCount = Hat_rollingFrameCount;

        runner->jumpingFrames = Hat_jumpingFrames;
        runner->jumpingColors = Hat_jumpingColors;
        runner->jumpingCollisionBox = Hat_jumpingCollisionBox;
        runner->jumpingFrameCount = Hat_jumpingFrameCount;

        runner->deadFrames = Hat_deadFrames;
        runner->deadColors = Hat_deadColors;
        runner->deadFrameCount = Hat_deadFrameCount;

        runner->jumpSpeed = Hat_jumpSpeed;
        runner->gravity = Hat_gravity;

        runner->switchTrackSpeed = Hat_switchTrackSpeed;
        runner->runningSpeed = Hat_runningSpeed;

        runnerNames[Runner_Hat] = Hat_name;
        runnerDescriptions[Runner_Hat] = Hat_description;
        runnerComments[Runner_Hat] = Hat_comment;
        runnerPrices[Runner_Hat] = Hat_price;
    } else if (type == Runner_Steel) {
        runner->runningFrames = Steel_runningFrames;
        runner->runningColors = Steel_runningColors;
        runner->runningCollisionBox = Steel_runningCollisionBox;
        runner->runningSeconds = Steel_runningSeconds;
        runner->runningFrameCount = Steel_runningFrameCount;

        runner->rollingFrames = Steel_rollingFrames;
        runner->rollingColors = Steel_rollingColors;
        runner->rollingCollisionBox = Steel_rollingCollisionBox;
        runner->rollingSeconds = Steel_rollingSeconds;
        runner->rollingFrameCount = Steel_rollingFrameCount;

        runner->jumpingFrames = Steel_jumpingFrames;
        runner->jumpingColors = Steel_jumpingColors;
        runner->jumpingCollisionBox = Steel_jumpingCollisionBox;
        runner->jumpingFrameCount = Steel_jumpingFrameCount;

        runner->deadFrames = Steel_deadFrames;
        runner->deadColors = Steel_deadColors;
        runner->deadFrameCount = Steel_deadFrameCount;

        runner->jumpSpeed = Steel_jumpSpeed;
        runner->gravity = Steel_gravity;

        runner->switchTrackSpeed = Steel_switchTrackSpeed;
        runner->runningSpeed = Steel_runningSpeed;

        runnerNames[Runner_Steel] = Steel_name;
        runnerDescriptions[Runner_Steel] = Steel_description;
        runnerComments[Runner_Steel] = Steel_comment;
        runnerPrices[Runner_Steel] = Steel_price;
    } else if (type == Runner_Triangle) {
        runner->runningFrames = TR_runningFrames;
        runner->runningColors = TR_runningColors;
        runner->runningCollisionBox = TR_runningCollisionBox;
        runner->runningSeconds = TR_runningSeconds;
        runner->runningFrameCount = TR_runningFrameCount;

        runner->rollingFrames = TR_rollingFrames;
        runner->rollingColors = TR_rollingColors;
        runner->rollingCollisionBox = TR_rollingCollisionBox;
        runner->rollingSeconds = TR_rollingSeconds;
        runner->rollingFrameCount = TR_rollingFrameCount;

        runner->jumpingFrames = TR_jumpingFrames;
        runner->jumpingColors = TR_jumpingColors;
        runner->jumpingCollisionBox = TR_jumpingCollisionBox;
        runner->jumpingFrameCount = TR_jumpingFrameCount;

        runner->deadFrames = TR_deadFrames;
        runner->deadColors = TR_deadColors;
        runner->deadFrameCount = TR_deadFrameCount;

        runner->jumpSpeed = TR_jumpSpeed;
        runner->gravity = TR_gravity;

        runner->switchTrackSpeed = TR_switchTrackSpeed;
        runner->runningSpeed = TR_runningSpeed;

        runnerNames[Runner_Triangle] = TR_name;
        runnerDescriptions[Runner_Triangle] = TR_description;
        runnerComments[Runner_Triangle] = TR_comment;
        runnerPrices[Runner_Triangle] = TR_price;
    } else if (type == Runner_Final) {
        runner->runningFrames = Final_runningFrames;
        runner->runningColors = Final_runningColors;
        runner->runningCollisionBox = Final_runningCollisionBox;
        runner->runningSeconds = Final_runningSeconds;
        runner->runningFrameCount = Final_runningFrameCount;

        runner->rollingFrames = Final_rollingFrames;
        runner->rollingColors = Final_rollingColors;
        runner->rollingCollisionBox = Final_rollingCollisionBox;
        runner->rollingSeconds = Final_rollingSeconds;
        runner->rollingFrameCount = Final_rollingFrameCount;

        runner->jumpingFrames = Final_jumpingFrames;
        runner->jumpingColors = Final_jumpingColors;
        runner->jumpingCollisionBox = Final_jumpingCollisionBox;
        runner->jumpingFrameCount = Final_jumpingFrameCount;

        runner->deadFrames = Final_deadFrames;
        runner->deadColors = Final_deadColors;
        runner->deadFrameCount = Final_deadFrameCount;

        runner->jumpSpeed = Final_jumpSpeed;
        runner->gravity = Final_gravity;

        runner->switchTrackSpeed = Final_switchTrackSpeed;
        runner->runningSpeed = Final_runningSpeed;

        runnerNames[Runner_Final] = Final_name;
        runnerDescriptions[Runner_Final] = Final_description;
        runnerComments[Runner_Final] = Final_comment;
        runnerPrices[Runner_Final] = Final_price;
    }
}

#endif // RUNNER_LIST
