#ifndef LAYER_H
#define LAYER_H

#include <QtCore>

typedef struct  {
    int number;
    QString name;
    int colorNumber;
    int fill;
    bool visible;
    bool active;
} Layer;

#endif // LAYER_H
