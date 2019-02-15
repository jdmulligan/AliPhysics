#ifndef ALIJETTREEHANDLER_H
#define ALIJETTREEHANDLER_H

/* Copyright(c) 1998-2008, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

//*************************************************************************
// \class AliJetTreeHandler
// \brief helper class to handle a tree for cut optimisation and MVA analyses, based heavily on AliHFTreeHandler and AliAnalysisTaskDmesonJets
// \authors:
// James Mulligan, james.mulligan@berkeley.edu
/////////////////////////////////////////////////////////////

class TClonesArray;

#include "TTree.h"

#include "AliTLorentzVector.h"
#include "AliJetInfoCompressed.h"
#include "AliJetContainer.h"

//________________________________________________________________
//****************************************************************
class AliJetTreeHandler : public TObject
{
  public:

    AliJetTreeHandler();
    virtual ~AliJetTreeHandler();

    // Core methods
    TTree* BuildTree(TString name, TString title);
    bool SetJetVariables();
    void FillTree(); //to be called for each event
  
    // Setters
    void SetJetContainer(AliJetContainer* jetCont) { fJetContainer = jetCont; }
  
    // Utility functions
    Double_t GetJetPt(const AliEmcalJet* jet, AliJetContainer* jetCont);

  protected:
  
    TTree*                                              fTreeVar;                 ///< Tree with compressed jet objects
    bool                                                fIsMCGenTree;             ///< flag to know if is a tree for MC generated particles
  
    AliJetContainer*                                    fJetContainer;            //!<! Jet container for this tree
    std::vector<AliJetInfoCompressed>                   fJetVariables;            //!<! vector of compressed jet info in the event
    AliJetInfoCompressed                                fCurrentJetCompressed;    //!<! Info of current jet (compressed)
  
  /// \cond CLASSIMP
  ClassDef(AliJetTreeHandler,2); ///
  /// \endcond
};

#endif
