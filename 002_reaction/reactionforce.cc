
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
reactionforce::setValue(doublereal& pmass, doublereal& pn_contact)
{
    mass = pmass;
	n_contact 	 = pn_contact;
    
}

void
reactionforce::get(doublereal& pmass, doublereal& pn_contact) const
{
    pmass = mass;
	pn_contact	  = n_contact;
}

reactionforce::force(doublereal& R)const
{
	R = mass/n_contact
}

/* ------------------------------ reactionforce end ---------------------------------------*/
