#ifndef HEADER_H
#define HEADER_H
#include <map>
#include <mainwindow.h>

void BuildKarnaugh(Ui::MainWindow *ui); // для построения карты

typedef struct Coord // тип структуры для строк и столбцов
{
    int row;
    int column;
} TCoord;

typedef std::map <int, TCoord> Indexes; // тип для словаря НОМЕР - КОРД-Ы

Indexes coordinates34 = {{ 0,  {2, 2} }, // для 3х, 4х переменных
                        { 1,  {2, 3} },
                        { 3,  {2, 4} },
                        { 2,  {2, 5} },
                        { 4,  {3, 2} },
                        { 5,  {3, 3} },
                        { 7,  {3, 4} },
                        { 6,  {3, 5} },
                        { 12, {4, 2} },
                        { 13, {4, 3} },
                        { 15, {4, 4} },
                        { 14, {4, 5} },
                        { 8,  {5, 2} },
                        { 9,  {5, 3} },
                        { 11, {5, 4} },
                        { 10, {5, 5} }};

Indexes coordinates2 = {{ 0, {2, 2} }, // для 2х
                        { 1, {2, 3} },
                        { 2, {3, 2} },
                        { 3, {3, 3} }};


#endif // HEADER_H
