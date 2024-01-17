#ifndef RUNNER_H
#define RUNNER_H


#include "../Globals.h"
#include "../resources/runners/RunnerList.h"
#include "../basics/boxchar/boxchar.h"


const Vector2f distPerChar = {1.f, 2.f};

typedef enum RunnerStatus {
    Idle,
    Running,
    Rolling,
    Jumping,
} RunnerStatus;

typedef enum RunnerKeys {
    GoLeft,
    GoRight,
    Jump,
    Roll,
    KeyCount,
};
const int runnerKeyValue[] = {75, 77, 72, 80};

typedef struct Runner {
    // Methods

    void                (*handleEvent)(Runner *, const int);
    void                (*update)(Runner *, float);
    void                (*render)(const Runner *, const Renderer *);

    const CollisionBox  (*getCollisionBox)(const Runner *);

    // Variables

    const Globals       *globals;

    const wchar_t       (*runningFrames)[4][4],
                        (*rollingFrames)[4][4],
                        (*jumpingFrames)[4][4],
                        (*deadFrames)[4][4];

    const Color         (*runningColors)[4][3],
                        (*rollingColors)[4][3],
                        (*jumpingColors)[4][3],
                        (*deadColors)[4][3];

    int                 frame,
                        targetTrack;

    bool                readyToRoll,
                        readyToJump;

    const char          (*runningCollisionBox)[4][4],
                        (*rollingCollisionBox)[4][4],
                        (*jumpingCollisionBox)[4][4];

    short               runningFrameCount,
                        rollingFrameCount,
                        jumpingFrameCount,
                        deadFrameCount;

    const float         *runningSeconds,
                        *rollingSeconds;

    float               jumpSpeed,
                        jumpVelocity,
                        gravity,
                        jumpDelta,
                        trackDelta,
                        switchTrackSpeed,
                        runningSpeed,
                        frameTimer,
                        trackDistance;

    Vector2f            position;

    Vector2i            center;

    RunnerStatus        status;
} Runner;   

#endif // RUNNER_H