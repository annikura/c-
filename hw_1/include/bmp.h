#ifndef HW_1_BMP_H
#define HW_1_BMP_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct bmpFileHeader{
    int16_t file_type;      // header field used to identify the BMP and DIB file is 0x42 0x4D in hexadecimal
    int32_t file_size;      // size of the BMP file in bytes
    int32_t reserved;       // actual value depends on the application that creates the image
    int32_t offset;         // starting address, of the byte where the bitmap image data (pixel array) can be found
} bmpFileHeader_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct bmpInfoHeader{
    uint32_t info_header_size;       // size of that header
    int32_t  bmp_width;              // bitmap width in pixels
    int32_t  bmp_height;             // bitmap height in pixels
    uint16_t color_planes_cnt;       // must be 1
    uint16_t color_depth;            // in bits_per_px
    uint32_t compression;            // compression method
    uint32_t bitmap_data_size;       // size of the raw bitmap data
    int32_t  hor_resolution;         // px per meter
    int32_t  ver_resolution;         // px per meter
    uint32_t colors_cnt;             // number of colors in the color palette of 0 to default to 2^bitmap_data_size
    uint32_t important_colors_cnt;   // number of important colors, when 0 every color is important
} bmpInfoHeader_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct bmp{
    bmpFileHeader_t file_header;
    bmpInfoHeader_t info_header;
    uint8_t ***pixels;
}bmp_t;
#pragma pack(pop)

void load_bmp(char const *filename, bmp_t *bmp);
void save_bmp(char const *filename, bmp_t *bmp);
void delete_px_matrix(bmp_t *bmp);
void crop(bmp_t *bmp, int32_t x, int32_t y, int32_t height, int32_t width);
void rotate(bmp_t *bmp);

#endif //HW_1_BMP_H
