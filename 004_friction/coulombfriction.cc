
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

/* -----------------------------静止摩擦力か動摩擦力か条件分岐を用いて出力　start*/

void
coulombfriction::setValue(doublereal value_Nu_s, doublereal value_Nu_d, doublereal value_Nu_s_max) const
{
    Nu_s = value_Nu_s;
    Nu_d = value_Nu_d;
    Nu_s_max = value_Nu_s_max;
}

void
coulombfriction::FrictionForce(doublereal F_Friction, doublereal F_Friction_s_max, int flag, doublereal Fx) const
{
    doublereal value_F = ;/*seabedreactionforceのF_seabedreactionに相当*/
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

/* -----------------------------frectionvector  start --------------------------------------*/

/*局所のz軸に関して外積計算し、局所座標系のx軸を定義*/

/*nodeの節点座標を全体座標系で呼び出し（n番目,n+1番目）*/

/*上記で取り出した座標から摩擦方向（係留長さ方向）ベクトルを定義*/

/*局所x軸を係留長さ方向に回転（海底反力と摩擦力の関係を見やすくするため）*/


/* -----------------------------frectionvector  end --------------------------------------*/
/* -----------------------------coulombfriction   end--------------------------------------*/