/* Siconos-Kernel version 1.3.0, Copyright INRIA 2005-2006.
 * Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 * Siconos is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * Siconos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Siconos; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Contact: Vincent ACARY vincent.acary@inrialpes.fr
*/
#include "LCP.h"
#include <stdlib.h>

// includes to be deleted thanks to factories?
#include "LagrangianLinearR.h"
#include "LinearTIR.h"

using namespace std;

// Default constructor (private)
LCP::LCP():
  OneStepNSProblem("LCP"), w(NULL), z(NULL), M(NULL), q(NULL),
  isWAllocatedIn(false), isZAllocatedIn(false), isMAllocatedIn(false), isQAllocatedIn(false) ,
  isMSparseBlock(false) , Mspbl(NULL)
{}

// xml constructor
LCP::LCP(OneStepNSProblemXML* onestepnspbxml, Simulation* newSimu):
  OneStepNSProblem("LCP", onestepnspbxml, newSimu), w(NULL), z(NULL), M(NULL), q(NULL),
  isWAllocatedIn(false), isZAllocatedIn(false), isMAllocatedIn(false), isQAllocatedIn(false) ,
  isMSparseBlock(false) , Mspbl(NULL)
{
  LCPXML * xmllcp = (static_cast<LCPXML*>(onestepnspbxml));

  // If both q and M are given in xml file, check if sizes are consistent
  if (xmllcp->hasQ() && xmllcp->hasM() && ((xmllcp->getM()).size(0) != (xmllcp->getQ()).size()))
    RuntimeException::selfThrow("LCP: xml constructor, inconsistent sizes between given q and M");

  // first nlcp is given by M matrix size in xml file
  if (xmllcp->hasM())
  {
    sizeOutput = (xmllcp->getM()).size(0);
    M = new SimpleMatrix(xmllcp->getM());
    isMAllocatedIn = true;
  }

  if (xmllcp->hasQ())
  {
    // get sizeOutput if necessary
    if (M == NULL)
      sizeOutput = (xmllcp->getQ()).size();

    q = new SimpleVector(xmllcp->getQ());
    isQAllocatedIn = true;
  }
}

// Constructor from a set of data (appart from Simulation and id, all arguments are optional)
LCP::LCP(Simulation* newSimu, const string newId, const string newSolver, const unsigned int MaxIter,
         const double  Tolerance, const string  NormType, const double  SearchDirection):
  OneStepNSProblem("LCP", newSimu, newId), w(NULL), z(NULL), M(NULL), q(NULL),
  isWAllocatedIn(false), isZAllocatedIn(false), isMAllocatedIn(false), isQAllocatedIn(false) ,
  isMSparseBlock(false) , Mspbl(NULL)
{
  // set solver:
  solver = new Solver(nspbType, newSolver, MaxIter, Tolerance, NormType, SearchDirection);
  isSolverAllocatedIn = true;
}

// Constructor from a set of data
LCP::LCP(Solver* newSolver, Simulation* newSimu, const string newId):
  OneStepNSProblem("LCP", newSimu, newId, newSolver), w(NULL), z(NULL), M(NULL), q(NULL),
  isWAllocatedIn(false), isZAllocatedIn(false), isMAllocatedIn(false), isQAllocatedIn(false) ,
  isMSparseBlock(false) , Mspbl(NULL)
{}

// destructor
LCP::~LCP()
{
  if (isWAllocatedIn) delete w;
  w = NULL;
  if (isZAllocatedIn) delete z;
  z = NULL;
  if (isMAllocatedIn)
    if (isMSparseBlock) freeSpBlMat(Mspbl);
    else delete M;
  M = NULL;
  Mspbl = NULL;
  if (isQAllocatedIn) delete q;
  q = NULL;
}

// Setters

void LCP::setW(const SimpleVector& newValue)
{
  if (sizeOutput != newValue.size())
    RuntimeException::selfThrow("LCP: setW, inconsistent size between given w size and problem size. You should set sizeOutput before");

  if (w == NULL)
  {
    w = new SimpleVector(sizeOutput);
    isWAllocatedIn = true;
  }
  else if (w->size() != sizeOutput)
    RuntimeException::selfThrow("LCP: setW, w size differs from sizeOutput");

  *w = newValue;
}

