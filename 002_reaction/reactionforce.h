#ifndef REACTION_H
#define REACTION_H

#include<mbconfig.h>
#include "dataman.h"


class reactionforce
{
private:
    doublereal mass;
    doublereal n_node;
public:
    reactionforce(void);
    virtual ~reactionforce(void);

	//set private variable
    virtual void setpmass(doublereal pmass) const;
    virtual void setpn_node(doublereal pn_node) const;

	//
    virtual void setValue(doublereal& pmass, doublereal& pn_node);
    virtual void get(doublereal& pmass, doublereal& pn_node) const;

};

#endif // REACTIONFORCE_H
