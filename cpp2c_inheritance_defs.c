#include "stdio.h"
#include "cpp2c_inheritance_defs_c.h"

/*materials*/
void _ZNC9MaterialsEPKs(Materials* const materials){}

void _ZNC9MaterialsEPKsKPK9Materials(Materials* const materials, const Materials* const otherMaterials)
{
    *materials = *otherMaterials;
}

void _ZN9Materials10copyAssignEPKsKPK9Materials(Materials* const materials, const Materials* const otherMaterials)
{
    *materials = *otherMaterials;
}

void _ZND9MaterialsEPKs(Materials* const materials){}



/*Material_t*/
_ZND10Material_tEPKs(Material_t *const material){}


//// PhysicalBox Defs ////////////

_ZNC11PhysicalBoxEPKsddde5Types(PhysicalBox *const pBox, double l, double w, double h, enum Types t){
    const char  *temp;
    _ZNC3BoxEPKsddd(&(pBox->_boxBase), l, w, h);/*base*/
    _ZNC9MaterialsEPKs(&(mat1._materialsBase));/*material*/
    mat1._material = t;/*other as default*/
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[t];
    }
    printf("Material created, set to %s\n", temp };

    _ZN11PhysicalBox6printpEKPKs(pBox);/*PhysicalBox*/
}


_ZNC11PhysicalBoxEPKse5Types(PhysicalBox *const pBox, enum Types t){
    const char  *temp;
    _ZNC3BoxEPKsd(&(pBox->_boxBase), 1);/*base*/
    _ZNC9MaterialsEPKs(&(mat1._materialsBase));/*material*/
    mat1._material = t;
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[t];
    }
    printf("Material created, set to %s\n", temp };

    _ZN11PhysicalBox6printpEKPKs(pBox);/*PhysicalBox*/
}


_ZND11PhysicalBoxEPKs(PhysicalBox *const pBox){
    char char *temp;
    /*PhysicalBox Dtor*/
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[pBox->material];
    }
    printf("PhysicalBox dtor, %f x %f x %f, %s; ", (pBox->_boxBase).length, (pBox->_boxBase).width, (pBox->_boxBase).height, temp);

    /*box Dtor*/
    _ZND3BoxEPKs(&(pBox->_boxBase));

    /*material Dtor*/
    _ZND10Material_tEPKs(&(pBox->material));
}


void _ZN11PhysicalBox6printpEKPKs(const PhysicalBox *const pBox){
    const char *temp;
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[pBox->material];
    }
    printf("PhysicalBox, made of %s; ", temp);
    _ZNK3Box5printEKPKs(&(pBox->_boxBase));
}

/*
PhysicalBox::PhysicalBox(double l, double w, double h)
:   Box(l, w, h)
{
    printp();
}


PhysicalBox::PhysicalBox(double l, double w, double h, Materials::Types t)
:   Box(l, w, h)
,   material(t)
{
    printp();
}


PhysicalBox::PhysicalBox(Materials::Types t)
:   material(t)
{
    printp();
}

 PhysicalBox::~PhysicalBox()
{
    printf("PhysicalBox dtor, %f x %f x %f, %s; ", getLength(), getWidth(), getHeight(), material.name());
}

void PhysicalBox::printp() const
{
    printf("PhysicalBox, made of %s; ", material.name());
    print();
}
 */




/// WeightBox Defs ////////////

WeightBox::WeightBox(double l, double w, double h, double wgt)
:   Box(l, w, h)
,   weight(wgt)
{
    printw();
}

WeightBox::WeightBox(const WeightBox& other)
:   weight(other.weight)
{
    printw();
}

WeightBox::~WeightBox()
{
    printf("Destructing WeightBox; ");
    printw();
}

WeightBox& WeightBox::operator=(const WeightBox& other)
{
    weight = other.weight;
    return *this;
}

void WeightBox::printw() const
{
    printf("WeightBox, weight: %f; ", weight);
    print();
}


