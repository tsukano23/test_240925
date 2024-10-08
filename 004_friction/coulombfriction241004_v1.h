
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
    virtual void setshearmodulus(doublereal value_K) const;
    virtual void setZ(Vec3 vec_Z) const;
    virtual void setNumNord(int value_N) const;
    virtual void setM(doublereal value_M) const;
    virtual void setStaticFrictionCoefficient(doublereal value_Nu_s) const;
    virtual void setDynamicFrictionCoefficient(doublereal value_Nu_d) const;
    virtual void setMaximamStaticFrictionCoefficient(doublereal value_Nu_s_max) const;


    //calculate strain and forces
    virtual void Force(Vec3 F, int value_N, doublereal value_M, Vec3 Z) const;
private:
    mutable doublereal K;
    //mutable doublereal Z;
    mutable doublereal M;
    mutable doublereal N;
    mutable doublereal Nu_s;
    mutable doublereal Nu_d;
    mutable doublereal Nu_s_max;
};

#endif //coulombfriction_H