void LCP::setWPtr(SimpleVector* newPtr)
{
  if (sizeOutput != newPtr->size())
    RuntimeException::selfThrow("LCP: setWPtr, inconsistent size between given w size and problem size. You should set sizeOutput before");

  if (isWAllocatedIn) delete w;
  w = newPtr;
  isWAllocatedIn = false;
}


void LCP::setZ(const SimpleVector& newValue)
{
  if (sizeOutput != newValue.size())
    RuntimeException::selfThrow("LCP: setZ, inconsistent size between given z size and problem size. You should set sizeOutput before");

  if (z == NULL)
  {
    z = new SimpleVector(sizeOutput);
    isZAllocatedIn = true;
  }

  *z = newValue;
}

void LCP::setZPtr(SimpleVector* newPtr)
{
  if (sizeOutput != newPtr->size())
    RuntimeException::selfThrow("LCP: setZPtr, inconsistent size between given z size and problem size. You should set sizeOutput before");

  if (isZAllocatedIn) delete z;
  z = newPtr;
  isZAllocatedIn = false;
}

void LCP::setM(const SiconosMatrix& newValue)
{
  if (isMSparseBlock)
    RuntimeException::selfThrow("LCP: setM, impossible since M is sparse by blocks.");
  if (sizeOutput != newValue.size(0) || sizeOutput != newValue.size(1))
    RuntimeException::selfThrow("LCP: setM, inconsistent size between given M size and problem size. You should set sizeOutput before");

  if (M == NULL)
  {
    M = new SimpleMatrix(sizeOutput, sizeOutput);
    isMAllocatedIn = true;
  }

  *M = newValue;
}

void LCP::setMPtr(SiconosMatrix* newPtr)
{
  if (isMSparseBlock)
    RuntimeException::selfThrow("LCP: setMPtr, impossible since M is sparse by blocks.");
  if (sizeOutput != newPtr->size(0) || sizeOutput != newPtr->size(1))
    RuntimeException::selfThrow("LCP: setMPtr, inconsistent size between given M size and problem size. You should set sizeOutput before");

  if (isMAllocatedIn) delete M;
  M = newPtr;
  isMAllocatedIn = false;
}


void LCP::setQ(const SimpleVector& newValue)
{
  if (sizeOutput != newValue.size())
    RuntimeException::selfThrow("LCP: setQ, inconsistent size between given q size and problem size. You should set sizeOutput before");

  if (q == NULL)
  {
    q = new SimpleVector(sizeOutput);
    isQAllocatedIn = true;
  }

  *q = newValue;
}

void LCP::setQPtr(SimpleVector* newPtr)
{
  if (sizeOutput != newPtr->size())
    RuntimeException::selfThrow("LCP: setQPtr, inconsistent size between given q size and problem size. You should set sizeOutput before");

  if (isQAllocatedIn) delete q;
  q = newPtr;
  isQAllocatedIn = false;
}

void LCP::initialize()
{
  // This function performs all steps that are not time dependant
  // General initialize for OneStepNSProblem
  OneStepNSProblem::initialize();

  // get topology
  Topology * topology = simulation->getModelPtr()->getNonSmoothDynamicalSystemPtr()->getTopologyPtr();

  // if all relative degrees are equal to 0 or 1
  if (topology->isTimeInvariant() &&   !OSNSInteractions.isEmpty())
  {
    // computeSizeOutput and updateBlocks were already done in OneStepNSProblem::initialize
    if (sizeOutput != 0)
    {
      assembleM();
      // check z and w sizes and reset if necessary
      if (z == NULL)
      {
        z = new SimpleVector(sizeOutput);
        isZAllocatedIn = true;
      }
      else if (z->size() != sizeOutput)
      {
        // reset z if it has a wrong size
        if (isZAllocatedIn) delete z;
        z = new SimpleVector(sizeOutput);
        isZAllocatedIn = true;
      }

      if (w == NULL)
      {
        w = new SimpleVector(sizeOutput);
        isWAllocatedIn = true;
      }
      else if (w->size() != sizeOutput)
      {
        // reset w if it has a wrong size
        if (isWAllocatedIn) delete w;
        w = new SimpleVector(sizeOutput);
        isWAllocatedIn = true;
      }

      w->zero();
      z->zero();
    }
  }

  // If topology is time-dependant, all the above commands are called during preCompute function.
}

