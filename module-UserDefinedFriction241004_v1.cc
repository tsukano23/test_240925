/*240903　springをもとに書き換え*/  

#include "mbconfig.h"

#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "coulombfriction.h"


/* ----------------------------- UserDefinedFriction start --------------------------------------*/

/*================================================
 * UserDefinedFriction
 * - Constructor
 *================================================*/
UserDefinedFriction::UserDefinedFriction (
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
			"(help message)\n"
			"==== Module: UserDefinedFriction ====\n"
			"- Note: \n"
			//"\tThe force is evaluated as F=EA(L-L0)/L0, where L is the current length between two nodes.\n\n"
			"- Usage: \n"
			"\tuser defined: <label>, UserDefinedFriction, \n"
			"\t//the nodes below shold be 3 DOF \n"
			"\t K, (real), <K>\n"
			"\t M, (real), <M>\n"
			"\t N, (int), <N>\n"
			"\t Nu_s, (real), <Nu_s>\n"
			"\t Nu_d, (real), <Nu_d>\n"
			"\t Nu_s_max, (real), <Nu_s_max>\n"
			<< std::endl);
		if (!HP.IsArg()) {
			throw NoErr(MBDYN_EXCEPT_ARGS);
		}
	}

	/*================================================================================privateの値を読み込む*/
	// read node /*のちのち追加（接触判定の部分が完成次第）
	//pNode = dynamic_cast<const StructNode *>(pDM->ReadNode(HP, Node::STRUCTURAL));

	// read K
	if (!HP.IsKeyWord("K")) {
		silent_cerr("UserDefinedFriction(" << GetLabel() << "): keyword \"K\" expected at line " << HP.GetLineData() << std::endl);
		throw ErrGeneric(MBDYN_EXCEPT_ARGS);
	}
	pHL.setK(HP.GetReal());/*pHLのHLはHookLineの略であるからCoulumbFrictionのCFでpCFに書き換える必要がありそう*/

	// read M
	if (!HP.IsKeyWord("M")) {
		silent_cerr("UserDefinedSpring(" << GetLabel() << "): keyword \"M\" expected at line " << HP.GetLineData() << std::endl);
		throw ErrGeneric(MBDYN_EXCEPT_ARGS);
	}
	pHL.setM(HP.GetReal());

	// read N
	if (!HP.IsKeyWord("N")) {
		silent_cerr("UserDefinedSpring(" << GetLabel() << "): keyword \"N\" expected at line " << HP.GetLineData() << std::endl);
		throw ErrGeneric(MBDYN_EXCEPT_ARGS);
	}
	pHL.setN(HP.GetReal());

	// read Nu_s
	if (!HP.IsKeyWord("Nu_s")) {
		silent_cerr("UserDefinedSpring(" << GetLabel() << "): keyword \"Nu_s\" expected at line " << HP.GetLineData() << std::endl);
		throw ErrGeneric(MBDYN_EXCEPT_ARGS);
	}
	pHL.setNu_s(HP.GetReal());

	// read Nu_d
	if (!HP.IsKeyWord("Nu_d")) {
		silent_cerr("UserDefinedSpring(" << GetLabel() << "): keyword \"Nu_d\" expected at line " << HP.GetLineData() << std::endl);
		throw ErrGeneric(MBDYN_EXCEPT_ARGS);
	}
	pHL.setNu_d(HP.GetReal());

	// read Nu_s_max
	if (!HP.IsKeyWord("Nu_s_max")) {
		silent_cerr("UserDefinedSpring(" << GetLabel() << "): keyword \"Nu_s_max\" expected at line " << HP.GetLineData() << std::endl);
		throw ErrGeneric(MBDYN_EXCEPT_ARGS);
	}
	pHL.setNu_s_max(HP.GetReal());


	//output flag
	SetOutputFlag(pDM->fReadOutput(HP, Elem::LOADABLE));

	//export log file
	pDM->GetLogFile() 
		<< "UserDefinedFriction: " << uLabel
		//<< " " << pNode1->GetLabel()
		//<< " " << pNode2->GetLabel()
		<< " " << K
		<< " " << M
		<< " " << N
		<< " " << Nu_s
		<< " " << Nu_d
		<< " " << Nu_s_max
		<< std::endl;
}

