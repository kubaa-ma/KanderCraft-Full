#ifndef CONFIG_H
#define CONFIG_H


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