void LCP::preCompute(const double time)
{
  // compute M and q operators for LCP problem

  // get topology
  Topology * topology = simulation->getModelPtr()->getNonSmoothDynamicalSystemPtr()->getTopologyPtr();

  if (!topology->isTimeInvariant())
    computeSizeOutput();

  if (sizeOutput != 0)
  {
    if (!topology->isTimeInvariant())
    {
      updateBlocks();
      assembleM();
      // check z and w sizes and reset if necessary
      if (z == NULL)
      {
        z = new SimpleVector(sizeOutput);
        isZAllocatedIn = true;
        z->zero();
      }
      else if (z->size() != sizeOutput)
      {
        // reset z if it has a wrong size
        if (isZAllocatedIn) delete z;
        z = new SimpleVector(sizeOutput);
        isZAllocatedIn = true;
        z->zero();
      }

      if (w == NULL)
      {
        w = new SimpleVector(sizeOutput);
        isWAllocatedIn = true;
        w->zero();
      }
      else if (w->size() != sizeOutput)
      {
        // reset w if it has a wrong size
        if (isWAllocatedIn) delete w;
        w = new SimpleVector(sizeOutput);
        isWAllocatedIn = true;
        w->zero();
      }
    }
    computeQ(time);
  }
}

void LCP::computeBlock(UnitaryRelation* UR1, UnitaryRelation* UR2)
{

  // Warning: we suppose that at this point, all non linear operators (G for lagrangian relation for example) have been computed through plug-in mechanism.

  // Get dimension of the NonSmoothLaw (ie dim of the block)
  unsigned int nslawSize1 = UR1->getNonSmoothLawSize();
  unsigned int nslawSize2 = UR2->getNonSmoothLawSize();
  // Check allocation
  if (blocks[UR1][UR2] == NULL)
    blocks[UR1][UR2] = new SimpleMatrix(nslawSize1, nslawSize2);

  // Get DS common between UR1 and UR2
  DynamicalSystemsSet commonDS = intersection(UR1->getDynamicalSystems(), UR2->getDynamicalSystems());
  DSIterator itDS;

  // Get the W and Theta maps of one of the Unitary Relation - Warning: in the current version, if OSI!=Moreau, this fails.
  // If OSI = MOREAU, centralBlocks = W
  // if OSI = LSODAR, centralBlocks = M (mass matrices)
  MapOfMatrices centralBlocks;
  MapOfDouble Theta; // If OSI = LSODAR, Theta remains empty
  getOSIMaps(UR1, centralBlocks, Theta);

  SiconosMatrix* currentBlock = blocks[UR1][UR2];
  currentBlock->zero();
  SiconosMatrix *leftBlock, *rightBlock, *extraBlock;
  unsigned int sizeDS;
  string relationType1, relationType2;
  double h = simulation->getTimeDiscretisationPtr()->getH();
  bool flagRightBlock = false;

  // Note that Lsodar is available only for Lagrangian systems at the time.
  // Exception will be thrown for any other DS (in getOSIMaps)

  // General form of the block is :   block = a*extraBlock + b * leftBlock * centralBlocks * rightBlock
  // a and b are scalars, centralBlocks a matrix depending on the integrator (and on the DS), the simulation type ...
  // left, right and extra depend on the relation type and the non smooth law.
  relationType1 = UR1->getRelationType();
  relationType2 = UR2->getRelationType();
  if (UR1 == UR2 &&  relationType1 == LINEARTIRELATION)
  {
    extraBlock = new SimpleMatrix(nslawSize1, nslawSize1);
    UR1->getExtraBlock(extraBlock);
    *currentBlock += *extraBlock;// specific to LinearTIR, get D matrix added only on blocks of the diagonal.
    delete extraBlock;
  }

  // loop over the common DS
  for (itDS = commonDS.begin(); itDS != commonDS.end(); itDS++)
  {
    sizeDS = (*itDS)->getDim();
    // get blocks corresponding to the current DS
    // These blocks depends on the relation type.
    leftBlock = new SimpleMatrix(nslawSize1, sizeDS);

    UR1->getLeftBlockForDS(*itDS, leftBlock);
    // Computing depends on relation type -> move this in UnitaryRelation method?
    if (relationType1 == LINEARTIRELATION && relationType2 == LINEARTIRELATION)
    {
      rightBlock = new SimpleMatrix(sizeDS, nslawSize2);
      UR2->getRightBlockForDS(*itDS, rightBlock);
      *currentBlock += h * Theta[*itDS]* *leftBlock * (*centralBlocks[*itDS] * *rightBlock); //left = C, right = B
      delete rightBlock;
    }
    else if ((relationType1 == LAGRANGIANRELATION || relationType1 == LAGRANGIANLINEARRELATION) && (relationType2 == LAGRANGIANRELATION ||  relationType2 == LAGRANGIANLINEARRELATION))
    {
      if (UR1 == UR2)
        rightBlock = leftBlock ;
      else
      {
        rightBlock = new SimpleMatrix(nslawSize2, sizeDS);
        UR2->getLeftBlockForDS(*itDS, rightBlock);
        // Warning: we use getLeft for Right block because right = transpose(left) and because of size checking inside the getBlock function,
        // a getRight call will fail.
        flagRightBlock = true;
      }

      *currentBlock +=  *leftBlock * (centralBlocks[*itDS])->multTranspose(*rightBlock); // left = right = G or H
    }
    else RuntimeException::selfThrow("LCP::computeBlock not yet implemented for relation of type " + relationType1);
    delete leftBlock;
    if (flagRightBlock) delete rightBlock;
  }
}

