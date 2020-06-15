#include "stdio.h"
#include "cpp2c_encapsulation_defs_c.h"

void construct_box(Box * const box){
    box->length = 1;
    box->width = 1;
    box->height = 1;
    print_b(box);
}


void construct_box_d(Box* const box, double dim){
    box->length = dim;
    box->width = dim;
    box->height = dim;
    print_b(box);
}

void construct_box_d_d_d(Box* const box, double l, double w, double h){
    box->length = l;
    box->width = w;
    box->height = h;
    print_b(box);
}

void destruct_box(Box* const box){
    printf("Box destructor, %f x %f x %f\n", box->width, box->height, box->length);
}


Box* mul_assign_d(Box* const box, double mult)
{
    box->width *= mult;
    box->height *= mult;
    box->length *= mult;

    return box;
}


void print_b(const Box* const box)
{
    printf("Box: %f x %f x %f\n", box->length, box->width, box->height);
}


Box mul_b_d(const Box* const box, double mult)
{
    Box ret = *box;
    mul_assign_d(&ret, mult);
    return ret;
}

Box mul_d_b(double mult, const Box* const box)
{
    return mul_b_d(box, mult);
}


/* Shelf */

#define DEF_MSG "The total volume held on the shelf is"
const char* message = DEF_MSG;



void destruct_shelf(Shelf *const shelf) {
    size_t i;
    for (i = 0; i < NUM_BOXES ; ++i){
        destruct_box(&(shelf->boxes[i]));
    }
}


void setBox(Shelf *const shelf, int index, const Box* dims){
    shelf->boxes[index] = *dims;
}


double getVolume_s(const Shelf* const shelf)
{
    size_t i;
    double vol = 0;
    for (i = 0; i < NUM_BOXES; ++i){
        vol += (&shelf->boxes[i])->width * (&shelf->boxes[i])->length * (&shelf->boxes[i])->height;;
    }
    return vol;
}


void print_s(const Shelf* const shelf)
{
    printf("%s %f\n", message, getVolume_s(shelf));
}



