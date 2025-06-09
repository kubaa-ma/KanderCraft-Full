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

#include "../include/config.h"


int create_config(Player_config *data, char *WorldName){
    FILE *config;

    data->render_distance = RENDER_DISTANCE_STANDARD;
    data->pos_x = (CHUNK_WIDTH*TOTAL_CHUNKS) / 2;
    data->pos_y = 52;
    data->pos_z = (CHUNK_LENGTH*TOTAL_CHUNKS) / 2;

    data->tar_x = 0;
    data->tar_y = 0;
    data->tar_z = 0;

   data->fovy = 54;

   char path[256];
   sprintf(path, "WorldFiles/%s/%s", WorldName, CONFIG_PATH);
    printf("%s", path);
    config = fopen(path, "w");

    if(config == NULL){
        printf("The file does not exist");
        return 1;
    }

    fprintf(config, "RENDER DISTANCE: %d\n", data->render_distance);
    fprintf(config, "PLAYER X POS: %f\n", data->pos_x);
    fprintf(config, "PLAYER Z POS: %f\n", data->pos_z);
    fprintf(config, "PLAYER Y POS: %f\n", data->pos_y);
    fprintf(config, "PLAYER X TAR: %f\n", data->tar_x);
    fprintf(config, "PLAYER Y TAR: %f\n", data->tar_y);
    fprintf(config, "PLAYER Z TAR: %f\n", data->tar_z);
    fprintf(config, "PLAYER FOVY SET: %f\n", data->fovy);      
    fclose(config);
    return 0;
}

int save_config(Player_config *data, char *WorldName){
    FILE *config;
    
    char path[256];
    sprintf(path, "WorldFiles/%s/%s", WorldName, CONFIG_PATH);
    config = fopen(path, "w");

    if(config == NULL){
        printf("The file does not exist");
        return 1;
    }

    fprintf(config, "RENDER DISTANCE: %d\n", data->render_distance);
    fprintf(config, "PLAYER X POS: %f\n", data->pos_x);
    fprintf(config, "PLAYER Z POS: %f\n", data->pos_z);
    fprintf(config, "PLAYER Y POS: %f\n", data->pos_y);
    fprintf(config, "PLAYER X TAR: %f\n", data->tar_x);
    fprintf(config, "PLAYER Y TAR: %f\n", data->tar_y);
    fprintf(config, "PLAYER Z TAR: %f\n", data->tar_z);
    fprintf(config, "PLAYER FOVY SET: %f\n", data->fovy);      
    fclose(config);

    return 0;
}

int load_config(Player_config *data, char *WorldName){
    FILE *config;
    char path[256];
    sprintf(path, "WorldFiles/%s/%s", WorldName, CONFIG_PATH);
    config = fopen(path, "r");
    
    if(config == NULL){
        return 1;
    }

    char line[128];

    fgets(line, sizeof(line), config);
    sscanf(line, "RENDER DISTANCE: %d", &data->render_distance);

    fgets(line, sizeof(line), config);
    sscanf(line, "PLAYER X POS: %f", &data->pos_x);

    fgets(line, sizeof(line), config);
    sscanf(line, "PLAYER Z POS: %f", &data->pos_z);

    fgets(line, sizeof(line), config);
    sscanf(line, "PLAYER Y POS: %f", &data->pos_y);

    fgets(line, sizeof(line), config);
    sscanf(line, "PLAYER X TAR: %f", &data->tar_x);

    fgets(line, sizeof(line), config);
    sscanf(line, "PLAYER Y TAR: %f", &data->tar_y);

    fgets(line, sizeof(line), config);
    sscanf(line, "PLAYER Z TAR: %f", &data->tar_z);

    fgets(line, sizeof(line), config);
    sscanf(line, "PLAYER FOVY SET: %f", &data->fovy);

    fclose(config);

    return 0;
}

void Centering_cursor(){
    int reserve = 800;
    Vector2 mousePos = GetMousePosition();
    Vector2 screenCenter = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    if (mousePos.x < screenCenter.x - reserve) {
        SetMousePosition(screenCenter.x - reserve, mousePos.y);
    } else if (mousePos.x > screenCenter.x + reserve) {
        SetMousePosition(screenCenter.x + reserve, mousePos.y);
    }

    if (mousePos.y < screenCenter.y - reserve) {
        SetMousePosition(mousePos.x, screenCenter.y - reserve);
    } else if (mousePos.y > screenCenter.y + reserve) {
        SetMousePosition(mousePos.x, screenCenter.y + reserve);
    }
    if (mousePos.x <= screenCenter.x - reserve || mousePos.x >= screenCenter.x + reserve ||
        mousePos.y <= screenCenter.y - reserve || mousePos.y >= screenCenter.y + reserve) {
        SetMousePosition(screenCenter.x, screenCenter.y);
        HideCursor();

    }
}