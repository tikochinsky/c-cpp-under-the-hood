#ifndef _UTH_H_
#define _UTH_H_

#include "stdbool.h"

/* Box */

struct _Box{
    double length;
    double width;
    double height;
};

typedef struct _Box Box;


void _ZNC3BoxEPKsd(Box* const box, double dim);
void _ZNC3BoxEPKsddd(Box* const box, double l, double w, double h);
void _ZNC3BoxEPKsKPK3Box(Box* const box1, const Box* const box2);
void _ZN3Box10copyAssignEPKsKPK3Box(Box* const box1, const Box* const box2);
void _ZND3BoxEPKs(Box* const box);
void _ZNK3Box5printEKPKs(const Box* const box);


/* Box Defs */

Box _ZN3Box3mulEKPKsKPK3Box(const Box* const box1, const Box* const box2);


/* Shelf */
#define _ZN5Shelf9NUM_BOXESE 3
extern const char *_ZN5Shelf7messageE;

struct _Shelf{
    Box boxes[_ZN5Shelf9NUM_BOXESE];
};

typedef struct _Shelf Shelf;

void _ZNC5ShelfEPKs(Shelf *const shelf);
void _ZND5ShelfEPKs(Shelf *const shelf);
void _ZN5Shelf6setBoxEPKsiKPK3Box(Shelf *const shelf, int index, const Box* const dims);
double _ZNK5Shelf9getVolumeEPKsiKPK3Box(const Shelf* const shelf);
void _ZNK5Shelf5printEKPKs(const Shelf* const shelf);


#endif
