#include "image.h"

int main(int argc, char** argv){
    
    char* name_image = "../images/image_drone.pgm";

    FILE* file_image = NULL;
    int width_image = 0, height_image = 0;
    char header[] = "";

    uint8_t** tab_im = read_image_pgm_P5(file_image, header, &width_image, &height_image, name_image);
    write_image_pgm_P5(tab_im, height_image, width_image, "img_drone.pgm");
    uint8_t** tab_im_rot = rotate_image_plus_90(tab_im, height_image, width_image);
    write_image_pgm_P5(tab_im_rot, width_image, height_image, "img_drone_rot.pgm");
    uint8_t** tab_im_mirr_horiz = mirror_image_horiz(tab_im, height_image, width_image);
    write_image_pgm_P5(tab_im_mirr_horiz, height_image, width_image, "img_drone_mirr_hor.pgm");
    uint8_t** tab_im_mirr_verti = mirror_image_verti(tab_im, height_image, width_image);
    write_image_pgm_P5(tab_im_mirr_verti, height_image, width_image, "img_drone_mirr_vert.pgm");
    free_image(tab_im, height_image);
    free_image(tab_im_rot, width_image);
    free_image(tab_im_mirr_horiz, height_image);
    free_image(tab_im_mirr_verti, height_image);
}
