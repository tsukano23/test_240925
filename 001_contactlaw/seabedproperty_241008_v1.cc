
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "mbconfig.h"
//#include "ContactLaw.h"


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

//各パラメータをメンバ変数としてセット
void
seabedprop::setValue(doublereal& sbz_node, doublereal& sbz_seabed)
{
    z_node = sbz_node;
    z_seabed = sbz_seabed;
}

//各パラメータを出力する
void
seabedprop::get(doublereal& sbz_node, doublereal& sbz_seabed) const
{
    sbz_node = z_node;
    sbz_seabed = z_seabed;
}