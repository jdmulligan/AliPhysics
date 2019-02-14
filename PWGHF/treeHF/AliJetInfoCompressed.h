#ifndef ALIJETINFOCOMPRESSED_H
#define ALIJETINFOCOMPRESSED_H

/* Copyright(c) 1998-2008, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

//*************************************************************************
// \class AliJetInfoCompressed
// \brief This class encapsulates jet information in a compact data structure (63 bits), based heavily on AliAnalysisTaskDmesonJets
// \authors:
// James Mulligan, james.mulligan@berkeley.edu
/////////////////////////////////////////////////////////////

class AliEmcalJet;
class AliJetContainer;

//________________________________________________________________
//****************************************************************
class AliJetInfoCompressed : public TObject
{
  
  public:
  
    AliJetInfoCompressed();
    virtual ~AliJetInfoCompressed() {;}
  
    void Reset();
    void Set(const AliEmcalJet* jet, AliJetContainer* jetCont);
    Double_t GetJetPt(const AliEmcalJet* jet, AliJetContainer* jetCont);
  
    /// Transverse momentum of the jet in GeV/c
    Double32_t  fPt        ; //[0,409.6,13]
    /// Eta of the jet
    Double32_t  fEta       ; //[-1.024,1.024,11]
    /// Phi of the jet
    Double32_t  fPhi       ; //[0,2*pi,12]
    /// Area of the jet
    Double32_t  fArea         ; //[0,1.28,6]
    /// Number of jet constituents
    Double32_t  fN         ; //[0, 128, 7]
    /// Transverse momentum of the jet in GeV/c after subtracting average background
    Double32_t  fCorrPt    ; //[-409.6,409.6,14]
  
    /// \cond CLASSIMP
    ClassDef(AliJetInfoCompressed, 1);
    /// \endcond
  
};

#endif

