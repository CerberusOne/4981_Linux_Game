/**
    Created  by Mark Tattrie    March 28, 2017
*/
#include "ZombieHand.h"

/**
 * Date: Mar 28, 2017
 * Author: Mark Tattrie
 * Function Interface: ZombieHand::ZombieHand(int32_t id) : MeleeWeapon(ZombieHandVars::TYPE,
 *       TEXTURES::SHOTGUN, ZombieHandVars::FIRESOUND, ZombieHandVars::HITSOUND,
 *       ZombieHandVars::RELOADSOUND, ZombieHandVars::EMPTYSOUND, ZombieHandVars::RANGE,
 *       ZombieHandVars::DAMAGE, ZombieHandVars::AOE, ZombieHandVars::PENETRATION, ZombieHandVars::CLIP,
 *       ZombieHandVars::CLIPMAX, ZombieHandVars::AMMO, ZombieHandVars::RELOADDELAY,
 *       ZombieHandVars::FIREDELAY, id)
 * Description:
 * Ctor for ZombieHand
 */
ZombieHand::ZombieHand(const int32_t id) : MeleeWeapon(ZombieHandVars::TYPE, TEXTURES::SHOTGUN, ZombieHandVars::FIRESOUND,
        ZombieHandVars::HITSOUND, ZombieHandVars::RELOADSOUND, ZombieHandVars::EMPTYSOUND, ZombieHandVars::RANGE,
        ZombieHandVars::DAMAGE, ZombieHandVars::AOE, ZombieHandVars::PENETRATION, ZombieHandVars::CLIP,
        ZombieHandVars::CLIPMAX, ZombieHandVars::AMMO, ZombieHandVars::RELOADDELAY, ZombieHandVars::FIREDELAY, id) {
}
