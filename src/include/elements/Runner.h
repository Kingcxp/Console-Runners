#ifndef RUNNER
#define RUNNER


#include "../Globals.h"

typedef enum RunnerStatus {
    Idle,
    Running,
    Rolling,
    Jumping,
} RunnerStatus;

typedef enum RunnerType RunnerType;

typedef struct Runner {
    // Methods

    void                (*handleEvent)(struct Runner *this, const int key);
    void                (*update)(struct Runner *this, float deltaTime);
    void                (*render)(const struct Runner *this, const Renderer *renderer);

    void                (*die)(struct Runner *this);
    void                (*revive)(struct Runner *this);

    const Rect          (*getCollisionRect)(const struct Runner *this);
    const char          (*getCollisionChar)(const struct Runner *this, const Vector2i position);

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
                        readyToJump,
                        isDead;

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
                        frameTimer;

    Vector2f            position;
    
    RunnerStatus        status;
} Runner;

Runner *createRunner(const RunnerType type);
void destroyRunner(Runner *runner);

#endif // RUNNER