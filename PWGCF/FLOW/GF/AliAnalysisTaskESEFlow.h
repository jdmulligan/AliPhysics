#ifndef AliAnalysisTaskESEFlow_H
#define AliAnalysisTaskESEFlow_H

#include "AliAnalysisTaskSE.h"
#include "AliEventCuts.h"
#include "AliAODTrack.h"
#include "AliGFWWeights.h"
#include "TComplex.h"
#include "TF1.h"
#include "TSpline.h"
#include "TProfile.h"
#include "TH1.h"
#include "TH2.h"


class AliAnalysisTaskESEFlow : public AliAnalysisTaskSE
{
    public:
                                AliAnalysisTaskESEFlow();
                                AliAnalysisTaskESEFlow(const char *name);
        virtual                 ~AliAnalysisTaskESEFlow();

        virtual void            UserCreateOutputObjects();
        virtual void            UserExec(Option_t* option);
        virtual void            Terminate(Option_t* option);

        //event and track selection
        void                    SetTrigger(AliVEvent::EOfflineTriggerTypes trigger) { fTrigger = trigger; }
        void                    SetRejectAddPileUp(Bool_t use = kTRUE) { fEventRejectAddPileUp = use; }
        void                    SetCentralityEst(TString est){ fCentEstimator = est; }
        void                    SetFilterBit(UInt_t filter) { fFilterBit = filter; }
        AliEventCuts            fEventCuts;
        void                    SetAbsEta(Double_t etaAbs) {fAbsEtaMax = etaAbs; }
        void                    SetUseWeightsRunByRun(Bool_t bRunByRun) { fFlowRunByRunWeights = bRunByRun; }

        void                    SetEtaGap(Double_t val) { dEtaGap = val; }

        void                    SetqSelectionRun(Bool_t actqRun) { fqRun = actqRun; }

        void                    SetReadMC(Bool_t activate) { fReadMC = activate;}
        void                    SetFlowRFPsPt(Double_t min, Double_t max) { fFlowRFPsPtMin = min; fFlowRFPsPtMax = max; }
        void                    SetFlowPOIsPt(Double_t min, Double_t max) { fFlowPOIsPtMin = min; fFlowPOIsPtMax = max; } 
        void                    AddTwoCorr(Bool_t actTwoCorr) { fnTwoCorr = actTwoCorr; }
        void                    AddFourCorr(Bool_t actFourCorr) { fnFourCorr = actFourCorr; }

        void                    SetTPCEse(Bool_t actTPCEse) { fTPCEse = actTPCEse; }
        void                    SetV0CEse(Bool_t actV0CEse) { fV0CEse = actV0CEse; }
        void                    SetV0AEse(Bool_t actV0AEse) { fV0AEse = actV0AEse; }


        void                    SetWeights(Bool_t kOwn) { bUseOwnWeights = kOwn; }
        

    private:
        //runAnalysis inputs
        Bool_t                  fFlowRunByRunWeights;
        Bool_t                  bUseOwnWeights;
        Double_t                dEtaGap;

        static const Int_t      fNumHarms = 13; // maximum harmonics length of flow vector array
        static const Int_t      fNumPowers = 9; // maximum weight power length of flow vector array
        static const Int_t      fNumHarmHists = 5; // how many harmonics hists
        static const Int_t      fNumCentHists = 10; // how many cent hists should there be
        static const Int_t      fESECuts = 10; // amount of ese percentiles 

        Bool_t                  fInit; // initilization check
        Bool_t                  fqRun; // make q-selections also used for V0 Calibration runs

        AliAODEvent*            fAOD;           //!
        TList*                  fOutputList;    //!
        TList*                  fObservables;   //!
        TList*                  fCorrDist;      //!
        TList*                  fpTDiff;        //!
        TList*                  fqnDist;        //!
        TList*                  fpTDiffESETPC;  //!
        TList*                  fcnESETPC;      //!
        TList*                  fpTDiffESEV0C;  //!
        TList*                  fcnESEV0C;      //!
        TList*                  fQAEvents;      //!

        TList*                  fFlowWeightsList; //! 
        AliGFWWeights*          fWeights;           //!
        TList*                  fV0CalibList;   //!
        TList*                  fqSelList;   //!
        //output histograms
        TH3F*                   fHistPhiEtaVz;    //!
        TH1F*                   fHistPhi;       //!
        TH1F*                   fHistEta;       //!
        TH1F*                   fHistPt;        //!
        TH1F*                   fHistZVertex;   //!