void LCP::assembleM() //
{
  // === Description ===
  // For each Unitary Relation which is active (ie which is in indexSet[1] of the Simulation), named itRow (it corresponds to a row of block in M),
  // and for each Unitary Relation connected to itRow and active, named itCol, we get the block[itRow][itCol] and copy it at the right place in M matrix of the LCP
  //
  // Note that if a Unitary Relation is connected to another one (ie if they have common DS), the corresponding block must be in blocks map. This is the role of
  // updateBlocks() to ensure this.
  // But the presence of a block in the map does not imply that its corresponding UR are active, since this block may have been computed at a previous time step.
  // That is why we need to check if itCol is in indexSet1.
  //
  // See updateBlocks function for more details.

  // Get index set 1 from Simulation
  UnitaryRelationsSet indexSet = simulation->getIndexSet(levelMin);
  UnitaryRelationIterator itRow;
  unsigned int pos = 0, col = 0; // index position used for block copy into M, see below.
  UnitaryMatrixColumnIterator itCol;

  if (isMSparseBlock)    // sparse block matrix Mspbl assembling
  {
    int i;

    Mspbl = new SparseBlockStructuredMatrix();
    Mspbl->size = blocksPositions.size();
    Mspbl->blocksize = (int*) malloc(Mspbl->size * sizeof(int));
    for (itRow = indexSet.begin(); itRow != indexSet.end(); ++itRow)
      Mspbl->blocksize[blocksIndexes[*itRow]] = blocksPositions[*itRow];
    for (i = 0; i < Mspbl->size - 1; i++) Mspbl->blocksize[i] = Mspbl->blocksize[i + 1] - Mspbl->blocksize[i];
    Mspbl->blocksize[Mspbl->size - 1] = sizeOutput - Mspbl->blocksize[Mspbl->size - 1];
    isMAllocatedIn = true;

    // computation of the number of non-null blocks
    Mspbl->nbblocks = 0;
    for (itRow = indexSet.begin(); itRow != indexSet.end(); ++itRow)
      for (itCol = blocks[*itRow].begin(); itCol != blocks[*itRow].end(); ++itCol)
        if ((indexSet.find((*itCol).first)) != indexSet.end())(Mspbl->nbblocks)++;

    // allocation of Mspbl coordinates vectors and non null block pointers vector
    Mspbl->RowIndex = (int*)malloc(Mspbl->nbblocks * sizeof(int));
    Mspbl->ColumnIndex = (int*)malloc(Mspbl->nbblocks * sizeof(int));
    Mspbl->block = (double**)malloc(Mspbl->nbblocks * sizeof(double*));

    // insertion of non null blocks pointers
    // each one is set to SimpleMatrix "mat" address : only pointer copy
    int nblins = 0;     // counter of blocks already inserted
    int rowind, colind;
    bool isMoreFar;

    for (itRow = indexSet.begin(); itRow != indexSet.end(); ++itRow)
    {
      for (itCol = blocks[*itRow].begin(); itCol != blocks[*itRow].end(); ++itCol)
      {
        if ((indexSet.find((*itCol).first)) != indexSet.end())
        {
          i = 0;
          isMoreFar = true;
          rowind = blocksIndexes[*itRow];
          colind = blocksIndexes[(*itCol).first];
          while (i < nblins && isMoreFar)
          {
            isMoreFar = (rowind > Mspbl->RowIndex[i]) || (rowind == Mspbl->RowIndex[i] && colind > Mspbl->ColumnIndex[i]);
            i++;
          }

          if (!isMoreFar)  // insert new block among existing blocks
          {
            for (int j = nblins ; j >= i ; j--)
            {
              Mspbl->RowIndex[j] = Mspbl->RowIndex[j - 1];
              Mspbl->ColumnIndex[j] = Mspbl->ColumnIndex[j - 1];
              Mspbl->block[j] = Mspbl->block[j - 1];
            }
            Mspbl->RowIndex[i - 1] = rowind;
            Mspbl->ColumnIndex[i - 1] = colind;
            Mspbl->block[i - 1] = (blocks[*itRow][(*itCol).first])->getArray();
          }
          else      // insert new block at the end of existing blocks (i == nblins)
          {
            Mspbl->RowIndex[i] = rowind;
            Mspbl->ColumnIndex[i] = colind;
            Mspbl->block[i] = (blocks[*itRow][(*itCol).first])->getArray();
          }
          nblins++;
        }
      }
    }

  }
  else      // full matrix M assembling
  {
    // === Memory allocation, if required ===
    if (M == NULL)
    {
      M = new SimpleMatrix(sizeOutput, sizeOutput);
      isMAllocatedIn = true;
    }
    else if (M->size(0) != sizeOutput || M->size(1) != sizeOutput)
    {
      // reset M matrix if it has a wrong size
      if (isMAllocatedIn) delete M;
      M = new SimpleMatrix(sizeOutput, sizeOutput);
      isMAllocatedIn = true;
    }

    M->zero();
    // === Loop through "active" Unitary Relations (ie present in indexSets[level]) ===

    for (itRow = indexSet.begin(); itRow != indexSet.end(); ++itRow)
    {
      for (itCol = blocks[*itRow].begin(); itCol != blocks[*itRow].end(); ++itCol)
      {
        // *itRow and itCol are UnitaryRelation*.

        // Check that itCol is in Index set 1
        if ((indexSet.find((*itCol).first)) != indexSet.end())
        {
          pos = blocksPositions[*itRow];
          col = blocksPositions[(*itCol).first];
          // copy the block into Mlcp - pos/col: position in M (row and column) of first element of the copied block
          M->blockMatrixCopy(*(blocks[*itRow][(*itCol).first]), pos, col); // \todo avoid copy
        }
      }
    }
    // === end of UnitaryRelations loop ===
  }
}

