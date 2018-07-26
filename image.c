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
	printf("test\n");
	tab_image = malloc_image(*height, *width);
	printf("test\n");
		
	for(int j=0; j<*height; j++)
		fread(tab_image[j], sizeof(uint8_t), *width, file_image);

	printf("header %s length %d heigth %d pixel value de l'image %d\n", header, *width, *height, value_px_image);
	return tab_image;
}


void write_image_pgm_P5(uint8_t** tab_image, int height, int width, char* name_file){

	FILE* file_image = NULL;
	file_image = fopen(name_file, "wb");

	if (file_image == NULL){
		printf("Impossible d'ouvrir le fichier image\n");
		exit(EXIT_FAILURE);		
	}

	printf("En train d'ecrire...\n");
	fprintf(file_image, "%s\n", "P5"); 
	fprintf(file_image, "%d %d\n", width, height);
	fprintf(file_image, "%d\n", 255);

	for(int j=0; j<height; j++)
			fwrite(tab_image[j], sizeof(uint8_t), width, file_image);
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