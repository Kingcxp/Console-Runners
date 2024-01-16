#ifndef RUNNER_H
#define RUNNER_H


#include "../Globals.h"
#include "../basics/boxchar/boxchar.h"


const Vector2f distPerChar = {1.f, 2.f};

typedef enum RunnerStatus {
    Idle,
    Running,
    Rolling,
    Jumping,
} RunnerStatus;

typedef struct Runner {
    // Methods

    // Variables

    const wchar_t   (*runningFrames)[4][4],
                    (*rollingFrames)[4][4],
                    (*jumpingFrames)[4][4],
                    (*deadFrames)[4][4];

    const Color     (*runningColors)[4][3],
                    (*rollingColors)[4][3],
                    (*jumpingColors)[4][3],
                    (*deadColors)[4][3];

    const char      (*runningCollisionBox)[4][4],
                    (*rollingCollisionBox)[4][4],
                    (*jumpingCollisionBox)[4][4];

    short           runningFrameCount,
                    rollingFrameCount,
                    jumpingFrameCount,
                    deadFrameCount;

    const float     *runningSeconds,
                    *rollingSeconds;

    float           jumpSpeed,
                    jumpVelocity,
                    jumpAcceleration,
                    jumpDelta;

    Vector2f        position;

    float           switchTrackSpeed,
                    runningSpeed;

    RunnerStatus    status;
} Runner;

#endif // RUNNER_H