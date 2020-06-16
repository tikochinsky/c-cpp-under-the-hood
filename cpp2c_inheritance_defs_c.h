#ifndef __CPP2C_INHERITANCE_DEFS_H__
#define __CPP2C_INHERITANCE_DEFS_H__

#include <cstdio>
#include "cpp2c_encapsulation_defs_c.h"

//// Materials ////////////

struct _Materials
{
    enum Types
    {
        PLASTIC,
        METAL,
        WOOD,
        PAPER,
        OTHER
    };
};

typedef struct _Materials Materials;

void _ZNC9MaterialsEPKs(Materials* const materials);
void _ZNC9MaterialsEPKsKPK9Materials(Materials* const materials, const Materials* const otherMaterials);
void _ZN9Materials10copyAssignEPKsKPK9Materials(Materials* const materials, const Materials* const otherMaterials);
void _ZND9MaterialsEPKs(Materials* const materials){}


/*inheruts from materials*/
struct _Material_t
{
    Materials _materialsBase;
    enum Types _material;
};

typedef struct _Material_t Material_t;

_ZND10Material_tEPKs(Material_t *const material);
/*inlines*/
/*
--materials:
 const char* getName(enum Types type)
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    return names[type];
}

--material_t:
Material_t(Types mat = OTHER): material(mat) { printf("Material created, set to %s\n", name()); }
const char* name() const { return getName(material); }

 */

//// PhysicalBox ////////////
struct _PhysicalBox{
    Box _boxBase;
    Material_t material;
};

typedef struct _PhysicalBox PhysicalBox;

_ZNC11PhysicalBoxEPKsddde5Types(PhysicalBox *const pBox, double l, double w, double h, enum Types t);
_ZNC11PhysicalBoxEPKse5Types(PhysicalBox *const pBox, enum Types t);
_ZND11PhysicalBoxEPKs(PhysicalBox *const pBox);

void _ZN11PhysicalBox6printpEKPKs(const PhysicalBox *const pBox);

/*inlines
//// PhysicalBox Defs ////////////

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

//// WeightBox ////////////

class WeightBox: public Box
{
public:
    WeightBox(double l, double w, double h, double wgt = 0.0);
    WeightBox(const WeightBox& other);
    ~WeightBox();

    WeightBox& operator=(const WeightBox& other);

    double getWeight() const;
    void printw() const;

private:
    double weight;
};

bool operator==(const WeightBox&, const WeightBox&);
bool operator!=(const WeightBox&, const WeightBox&);

//// WeightBox Defs ////////////

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



#endif // __CPP2C_INHERITANCE_DEFS_H__