void LCP::computeQ(const double time)
{

  // === Memory allocation, if required ===
  if (q == NULL)
  {
    q = new SimpleVector(sizeOutput);
    isQAllocatedIn = true;
  }
  else if (q->size() != sizeOutput)
  {
    // reset q if it has a wrong size
    if (isQAllocatedIn) delete q;
    q = new SimpleVector(sizeOutput);
    isQAllocatedIn = true;
  }
  q->zero();

  // === Get index set from Simulation ===
  UnitaryRelationsSet indexSet = simulation->getIndexSet(levelMin);
  SimpleVector * yOut;

  // === Loop through "active" Unitary Relations (ie present in indexSets[level]) ===

  unsigned int pos = 0;
  unsigned int nsLawSize;
  UnitaryRelationIterator itCurrent, itLinked;
  string simulationType = simulation->getType();
  for (itCurrent = indexSet.begin(); itCurrent !=  indexSet.end(); ++itCurrent)
  {
    // *itCurrent is a UnitaryRelation*.

    // Compute free output, this depends on the type of non smooth problem, on the relation type and on the non smooth law
    nsLawSize = (*itCurrent)->getNonSmoothLawSize();
    yOut = new SimpleVector(nsLawSize);

    (*itCurrent)->computeEquivalentY(time, levelMin, simulationType, yOut);

    pos = blocksPositions[*itCurrent];
    // Copy yOut at the right position in q.
    for (unsigned int i = 0; i < yOut->size(); i++)
      (*q)(i + pos) = (*yOut)(i);
    delete yOut;
  }
}

