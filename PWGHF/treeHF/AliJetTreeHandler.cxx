/************************************************************************************
 * Copyright (C) 2017, Copyright Holders of the ALICE Collaboration                 *
 * All rights reserved.                                                             *
 *                                                                                  *
 * Redistribution and use in source and binary forms, with or without               *
 * modification, are permitted provided that the following conditions are met:      *
 *     * Redistributions of source code must retain the above copyright             *
 *       notice, this list of conditions and the following disclaimer.              *
 *     * Redistributions in binary form must reproduce the above copyright          *
 *       notice, this list of conditions and the following disclaimer in the        *
 *       documentation and/or other materials provided with the distribution.       *
 *     * Neither the name of the <organization> nor the                             *
 *       names of its contributors may be used to endorse or promote products       *
 *       derived from this software without specific prior written permission.      *
 *                                                                                  *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND  *
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED    *
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
 * DISCLAIMED. IN NO EVENT SHALL ALICE COLLABORATION BE LIABLE FOR ANY              *
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES       *
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;     *
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND      *
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS    *
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                     *
 ************************************************************************************/

/**
 * \class AliJetTreeHandler
 * \brief Helper class to handle a tree for cut optimisation and MVA analyses, based heavily on AliHFTreeHandler and AliAnalysisTaskDmesonJets
 *
 * \author James Mulligan <james.mulligan@berkeley.edu>
 * \date Feb 15 2019
 */

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
  fJetContainer(nullptr),
  fFillMatchingJetID(false),
  fPtUncorr(),
  fPtCorr(),
  fEta(),
  fPhi(),
  fArea(),
  fN(),
  fMatchedJetID()
{
}

//________________________________________________________________
// Destructor
AliJetTreeHandler::~AliJetTreeHandler()
{
  if(fTreeVar) delete fTreeVar;
}

/**
 * Create jet TTree, with a branch of vectors for each jet variable.
 * There will be one entry in each vector for each jet that is found.
 */
//________________________________________________________________
TTree* AliJetTreeHandler::BuildTree(TString name, TString title)
{
  if(fTreeVar) {
    delete fTreeVar;
    fTreeVar=0x0;
  }
  fTreeVar = new TTree(name.Data(),title.Data());
  
  // Create branches for each jet variable
  fTreeVar->Branch("PtUncorr",&fPtUncorr);
  fTreeVar->Branch("PtCorr",&fPtCorr);
  fTreeVar->Branch("Eta",&fEta);
  fTreeVar->Branch("Phi",&fPhi);
  fTreeVar->Branch("Area",&fArea);
  fTreeVar->Branch("N",&fN);
  
  if (fFillMatchingJetID) {
    fTreeVar->Branch("MatchedJetID", &fMatchedJetID);
  }
  
  return fTreeVar;
}

/**
 * Set jet tree variables
 */
//________________________________________________________________
bool AliJetTreeHandler::SetJetVariables()
{

  for (const auto jet : fJetContainer->accepted()) {
    
    fPtUncorr.push_back(jet->Pt());
    fPtCorr.push_back(GetJetPt(jet));
    fEta.push_back(jet->Eta());
    fPhi.push_back(jet->Phi_0_2pi());
    fN.push_back(jet->GetNumberOfConstituents());
    fArea.push_back(jet->Area());
    
    // Get matched jet (assumes the matches have been filled by a previous task)
    if (fFillMatchingJetID) {
      
      int matchedJetLabel = -1;
      const AliEmcalJet* matchedJet = jet->ClosestJet();
      if (matchedJet) {
        matchedJetLabel = matchedJet->GetLabel();
      }
      fMatchedJetID.push_back(matchedJetLabel);
      
    }

  }
  
  return true;
}

/**
 * Fill jet tree, and reset all vectors
 */
//________________________________________________________________
void AliJetTreeHandler::FillTree() {

  fTreeVar->Fill();
  
  // Reset all vectors
  fPtUncorr.clear();
  fPtCorr.clear();
  fEta.clear();
  fPhi.clear();
  fN.clear();
  fArea.clear();
  
  if (fFillMatchingJetID) {
    fMatchedJetID.clear();
  }
  
}

/**
 *  If filling jet matching info (for MC), loop through jets and set fLabel,
 *  which specifies the index of the jet in the tree variable std::vectors.

 */
//________________________________________________________________
void AliJetTreeHandler::SetJetLabels()
{
  int i = 0;
  for (auto jet : fJetContainer->accepted()) {
    jet->SetLabel(i);
    i++;
  }
}

/**
 * Get pT of jet -- background subtracted
 */
//________________________________________________________________
Double_t AliJetTreeHandler::GetJetPt(const AliEmcalJet* jet)
{
  Float_t rhoVal = 0;
  if (fJetContainer->GetRhoParameter()) {
    rhoVal = fJetContainer->GetRhoVal();
  }
  
  Float_t pTCorr = jet->Pt() - rhoVal * jet->Area();
  return pTCorr;
}
