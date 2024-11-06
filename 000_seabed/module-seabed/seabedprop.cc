
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "mbconfig.h"
#include "seabedprop.h"

seabedprop::seabedprop(void)
{
    NO_OP;
}

seabedprop::~seabedprop(void)
{
    NO_OP;
}

void
seabedprop::setValue(doublereal& pz_node, doublereal& pz_seabed)
{
    z_node = pz_node;
    z_seabed = pz_seabed;
}

void
seabedprop::get(doublereal& pz_node, doublereal& pz_seabed) const
{
    pz_node = z_node;
    pz_seabed = z_seabed;
}

seabedpropowner::seabedpropowner(void)
{
    NO_OP;
}

seabedpropowner::~seabedpropowner(void)
{
    NO_OP;   
}

void
seabedpropowner::setSeabedprop(doublereal& z_node, doublereal& z_seabed)const
{
    pSeabedprop.setValue(z_node, z_seabed);
}

void
seabedpropowner::get(doublereal& z_node, doublereal& z_seabed) const
{
    pSeabedprop.get(z_node, z_seabed);
}