        TSpline3*               fSplq2TPC[90];  // q2 TPC splines
        TSpline3*               fSplq3TPC[90];  // q3 TPC splines
        TSpline3*               fSplq2V0C[90];  // q2 V0C splines
        TSpline3*               fSplq3V0C[90];  // q3 V0C splines
        TSpline3*               fSplq2V0A[90];  // q2 V0A splines
        TSpline3*               fSplq3V0A[90];  // q3 V0A splines

        TProfile*               fcn2Gap[fNumHarmHists]; //!
        TProfile*               fdn2GapPt[fNumHarmHists][fNumCentHists];    //!
        TProfile*               fdn2GapPtB[fNumHarmHists][fNumCentHists];    //!

        TH2D*                   fh2Weights; //!
        TH1F*                   fhV0Calib;  //!
        TH1F*                   fHistPDG; //!

        ////////////////////// TPC ///////////////////////
        TProfile*               fcn2GapESETPC[fNumHarmHists][2][fESECuts]; //!        
        TProfile*               fdn2GapESETPC[fNumHarmHists][2][fNumCentHists][fESECuts]; //! 
        TProfile*               fcn4Gap; //!
        TProfile*               fdn4GapPt[fNumCentHists];    //! 
        TProfile*               fcn4GapESETPC[2][fESECuts]; //!        
        TProfile*               fdn4GapESETPC[2][fNumCentHists][fESECuts]; //! 
        ////////////////////// V0C ////////////////////// 
        TProfile*               fcn2GapESEV0C[fNumHarmHists][2][fESECuts]; //!        
        TProfile*               fdn2GapESEV0C[fNumHarmHists][2][fNumCentHists][fESECuts]; //! 
        TProfile*               fcn4GapESEV0C[2][fESECuts]; //!        
        TProfile*               fdn4GapESEV0C[2][fNumCentHists][fESECuts]; //! 

        ////////////////////// V0A ////////////////////// 
        TProfile*               fcn2GapESEV0A[fNumHarmHists][2][fESECuts]; //!        
        TProfile*               fdn2GapESEV0A[fNumHarmHists][2][fNumCentHists][fESECuts]; //! 
        /////////////////////////////////////////////////

        TProfile*               fc22c32Unb;                 //!
        TProfile*               fc22c32ESETPC[2][fESECuts]; //! 
        

        /////////////////////////// CALIBRATION HISTOGRAMS ////////////////////////////////////
        TH2D*                   fq2TPC;    //!
        TH2D*                   fq3TPC;    //!
        TH2D*                   fq2V0C;    //!
        TH2D*                   fq3V0C;    //!
        TH2D*                   fq2V0A;    //!
        TH2D*                   fq3V0A;    //!

        TH2F*                   fQnxV0C[2];    //!
        TH2F*                   fQnyV0C[2];    //!
        TH2F*                   fQnxV0A[2];    //!
        TH2F*                   fQnyV0A[2];    //!
        TH2F*                   fQnxTPC[2];    //!
        TH2F*                   fQnyTPC[2];    //!

        
        TH1F*                   fQnxV0Cm[2];    //!
        TH1F*                   fQnyV0Cm[2];    //!
        TH1F*                   fQnxV0Am[2];    //!
        TH1F*                   fQnyV0Am[2];    //!
        TH1F*                   fQnxTPCm[2];    //!
        TH1F*                   fQnyTPCm[2];    //!

        TH2F*                   fQnxV0CEse[2];    //!
        TH2F*                   fQnyV0CEse[2];    //!
        TH2F*                   fQnxV0AEse[2];    //!
        TH2F*                   fQnyV0AEse[2];    //!
        TH2F*                   fQnxTPCEse[2];    //!
        TH2F*                   fQnyTPCEse[2];    //! 
        ////////////////////////// CALIBRATION HISTOGRAMS /////////////////////////////////////////

        TH3F*                   fCentq2TPCvsv22;   //!
        TH3F*                   fCentq2V0Cvsv22;   //!
        TProfile*               fProfNPar; //!
        TH2F*                   fhV0Multiplicity;    //!
        TH2F*                   fhV0CorrMult;       //!
        TH2F*                   fhq2TPCvq2V0C;  //!

