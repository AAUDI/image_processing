#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdint.h>

#define TAILLE_MAXIMUM 10000


uint8_t** read_image_pgm_P5(FILE* file_image, char* header, int* width, int* height, char* name_file);
void write_image_pgm_P5(uint8_t** tab_image, int height, int width, char* name_file);
uint8_t** malloc_image(int height, int width);
void free_image(uint8_t** tab_image, int height);
uint8_t** rotate_image_plus_90(uint8_t** im, int height, int width);
uint8_t** rotate_image_minus_90(uint8_t** im, int height, int width);
uint8_t** mirror_image_horiz(uint8_t** im, int height, int width);
uint8_t** mirror_image_verti(uint8_t** im, int height, int width);


#endif