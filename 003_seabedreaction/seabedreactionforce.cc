
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "mbconfig.h"
#include "seabedreactinoforce.h"

/* ------------------------------ seabedreactionforce start ---------------------------------------*/

seabedreactionforce::seabedreactionforce(void)
{
    NO_OP;
}

seabedreactionforce::~seabedreactionforce(void)
{
    NO_OP;
}

void
reactionforce::seabedreactionvec(Vec3& z_direction)const
{
    z_direction = {0.,0.,1.};
}

reactionforce::force(Vec3& z_direction, Vec3& F_seabedreaction)const
{
	F_seabedreaction = z_direction*@@@/*他のクラス(接触力)からどのように接触力の値を引っ張ってくるか*/
}

/*同一ファイルにreactionクラスを転記してsabedpropとseabedpropownerのように継承関係においてもよい*/
/*coulombfrictionについても上記と同様に同一ファイルにクラスを置いてクラス間で継承させた方が楽かもしれない*/


/* ------------------------------ seabedreactionforce end ---------------------------------------*/
