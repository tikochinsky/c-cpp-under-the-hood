#include "stdio.h"
#include "memory.h"
#include "cpp2c_inheritance_defs_c.h"

/*----Materials Defs----*/


/*----Materials----*/

/*default ctor*/
void _ZNC9MaterialsEPKs(Materials* const materials){}

/*copy ctor*/
void _ZNC9MaterialsEPKsKPK9Materials(Materials* const materials, const Materials* const otherMaterials)
{
    memcpy(materials, otherMaterials, sizeof(Materials));
}

/*copy assignment*/
const Materials* const _ZN9Materials10copyAssignEPKsKPK9Materials(Materials* const materials, const Materials* const otherMaterials)
{
    memcpy(materials, otherMaterials, sizeof(Materials));
    return materials;
}

/*default dtor*/
void _ZND9MaterialsEPKs(Materials* const materials){}



/*----Material_t----*/

/*default ctor is inline*/

/*copy ctor*/
void _ZNC10Material_tEPKsKPK10Material_t(Material_t* const material_t, const Material_t* const otherMaterial_t){
    _ZNC9MaterialsEPKsKPK9Materials(&(material_t->_materialsBase), &(otherMaterial_t->_materialsBase));
    memcpy(&(material_t->_material), &(otherMaterial_t->_material), sizeof(enum Types));
}

/*default dtor*/
void _ZND10Material_tEPKs(Material_t *const material_t){}


/*copy assignment
const Material_t* const _ZN10Material_t10copyAssignEPKsKPK10Material_t(Material_t* const material_t, const Material_t* const otherMaterial_t){
    _ZN9Materials10copyAssignEPKsKPK9Materials(&(material_t->_materialsBase), &(otherMaterial_t->_materialsBase));
    memcpy(&(material_t->_material), &(otherMaterial_t->_material), sizeof(enum Types));
    return material_t;
}*/



/* ----PhysicalBox Defs---- */

/*ctor ddd, default OTHER*/
void _ZNC11PhysicalBoxEPKsddde5Types(PhysicalBox *const pBox, double l, double w, double h, enum Types t){
    const char  *temp;
    _ZNC3BoxEPKsddd(&(pBox->m_boxBase), l, w, h);/*base*/

    _ZNC9MaterialsEPKs(&(pBox->m_material._materialsBase));/*material*/
    pBox->m_material._material = t;/*OTHER as default*/
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[t];
    }
    printf("Material created, set to %s\n", temp );

    _ZN11PhysicalBox6printpEKPKs(pBox);/*PhysicalBox*/
}

/*ctor default box*/
void _ZNC11PhysicalBoxEPKse5Types(PhysicalBox *const pBox, enum Types t){
    const char  *temp;
    _ZNC3BoxEPKsd(&(pBox->m_boxBase), 1);/*base*/

    _ZNC9MaterialsEPKs(&(pBox->m_material._materialsBase));/*material*/
    pBox->m_material._material = t;/*OTHER as default*/
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[t];
    }
    printf("Material created, set to %s\n", temp );

    _ZN11PhysicalBox6printpEKPKs(pBox);/*PhysicalBox*/
}

/*copy ctor*/
void _ZNC11PhysicalBoxEPKsKPK11PhysicalBox(PhysicalBox *const pBox, const PhysicalBox *const otherPBox){
    _ZNC3BoxEPKsKPK3Box(&(pBox->m_boxBase), &(otherPBox->m_boxBase));/*copy ctor box*/
    _ZNC10Material_tEPKsKPK10Material_t(&(pBox->m_material), &(otherPBox->m_material));/*copy ctor material_t*/
}

/*copy assignment*/
const PhysicalBox *const _ZN11PhysicalBox10copyAssignEPKsKPK11PhysicalBox(PhysicalBox *const pBox, const PhysicalBox *const otherPBox){
    _ZN3Box10copyAssignEPKsKPK3Box(&(pBox->m_boxBase), &(otherPBox->m_boxBase));
    memcpy(&(pBox->m_material), &(otherPBox->m_material), sizeof(Material_t));
    return pBox;
}

/*dtor*/
void _ZND11PhysicalBoxEPKs(PhysicalBox *const pBox){
    const char *temp;
    /*PhysicalBox Dtor*/
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[pBox->m_material._material];
    }
    printf("PhysicalBox dtor, %f x %f x %f, %s; ", (pBox->m_boxBase).length, (pBox->m_boxBase).width, (pBox->m_boxBase).height, temp);

    /*material Dtor*/
    _ZND10Material_tEPKs(&(pBox->m_material));

    /*box Dtor*/
    _ZND3BoxEPKs(&(pBox->m_boxBase));

}

/*printp*/
void _ZN11PhysicalBox6printpEKPKs(const PhysicalBox *const pBox){
    const char *temp;
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        temp = names[pBox->m_material._material];
    }
    printf("PhysicalBox, made of %s; ", temp);
    _ZNK3Box5printEKPKs(&(pBox->m_boxBase));
}



/* WeightBox Defs */

/*ctor - default wgt 0.0*/
void _ZNC9WeightBoxEPKsdddd(WeightBox *const weightBox, double l, double w, double h, double wgt){
    _ZNC3BoxEPKsddd(&(weightBox->m_boxBase), l, w, h);
    weightBox->m_weight = wgt;

    _ZN9WeightBox6printwEKPKs(weightBox);
}

/*copy ctor*/
void _ZNC9WeightBoxEPKsKPK9WeightBox(WeightBox *const weightBox, const WeightBox *const otherWeightBox){
    _ZNC3BoxEPKs(&(weightBox->m_boxBase));
    memcpy(&(weightBox->m_weight), &(otherWeightBox->m_weight), sizeof(double));

    _ZN9WeightBox6printwEKPKs(weightBox);
}

/*dtor*/
void _ZND9WeightBoxEPKs(WeightBox *const weightBox){
    printf("Destructing WeightBox; ");
    _ZN9WeightBox6printwEKPKs(weightBox);

    /*box Dtor*/
    _ZND3BoxEPKs(&(weightBox->m_boxBase));
}

/*copy assignment*/
WeightBox* _ZN9WeightBox10copyAssignEPKsKPK9WeightBox(WeightBox *const weightBox, const WeightBox *const otherWeightBox){
    weightBox->m_weight = otherWeightBox->m_weight;
    return weightBox;
}

/*printw*/
void _ZN9WeightBox6printwEKPKs(const WeightBox *const weightBox){
    printf("WeightBox, weight: %f; ", weightBox->m_weight);
    _ZNK3Box5printEKPKs(&(weightBox->m_boxBase));
}

