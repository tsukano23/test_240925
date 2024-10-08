
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "mbconfig.h"
#include "seabedpropowner_241008_v1.h"

seabedpropowner::seabedpropowner(void)
{
    NO_OP;
}

seabedpropowner::~seabedpropowner(void)
{
    NO_OP;   
}

void
seabedpropowner::setSeabedprop(doublereal& z_node, doublereal& z_seabed)
{
    pSeabedprop.setValue(z_node,z_seabed);
}

void
seabedpropowner::get(doublereal& z_node, doublereal& z_seabed) const
{
    pSeabedprop.get(z_node,z_seabed);
}