        void CorrelationTask(const Float_t centrality, const Int_t iTracks, const AliAODEvent* fAOD, const float dVz, Int_t fSpCent);
        void FillObsDistributions(const Int_t iTracks, const AliAODEvent* fAOD, const float dVz, const Float_t centrality);
        // Calculate flow vectors for reference and POIs
        void RFPVectors(const Float_t centrality, const Int_t iTracks, const AliAODEvent* fAOD, const float dVz, Int_t q2ESECodeTPC, Int_t q3ESECodeTPC, Int_t q2ESECodeV0C, Int_t q3ESECodeV0C);
        void POIVectors(const Int_t CenterCode, const Int_t iTracks, const AliAODEvent* fAOD, const float dVz, Int_t q2ESECodeTPC, Int_t q3ESECodeTPC, Int_t q2ESECodeV0C, Int_t q3ESECodeV0C);
        void ReducedqVectorsTPC(const Float_t centrality, const Int_t iTracks, const AliAODEvent* fAOD, const float dVz);
        void ReducedqVectorsV0(const Float_t centrality, const AliAODEvent* fAOD, const Int_t SPCode);
        void FillRFP(const Float_t centrality,const Int_t iTracks, const int nHarm, const int nCorr, Int_t q2ESECodeTPC, Int_t q3ESECodeTPC, Int_t q2ESECodeV0C, Int_t q3ESECodeV0C);
        void Filldn(const Int_t CenterCode, const double dPt, const int nHarm, const int nCorr, Int_t q2ESECodeTPC, Int_t q3ESECodeTPC, Int_t q2ESECodeV0C, Int_t q3ESECodeV0C);
        void FillqnRedTPC(const Float_t centrality);
        void FillqnRedV0(const Float_t centrality, TString V0type);
        void FillPOI(const Double_t dPtL, const Double_t dPtLow, const Double_t dPtHigh, const float dVz, Int_t iTracks);
        void FillESEcn(const Float_t centrality, const int nHarm, const double c, const double c_weight,const int nCorr, Int_t q2ESECodeTPC, Int_t q3ESECodeTPC, Int_t q2ESECodeV0C, Int_t q3ESECodeV0C);
        void FillESEdnPt(const Int_t CenterCode, const int nHarm, const Double_t dPt, const double d, const double d_weight,const int nCorr, Int_t q2ESECodeTPC, Int_t q3ESECodeTPC, Int_t q2ESECodeV0C, Int_t q3ESECodeV0C);
        Int_t GetCentrCode(const Float_t centrality);
        Int_t GetPercCode(Double_t qPerc) const;
        Bool_t WithinRFP(const AliVParticle* track) const;
        Bool_t WithinPOI(const AliVParticle* track) const;
        Bool_t LoadqSelection();
        Bool_t ProcessMCParticles();

        Bool_t InitializeTask();
        Bool_t LoadWeights(); // load weights histograms
        Bool_t LoadV0Calibration();
        Double_t GetFlowWeight(const AliAODTrack* track, const float dVz) const;
        //############ GENERIC FRAMEWORK ############# MODIFIED WITH ESE //

        double GetWeight(double phi, double eta, double vz,  double runNumber);
        double GetPtWeight(double pt, double eta, float vz,  double runNumber);
        void ResetFlowVector(TComplex (&array)[fNumHarms][fNumPowers]); // set values to TComplex(0,0,0) for given array
        void ResetReducedqVector(Double_t (&array)[2]);

        Bool_t sortPt(const AliAODTrack* t1, const AliAODTrack* t2) { return (t1->Pt() < t2->Pt()); } // function for std::sort
        
        TComplex pvector[fNumHarms][fNumPowers];
        TComplex pvector10M[fNumHarms][fNumPowers];
        TComplex pvector10P[fNumHarms][fNumPowers];
        TComplex qvector[fNumHarms][fNumPowers];
        TComplex pvectorPtB[fNumHarms][fNumPowers];
        TComplex qvectorPtB[fNumHarms][fNumPowers];
        TComplex pvectorPtB10M[fNumHarms][fNumPowers];
        TComplex pvectorPtB10P[fNumHarms][fNumPowers];
        TComplex Qvector[fNumHarms][fNumPowers];
        TComplex Qvector10M[fNumHarms][fNumPowers];
        TComplex Qvector10P[fNumHarms][fNumPowers];

        Double_t qnTPC[2];
        Double_t QxnTPC[2];
        Double_t QynTPC[2];

        Double_t qnV0C[2];
        Double_t QxnV0C[2];
        Double_t QynV0C[2];

        Double_t qnV0A[2];
        Double_t QxnV0A[2];
        Double_t QynV0A[2];

        Double_t QxnTPCEse[2]; // after correction
        Double_t QynTPCEse[2];

        Double_t QxnV0CEse[2];
        Double_t QynV0CEse[2];

