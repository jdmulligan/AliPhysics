/* Copyright(c) 1998-2008, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

//*************************************************************************
// \class AliJetTreeHandler
// \brief helper class to handle a tree for cut optimisation and MVA analyses, based on AliHFTreeHandler and AliAnalysisTaskDmesonJets
// \authors:
// James Mulligan, james.mulligan@berkeley.edu
/////////////////////////////////////////////////////////////

#include "TClonesArray.h"

#include "AliJetTreeHandler.h"

//________________________________________________________________
/// \cond CLASSIMP
ClassImp(AliJetTreeHandler);
/// \endcond

//________________________________________________________________
// Default constructor
AliJetTreeHandler::AliJetTreeHandler():
  TObject(),
  fTreeVar(nullptr),
  fIsMCGenTree(false),
  fJetContainer(nullptr),
  fJetVariables(),
  fCurrentJetCompressed()
{
}

//________________________________________________________________
// Destructor
AliJetTreeHandler::~AliJetTreeHandler()
{
  if(fTreeVar) delete fTreeVar;
}

/**
 * Create jet TTree, with a branch for each jet container
 */
//________________________________________________________________
TTree* AliJetTreeHandler::BuildTree(TString name, TString title)
{
  if(fTreeVar) {
    delete fTreeVar;
    fTreeVar=0x0;
  }
  fTreeVar = new TTree(name.Data(),title.Data());
  
  // Create a branch for the current jet container
  fTreeVar->Branch("Jets", "std::vector<AliJetInfoCompressed>", &fJetVariables);
  
  return fTreeVar;
}

/**
 * Set jet tree variables
 */
//________________________________________________________________
bool AliJetTreeHandler::SetJetVariables()
{
  
  for (const auto jet : fJetContainer->accepted()) {
    
    // Fill AliJetInfoCompressed object from AliEmcalJet object
    fCurrentJetCompressed.Set(jet, fJetContainer);
    
    // Add the AliJetInfoCompressed object to the current jet container's branch
    fJetVariables.push_back(fCurrentJetCompressed);
    
  }
  
  return true;
}

/**
 * Fill jet tree
 */
//________________________________________________________________
void AliJetTreeHandler::FillTree() {

  fTreeVar->Fill();
  
  fJetVariables.clear();
  
}
