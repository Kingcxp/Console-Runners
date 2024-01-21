#ifndef PICKUP_LIST
#define PICKUP_LIST


#include "../../elements/PickUp.h"
#include "Coin.h"
#include "Invincible.h"
#include "SuperCoin.h"

typedef enum PickUpType {
    PickUp_Coin,
    PickUp_Invincible,
    PickUp_SuperCoin,
    PickUp_Count,
    // TODO: Register more pickups.
} PickUpType;

void setPickUp(PickUp *pickup, PickUpType type) {
    if (type == PickUp_Coin) {
        pickup->frame = Coin_frame;
        pickup->colors = Coin_colors;
        pickup->collisionBox = Coin_collisionBox;
        pickup->height = Coin_height;
        pickup->spawnChance = pickup->spawnChanceTotal = 0;
        pickup->takeEffect = Coin_takeEffect;
    } else if (type == PickUp_Invincible) {
        pickup->frame = Invincible_frame;
        pickup->colors = Invincible_colors;
        pickup->collisionBox = Invincible_collisionBox;
        pickup->height = Invincible_height;
        pickup->spawnChance = 2,
        pickup->spawnChanceTotal = 100;
        pickup->takeEffect = Invincible_takeEffect;
    } else if (type == PickUp_SuperCoin) {
        pickup->frame = SuperCoin_frame;
        pickup->colors = SuperCoin_colors;
        pickup->collisionBox = SuperCoin_collisionBox;
        pickup->height = SuperCoin_height;
        pickup->spawnChance = 1,
        pickup->spawnChanceTotal = 100;
        pickup->takeEffect = SuperCoin_takeEffect;
    }
}

#endif // PICKUP_LIST