void LCP::compute(const double time)
{
  // --- Prepare data for LCP computing ---
  preCompute(time);

  // --- Call Numerics solver ---
  if (sizeOutput != 0)
  {
    int info;
    int Nlcp = (int)sizeOutput;
    int iter, titer;
    double err;

    method solvingMethod = *(solver->getSolvingMethodPtr());

    if (isMSparseBlock)
      info = lcp_solver_block(Mspbl , q->getArray() , &solvingMethod , z->getArray() , w->getArray() , &iter , &titer , &err);
    else
      info = lcp_solver(M->getArray(), q->getArray(), &Nlcp, &solvingMethod, z->getArray(), w->getArray());

    // \warning : info value and signification depends on solver type ...
    check_solver(info);
    // --- Recover the desired variables from LCP output ---
    postCompute(w, z);
  }
}

void LCP::postCompute(SiconosVector* w, SiconosVector* z)
{
  // === Get index set from Topology ===
  UnitaryRelationsSet indexSet = simulation->getIndexSet(levelMin);

  // y and lambda vectors
  //  vector< SimpleVector* >  Y, Lambda;
  SimpleVector *lambda, *y;

  // === Loop through "active" Unitary Relations (ie present in indexSets[1]) ===

  unsigned int pos = 0;
  unsigned int nsLawSize;
  UnitaryRelationIterator itCurrent, itLinked;

  for (itCurrent = indexSet.begin(); itCurrent !=  indexSet.end(); ++itCurrent)
  {
    // *itCurrent is a UnitaryRelation*.
    // size if a block that corresponds to the current UnitaryRelation
    nsLawSize = (*itCurrent)->getNonSmoothLawSize();
    // Get the relative position of UR-block in the vector w or z
    pos = blocksPositions[*itCurrent];

    // Get Y and Lambda for the current Unitary Relation
    y = static_cast<SimpleVector*>((*itCurrent)-> getYPtr(levelMin));
    lambda = static_cast<SimpleVector*>((*itCurrent)->getLambdaPtr(levelMin));
    static_cast<SimpleVector*>(w)->getBlock(pos, nsLawSize, *y) ; // Warning: yEquivalent is saved in y !!
    static_cast<SimpleVector*>(z)->getBlock(pos, nsLawSize, *lambda) ;
  }
}

void LCP::display() const
{
  cout << "======= LCP display ======" << endl;
  cout << "| sizeOutput : " << sizeOutput << endl;
  cout << "| LCP Matrix M  : " << endl;
  if (M != NULL) M->display();
  else cout << "-> NULL" << endl;
  cout << "| LCP vector q : " << endl;
  if (q != NULL) q->display();
  else cout << "-> NULL" << endl;
  cout << "==========================" << endl;

}

void LCP::saveNSProblemToXML()
{
  OneStepNSProblem::saveNSProblemToXML();
  if (onestepnspbxml != NULL)
  {
    (static_cast<LCPXML*>(onestepnspbxml))->setM(*M);
    (static_cast<LCPXML*>(onestepnspbxml))->setQ(*q);
  }
  else RuntimeException::selfThrow("LCP::saveNSProblemToXML - OneStepNSProblemXML object not exists");
}

void LCP::saveMToXML()
{
  if (onestepnspbxml != NULL)
  {
    (static_cast<LCPXML*>(onestepnspbxml))->setM(*M);
  }
  else RuntimeException::selfThrow("LCP::saveMToXML - OneStepNSProblemXML object not exists");
}

void LCP::saveQToXML()
{
  if (onestepnspbxml != NULL)
  {
    (static_cast<LCPXML*>(onestepnspbxml))->setQ(*q);
  }
  else RuntimeException::selfThrow("LCP::saveQToXML - OneStepNSProblemXML object not exists");
}

LCP* LCP::convert(OneStepNSProblem* osnsp)
{
  LCP* lcp = dynamic_cast<LCP*>(osnsp);
  return lcp;
}

