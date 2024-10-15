#include "mbconfig.h"
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "module-contactlaw.h"
/* -----------------------------contactlaw  start --------------------------------------*/
/*=======================================================================================
 * Constructor and Destructor
 *=======================================================================================*/
//constructor
contactlaw::contactlaw (
	unsigned uLabel,
	const DofOwner *pDO,
	DataManager* pDM,
	MBDynParser& HP
)
: Elem(uLabel, flag(0)), UserDefinedElem(uLabel, pDO)
{
	// help message or no arg error
	if (HP.IsKeyWord("help")) {
		silent_cout(
			"help message\n"
			"==== Module: contactlaw ====\n"
			"- Note: \n"
			"\ttest\n"
			"- Usage: \n"
			"\tcontactlaw;\n"
			<< std::endl);
		if (!HP.IsArg()) {
			throw NoErr(MBDYN_EXCEPT_ARGS);
		}
	}

	// read node
	pNode = dynamic_cast<const StructNode *>(pDM->ReadNode(HP, Node::STRUCTURAL));


	// read SeaBed object
	/*module-seabedのelementのラベルを取得することで間接的にseabedpropertyクラスにアクセスできるようにしている。*/
	unsigned int uElemLabel = (unsigned int)HP.GetInt();
	pSeaBed = dynamic_cast<SeaBed *>(pDM->pFindElem(Elem::LOADABLE, uElemLabel));

/*懸念点(1)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
　・モデルから読み取りが必要かつ、今までクラスで定義していたz_node,z_seabedらをここで再定義してmbdynファイルから読み取るという認識であっているか？
*/
	// read z_node
	if (!HP.IsKeyWord("z_node")) {
		silent_cerr("UserDefinedSpring(" << GetLabel() << "): keyword \"z_node\" expected at line " << HP.GetLineData() << std::endl);
		throw ErrGeneric(MBDYN_EXCEPT_ARGS);
	}
	z_node = HP.GetReal();

	// read z_seabed
	if (!HP.IsKeyWord("z_seabed")) {
		silent_cerr("UserDefinedSpring(" << GetLabel() << "): keyword \"z_seabed\" expected at line " << HP.GetLineData() << std::endl);
		throw ErrGeneric(MBDYN_EXCEPT_ARGS);
	}
	z_seabed = HP.GetReal();

	//output flag
	SetOutputFlag(pDM->fReadOutput(HP, Elem::LOADABLE));
	//export log file
	pDM->GetLogFile()
		<< "contactlaw: " << uLabel
		<< " " << pNode->GetLabel()
		<< " " << pSea->GetLabel()
		<< std::endl;
}

//destructor
contactlaw::~contactlaw (void)
{
	NO_OP;
}


/*=======================================================================================
 * Intial Assembly Process
 *=======================================================================================*/
//set number of DOF
unsigned int
contactlaw::iGetInitialNumDof(void) const
{
	return 0;
}

//set initial value
void
contactlaw::SetInitialValue(VectorHandler& XCurr)
{
	return;
}

//set initial assembly matrix dimension
void 
contactlaw::InitialWorkSpaceDim(integer* piNumRows, integer* piNumCols) const
{
	*piNumRows = 0;
	*piNumCols = 0;
}

//calculate residual vector for initial assembly analysis
SubVectorHandler& 
contactlaw::InitialAssRes(
	SubVectorHandler& WorkVec,
	const VectorHandler& XCurr)
{
	WorkVec.ResizeReset(0);
	return WorkVec;
}

