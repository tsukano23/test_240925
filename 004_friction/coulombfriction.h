
#ifndef coulombfriction_H
#define coulombfriction_H

#include <mbconfig.h>
#include "dataman.h"

/* =================================================
 * class coulombfriction
 * ================================================= */
class coulombfriction
{
public:
    coulombfriction(void);
    ~coulombfriction(void);

    //set private variable
    virtual void setValue(doublereal value_Nu_s, doublereal value_Nu_d, doublereal value_Nu_s_max) const;

    //calculate strain and forces
    virtual void FrictionForce(doublereal F_Friction, doublereal F_Friction_s_max, int flag, doublereal Fx) const
{
private:
    mutable doublereal Nu_s;
    mutable doublereal Nu_d;
    mutable doublereal Nu_s_max;
};

#endif //coulombfriction_H