/* Copyright(c) 1998-2008, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

//*************************************************************************
// \class AliJetInfoCompressed
// \brief This class encapsulates jet information in a compact data structure (63 bits), based heavily on AliAnalysisTaskDmesonJets
// \authors:
// James Mulligan, james.mulligan@berkeley.edu
/////////////////////////////////////////////////////////////

#include "AliJetContainer.h"

#include "AliJetInfoCompressed.h"

//________________________________________________________________
/// \cond CLASSIMP
ClassImp(AliJetInfoCompressed);
/// \endcond

//________________________________________________________________
// Default constructor
AliJetInfoCompressed::AliJetInfoCompressed():
  fPt(0),
  fEta(0),
  fPhi(0),
  fArea(0),
  fN(0),
  fCorrPt(0)
{
}

//________________________________________________________________
// Reset all variables to default values
void AliJetInfoCompressed::Reset() {
  fPt = 0;
  fEta = 0;
  fPhi = 0;
  fArea = 0;
  fN = 0;
  fCorrPt = 0;
}

//________________________________________________________________
// Set all variables from a AliJetInfo object
void AliJetInfoCompressed::Set(const AliEmcalJet* jet, AliJetContainer* jetCont) {
  fPt = jet->Pt();
  fEta = jet->Eta();
  fPhi = jet->Phi_0_2pi();
  fN = jet->GetNumberOfConstituents();
  fArea = jet->Area();
  fCorrPt = GetJetPt(jet, jetCont);
}

/**
 * Get pT of jet -- background subtracted
 */
//________________________________________________________________
Double_t AliJetInfoCompressed::GetJetPt(const AliEmcalJet* jet, AliJetContainer* jetCont)
{
  Double_t rhoVal = 0;
  if (jetCont->GetRhoParameter()) {
    rhoVal = jetCont->GetRhoVal();
  }
  
  Double_t pT = jet->Pt() - rhoVal * jet->Area();
  return pT;
}