//calculate Jaconbian for initial assembly analysis
VariableSubMatrixHandler&
contactlaw::InitialAssJac(
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
contactlaw::iGetNumDof(void) const
{
	return 0;
}

//set DOF type
DofOrder::Order
contactlaw::GetDofType(unsigned int i) const
{

	return DofOrder::DIFFERENTIAL;
}

//set initial value
void
contactlaw::SetValue(
	DataManager *pDM,
	VectorHandler& X,
	VectorHandler& XP,
	SimulationEntity::Hints *ph)
{
	return;
}

//print explanation of variables and equations
std::ostream&
contactlaw::DescribeDof(std::ostream& out, const char *prefix, bool bInitial) const
{
}
std::ostream&
contactlaw::DescribeEq(std::ostream& out, const char *prefix, bool bInitial) const
{
}


//set matrix dimension
void
contactlaw::WorkSpaceDim(integer* piNumRows, integer* piNumCols) const
{
	*piNumRows = 1;
	*piNumCols = 1;	
}

//calculate residual vector
SubVectorHandler& 
contactlaw::AssRes(
	SubVectorHandler& WorkVec,
	doublereal dCoef,
	const VectorHandler& XCurr, 
	const VectorHandler& XPrimeCurr)
{
	//obtain vector dimension
	integer iNumRows;
	integer iNumCols;
	WorkSpaceDim(&iNumRows, &iNumCols);
	WorkVec.ResizeReset(iNumRows);

	//set index from global state vector
	const integer iPositionIndex = pNode->iGetFirstPositionIndex();
	const integer iMomentumIndex = pNode->iGetFirstMomentumIndex();
	WorkVec.PutRowIndex(1, iMomentumIndex+3);

/*=====================================================================================================*/

	//compare z coordinates
	doublereal rho,g,Zs;
	pSeabed->get(z_node, z_seabed);

	integer s;
	doublereal D = z_node - z_seabed;

	if(D>0.0){
		s = 0;
	} else{
		s = 1;
		std ::cout << "this node is contact"<<endl;
	}

}

/*=====================================================================================================*/

//calculate Jacobian matrix
VariableSubMatrixHandler& 
contactlaw::AssJac(
	VariableSubMatrixHandler& WorkMat,
	doublereal dCoef, 
	const VectorHandler& XCurr,
	const VectorHandler& XPrimeCurr)
{
	FullSubMatrixHandler& WM = WorkMat.SetFull();

	//obtain vector dimension
	integer iNumRows;
	integer iNumCols;
	WorkSpaceDim(&iNumRows, &iNumCols);
	WM.ResizeReset(iNumRows, iNumCols);

	//set index from global matrix
  	const integer iPositionIndex = pNode->iGetFirstPositionIndex();
	const integer iMomentumIndex = pNode->iGetFirstMomentumIndex();
	WM.PutRowIndex(1, iMomentumIndex+3);
	WM.PutColIndex(1, iPositionIndex+3);

	//calculate forces
	
}

/*=====================================================================================================*/

/*=======================================================================================
 * Private Data
 *=======================================================================================*/
//set number of private data
unsigned int
contactlaw::iGetNumPrivData(void) const
{
	return 0;
}

/*
//set index of private data
unsigned int
contactlaw::iGetPrivDataIdx(const char *s) const
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

	silent_cerr("contactlaw (" << GetLabel() << "): no private data \"" << s << "\"" << std::endl);

	return 0;	
}
//function to get private data
doublereal
contactlaw::dGetPrivData(unsigned int i) const;
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
contactlaw::Update(const VectorHandler& XCurr, const VectorHandler& XPrimeCurr)
{
	return;
}
//process before each iteration
void
contactlaw::BeforePredict(VectorHandler& /* X */ ,
					VectorHandler& /* XP */ ,
					VectorHandler& /* XPrev */ ,
					VectorHandler& /* XPPrev */ ) const
{
	return;
}
//process after each iteration
void
contactlaw::AfterPredict(VectorHandler& X, VectorHandler& XP)
{
	return;
}
//process after convergence (each time step)
void
contactlaw::AfterConvergence(const VectorHandler& X, const VectorHandler& XP)
{
	return;
}


/*=======================================================================================
 * Output
 *=======================================================================================*/
//output file 
void
contactlaw::Output(OutputHandler& OH) const
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
//print information of connected nodes
int
contactlaw::iGetNumConnectedNodes(void) const
{
	return 0;
}
void
contactlaw::GetConnectedNodes(std::vector<const Node *>& connectedNodes) const
{
	return;
}
//output restart file
std::ostream&
contactlaw::Restart(std::ostream& out) const
{
   	return out << "# contactlaw (" << GetLabel() << "): not implemented yet" << std::endl;
}

/* ----------------------------- contactlaw end -------------------------------------- */


/*=======================================================================================
 *  Module init function
 *=======================================================================================*/
extern "C"
int module_init(const char *module_name, void *pdm, void *php)
{
	bool UDEset = true;

	UserDefinedElemRead *rf = new UDERead<contactlaw>;
	if (!SetUDE("contactlaw", rf)) {
		delete rf;
		return false;
	}

	if (!UDEset) {
		silent_cerr("contactlaw: "
			"module_init(" << module_name << ") "
			"failed" << std::endl);
		return -1;
	}

	return 0;
}

