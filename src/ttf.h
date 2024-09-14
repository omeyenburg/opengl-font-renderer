#ifndef TTF_H
#define TTF_H

// #include "tables/glyf.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint16_t unicode;
    uint16_t index;
} CharacterMap;

typedef struct {
    bool initialized;
    uint32_t checkSum;
    uint32_t offset;
    uint32_t length;
} Table;

typedef struct {
    int16_t x;
    int16_t y;
    bool onCurve;
} Point;

typedef struct {
    int16_t numberOfContours;
    int16_t xMin;
    int16_t yMin;
    int16_t xMax;
    int16_t yMax;
    uint32_t numPoints;
    Point* points;
    uint16_t* endPtsOfContours;
} Glyph;

#define getInt16(buffer, offset)                                                       \
    (((unsigned char) buffer[offset] << 8) | ((unsigned char) buffer[offset + 1]))
#define getInt24(buffer, offset)                                                       \
    ((unsigned char) buffer[offset] << 16) |                                           \
        ((unsigned char) buffer[offset + 1] << 8) |                                    \
        ((unsigned char) buffer[offset + 2])
#define getInt32(buffer, offset)                                                       \
    (((unsigned char) buffer[offset] << 24) |                                          \
     ((unsigned char) buffer[offset + 1] << 16) |                                      \
     ((unsigned char) buffer[offset + 2] << 8) | ((unsigned char) buffer[offset + 3]))

bool validateCheckSum(unsigned char* buffer, Table* table, uint32_t adjustment);
void load(char* path);
int16_t parse_head(unsigned char* buffer, Table* head);
uint16_t parse_maxp(unsigned char* buffer, Table* maxp);
void parse_loca(uint32_t* glyf_offsets,
                unsigned char* buffer,
                Table* loca,
                uint16_t numGlyphs,
                int16_t indexToLocFormat);
void parse_glyf(Glyph* glyphs,
                unsigned char* buffer,
                Table* glyf,
                uint32_t* glyf_offsets,
                uint16_t numGlyphs);
uint16_t get_cmap_size(unsigned char* buffer, Table* cmap);
void parse_cmap(CharacterMap* charMap,
                unsigned char* buffer,
                Table* cmap,
                uint16_t numChars);
void parse_hmtx(unsigned char* buffer, Table* hmtx);

#endif // TTF_H
