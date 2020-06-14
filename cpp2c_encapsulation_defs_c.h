#ifndef UTH_CPP2C_ENCAPSULATION_DEFS_C_H
#define UTH_CPP2C_ENCAPSULATION_DEFS_C_H

#include "stdbool.h"

/* Box */
struct _Box{
    double length;
    double width;
    double height;
};

typedef struct _Box Box;

void construct_box(const Box *box);
void construct_box_d(const Box *box, double dim);
void construct_box_d_d_d(const Box *box, double l, double w, double h);
void destruct_box(const Box *box);
Box* mul_assign_d(const Box *box, double mult);
void print_b( Box const *box);


/* Box Defs */
double getWidth(Box const* box)
{
    return box->width;
}


double getLength(Box const* box)
{
    return box->length;
}


double getHeight(Box const* box)
{
    return box->height;
}


double getVolume_b(Box const* box)
{
    return box->width * box->length * box->height;
}


Box mul_b_d(Box const* box, double mult)
{
    Box ret = *box;
    mul_assign_d(&ret, mult);
    return ret;
}


Box mul_d_b(double mult, Box const* box)
{
    return mul_b_d(box, mult);
}


bool isEqual(const Box* lhs, const Box* rhs)
{
    return lhs->width == rhs->width && lhs->height == rhs->height && lhs->length == rhs->length;
}


bool isNotEqual(const Box* lhs, const Box* rhs)
{
    return !isEqual(lhs, rhs);
}




/* Shelf */
#define NUM_BOXES 3
const char* message;

struct _Shelf{
    Box boxes[NUM_BOXES];
};

typedef struct _Shelf Shelf;

void destruct_shelf(const Shelf *shelf);
void setBox(Shelf const *shelf, int index, const Box* dims);
double getVolume_s(Shelf const *shelf);
void print_s(Shelf const *shelf);


/* Shelf Defs */

Box const* getBox(const Shelf *shelf, int index)
{
    return (shelf->boxes)[index];
}

int getNumBoxes()
{
    return NUM_BOXES;
}

void setMessage(const char* msg)
{
    message = msg;
}

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

#endif //UTH_CPP2C_ENCAPSULATION_DEFS_C_H
