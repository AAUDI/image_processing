#include "image.h"

uint8_t mask_gradient_x[N_MASK][N_MASK] =
                {
                {0, 0, 0},
                {0, 1, -1}, 
                {0, 0, 0}
                };

uint8_t mask_gradient_y[N_MASK][N_MASK] =
                {
                {0, 0, 0},
                {0, 1, 0}, 
                {0, -1, 0}
                };


uint8_t mask_gradient_laplacien[N_MASK][N_MASK] =
                {
                {0, 1, 0},
                {1, -4, 1}, 
                {0, 1, 0}
                };
                


int main(int argc, char** argv){

    char* name_image = "../images/image_drone.pgm";

    FILE* file_image = NULL;
    int width_image = 0, height_image = 0;
    char header[] = "";

    uint8_t** tab_im = read_image_pgm_P5(file_image, header, &width_image, &height_image, name_image);
    write_image_pgm_P5(tab_im, height_image, width_image, "img_drone.pgm");
    /*uint8_t** tab_im_rot_plus_90 = rotate_image_plus_90(tab_im, height_image, width_image);
    write_image_pgm_P5(tab_im_rot_plus_90, width_image, height_image, "img_drone_rot_plus_90.pgm");
    uint8_t** tab_im_rot_minus_90 = rotate_image_minus_90(tab_im, height_image, width_image);
    write_image_pgm_P5(tab_im_rot_minus_90, width_image, height_image, "img_drone_rot_minus_90.pgm");
    uint8_t** tab_im_mirr_horiz = mirror_image_horiz(tab_im, height_image, width_image);
    write_image_pgm_P5(tab_im_mirr_horiz, height_image, width_image, "img_drone_mirr_hor.pgm");
    uint8_t** tab_im_mirr_verti = mirror_image_verti(tab_im, height_image, width_image);
    write_image_pgm_P5(tab_im_mirr_verti, height_image, width_image, "img_drone_mirr_vert.pgm");
    */

    uint8_t** tab_im_mask_gradient_x = apply_filter_image(tab_im, height_image, width_image, mask_gradient_x);
    write_image_pgm_P5(tab_im_mask_gradient_x, height_image, width_image, "tab_im_mask_gradient_x.pgm");

   /* uint8_t** tab_im_mask_gradient_y = apply_filter_image(tab_im, height_image, width_image, mask_gradient_y);
    write_image_pgm_P5(tab_im_mask_gradient_y, height_image, width_image, "tab_im_mask_gradient_y.pgm");

    uint8_t** tab_im_mask_gradient_laplacien = apply_filter_image(tab_im, height_image, width_image, mask_gradient_laplacien);
    write_image_pgm_P5(tab_im_mask_gradient_laplacien, height_image, width_image, "tab_im_mask_gradient_laplacien.pgm");
    */
    //uint8_t** tab_inv_im = inverse_image(tab_im, height_image, width_image);
    //write_image_pgm_P5(tab_inv_im, height_image, width_image, "img_dron_inv.pgm");

    uint8_t** tab_im_grad = norme_gradient(tab_im, height_image, width_image);
    write_image_pgm_P5(tab_im_grad, height_image, width_image, "img_drone_gradient.pgm");

    free_image(tab_im, height_image);
    /*free_image(tab_im_rot_plus_90, width_image);
    free_image(tab_im_rot_minus_90, width_image);
    free_image(tab_im_mirr_horiz, height_image);
    free_image(tab_im_mirr_verti, height_image);
    */
    free_image(tab_im_mask_gradient_x, height_image);
   // free_image(tab_im_mask_gradient_y, height_image);
   // free_image(tab_im_mask_gradient_laplacien, height_image);

    free_image(tab_im_grad, height_image);
   //free_image(tab_inv_im, height_image);
}