/*================================================
 * UserDefinedFriction
 * - Destructor
 *================================================*/
UserDefinedFriction::~UserDefinedFriction (void)
{
	NO_OP;
}

//==================240925-機能が未完成過ぎてこれ以上変数など少ない状況で作れないので一時中断==================================================================================================================================

/*================================================
 * UserDefinedFriction
 * - Initial assembly configuration
 *================================================*/
void 
UserDefinedFriction::InitialWorkSpaceDim(
	integer* piNumRows,
	integer* piNumCols) const
{
	*piNumRows = 0;
	*piNumCols = 0;
}

VariableSubMatrixHandler&
UserDefinedSpring::InitialAssJac(
	VariableSubMatrixHandler& WorkMat, 
	const VectorHandler& XCurr)
{
	ASSERT(0);
	WorkMat.SetNullMatrix();
	return WorkMat;
}

SubVectorHandler& 
UserDefinedSpring::InitialAssRes(
	SubVectorHandler& WorkVec,
	const VectorHandler& XCurr)
{
	ASSERT(0);
	WorkVec.ResizeReset(0);
	return WorkVec;
}

/*================================================
 * UserDefinedSpring
 * - Initial assembly configuration
 *================================================*/
void
UserDefinedSpring::WorkSpaceDim(integer* piNumRows, integer* piNumCols) const
{
	*piNumRows = 6;
	*piNumCols = 6;
}

SubVectorHandler& 
UserDefinedSpring::AssRes(SubVectorHandler& WorkVec,
	doublereal dCoef,
	const VectorHandler& XCurr, 
	const VectorHandler& XPrimeCurr)
{
	//node1 current data
	const integer iFirstMomentumIndex1 = pNode1->iGetFirstMomentumIndex();
	const Vec3& r1 = pNode1->GetXCurr();

	//node2 current data
	const integer iFirstMomentumIndex2 = pNode2->iGetFirstMomentumIndex();
	const Vec3& r2 = pNode2->GetXCurr();

	//configuring workvec
	integer iNumRows;
	integer iNumCols;
	WorkSpaceDim(&iNumRows, &iNumCols);
	WorkVec.ResizeReset(iNumRows);
	for(int iCnt = 1; iCnt <=3; iCnt++){
		WorkVec.PutRowIndex(iCnt, iFirstMomentumIndex1+iCnt);
	}
	for(int iCnt = 1; iCnt <=3; iCnt++){
		WorkVec.PutRowIndex(iCnt+3, iFirstMomentumIndex2+iCnt);
	}

	//unit vector
	Vec3 unit = Vec3(0.0,0.0,0.0);
	pDV.unitVec(unit, r1, r2);

	//force amplitude	
	doublereal Lnorm = 0.0;
	pDV.norm(Lnorm, r1, r2);
	strain = pHL.strain(Lnorm);
	pHL.force(elastic_force, Lnorm);

	//force calculation
	F_node1 = unit*elastic_force;
	F_node2 = -F_node1;	

	//set vector
	WorkVec.Put(1, F_node1);
	WorkVec.Put(4, F_node2);	

	return WorkVec;
}

