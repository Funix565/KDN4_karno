#ifndef HEADER_H
#define HEADER_H
#include <map>

typedef struct Coord
{
    int row;
    int column;
} TCoord;

typedef std::map <int, TCoord> Indexes;


#endif // HEADER_H
