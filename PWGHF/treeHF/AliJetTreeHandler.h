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
    AliJetTreeHandler(int nJetContainers);
    virtual ~AliJetTreeHandler();

    //core methods
    TTree* BuildTree(TString name, TString title);
    bool SetJetVariables(int i, AliJetContainer* jetCont);
    void FillTree(); //to be called for each event
  
    Double_t GetJetPt(const AliEmcalJet* jet, AliJetContainer* jetCont);

  protected:
  
    TTree*                                              fTreeVar;                 ///< Tree with compressed jet objects
    bool                                                fIsMCGenTree;             ///< flag to know if is a tree for MC generated particles
  
    std::vector< std::vector<AliJetInfoCompressed> >    fJetVariables;            //!<! 2-d vector of (jet container, compressed jet info) in the event
    AliJetInfoCompressed                                fCurrentJetCompressed;    //!<! Info of current jet (compressed)
  
  /// \cond CLASSIMP
  ClassDef(AliJetTreeHandler,1); ///
  /// \endcond
};

#endif
