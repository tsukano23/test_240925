#include "mbconfig.h"
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "module-seabed.h"
#include "seabedproperty.h"
#include "seabedpropowner.h"

/* -----------------------------ContactLaw  start --------------------------------------*/
/*ContactLaw::ContactLaw(void)
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
*/
/* -----------------------------海底面と接触しているか判別　distinction　start*/
/*void
ContactLaw::Distincion(doublereal D1) const
{
    D1 = D[3] - H[3];
    if (D1 >= 0 )
    {
        flag = 1;
    }
}*/
/* -----------------------------海底面と接触しているか判別　distinction　end*/


/* -----------------------------seabed   end--------------------------------------*/

/*=======================================================================================
 * Constructor and Destructor
 *=======================================================================================*/
//constructor
seabed::seabed (
	unsigned uLabel,
	const DofOwner *pDO,
	DataManager* pDM,
	MBDynParser& HP
)
: Elem(uLabel, flag(0)), UserDefinedElem(uLabel, pDO), seabedpropowner()
//seabedpropとseabedpropownerを分けた場合、seabedpropertyも記載したほうが良いのか？
{
	// help message or no arg error
	if (HP.IsKeyWord("help")) {
		silent_cout(
			"help message\n"
			"==== Module: seabed ====\n"
			"- Note: \n"
			"\tTest, \n"
			"- Usage: \n"
			"\tseabed, z_node, z_seabed;\n"
			<< std::endl);
		
		if (!HP.IsArg()) {
			throw NoErr(MBDYN_EXCEPT_ARGS);
		}
	}

    //ここで、.mbdのインプットファイルからの値をseapropertyクラスにセットする
	doublereal z_node = HP.GetReal();
	doublereal z_seabed = HP.GetReal();
	pseabedprop.setValue(z_node, z_seabed);

	//output flag
	SetOutputFlag(pDM->fReadOutput(HP, Elem::LOADABLE));
	//export log file
	pDM->GetLogFile()
		<< "seabed: " << uLabel
		<< std::endl;
}

//destructor
seabed::~seabed (void)
{
	NO_OP;
}


/*=======================================================================================
 * Intial Assembly Process
 *=======================================================================================*/
//set number of DOF
unsigned int
seabed::iGetInitialNumDof(void) const
{
	return 0;
}

//set initial value
void
seabed::SetInitialValue(VectorHandler& XCurr)
{
	return;
}

//set initial assembly matrix dimension
void 
seabed::InitialWorkSpaceDim(integer* piNumRows, integer* piNumCols) const
{
	*piNumRows = 0;
	*piNumCols = 0;
}

//calculate residual vector for initial assembly analysis
SubVectorHandler& 
seabed::InitialAssRes(
	SubVectorHandler& WorkVec,
	const VectorHandler& XCurr)
{
	WorkVec.ResizeReset(0);
	return WorkVec;
}

//calculate Jaconbian for initial assembly analysis
VariableSubMatrixHandler&
seabed::InitialAssJac(
	VariableSubMatrixHandler& WorkMat, 
	const VectorHandler& XCurr)
{
	WorkMat.SetNullMatrix();
	return WorkMat;
}


/*=======================================================================================
 * Initial Value Problem
 *=======================================================================================*/
//set number of DOF
unsigned int
seabed::iGetNumDof(void) const
{
	return 0;
}

//set DOF type
DofOrder::Order
seabed::GetDofType(unsigned int i) const
{

	return DofOrder::DIFFERENTIAL;
}

//set initial value
void
seabed::SetValue(
	DataManager *pDM,
	VectorHandler& X,
	VectorHandler& XP,
	SimulationEntity::Hints *ph)
{
	return;
}

/*
//print explanation of variables and equations
std::ostream&
seabed::DescribeDof(std::ostream& out, const char *prefix, bool bInitial) const
{
}
std::ostream&
seabed::DescribeEq(std::ostream& out, const char *prefix, bool bInitial) const
{
}
*/

