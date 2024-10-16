
#ifndef SEABEDPROP_H
#define SEABEDPROP_H

#include "dataman.h"

/* -----------------------------------------------------------------------*/

class seabedprop
{
private:
    doublereal z_node;              //係留物のZ座標
    doublereal z_seabed;            //海底面のZ座標             
public:
    seabedprop(void);
    virtual ~seabedprop(void);

    virtual void setValue(doublereal& sbz_node, doublereal& sbz_seabed);
    virtual void get(doublereal& sbz_node, doublereal& sbz_seabed) const;
};

#endif // SEABEDPROP_H

/* -----------------------------------------------------------------------*/

#ifndef SEABEDPROPOWNER_H
#define SEABEDPROPOWNER_H

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

/* -----------------------------------------------------------------------*/