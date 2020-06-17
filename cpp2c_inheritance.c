#include "stdio.h"
#include "cpp2c_inheritance_defs_c.h"


void doMaterials()
{
    Materials mat;
    Material_t mat1, mat2;
    const char *temp;
    /*
    struct _MatTest {
        Materials mat;
        Material_t mat_t;
    };
*/
    printf("\n--- Start doMaterials() ---\n\n");

    _ZNC9MaterialsEPKs(&mat);
    printf("Size of Materials: %lu\n", sizeof(Materials));
    printf("Size of mat: %lu\n", sizeof(mat));
    printf("Size of Materials::Types: %lu\n", sizeof(enum Types));/*1 - 4*/
    printf("Size of Material_t: %lu\n", sizeof(enum Types));/*1 - 4*/

    printf("Size of Materials + Material_t: %lu\n", sizeof(Material_t));/*2 - 8*/

    /*construct mat1*/
    _ZNC9MaterialsEPKs(&(mat1._materialsBase));/*material*/
    mat1._material = OTHER;
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[OTHER];
    }
    printf("Material created, set to %s\n", temp );

    /*construct mat2*/
    _ZNC9MaterialsEPKs(&(mat1._materialsBase));/*material*/
    mat1._material = METAL;
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[METAL];
    }
    printf("Material created, set to %s\n", temp );

    printf("\n--- End doMaterials() ---\n\n");

    _ZND9MaterialsEPKs(&mat);
    _ZND10Material_tEPKs(&mat1);
    _ZND10Material_tEPKs(&mat2);
}

void doPhysicalBox()
{
    PhysicalBox pb1, pb2, pb3, pb4;

    printf("\n--- Start doPhysicalBox() ---\n\n");

    _ZNC11PhysicalBoxEPKsddde5Types(&pb1, 8, 6, 4, PLASTIC);
    _ZNC11PhysicalBoxEPKse5Types(&pb2, WOOD);
    _ZNC11PhysicalBoxEPKsddde5Types(&pb3, 7,7,7, OTHER);

    printf("\npb4 is copy-constructed from pb1\n");
    _ZNC11PhysicalBoxEPKsKPK11PhysicalBox(&pb4, &pb1);
    _ZN11PhysicalBox6printpEKPKs(&pb4);
    _ZN11PhysicalBox6printpEKPKs(&pb1);

    printf("pb4 %s pb1\n", ((const Box*)&pb4)->width == ((const Box*)&pb1)->width && \
    ((const Box*)&pb4)->height == ((const Box*)&pb1)->height &&\
    ((const Box*)&pb4)->length == ((const Box*)&pb1)->length && \
    pb4.m_material._material == pb1.m_material._material ? "equals" : "does not equal");

    printf("\npb4 is copy-assigned from pb3\n");
    _ZN11PhysicalBox10copyAssignEPKsKPK11PhysicalBox(&pb4, &pb3);
    _ZN11PhysicalBox6printpEKPKs(&pb4);
    _ZN11PhysicalBox6printpEKPKs(&pb3);

    printf("pb4 %s pb3\n", ((const Box*)&pb4)->width == ((const Box*)&pb3)->width && \
    ((const Box*)&pb4)->height == ((const Box*)&pb3)->height &&\
    ((const Box*)&pb4)->length == ((const Box*)&pb3)->length && \
    pb4.m_material._material == pb3.m_material._material ? "equals" : "does not equal");

    printf("\n--- End doPhysicalBox() ---\n\n");

    _ZND11PhysicalBoxEPKs(&pb1);
    _ZND11PhysicalBoxEPKs(&pb2);
    _ZND11PhysicalBoxEPKs(&pb3);
    _ZND11PhysicalBoxEPKs(&pb4);
}

void doWeightBox()
{
    WeightBox pw1, pw2, pw3, pw4;
    printf("\n--- Start doWeightBox() ---\n\n");

    _ZNC9WeightBoxEPKsdddd(&pw1, 8, 6, 4, 25);
    _ZNC9WeightBoxEPKsdddd(&pw2, 1, 2, 3, 0.0);
    _ZNC9WeightBoxEPKsdddd(&pw3, 10, 20, 30, 15);

    
    printf("\npw4 is copy-constructed from pw1\n");
    _ZNC9WeightBoxEPKsKPK9WeightBox(&pw4, &pw1);
    _ZN9WeightBox6printwEKPKs(&pw4);
    _ZN9WeightBox6printwEKPKs(&pw1);

    printf("pw4 %s pw1\n", ((const Box*)&pw4)->width == ((const Box*)&pw1)->width && \
    ((const Box*)&pw4)->height == ((const Box*)&pw1)->height &&\
    ((const Box*)&pw4)->length == ((const Box*)&pw1)->length && \
    pw4.m_weight == pw1.m_weight ? "equals" : "does not equal");

    printf("\npw4 is copy-assigned from pw3\n");
    _ZN9WeightBox10copyAssignEPKsKPK9WeightBox(&pw4, &pw3);
    _ZN9WeightBox6printwEKPKs(&pw4);
    _ZN9WeightBox6printwEKPKs(&pw3);

    printf("pw4 %s pw3\n", ((const Box*)&pw4)->width == ((const Box*)&pw3)->width && \
    ((const Box*)&pw4)->height == ((const Box*)&pw3)->height &&\
    ((const Box*)&pw4)->length == ((const Box*)&pw3)->length && \
    pw4.m_weight == pw3.m_weight ? "equals" : "does not equal");

    printf("\n--- End doWeightBox() ---\n\n");

    _ZND9WeightBoxEPKs(&pw1);
    _ZND9WeightBoxEPKs(&pw2);
    _ZND9WeightBoxEPKs(&pw3);
    _ZND9WeightBoxEPKs(&pw4);

}




int main()
{
    printf("\n--- Start main() ---\n\n");

    doMaterials();

    doPhysicalBox();

    doWeightBox();

    printf("\n--- End main() ---\n\n");

    return 0;
}
