
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "mbconfig.h"
#include "reactinoforce.h"

/* ------------------------------ reactionforce start ---------------------------------------*/

reactionforce::reactionforce(void)
{
    NO_OP;
}

reactionforce::~reactionforce(void)
{
    NO_OP;
}

void
reactionforce::setValue(doublereal& pmass, doublereal& pn_node)
{
    mass = pmass;
	n_node 	 = pn_node;
    
}

void
reactionforce::get(doublereal& pmass, doublereal& pn_node) const
{
    pmass = mass;
	pn_node	= n_node;
}

reactionforce::force(doublereal& R)const
{
	R = mass/n_node
}

void
reactionforce::reactionvec(Vec3& z_direction)const
{
    z_direction = {0.,0.,1.};
}

void
reactionforce::forcevector(Vec3& z_direction, doublereal& R)const
{
	Vec3 F = z_direction*R;         /*reactionforce(vector)*/
}

/* ------------------------------ reactionforce end ---------------------------------------*/