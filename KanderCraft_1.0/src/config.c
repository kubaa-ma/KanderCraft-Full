#include "../include/config.h"


int create_config(Player_config *data){
    FILE *config;

    data->render_distance = RENDER_DISTANCE_STANDARD;
    data->pos_x = 14.0f;
    data->pos_y = 52.0f;
    data->pos_z = 10.0f;

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

    fscanf(config, "RENDER DISTANCE: %d\n", &data->render_distance);
    fscanf(config, "PLAYER X POS: %f\n", &data->pos_x);
    fscanf(config, "PLAYER Z POS: %f\n", &data->pos_z);
    fscanf(config, "PLAYER Y POS: %f\n", &data->pos_y);


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