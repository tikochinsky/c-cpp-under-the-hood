#include "stdio.h"
#include "cpp2c_inheritance_defs_c.h"




void doMaterials()
{
    Materials mat1, mat2;
    Material_t mat1;
    const char *temp;
    struct MatTest { Materials mat; Material_t mat_t; };

    printf("\n--- Start doMaterials() ---\n\n");
    
    ZNC9MaterialsEPKs(&mat);

    printf("Size of Materials: %lu\n", 1);
    printf("Size of mat: %lu\n", sizeof(mat));
    printf("Size of Materials::Types: %lu\n", sizeof(Materials::Types));/*?*/
    printf("Size of Material_t: %lu\n", sizeof(Material_t));/*?*/

    printf("Size of Materials + Material_t: %lu\n", sizeof(MatTest));/*?*/


    _ZNC9MaterialsEPKs(&(mat1._materialsBase));
    mat1._material = Materials.OTHER;
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[mat1._material];
    }
    printf("Material created, set to %s\n", temp };


    _ZNC9MaterialsEPKs(&(mat2._materialsBase));
    mat2._material = Materials.METAL;
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[mat2._material];
    }
    printf("Material created, set to %s\n", temp };

    printf("\n--- End doMaterials() ---\n\n");
}

void doPhysicalBox()
{
    PhysicalBox pb1, pb2, pb3, pb4;
    printf("\n--- Start doPhysicalBox() ---\n\n");

    _ZNC11PhysicalBoxEPKsddde5Types(&pb1, 8, 6, 4, Materials.PLASTIC);
    _ZNC11PhysicalBoxEPKse5Types(&pb2, Materials.WOOD);
    _ZNC11PhysicalBoxEPKsddde5Types(&pb3, 7, 7, 7, Materials.OTHER);
    
    printf("\npb4 is copy-constructed from pb1\n");
    PhysicalBox pb4 = pb1;
    pb4.printp();
    pb1.printp();
    printf("pb4 %s pb1\n", pb4 == pb1 ? "equals" : "does not equal");

    printf("\npb4 is copy-assigned from pb3\n");
    pb4 = pb3;
    pb4.printp();
    pb3.printp();
    printf("pb4 %s pb3\n", pb4 == pb3 ? "equals" : "does not equal");

    printf("\n--- End doPhysicalBox() ---\n\n");
}

void doWeightBox()
{
    printf("\n--- Start doWeightBox() ---\n\n");

    WeightBox pw1(8, 6, 4, 25);
    WeightBox pw2(1, 2, 3);
    WeightBox pw3(10, 20, 30, 15);
    
    printf("\npw4 is copy-constructed from pw1\n");
    WeightBox pw4 = pw1;
    pw4.printw();
    pw1.printw();
    printf("pw4 %s pw1\n", pw4 == pw1 ? "equals" : "does not equal");

    printf("\npw4 is copy-assigned from pw3\n");
    pw4 = pw3;
    pw4.printw();
    pw3.printw();
    printf("pw4 %s pw3\n", pw4 == pw3 ? "equals" : "does not equal");

    printf("\n--- End doWeightBox() ---\n\n");
}





int main()
{
    printf("\n--- Start main() ---\n\n");

    doMaterials();

    doPhysicalBox();

    doWeightBox();

    printf("\n--- End main() ---\n\n");

}
