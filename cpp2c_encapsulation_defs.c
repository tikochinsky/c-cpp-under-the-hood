#include "stdio.h"
#include "cpp2c_encapsulation_defs_c.h"


void _ZNC3BoxEPKsd(Box* const box, double dim){
    box->length = dim;
    box->width = dim;
    box->height = dim;
    _ZNK3Box5printEKPKs(box);
}

void _ZNC3BoxEPKsddd(Box* const box, double l, double w, double h){
    box->length = l;
    box->width = w;
    box->height = h;
    _ZNK3Box5printEKPKs(box);
}


void _ZNC3BoxEPKsKPK3Box(Box* const box1, const Box* const box2){
    _ZN3Box10copyAssignEPKsKPK3Box(box1, box2);
}


void _ZN3Box10copyAssignEPKsKPK3Box(Box* const box1, const Box* const box2){
    box1->length = box2->length;
    box1->width = box2->width;
    box1->height = box2->height;
}


void _ZND3BoxEPKs(Box* const box){
    printf("Box destructor, %f x %f x %f\n", box->width, box->height, box->length);
}




void _ZNK3Box5printEKPKs(const Box* const box)
{
    printf("Box: %f x %f x %f\n", box->length, box->width, box->height);
}


Box _ZN3Box3mulEKPKsKPK3Box(const Box* const box1, const Box* const box2)
{
    Box ret = *box1;
    ret.width *= box2->width;
    ret.height *= box2->height;
    ret.length *= box2->length;
    return ret;
}


/* Shelf */

#define _ZN5Shelf7DEF_MSGE "The total volume held on the shelf is"
const char* _ZN5Shelf7messageE = _ZN5Shelf7DEF_MSGE;


void _ZNC5ShelfEPKs(Shelf *const shelf){}

void _ZND5ShelfEPKs(Shelf *const shelf) {
    size_t i;
    for (i = 0; i < _ZN5Shelf9NUM_BOXESE ; ++i){
        _ZND3BoxEPKs(&(shelf->boxes[i]));
    }
}


void _ZN5Shelf6setBoxEPKsiKPK3Box(Shelf *const shelf, int index, const Box* dims){
    shelf->boxes[index] = *dims;
}


double _ZNK5Shelf9getVolumeEPKsiKPK3Box(const Shelf* const shelf)
{
    size_t i;
    double vol = 0;
    for (i = 0; i < _ZN5Shelf9NUM_BOXESE; ++i){
        vol += (&shelf->boxes[i])->width * (&shelf->boxes[i])->length * (&shelf->boxes[i])->height;;
    }
    return vol;
}


void _ZNK5Shelf5printEKPKs(const Shelf* const shelf)
{
    printf("%s %f\n", _ZN5Shelf7messageE, _ZNK5Shelf9getVolumeEPKsiKPK3Box(shelf));
}



