#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TH2.h"
#include "TCanvas.h"
#include <iostream>
#include "TLegend.h"
#include "TProfile.h"
#include "TChain.h"


void Compare_Delta_w_PU_and_wo_PU()
{ 

   TCanvas *c1 = new TCanvas("MC_Data","",900,600);

   TChain no_PU_files("CalibTree");
   no_PU_files.Add("/eos/cms/store/group/dpg_hcal/comm_hcal/CMS_POS/IsoTrack2019/mc/mc2018noPUnew.root");

   int no_PU_ieta = 0;
   double no_PU_HCAL_E = 0, no_PU_Tracker_P = 0;
   double no_PU_eHcal30 = 0, no_PU_eHcal10 = 0;
   bool no_PU_selectTk = 0, no_PU_qltyMissFlag = 0, no_PU_qltyPVFlag = 0;
   no_PU_files.SetBranchAddress("t_ieta",&no_PU_ieta);
   no_PU_files.SetBranchAddress("t_eHcal",&no_PU_HCAL_E);
   no_PU_files.SetBranchAddress("t_p",&no_PU_Tracker_P);
   no_PU_files.SetBranchAddress("t_eHcal10",&no_PU_eHcal10);
   no_PU_files.SetBranchAddress("t_eHcal30",&no_PU_eHcal30);
   no_PU_files.SetBranchAddress("t_selectTk",&no_PU_selectTk);
   no_PU_files.SetBranchAddress("t_qltyMissFlag",&no_PU_qltyMissFlag);
   no_PU_files.SetBranchAddress("t_qltyPVFlag",&no_PU_qltyPVFlag);


   long int  no_PU_nentries = no_PU_files.GetEntries();

   TProfile* hist_no_PU =  new TProfile("no_PU", ";ieta;#Delta (GeV)", 60, -30, 30);

   for (long int i=0; i < no_PU_nentries; ++i)
   {
      no_PU_files.GetEntry(i) ;
      if ( std::abs(no_PU_ieta) > 23 ) continue;
      if ( no_PU_selectTk && no_PU_qltyMissFlag && no_PU_qltyPVFlag )
         hist_no_PU->Fill(no_PU_ieta, no_PU_eHcal30 - no_PU_eHcal10);
   }

   TChain PU_files("CalibTree");
   PU_files.Add("/eos/cms/store/group/dpg_hcal/comm_hcal/CMS_POS/IsoTrack2019/mc/mc2018PUnew.root");
   
   int PU_ieta = 0;
   double PU_HCAL_E = 0, PU_Tracker_P = 0;
   double PU_eHcal30 = 0, PU_eHcal10 = 0;
   bool PU_selectTk = 0, PU_qltyMissFlag = 0, PU_qltyPVFlag = 0;
   PU_files.SetBranchAddress("t_ieta",&PU_ieta);
   PU_files.SetBranchAddress("t_eHcal",&PU_HCAL_E);
   PU_files.SetBranchAddress("t_p",&PU_Tracker_P);
   PU_files.SetBranchAddress("t_eHcal10",&PU_eHcal10);
   PU_files.SetBranchAddress("t_eHcal30",&PU_eHcal30);
   PU_files.SetBranchAddress("t_selectTk",&PU_selectTk);
   PU_files.SetBranchAddress("t_qltyMissFlag",&PU_qltyMissFlag);
   PU_files.SetBranchAddress("t_qltyPVFlag",&PU_qltyPVFlag);
   

   long int  PU_nentries = PU_files.GetEntries();
   
   TProfile* hist_PU = new TProfile("PU", ";ieta;#Delta (GeV)", 60, -30, 30);

   for (long int i=0; i < PU_nentries; ++i)
   {  
      PU_files.GetEntry(i) ;
      if ( std::abs(PU_ieta) > 23 ) continue;
      if ( PU_selectTk && PU_qltyMissFlag && PU_qltyPVFlag )
         hist_PU->Fill(PU_ieta, PU_eHcal30 - PU_eHcal10);
   }


   TLegend *leg = new TLegend(0.8,0.85,0.95,0.95);

   leg->AddEntry(hist_no_PU, "no PU");
   leg->AddEntry(hist_PU, "with PU");

   hist_no_PU->SetMaximum(10);
   hist_no_PU->SetMinimum(0);
   hist_no_PU->SetLineColor(kBlue);
   hist_no_PU->SetStats(0);
   hist_no_PU->Draw("");

   hist_PU->SetLineColor(kRed);
   hist_PU->Draw("same");

   leg->Draw();

c1->SaveAs("Compare_Delta_w_PU_and_wo_PU.pdf");
}
