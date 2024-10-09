
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "mbconfig.h"
#include "coulombfriction.h"


/* -----------------------------coulombfriction  start --------------------------------------*/
coulombfriction::coulombfriction(void)
{
	NO_OP;
}

coulombfriction::~coulombfriction(void)
{
	NO_OP;
}

void
coulombfriction::setshearmodulus(doublereal value_K) const
{
    K = value_K
}

void
coulombfriction::setZ(Vec3 vec_Z) const
{
    Z = {0., 0., 1.};/*vec_Z*/
}

void
coulombfriction::setNumNord(int value_N) const
{
    N = value_N;
}

void
coulombfriction::setM(doublereal value_M) const
{
    M = value_M;
}

/*
void
coulombfriction::setL0(doublereal value_L0) const
{
    L0 = value_L0;
}
*/

void
coulombfriction::Force(Vec3 F, Vec3 Z)
{
    doublereal value_F = M/N;
    F = Vec3(value_F*Z[0], value_F*Z[1], value_F*[2]);
}

/* -----------------------------静止摩擦力か動摩擦力か条件分岐を用いて出力　start*/

void
coulombfriction::setStaticFrictionCoefficient(doublereal value_Nu_s) const
{
    Nu_s = value_Nu_s;
}

void
coulombfriction::setDynamicFrictionCoefficient(doublereal value_Nu_d) const
{
    Nu_d = value_Nu_d;
}

void
coulombfriction::setMaximamStaticFrictionCoefficient(doublereal value_Nu_s_max) const
{
    Nu_s_max = value_Nu_s_max;
}

void
coulombfriction::FrictionForce(doublereal F_Friction, doublereal F_Friction_s_max, int flag, doublereal Fx) const
{
    doublereal value_F = M/N;
    F_Friction = Nu_s*value_F;
    F_Friction_s_max = Nu_s_max*value_F;
    if (F_Friction <= F_Friction_s_max)
    {
        flag = 0; /*動かない*/
        Fx = Nu_s*value_F;/*静止摩擦力*/
    }
    else
    {
        flag = 1;/*動く*/
        Fx = Nu_d*value_F;/*動摩擦力*/
    }
}
/* -----------------------------静止摩擦力か動摩擦力か条件分岐を用いて出力　end*/


/* -----------------------------coulombfriction   end--------------------------------------*/