//set matrix dimension
void
seabed::WorkSpaceDim(integer* piNumRows, integer* piNumCols) const
{
	*piNumRows = 0;
	*piNumCols = 0;	
}

//calculate residual vector
SubVectorHandler& 
seabed::AssRes(
	SubVectorHandler& WorkVec,
	doublereal dCoef,
	const VectorHandler& XCurr, 
	const VectorHandler& XPrimeCurr)
{
	WorkVec.ResizeReset(0);
	return WorkVec;
}

//calculate Jacobian matrix
VariableSubMatrixHandler& 
seabed::AssJac(
	VariableSubMatrixHandler& WorkMat,
	doublereal dCoef, 
	const VectorHandler& XCurr,
	const VectorHandler& XPrimeCurr)
{
	WorkMat.SetNullMatrix();
	return WorkMat;
}


/*=======================================================================================
 * Private Data
 *=======================================================================================*/
//set number of private data
unsigned int
seabed::iGetNumPrivData(void) const
{
	return 0;
}

/*
//set index of private data
unsigned int
seabed::iGetPrivDataIdx(const char *s) const
{	
	static const struct {
		int index;
		char name[3];
	}

	data[] = {
			{ 1, "A"},
			{ 2, "B"},
			{ 3, "C"},
	};

	for (unsigned i = 0; i < sizeof(data) / sizeof(data[0]); ++i ) {
		if (0 == strcmp(data[i].name,s)) {
			return data[i].index;
		}
	}

	silent_cerr("seabed (" << GetLabel() << "): no private data \"" << s << "\"" << std::endl);

	return 0;	
}
//function to get private data
doublereal
seabed::dGetPrivData(unsigned int i) const;
{
	switch (i) {
	case 1:
		return a;
	case 2:
		return b;
	case 3:
		return c;
	}
	throw DataManager::ErrGeneric(MBDYN_EXCEPT_ARGS);
}
*/

/*=======================================================================================
 * Configure runtime processing
 *=======================================================================================*/
//describe update function
void 
seabed::Update(const VectorHandler& XCurr, const VectorHandler& XPrimeCurr)
{
	return;
}
//process before each iteration
void
seabed::BeforePredict(VectorHandler& /* X */ ,
					VectorHandler& /* XP */ ,
					VectorHandler& /* XPrev */ ,
					VectorHandler& /* XPPrev */ ) const
{
	return;
}
//process after each iteration
void
seabed::AfterPredict(VectorHandler& X, VectorHandler& XP)
{
	return;
}
//process after convergence (each time step)
void
seabed::AfterConvergence(const VectorHandler& X, const VectorHandler& XP)
{
	return;
}


/*=======================================================================================
 * Output
 *=======================================================================================*/
//output file 
void
seabed::Output(OutputHandler& OH) const
{
	if (bToBeOutput()) {
		if (OH.UseText(OutputHandler::LOADABLE)) {
			OH.Loadable() << GetLabel()
				<< std::endl;
		}
	}
}


/*=======================================================================================
 * etc
 *=======================================================================================*/
/*
//print information of connected nodes
int
seabed::iGetNumConnectedNodes(void) const
{
	return 0;
}
void
seabed::GetConnectedNodes(std::vector<const Node *>& connectedNodes) const
{
	return;
}
*/
//output restart file
std::ostream&
seabed::Restart(std::ostream& out) const
{
   	return out << "# seabed (" << GetLabel() << "): not implemented yet" << std::endl;
}
/* ----------------------------- seabed end -------------------------------------- */


/*=======================================================================================
 *  Module init function
 *=======================================================================================*/
extern "C"
int module_init(const char *module_name, void *pdm, void *php)
{
	bool UDEset = true;

	UserDefinedElemRead *rf = new UDERead<seabed>;
	if (!SetUDE("seabed", rf)) {
		delete rf;
		return false;
	}

	if (!UDEset) {
		silent_cerr("seabed: "
			"module_init(" << module_name << ") "
			"failed" << std::endl);
		return -1;
	}

	return 0;
}



