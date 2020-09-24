#include "stdio.h"
#include "cpp2c_encapsulation_defs_c.h"


static Box _ZL8largeBox;
unsigned char box99Flag = 0;
unsigned char box88Flag = 0;



static void _Z10initGlobalv(){
    _ZNC3BoxEPKsddd(&_ZL8largeBox, 10, 20, 30);
}


void Z8thisFuncv()
{
    static Box box99;
    if(box99Flag == 2){
        _ZND3BoxEPKs(&box99);
        return;
    }

    printf("\n--- thisFunc() ---\n\n");
    if(!box99Flag)
    {
        _ZNC3BoxEPKsddd(&box99, 99, 99, 99);
        box99Flag = 1;
    }

    (&box99)->width *= 10;
    (&box99)->height *= 10;
    (&box99)->length *= 10;
}

void Z8thatFuncv()
{
    static Box box88;
    if(box88Flag == 2){
        _ZND3BoxEPKs(&box88);
        return;
    }

    printf("\n--- thatFunc() ---\n\n");
    if(!box88Flag)
    {
        _ZNC3BoxEPKsddd(&box88, 99, 99, 99);
        box88Flag = 1;
    }

    (&box88)->width *= 10;
    (&box88)->height *= 10;
    (&box88)->length *= 10;
}


void _Z7doBoxesv()
{
    Box b1, b2, b3, b4, temp;


    printf("\n--- Start doBoxes() ---\n\n");

    _ZNC3BoxEPKsd(&b1, 3);
    _ZNC3BoxEPKsddd(&b2, 4, 5, 6);

    printf("b1 volume: %f\n", b1.width * b1.length * b1.height);
    printf("b2 volume: %f\n", b2.width * b2.length * b2.height);

    (&b1)->width *= 1.5;
    (&b1)->height *= 1.5;
    (&b1)->length *= 1.5;

    (&b2)->width *= 0.5;
    (&b2)->height *= 0.5;
    (&b2)->length *= 0.5;

    printf("b1 volume: %f\n", b1.width * b1.length * b1.height);
    printf("b2 volume: %f\n", b2.width * b2.length * b2.height);

    _ZN3Box10copyAssignEPKsKPK3Box(&b3, &b2);

    _ZNC3BoxEPKsd(&temp, 3);
    temp = _ZN3Box3mulEKPKsKPK3Box(&temp, &b2);
    _ZNC3BoxEPKsKPK3Box(&b4, &temp);
    _ZND3BoxEPKs(&temp);
    printf("b3 %s b4\n", b3.width == b4.width && b3.height == b4.height && b3.length == b4.length ? "equals" : "does not equal");

    (&b3)->width *= 1.5;
    (&b3)->height *= 1.5;
    (&b3)->length *= 1.5;

    (&b4)->width *= 0.5;
    (&b4)->height *= 0.5;
    (&b4)->length *= 0.5;
    printf("Now, b3 %s b4\n", b3.width == b4.width && b3.height == b4.height && b3.length == b4.length ? "equals" : "does not equal");

    printf("\n--- End doBoxes() ---\n\n");

    _ZND3BoxEPKs(&b1);
    _ZND3BoxEPKs(&b2);
    _ZND3BoxEPKs(&b3);
    _ZND3BoxEPKs(&b4);
}


void _Z9doShelvesv()
{
    size_t i;
    Box aBox, temp1, temp2;
    Shelf aShelf;

    printf("\n--- start doShelves() ---\n\n");

    _ZNC3BoxEPKsd(&aBox, 5);

    for(i=0; i<_ZN5Shelf9NUM_BOXESE; i++){
        _ZNC3BoxEPKsd(&aShelf.boxes[i], 1);
    }
    _ZNC5ShelfEPKs(&aShelf);

    _ZNK5Shelf5printEKPKs(&aShelf);
    _ZN5Shelf6setBoxEPKsiKPK3Box(&aShelf, 1, &_ZL8largeBox);
    _ZN5Shelf6setBoxEPKsiKPK3Box(&aShelf, 0, &aBox);

    _ZNK5Shelf5printEKPKs(&aShelf);
    _ZN5Shelf7messageE = "This is the total volume on the shelf:";
    _ZNK5Shelf5printEKPKs(&aShelf);
    _ZN5Shelf7messageE = "Shelf's volume:";
    _ZNK5Shelf5printEKPKs(&aShelf);

    _ZNC3BoxEPKsddd(&temp1, 2, 4, 6);
    _ZN5Shelf6setBoxEPKsiKPK3Box(&aShelf, 1, &temp1);
    _ZND3BoxEPKs(&temp1);

    _ZNC3BoxEPKsd(&temp2, 2);
    _ZN5Shelf6setBoxEPKsiKPK3Box(&aShelf, 2, &temp2);
    _ZND3BoxEPKs(&temp2);

    _ZNK5Shelf5printEKPKs(&aShelf);

    printf("\n--- end doShelves() ---\n\n");

    _ZND3BoxEPKs(&aBox);
    _ZND5ShelfEPKs(&aShelf);
}

int main()
{
    _Z10initGlobalv();
    printf("\n--- Start main() ---\n\n");

    _Z7doBoxesv();

    Z8thisFuncv();
    Z8thisFuncv();
    Z8thisFuncv();
    Z8thatFuncv();
    Z8thatFuncv();

    _Z9doShelvesv();


    printf("\n--- End main() ---\n\n");

    if(box99Flag){
        box99Flag++;
        Z8thisFuncv();
    }

    if(box88Flag){
        box88Flag++;
        Z8thatFuncv();
    }

    _ZND3BoxEPKs(&_ZL8largeBox);

    return 0;
}

