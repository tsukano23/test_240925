#ifndef REACTION_H
#define REACTION_H

#include<mbconfig.h>
#include "dataman.h"


class reactionforce
{
private:
    doublereal mass;
    doublereal n;
public:
    reactionforce(void);
    virtual ~reactionforce(void);

	//set private variable
    virtual void setpmass(doublereal pmass) const;
    virtual void setpn_contact(doublereal pn_contact) const;

	//
    virtual void setValue(doublereal& pmass, doublereal& pn);
    virtual void get(doublereal& pmass, doublereal& pn) const;

};

#endif // REACTIONFORCE_H
