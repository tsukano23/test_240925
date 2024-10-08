
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "mbconfig.h"
#include "ContactLaw.h"


/* -----------------------------ContactLaw  start --------------------------------------*/
ContactLaw::ContactLaw(void)
{
	NO_OP;
}

ContactLaw::~ContactLaw(void)
{
	NO_OP;
}

void
ContactLaw::setSeaDepth(Vec3 value_SeaDepth) const
{
    D = value_SeaDepth
}

void
ContactLaw::setNodeHeight(Vec3 value_NodeHeight) const
{
    H = value_NodeHeight
}

/* -----------------------------海底面と接触しているか判別　distinction　start*/
void
ContactLaw::Distincion(doublereal D1) const
{
    D1 = D[3] - H[3];
    if (D1 >= 0 )
    {
        flag = 1;
    }
}
/* -----------------------------海底面と接触しているか判別　distinction　end*/


/* -----------------------------ContactLaw   end--------------------------------------*/