//
// Created by adven on 2024/4/6.
//
#include "Equipment/Weapon/EntityBroadsword.h"

//ToolSystem::EntityBroadsword::EntityBroadsword()
//    : TBaseWeapon(normal, blood, glass, golden, "1-3", titanium,
//                  ImagePath.c_str()) {};

ToolSystem::EntityBroadsword::EntityBroadsword()
    : TBaseWeapon(ASSETS_DIR "/items/weapon_broadsword.png", normal, blood, glass, golden){};
