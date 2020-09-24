#ifndef __CPP2C_INHERITANCE_DEFS_H__
#define __CPP2C_INHERITANCE_DEFS_H__

#include "stdio.h"
#include "cpp2c_encapsulation_defs_c.h"

/*/// Materials ///////////*/

/*Materials*/
enum Types
{
    PLASTIC,
    METAL,
    WOOD,
    PAPER,
    OTHER
};

struct _Materials
{
    char c;
};

typedef struct _Materials Materials;


void _ZNC9MaterialsEPKs(Materials* const materials);/*default ctor*/
void _ZNC9MaterialsEPKsKPK9Materials(Materials* const materials, const Materials* const otherMaterials);/*copy ctor*/
const Materials* const _ZN9Materials10copyAssignEPKsKPK9Materials(Materials* const materials, const Materials* const otherMaterials);/*copy assignment*/
void _ZND9MaterialsEPKs(Materials* const materials);/*default dtor*/

/*
materials inlines:
 const char* getName(enum Types type)
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    return names[type];
}



/*Material_t*/
struct _Material_t
{
    Materials _materialsBase;
    enum Types _material;
};

typedef struct _Material_t Material_t;


/*default ctor is inline*/
void _ZNC10Material_tEPKsKPK10Material_t(Material_t* const material_t, const Material_t* const otherMaterial_t);/*copy ctor*/
void _ZND10Material_tEPKs(Material_t *const material_t);


/*const Material_t* const _ZN10Material_t10copyAssignEPKsKPK10Material_t(Material_t* const material_t, const Material_t* const otherMaterial_t);copy assignment*/
/*
material_t inlines:
Material_t(Types mat = OTHER): material(mat) { printf("Material created, set to %s\n", name()); }
const char* name() const { return getName(material); }

 */



/* PhysicalBox */

struct _PhysicalBox{
    Box m_boxBase;
    Material_t m_material;
};

typedef struct _PhysicalBox PhysicalBox;


void _ZNC11PhysicalBoxEPKsddde5Types(PhysicalBox *const pBox, double l, double w, double h, enum Types t);/*ctor ddd, default OTHER*/
void _ZNC11PhysicalBoxEPKse5Types(PhysicalBox *const pBox, enum Types t);/*ctor default box*/
void _ZNC11PhysicalBoxEPKsKPK11PhysicalBox(PhysicalBox *const pBox, const PhysicalBox *const otherPBox);/*copy ctor*/
const PhysicalBox *const _ZN11PhysicalBox10copyAssignEPKsKPK11PhysicalBox(PhysicalBox *const pBox, const PhysicalBox *const otherPBox);/*copy assignment*/
void _ZND11PhysicalBoxEPKs(PhysicalBox *const pBox);/*dtor*/

void _ZN11PhysicalBox6printpEKPKs(const PhysicalBox *const pBox);/*printp*/


/* PhysicalBox inlines:

inline Materials::Types PhysicalBox::getMaterial() const
{
    return material.material;
}

inline bool operator==(const PhysicalBox& lhs, const PhysicalBox& rhs)
{
    return (const Box&)lhs == (const Box&)rhs && lhs.getMaterial() == rhs.getMaterial();
}

inline bool operator!=(const PhysicalBox& lhs, const PhysicalBox& rhs)
{
    return !(lhs == rhs);
}
*/



/* WeightBox */
struct WeightBox{
    Box m_boxBase;
    double m_weight;
};

typedef struct WeightBox WeightBox;


void _ZNC9WeightBoxEPKsdddd(WeightBox *const weightBox, double l, double w, double h, double wgt);/*ctor - default wgt 0.0*/
void _ZNC9WeightBoxEPKsKPK9WeightBox(WeightBox *const weightBox, const WeightBox *const otherWeightBox);/*copy ctor*/
void _ZND9WeightBoxEPKs(WeightBox *const weightBox);/*dtor*/
WeightBox* _ZN9WeightBox10copyAssignEPKsKPK9WeightBox(WeightBox *const weightBox, const WeightBox *const otherWeightBox);/*copy assign*/

void _ZN9WeightBox6printwEKPKs(const WeightBox *const weightBox);/*printw*/


/*WeightBox Defs inlines

inline double WeightBox::getWeight() const
{
    return weight;
}

inline bool operator==(const WeightBox& lhs, const WeightBox& rhs)
{
    return (const Box&)lhs == (const Box&)rhs && lhs.getWeight() == rhs.getWeight();
}

inline bool operator!=(const WeightBox& lhs, const WeightBox& rhs)
{
    return !(lhs == rhs);
}

*/

#endif


