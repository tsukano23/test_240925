
#ifndef SEABEDPROPOWNER_H
#define SEABEDPROPOWNER_H

#include "dataman.h"

class seabedpropowner
{
protected:
    seabedprop pSeabedprop; 
public:
    seabedpropowner(void);
    virtual ~seabedpropowner(void);

    virtual void setSeabedprop(doublereal& z_node, doublereal& z_seabed);
    virtual void get(doublereal& z_node, doublereal& z_seabed) const;
};

#endif // SEABEDPROPOWBER_H