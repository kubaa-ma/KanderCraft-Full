#include "../include/config.h"


int create_config(Player_config *data){
    FILE *config;

    data->render_distance = RENDER_DISTANCE_STANDARD;
    data->pos_x = 5.0f;
    data->pos_y = 14.75f;
    data->pos_z = 5.0f;

    config = fopen("game_settings/config.txt", "w");

    if(config == NULL){
        printf("The file does not exist");
        return 1;
    }

    fprintf(config, "RENDER DISTANCE: %d\nPLAYER X POS: %f\nPLAYER Z POS: %f\nPLAYER Y POS: %f", data->render_distance, data->pos_x, data->pos_z, data->pos_y);
    fclose(config);

    return 0;
}

int save_config(Player_config *data){
    FILE *config;
    
    config = fopen("game_settings/config.txt", "w");

    if(config == NULL){
        printf("The file does not exist");
        return 1;
    }

    fprintf(config, "RENDER DISTANCE: %d\nPLAYER X POS: %f\nPLAYER Z POS: %f\nPLAYER Y POS: %f", data->render_distance, data->pos_x, data->pos_z, data->pos_y);
    fclose(config);

    return 0;
}

int load_config(Player_config *data){
    FILE *config;
    char value[100];

    config = fopen("game_settings/config.txt", "r");
    
    if(config == NULL){
        printf("The file does not exist");
        return 1;
    }

    fgets(value, sizeof(value), config);

    fclose(config);

    return 0;
}