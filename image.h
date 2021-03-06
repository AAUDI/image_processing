#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdint.h>
#include "math.h"

#define TAILLE_MAXIMUM      10000
#define N_MASK              3
#define SIZE_FAST_DETECTOR  7

uint8_t** read_image_pgm_P5(FILE* file_image, char* header, int* width, int* height, char* name_file);
void write_image_pgm_P5(uint8_t** tab_image, int height, int width, char* name_file);
uint8_t** malloc_image(int height, int width);
void free_image(uint8_t** tab_image, int height);
uint8_t** rotate_image_plus_90(uint8_t** im, int height, int width);
uint8_t** rotate_image_minus_90(uint8_t** im, int height, int width);
uint8_t** mirror_image_horiz(uint8_t** im, int height, int width);
uint8_t** mirror_image_verti(uint8_t** im, int height, int width);
uint8_t** apply_filter_image(uint8_t** im, int height, int width, uint8_t mask[N_MASK][N_MASK]);
uint8_t** norme_gradient(uint8_t** im, int height, int width);
uint8_t** detect_features_FAST(uint8_t** im, int height, int width);
uint8_t** inverse_image(uint8_t** im, int height, int width);
uint8_t** contrast_image(uint8_t** im, int height, int width, int pourcentage);


#endif