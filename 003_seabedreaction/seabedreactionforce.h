#ifndef SEABEDREACTION_H
#define SEABEDREACTION_H

#include<mbconfig.h>
#include "dataman.h"


class seabedreactionforce
{
/*private:
    doublereal z_direction;*/
public:
    seabedreactionforce(void);
    virtual ~seabedreactionforce(void);

	//set private variable
    virtual void seabedreactionvec(Vec3& z_direction)const;
    virtual void force(Vec3& z_direction, Vec3& F_seabedreaction)const;

};

#endif // seabedreactionforce_H