        Double_t QxnV0AEse[2];
        Double_t QynV0AEse[2];
        

        TComplex Q(int n, int p);
        TComplex QGap10M(int n, int p);
        TComplex QGap10P(int n, int p);
        TComplex p(int n, int p);
        TComplex pGap10M(int n, int p);
        TComplex pGap10P(int n, int p);
        TComplex pPtBGap10M(int n, int p);
        TComplex pPtBGap10P(int n, int p);
        TComplex q(int n, int p);
        TComplex qGap10M(int n, int p);
        TComplex qGap10P(int n, int p);
        TComplex pPtA(int n, int p);
        TComplex pPtB(int n, int p);
        TComplex qPtA(int n, int p);
        TComplex qPtB(int n, int p);

        TComplex Two(int n1, int n2);
        TComplex TwoGap10(int n1, int n2);
        TComplex TwoDiff(int n1, int n2);
        TComplex TwoDiffGap10M(int n1, int n2);
        TComplex TwoDiffGap10P(int n1, int n2);
        TComplex TwoDiff_Pt(int n1, int n2);
        TComplex TwoDiffGap10_Pt(int n1, int n2);
        TComplex TwoDiff_PtA(int n1, int n2);
        TComplex TwoDiff_PtB(int n1, int n2);
        TComplex TwoDiffGap10M_PtA(int n1, int n2);
        TComplex TwoDiffGap10P_PtB(int n1, int n2);
        TComplex TwoDiff_PtA_PtB(int n1, int n2);
        TComplex TwoDiffGap10_PtA_PtB(int n1, int n2);
        TComplex Three(int n1, int n2, int n3);
        TComplex ThreeGapP(int n1, int n2, int n3);
        TComplex ThreeGapM(int n1, int n2, int n3);
        TComplex ThreeDiff(int n1, int n2, int n3);
        TComplex ThreeDiffGapP(int n1, int n2, int n3);
        TComplex ThreeDiffGapM(int n1, int n2, int n3);
        TComplex Four(int n1, int n2, int n3, int n4);
        TComplex FourGap10(int n1, int n2, int n3, int n4);
        TComplex FourDiff(int n1, int n2, int n3, int n4);
        TComplex FourDiffGap10P(int n1, int n2, int n3, int n4);
        TComplex FourDiffGap10M(int n1, int n2, int n3, int n4);
        TComplex FourDiff_PtA_PtA(int n1, int n2, int n3, int n4);
        TComplex FourDiff_PtA_PtB(int n1, int n2, int n3, int n4);
        TComplex FourDiffGap10_PtA_PtB(int n1, int n2, int n3, int n4);
        TComplex Five(int n1, int n2, int n3, int n4, int n5);
        TComplex Six(int n1, int n2, int n3, int n4, int n5, int n6);
        TComplex SixDiff(int n1, int n2, int n3, int n4, int n5, int n6);
        TComplex Seven(int n1, int n2, int n3, int n4, int n5, int n6, int n7);
        TComplex Eight(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8);

        //############# END #############//

        AliAnalysisTaskESEFlow(const AliAnalysisTaskESEFlow&); // not implemented
        AliAnalysisTaskESEFlow& operator=(const AliAnalysisTaskESEFlow&); // not implemented

        //event and track selection
        AliVEvent::EOfflineTriggerTypes    fTrigger;
        Bool_t                  fEventRejectAddPileUp;
        UInt_t                  fFilterBit;
        Double_t                fAbsEtaMax;
        TString                 fCentEstimator;
        Bool_t                  IsEventSelected();
        Bool_t                  IsEventRejectedAddPileUp() const;
        Bool_t                  IsTrackSelected(const AliAODTrack* track) const;

        Bool_t                  fReadMC;
        AliMCEvent*             fMCEvent;       //! corresponding MC event
        Double_t                fFlowRFPsPtMin; // [0.2] (GeV/c) min pT treshold for RFPs particle for reference flow
        Double_t                fFlowRFPsPtMax; // [5.0] (GeV/c) max pT treshold for RFPs particle for reference flow
        Double_t                fFlowPOIsPtMin; // [0] (GeV/c) min pT treshold for POIs for differential flow
        Double_t                fFlowPOIsPtMax; // [10] (GeV/c) max pT treshold for POIs for differential flow
        Bool_t                  fnTwoCorr;
        Bool_t                  fnFourCorr;
        Bool_t                  fTPCEse;
        Bool_t                  fV0CEse;
        Bool_t                  fV0AEse;


        ClassDef(AliAnalysisTaskESEFlow, 1);
};

#endif
