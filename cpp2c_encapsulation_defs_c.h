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


void construct_box(Box* const box);
void construct_box_d(Box* const box, double dim);
void construct_box_d_d_d(Box* const box, double l, double w, double h);
void destruct_box(Box* const box);
Box* mul_assign_d(Box* const box, double mult);
void print_b(const Box* const box);


/* Box Defs */

Box mul_b_d(const Box* const box, double mult);
Box mul_d_b(double mult, const Box* const box);

/*
bool isEqual(const Box* const lhs, const Box* const rhs)
{
    return lhs->width == rhs->width && lhs->height == rhs->height && lhs->length == rhs->length;
}


bool isNotEqual(const Box* const lhs, const Box* const rhs)
{
    return !isEqual(lhs, rhs);
}*/




/* Shelf */
#define NUM_BOXES 3
const char* message;


struct _Shelf{
    Box boxes[NUM_BOXES];
};

typedef struct _Shelf Shelf;

void destruct_shelf(Shelf *const shelf);
void setBox(Shelf *const shelf, int index, const Box* const dims);
double getVolume_s(const Shelf* const shelf);
void print_s(const Shelf* const shelf);


/* Shelf Defs */
/*
Box* const getBox(const Shelf* const shelf, int index)
{
    return &(shelf->boxes[index]);
}

int getNumBoxes()
{
    return NUM_BOXES;
}

void setMessage(const char* msg)
{
    message = msg;
}*/

/*
//class Shelf
//{
//public:
//    void setBox(int index, const Box& dims);
//    double getVolume() const;
//    Box& getBox(int index);
//    void print() const;
//
//    static int getNumBoxes();
//    static void setMessage(const char* msg);
//
//private:
//    static const unsigned int NUM_BOXES = 3;
//    static const char* const DEF_MSG;
//    static const char* message;
//
//    Box boxes[NUM_BOXES];
//};*/

#endif
