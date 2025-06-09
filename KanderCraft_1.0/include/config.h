#ifndef CONFIG_H
#define CONFIG_H

/***************************************************************
 *  Project:       KanderCraft
 *  Author:        Jakub Jansa
 *  License:       BSD 2-Clause License
 *
 *  Copyright (c) 2025, Jakub Jansa
 *  All rights reserved.
 *
 *  This file is part of a free software project and is licensed
 *  under the BSD 2-Clause License. See LICENSE file for details.
 ***************************************************************/

#include "world.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "player_configuration.h"
#define CONFIG_PATH "game_settings/config.txt"
#define RENDER_DISTANCE_STANDARD 5

int create_config(Player_config *data, char *WorldName);
int load_config(Player_config *data, char *WorldName);
int save_config(Player_config *data, char *WorldName);

void Centering_cursor();

#endif