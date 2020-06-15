#include "stdio.h"
#include "cpp2c_encapsulation_defs_c.h"

static Box largeBox;

static void initGlobal(){
    construct_box_d_d_d(&largeBox, 10, 20, 30);
}

Box box99;
Box box88;


void thisFunc()
{
    static int flag = 1;
    printf("\n--- thisFunc() ---\n\n");
    if(flag)
    {
        construct_box_d_d_d(&box99, 99, 99, 99);
    }
    mul_assign_d(&box99, 10);
    flag = 0;
}

void thatFunc()
{
    static int flag = 1;
    printf("\n--- thatFunc() ---\n\n");
    if(flag)
    {
        construct_box_d_d_d(&box88, 88, 88, 88);
    }
    mul_assign_d(&box88, 10);
    flag = 0;
}

void doBoxes()
{
    Box b1;
    Box b2;
    Box b3;
    Box b4;


    printf("\n--- Start doBoxes() ---\n\n");

    construct_box_d(&b1, 3);
    construct_box_d_d_d(&b2, 4, 5, 6);

    printf("b1 volume: %f\n", (&b1)->width * (&b1)->length * (&b1)->height);
    printf("b2 volume: %f\n", (&b2)->width * (&b2)->length * (&b2)->height);

    mul_assign_d(&b1, 1.5);
    mul_assign_d(&b2, 0.5);

    printf("b1 volume: %f\n", (&b1)->width * (&b1)->length * (&b1)->height);
    printf("b2 volume: %f\n", (&b2)->width * (&b2)->length * (&b2)->height);

    b3 = b2;
    b4 = mul_d_b(3, &b2);
    printf("b3 %s b4\n", (&b3)->width == (&b4)->width && (&b3)->height == (&b4)->height && (&b3)->length == (&b4)->length ? "equals" : "does not equal");

    mul_assign_d(&b3, 1.5);
    mul_assign_d(&b4, 0.5);
    printf("Now, b3 %s b4\n", !((&b3)->width == (&b4)->width && (&b3)->height == (&b4)->height && (&b3)->length == (&b4)->length) ? "equals" : "does not equal");

    printf("\n--- End doBoxes() ---\n\n");

    destruct_box(&b1);
    destruct_box(&b2);
    destruct_box(&b3);
    destruct_box(&b4);
}


void doShelves()
{
    size_t i;
    Box aBox, temp1, temp2;
    Shelf aShelf;

    printf("\n--- start doShelves() ---\n\n");

    construct_box_d(&aBox, 5);

    for(i=0; i<NUM_BOXES; i++){
        construct_box(&aShelf.boxes[i]);
    }

    print_s(&aShelf);
    setBox(&aShelf, 1, &largeBox);
    setBox(&aShelf, 0, &aBox);

    print_s(&aShelf);
    message = "This is the total volume on the shelf:";
    print_s(&aShelf);
    message = "Shelf's volume:";
    print_s(&aShelf);

    construct_box_d_d_d(&temp1, 2, 4, 6);
    setBox(&aShelf, 1, &temp1);
    destruct_box(&temp1);

    construct_box_d(&temp2, 2);
    setBox(&aShelf, 2, &temp2);
    destruct_box(&temp2);

    print_s(&aShelf);

    printf("\n--- end doShelves() ---\n\n");

    destruct_box(&aBox);
    destruct_shelf(&aShelf);
}

int main()
{
    initGlobal();
    printf("\n--- Start main() ---\n\n");

    doBoxes();

    thisFunc();
    thisFunc();
    thisFunc();
    thatFunc();
    thatFunc();

    doShelves();


    printf("\n--- End main() ---\n\n");
    destruct_box(&box99);
    destruct_box(&box88);


    return 0;
}