VariableSubMatrixHandler& 
UserDefinedSpring::AssJac(VariableSubMatrixHandler& WorkMat,
	doublereal dCoef, 
	const VectorHandler& XCurr,
	const VectorHandler& XPrimeCurr)
{
	FullSubMatrixHandler& WM = WorkMat.SetFull();

	//node1 current data
	const integer iFirstMomentumIndex1 = pNode1->iGetFirstMomentumIndex();
	const integer iPositionIndex1 = pNode1->iGetFirstPositionIndex();
	const Vec3& r1 = pNode1->GetXCurr();

	//node2 current data
	const integer iFirstMomentumIndex2 = pNode2->iGetFirstMomentumIndex();
	const integer iPositionIndex2 = pNode2->iGetFirstPositionIndex();
	const Vec3& r2 = pNode2->GetXCurr();

	//configuring workmat
	integer iNumRows;
	integer iNumCols;
	WorkSpaceDim(&iNumRows, &iNumCols);
	WM.ResizeReset(iNumRows, iNumCols);
	for(int iCnt = 1; iCnt<=3; iCnt++){
		WM.PutRowIndex(iCnt, iFirstMomentumIndex1+iCnt);
		WM.PutColIndex(iCnt, iPositionIndex1+iCnt);
	}	
	for(int iCnt = 1; iCnt<=3; iCnt++){
		WM.PutRowIndex(iCnt+3, iFirstMomentumIndex2+iCnt);
		WM.PutColIndex(iCnt+3, iPositionIndex2+iCnt);
	}

	//unit vector
	Vec3 unit = Vec3(0.0,0.0,0.0);
	pDV.unitVec(unit, r1, r2);

	//force amplitude	
	doublereal Lnorm = 0.0;
	doublereal Fabs = 0.0;
	pDV.norm(Lnorm, r1, r2);
	pHL.force(Fabs, Lnorm);

	//force jacobian
	Vec3 Fx = Vec3(0.0,0.0,0.0);
	pHL.jacobian(Fx, unit);

	//direction vector jacobian
	Mat3x3 J = Eye3;
	pDV.jacobian(J,r1,r2);

	//calc jacobian
	Mat3x3 dF_dx = Mat3x3((unit*Fx.dGet(1)), (unit*Fx.dGet(2)), (unit*Fx.dGet(3)));
	dF_dx += J*Fabs;

	//set matrix
	WM.Put( 1,  1,  dF_dx*dCoef );
	WM.Put( 1,  4, -dF_dx*dCoef );
	WM.Put( 4,  1, -dF_dx*dCoef );
	WM.Put( 4,  4,  dF_dx*dCoef );
	
	return WorkMat;
}

/*================================================
 * UserDefinedSpring
 * - Get connected nodes
 *================================================*/
int
UserDefinedSpring::iGetNumConnectedNodes(void) const
{
	return 2;
}

void
UserDefinedSpring::GetConnectedNodes(std::vector<const Node *>& connectedNodes) const
{
	connectedNodes.resize(2);

	connectedNodes[0] = pNode1;
	connectedNodes[1] = pNode2;
}


/*================================================
 * UserDefinedSpring
 * - etc
 *================================================*/
void 
UserDefinedSpring::SetValue(DataManager *pDM,
	VectorHandler& X, VectorHandler& XP,
	SimulationEntity::Hints *ph)
{
   	NO_OP;
}

std::ostream& 
UserDefinedSpring::Restart(std::ostream& out) const
{
   	return out << "# not implemented yet" << std::endl;
}

unsigned
UserDefinedSpring::iGetInitialNumDof(void) const
{
	return 0;
}

/*================================================
 * UserDefinedSpring
 * - output
 *================================================*/
void
UserDefinedSpring::Output(OutputHandler& OH) const
{
	if (bToBeOutput()) {
		if (OH.UseText(OutputHandler::LOADABLE)) {
			OH.Loadable() << GetLabel()
				<< " " << strain
				<< " " << elastic_force
				<< " " << F_node1
				<< " " << F_node2
				<< std::endl;
		}
	}
}


/* ----------------------------- UserDefinedSpring end -------------------------------------- */


/*===================================================================
 *  Module init function
 *===================================================================*/
extern "C"
int module_init(const char *module_name, void *pdm, void *php)
{
	bool UDEset = true;

	UserDefinedElemRead *rf = new UDERead<UserDefinedSpring>;
	if (!SetUDE("UserDefinedSpring", rf)) {
		delete rf;
		return false;
	}

	if (!UDEset) {
		silent_cerr("UserDefinedSpring: "
			"module_init(" << module_name << ") "
			"failed" << std::endl);
		return -1;
	}

	return 0;
}
