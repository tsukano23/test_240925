
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "mbconfig.h"
#include "seabedproperty_241008_v1.h"

seabedprop::seabedprop(void)
{
    NO_OP;
}

seabedprop::~seabedprop(void)
{
    NO_OP;
}

//各パラメータをメンバ変数としてセット
void
seabedprop::setValue(doublereal& sbz_node, doublereal& sbz_seabed)
{
    z_node = sbz_node;
    z_seabed = sbz_seabed;
}

//各パラメータを出力する
void
seabedprop::get(doublereal& sbz_node, doublereal& sbz_seabed) const
{
    sbz_node = z_node;
    sbz_seabed = z_seabed;
}

