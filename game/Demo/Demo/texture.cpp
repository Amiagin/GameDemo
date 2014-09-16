#include "texture.h"

Texture::Texture() {
	this->size = 0;
}

Texture::~Texture() {
	this->size = 0;
}

void Texture::load(const char *filename) {		
	glGenTextures(1,&texture_id);
	glBindTexture(GL_TEXTURE_2D,texture_id);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	load_png(filename);
	if (png_image_buf != NULL) {
	    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,png_image_width,png_image_height,0,GL_RGBA,GL_UNSIGNED_BYTE,png_image_buf);
	    free(png_image_buf);
        png_image_buf = NULL;
	} else {
        printf("warning: could not load texture %s\n",filename);
    }
}

void read_png_data(png_structp png_ptr,png_bytep data, png_size_t length) {
	if (png_get_io_ptr(png_ptr) != NULL) { // ->io_ptr
		png_size_t bytes_read = (png_size_t)fread(data,length,1,(FILE *)png_get_io_ptr(png_ptr)); // ->io_ptr
	}
}

void Texture::load_png(const char *filename) {
	png_structp png_ptr;
    png_infop png_info_ptr;
    png_byte png_color_type, png_bit_depth;
    png_bytep *row_pointers;

    unsigned char *png_image_buf_ptr;    
    int number_of_passes;
    int x, y;

	FILE *pngFile;
	char png_header[8];

	png_image_buf = NULL;

	pngFile = fopen(filename,"rb");
	if (pngFile != NULL) {
		fread(png_header,1,sizeof(png_header),pngFile);
		if (!png_sig_cmp((png_bytep)png_header, 0, 8)) {
			png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
			if (png_ptr) {
				png_info_ptr = png_create_info_struct(png_ptr);
				if (png_info_ptr) {
					if (!setjmp(png_jmpbuf(png_ptr))) {
						png_set_read_fn(png_ptr, pngFile,read_png_data);
						png_set_sig_bytes(png_ptr, 8);
						png_read_info(png_ptr, png_info_ptr);

						png_image_width = png_get_image_width(png_ptr, png_info_ptr);
						png_image_height = png_get_image_height(png_ptr, png_info_ptr);
						png_color_type = png_get_color_type(png_ptr, png_info_ptr);
						png_bit_depth = png_get_bit_depth(png_ptr, png_info_ptr);
						
						number_of_passes = png_set_interlace_handling(png_ptr);
						png_read_update_info(png_ptr, png_info_ptr);						

						if (!setjmp(png_jmpbuf(png_ptr))) {
							row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * png_image_height);
                            if (row_pointers != NULL) {
                                y = 0;
                                while (y < png_image_height) {
                                    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, png_info_ptr));
                                    y++;
                                }
                                
                                png_read_image(png_ptr, row_pointers);
                                
                                png_image_buf = (unsigned char *)malloc(png_image_width*png_image_height*4);
                                if (png_image_buf != NULL) {
                                    png_image_buf_ptr = png_image_buf;
                                    
                                    y = 0;
                                    while (y < png_image_height) {
                                        png_byte *png_row = row_pointers[y];
                                        x = 0;
                                        while (x < png_image_width) {
                                            png_byte *png_color_ptr = &(png_row[x*4]);
                                            png_image_buf_ptr[0] = png_color_ptr[0];
                                            png_image_buf_ptr[1] = png_color_ptr[1];
                                            png_image_buf_ptr[2] = png_color_ptr[2];
                                            png_image_buf_ptr[3] = png_color_ptr[3];
                                            png_image_buf_ptr += 4;
                                            x++;
                                        }
                                        y++;
                                    }
                                    if (png_ptr && png_info_ptr) {
                                        png_destroy_read_struct(&png_ptr, &png_info_ptr, NULL);
                                        png_ptr = NULL;
                                        png_info_ptr = NULL;
                                    }
                                    free (row_pointers);
                                } else {
                                    printf("warning: could not allocate more space for texture %s\n",filename);
                                }
                            }
						}
					}
				}
			}
		}
		fclose(pngFile);
	}
}

void Texture::destroy() {
	glDeleteTextures(1,&this->texture_id);
	this->texture_id = 0;
}

GLuint Texture::getId() {
	return this->texture_id;
}

int Texture::getWidth() {
	return png_image_width;
}

int Texture::getHeight() {
	return png_image_height;
}