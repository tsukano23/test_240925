#ifndef REACTION_H
#define REACTION_H

#include<mbconfig.h>
#include "dataman.h"


class reactionforce
{
private:
    doublereal mass;
    doublereal n_node;
    Vec3 F;

public:
    reactionforce(void);
    virtual ~reactionforce(void);

	//set private variable
    virtual void setValue(doublereal& pmass, doublereal& pn_node);
    virtual void get(doublereal& pmass, doublereal& pn_node) const;
    virtual void force(doublereal& R)const;
    virtual void reactionvec(Vec3& z_direction)const;
    virtual void forcevector(Vec3& z_direction, doublereal& R)const;


};

#endif // REACTIONFORCE_H
