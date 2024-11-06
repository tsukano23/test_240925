
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
coulombfriction::setValue(doublereal& pstarting_cofficient_friction, doublereal& psliding_cofficient_friction,doublereal& pks, doublereal& pDiameter, doublereal& pvirtual_seabed, doublereal& pdisiatnce_node_seabed, doublereal& plength_node_distance) const
{
    //静止摩擦力か動摩擦力か
    starting_cofficient_friction = pstarting_cofficient_friction;
    sliding_cofficient_friction  = psliding_cofficient_friction;
    ks = pks;
    //弾性床
    Diameter = pDiameter;
    virtual_seabed = pvirtual_seabed;
    disiatnce_node_seabed = pdisiatnce_node_seabed;
    length_node_distance = plength_node_distance;
}

void
coulombfriction::get(doublereal& pstarting_cofficient_friction, doublereal& psliding_cofficient_friction,doublereal& pks, doublereal& pDiameter, doublereal& pvirtual_seabed, doublereal& pdisiatnce_node_seabed, doublereal& plength_node_distance) const
{
    //静止摩擦力か動摩擦力か
    pstarting_cofficient_friction = starting_cofficient_friction;
    psliding_cofficient_friction  = sliding_cofficient_friction;
    pks = ks;
    //弾性床
    pDiameter = Diameter;
    pvirtual_seabed = virtual_seabed;
    pdisiatnce_node_seabed = disiatnce_node_seabed;
    plength_node_distance = length_node_distance;
}

/* -----------------------------静止摩擦力か動摩擦力か条件分岐を用いて出力　end*/

/* -----------------------------frectionvector  start --------------------------------------*/

/*局所のz軸に関して外積計算し、局所座標系のx軸を定義*/

/*nodeの節点座標を全体座標系で呼び出し（n番目,n+1番目）*/

/*上記で取り出した座標から摩擦方向（係留長さ方向）ベクトルを定義*/

/*局所x軸を係留長さ方向に回転（海底反力と摩擦力の関係を見やすくするため）*/


/* -----------------------------frectionvector  end --------------------------------------*/
/* -----------------------------coulombfriction   end--------------------------------------*/