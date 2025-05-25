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

#define RENDER_DISTANCE_STANDARD 5

int create_config(Player_config *data);
int load_config(Player_config *data);
int save_config(Player_config *data);

void Centering_cursor();

#endif