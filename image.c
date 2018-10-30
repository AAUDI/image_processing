#include "image.h"


uint8_t** malloc_image(int height, int width){	
	uint8_t** im = (uint8_t**)malloc(height*sizeof(uint8_t*));
	for(int j=0; j<height; j++){
		if ((im[j] = (uint8_t*)malloc(width*sizeof(uint8_t))) == NULL){
			printf("error while allocating memory\n");
			exit(1);
		}
	}
	return im;
}


void free_image(uint8_t** tab_image, int height){
	for(int j=0; j<height; j++)
		free(tab_image[j]);
	free(tab_image);
}


uint8_t** read_image_pgm_P5(FILE* file_image, char* header, int* width, int* height, char* name_file){

	char chaine[TAILLE_MAXIMUM] = "";
	char commentaires[TAILLE_MAXIMUM] = "";
	int value_px_image = 0;
	file_image = fopen(name_file, "r");
	uint8_t** tab_image = NULL; 

	if (file_image == NULL){
			printf("Impossible to open IMAGE %s\n", name_file);
			exit(EXIT_FAILURE);
	}

	if (fgets(chaine,TAILLE_MAXIMUM,file_image) != NULL){
		sscanf(chaine, "%s", header);
        printf("header : %s\n", header);
	}
	if (fgets(chaine,TAILLE_MAXIMUM,file_image) != NULL){
		sscanf(chaine, "%s", commentaires);
        printf("comments : %s\n", commentaires);
	}	 
	if (fgets(chaine,TAILLE_MAXIMUM,file_image) != NULL){
		sscanf(chaine, "%d %d", width, height);
        printf("width : %d | height : %d\n", *width, *height);
    }
	if (fgets(chaine,TAILLE_MAXIMUM,file_image) != NULL){
		sscanf(chaine, "%d", &value_px_image);
        printf("value_px_image %d\n", value_px_image);
	}
	
	tab_image = malloc_image(*height, *width);
		
	for(int j=0; j<*height; j++)
		fread(tab_image[j], sizeof(uint8_t), *width, file_image);

	printf("header %s width %d height %d pixel value de l'image %d\n", header, *width, *height, value_px_image);
	return tab_image;
}


void write_image_pgm_P5(uint8_t** tab_image, int height, int width, char* name_file){

	FILE* file_image = NULL;
	file_image = fopen(name_file, "wb");

	if (file_image == NULL){
		printf("Impossible d'ouvrir le fichier image\n");
		exit(EXIT_FAILURE);		
	}

	printf("Please wait : writing image in process...\n");
	fprintf(file_image, "%s\n", "P5"); 
	fprintf(file_image, "%d %d\n", width, height);
	fprintf(file_image, "%d\n", 255);

	for(int j=0; j<height; j++){
		fwrite(tab_image[j], sizeof(uint8_t), width, file_image);
	}
	printf("image was written\n");
	fclose(file_image);
}

uint8_t** rotate_image_plus_90(uint8_t** im, int height, int width){
	uint8_t** img_rot = malloc_image(width, height);
	for(int j=0; j<width; j++)
		for(int i=0; i<height; i++)
			img_rot[width-j-1][i] = im[i][j];
	return img_rot;
}

uint8_t** rotate_image_minus_90(uint8_t** im, int height, int width){
	uint8_t** img_rot = malloc_image(width, height);
	for(int j=0; j<width; j++)
		for(int i=0; i<height; i++)
			img_rot[j][i] = im[i][j];
	return img_rot;
}


uint8_t** mirror_image_horiz(uint8_t** im, int height, int width){
	uint8_t** img_mirror = malloc_image(height, width);
	for(int j=0; j<height; j++)
		for(int i=0; i<width; i++)
			img_mirror[j][i] = im[j][width-i-1];
	return img_mirror;
}


uint8_t** mirror_image_verti(uint8_t** im, int height, int width){
	uint8_t** img_mirror = malloc_image(height, width);
	for(int j=0; j<height; j++)
		for(int i=0; i<width; i++)
			img_mirror[j][i] = im[height-j-1][i];
	return img_mirror;
}


uint8_t** apply_filter_image(uint8_t** im, int height, int width, uint8_t mask[N_MASK][N_MASK]){
	uint8_t** filtered_img = malloc_image(height, width);
	int tmp=0;
	for(int j=N_MASK/2; j<height-N_MASK/2; j++){
		for(int i=N_MASK/2; i<width-N_MASK/2; i++){
			for(int k=-N_MASK/2; k<=N_MASK/2; k++){
				for(int l=-N_MASK/2; l<=N_MASK/2; l++){
					tmp += im[j + k][i + l] * mask[k + N_MASK/2][l + N_MASK/2];
				}
			}
			//printf("tmp %d\n", tmp);
			filtered_img[j][i] = tmp;
			tmp = 0;
		}
	}
	return filtered_img;
}


uint8_t** norme_gradient(uint8_t** im, int height, int width){

	uint8_t** gradient_im = malloc_image(height, width);
	int gradient_x = 0;
	int gradient_y = 0;
	float norme_gradient = 0.0;
	for(int j=0; j<height-1; j++){
		for(int i=0; i<width-1; i++){
			gradient_x = abs(im[j][i+1] - im[j][i]);
			gradient_y = abs(im[j+1][i] - im[j][i]);
			norme_gradient = sqrt(gradient_x*gradient_x + gradient_y*gradient_y);
			//printf("im[j][i] %d im[j][i+1] %d im[j+1][i] %d\n", im[j][i], im[j][i+1], im[j+1][i]);
			//printf("gradient_x %d gradient_y %d norme_gradient %f\n", gradient_x, gradient_y, norme_gradient);
			gradient_im[j][i] = 10*floor(norme_gradient);
		}
	}
	
	return gradient_im;

}



uint8_t** inverse_image(uint8_t** im, int height, int width){
	uint8_t** inv_img = malloc_image(height, width);
	for(int j=0; j<height; j++)
		for(int i=0; i<width; i++)
			inv_img[j][i] = 255 - im[j][i];
	return inv_img; 
}


uint8_t** contrast_image(uint8_t** im, int height, int width, int pourcentage){
	uint8_t mask[N_MASK][N_MASK];

	for(int j=0; j<N_MASK/2; j++)
		for(int i=0; i<N_MASK/2; i++)
			mask[j][i]

	uint8_t** contrast_img = malloc_image(height, width);
	contrast_img = apply_filter_image(im, height, width, mask);	
	return contrast_img;
}
