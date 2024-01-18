#ifndef PICKUP_LIST
#define PICKUP_LIST


#include "../../elements/PickUp.h"
#include "Coin.h"

typedef enum PickUpType {
    PickUp_Coin,
    PickUp_Count,
    // TODO: Register more pickups.
} PickUpType;

void setPickUp(PickUp *pickup, PickUpType type) {
    if (type == PickUp_Coin) {
        pickup->frame = Coin_frame;
        pickup->colors = Coin_colors;
        pickup->collisionBox = Coin_collisionBox;
        pickup->height = Coin_height;
    }
}

#endif // PICKUP_LIST