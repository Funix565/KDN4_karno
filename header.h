#ifndef HEADER_H
#define HEADER_H
#include <map>
#include <mainwindow.h>

void BuildKarnaugh(Ui::MainWindow *ui);

typedef struct Coord
{
    int row;
    int column;
} TCoord;

typedef std::map <int, TCoord> Indexes;

Indexes coordinates = {{ 0,  {0, 0} },
                       { 1,  {0, 1} },
                       { 3,  {0, 2} },
                       { 2,  {0, 3} },
                       { 4,  {1, 0} },
                       { 5,  {1, 1} },
                       { 7,  {1, 2} },
                       { 6,  {1, 3} },
                       { 12, {2, 0} },
                       { 13, {2, 1} },
                       { 15, {2, 2} },
                       { 14, {2, 3} },
                       { 8,  {3, 0} },
                       { 9,  {3, 1} },
                       { 11, {3, 2} },
                       { 10, {3, 3} }};


#endif // HEADER_H
