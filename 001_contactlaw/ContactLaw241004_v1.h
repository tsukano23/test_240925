
#ifndef CONTACTLAW_H
#define CONTACTLAW_H

#include <mbconfig.h>
#include "dataman.h"

/* =================================================
 * class ContactLaw
 * ================================================= */
class ContactLaw
{
public:
    ContactLaw(void);
    ~ContactLaw(void);

    //set private variable
    virtual void setSeaDepth(Vec3 value_SeaDepth) const;
    virtual void setNodeHeight(Vec3 value_NodeHeight) const;

    //calculate strain and forces
    virtual void Distinction(doublereal D1) const;
private:
    mutable Vec3 D;
    mutable Vec3 H;
};

#endif //ContactLaw_H