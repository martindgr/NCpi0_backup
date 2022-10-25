

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <THStack.h>
#include "SetT2KStyle.H"
#include <TArrow.h>
#include <iostream>
#include <algorithm>

float ChThresh(int pid) {
	float thresh = -1;
	if (pid == 11) thresh =  0.583; //electron
	if (pid == 14) thresh = 120.5; //muon
	if (pid == 111) thresh = 0; //pi0 or is generator photon??
	if (pid == 211) thresh = 159.2; //pipm
	if (pid == 221) thresh = 0; //eta
	if (pid == 2212) thresh = 1070; //P
	if (pid == 2112) thresh = 0; 

	return thresh;
}

float CherenkovThresh_mass(float mass) {
	//mass in MeV/c2
	float n = 1.33;
	float thresh = mass / sqrt(n*n - 1);
	return thresh;
}

void FormatHist(THStack* h, int linecolor, int linestyle){
  //  h->SetStats(0);
    h->GetXaxis()->SetTitleFont(132);
    h->GetYaxis()->SetTitleFont(132);
    h->GetXaxis()->SetTitleSize(0.04);
    h->GetYaxis()->SetTitleSize(0.04);
    h->GetXaxis()->SetLabelFont(132);
    h->GetYaxis()->SetLabelFont(132);
    h->GetXaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitle("Events");

//  h->SetLineWidth(2);
//  h->SetLineColor(linecolor);
//  h->SetLineStyle(linestyle);
}


/*
int SKMCplots_byevent(int argc, char ** argv){
	std::string idir = argv[1];
  std::string horn_current = argv[2];
	std::string select = argv[3];
	std::cout << idir <<" " << horn_current << " " << select << std::endl;
*/
void SKMCplots_byevent(){
	std::string select = "tuned";
	std::string horn_current = "fhc";
	std::string idir = "/home/dm3315/Documents/T2K-SK/NCpi0/output/";
	std::string ifilename = Form("NCpi0_%s_13av7p1_t2ksk19b.fqv4r0.%s.all_cut6.root", select.c_str(), horn_current.c_str());
	//std::string odir = Form("%s%s/", idir.c_str(), select.c_str());
	std::string odir = "/home/dm3315/Documents/T2K-SK/NCpi0/figs/selection_plots/_1Repi0_reject/";


//  TFile* ifile = new TFile(Form("%s%s", idir.c_str(), ifilename.c_str()));
	TChain *chain = new TChain("h1");
	chain->Add(Form("%s%s", idir.c_str(), ifilename.c_str()));

   Int_t           numnu;
   Int_t           mode;
   Int_t           ipnu[50];   //[numnu]
   Float_t         pnu[50];   //[numnu]
   Float_t         dirnu[50][3];   //[numnu]
   Float_t         fqpi0nll[2];
   Float_t         fq1rnll[12][7];   //[fqnse]
   Int_t           fqnmrfit;
   Int_t           fqmrifit[32];   //[fqnmrfit]
   Int_t           fqmrnring[32];   //[fqnmrfit]
   Int_t           fqmrpcflg[32];   //[fqnmrfit]
   Float_t         fqmrnll[32];   //[fqnmrfit]
   Float_t         fqmrtotmu[32];   //[fqnmrfit]
   Int_t           fqmrpid[32][6];   //[fqnmrfit]
   Float_t         fqmrmom[32][6];   //[fqnmrfit]
   Float_t         fqmrdconv[32][6];   //[fqnmrfit]
   Float_t         fqmreloss[32][6];   //[fqnmrfit]
   Float_t         fqmrt0[32][6];   //[fqnmrfit]
   Float_t         fqmrpos[32][6][3];   //[fqnmrfit]
   Float_t         fqmrdir[32][6][3];   //[fqnmrfit]
   Float_t         fqtotq[12];   //[fqnse]
   Int_t           fqnse;
   Double_t           totweight;

    TBranch        *b_numnu;   //!
   TBranch        *b_fqpi0nll;   //!
   TBranch        *b_mode;   //!
   TBranch        *b_ipnu;   //!
   TBranch        *b_pnu;   //!
   TBranch        *b_fq1rnll;   //!
	 TBranch				*b_dirnu;
   TBranch        *b_fqnmrfit;   //!
   TBranch        *b_fqmrifit;   //!
   TBranch        *b_fqmrnring;   //!
   TBranch        *b_fqmrpcflg;   //!
   TBranch        *b_fqmrnll;   //!
   TBranch        *b_fqmrtotmu;   //!
   TBranch        *b_fqmrpid;   //!
   TBranch        *b_fqmrmom;   //!
   TBranch        *b_fqmrdconv;   //!
   TBranch        *b_fqmreloss;   //!
   TBranch        *b_fqmrt0;   //!
   TBranch        *b_fqmrpos;   //!
   TBranch        *b_fqmrdir;   //!
   TBranch        *b_fqtotq;   //!
   TBranch        *b_fqnse;   //!
	 TBranch        *b_totweight;   //!
 
	 chain->SetBranchAddress("fqpi0nll", fqpi0nll, &b_fqpi0nll);
   chain->SetBranchAddress("fq1rnll", fq1rnll, &b_fq1rnll);
   chain->SetBranchAddress("numnu", &numnu, &b_numnu);
   chain->SetBranchAddress("mode", &mode, &b_mode);
   chain->SetBranchAddress("ipnu", ipnu, &b_ipnu);
   chain->SetBranchAddress("pnu", pnu, &b_pnu);
   chain->SetBranchAddress("dirnu", dirnu, &b_dirnu);
   chain->SetBranchAddress("fqnmrfit", &fqnmrfit, &b_fqnmrfit);
   chain->SetBranchAddress("fqmrifit", fqmrifit, &b_fqmrifit);
   chain->SetBranchAddress("fqmrnring", fqmrnring, &b_fqmrnring);
   chain->SetBranchAddress("fqmrpcflg", fqmrpcflg, &b_fqmrpcflg);
   chain->SetBranchAddress("fqmrnll", fqmrnll, &b_fqmrnll);
   chain->SetBranchAddress("fqmrtotmu", fqmrtotmu, &b_fqmrtotmu);
   chain->SetBranchAddress("fqmrpid", fqmrpid, &b_fqmrpid);
   chain->SetBranchAddress("fqmrmom", fqmrmom, &b_fqmrmom);
   chain->SetBranchAddress("fqmrdconv", fqmrdconv, &b_fqmrdconv);
   chain->SetBranchAddress("fqmreloss", fqmreloss, &b_fqmreloss);
   chain->SetBranchAddress("fqmrt0", fqmrt0, &b_fqmrt0);
   chain->SetBranchAddress("fqmrpos", fqmrpos, &b_fqmrpos);
   chain->SetBranchAddress("fqmrdir", fqmrdir, &b_fqmrdir);
   chain->SetBranchAddress("fqtotq", fqtotq, &b_fqtotq);
   chain->SetBranchAddress("fqnse", &fqnse, &b_fqnse);
   chain->SetBranchAddress("totweight", &totweight, &b_totweight);



	int NBins = 100;
	int lo_x = 0;
	int hi_x = 10;
	const static int npart = 5;
	TH1F* mom_CC_reject_histo[npart] ={0}; 
	TH1F* mom_NCpi0_reject_histo[npart] ={0};  
	TH1F* mom_NCbg_reject_histo[npart] ={0}; 

	TH1F* mom_CC_acc_histo[npart] ={0}; 
	TH1F* mom_NCpi0_acc_histo[npart] ={0};
	TH1F* mom_NCbg_acc_histo[npart] ={0}; 
					  										
  for (int i=0; i<npart; i++){
		mom_CC_reject_histo[i] = new TH1F(Form("pnu_%d_rj_CC", i), "" ,NBins, lo_x, hi_x);
		mom_NCpi0_reject_histo[i] = new TH1F(Form("pnu_%d_rj_pi0", i), "" ,NBins, lo_x, hi_x);
		mom_NCbg_reject_histo[i] = new TH1F(Form("pnu_%d_rj_NCbg", i), "" ,NBins, lo_x, hi_x);
		mom_CC_acc_histo[i] = new TH1F(Form("pnu_%d_ac_CC", i), "" ,NBins, lo_x, hi_x);
		mom_NCpi0_acc_histo[i] = new TH1F(Form("pnu_%d_ac_pi0", i), "" ,NBins, lo_x, hi_x);
		mom_NCbg_acc_histo[i] = new TH1F(Form("pnu_%d_ac_NCbg", i), "" ,NBins, lo_x, hi_x);
}

	TH1F* mom_CC_tot_histo = new TH1F("pnu_%d_tot_CC", "" ,NBins, lo_x, hi_x);
	TH1F* mom_NCpi0_tot_histo = new TH1F("pnu_%d_tot_NCpi0", "" ,NBins, lo_x, hi_x);
	TH1F* mom_NCbg_tot_histo = new TH1F("pnu_%d_tot_NCbg", "" ,NBins, lo_x, hi_x);




  const static int NSigVars = 2;
  const static int NBkgVars = 14;
  const static int NVars = 16;
  std::string SignalName[NSigVars] = {"NC1pi0", "NCCoh"}; 
  std::string BkgName[NBkgVars] = {"CCqe", "CC1pi", "CCCoh", "CCmultipi", "CCDis", "NC1pipm", "NCOther", "CC2p2h", "NC1gamma", "CCmisc"} ; 
	std::string AllName[NVars] = {"CCqe", "CC1pi", "CCCoh", "CCmultipi", "CCDis", "NC1pi0", "NC1pipm", "NCCoh", "NCOther", "CC2p2h", "NC1gamma", "CCmisc", "NCmpi", "NCEta", "NCDIS", "NCElastic"} ; 
  int DrawReorder[NVars] =  {0, 1, 2, 3, 4, 9, 11, 6, 8, 10, 12, 13, 14, 15, 7, 5} ; 
  int DrawPallette[NVars] = {kRed+3, kRed-6, kRed+1, kPink, kMagenta+3, kMagenta, kViolet, kTeal-5, kCyan+1, kCyan+3, kAzure+7, kAzure, kAzure+2, kBlue+4, kGreen, kGreen+1} ; 

	const static int NCuts = 10;

  
  Int_t entries = chain->GetEntries();

  for (int j=0;j<entries; j++){
    	chain->GetEntry(j);
		
    float maxCharge = 0.;
    int mainEventIndex = 0;
    for(int i=0; i<fqnse; i++){
        if(fqtotq[i]>maxCharge){
            maxCharge = fqtotq[i];
            mainEventIndex = i;
        }
			}

		std::map<double, int, std::greater<double>> pnu_map;
		
		//std::cout << "////" << std::endl;
		for (int i=2; i<numnu; i++) {
		//	std::cout << i << " " << numnu << " " << pnu[i] << std::endl;
			pnu_map.insert(std::make_pair(pnu[i], i));	
		}
    /*
		for (auto const& entry: pnu_map)
    {
        std::cout << " " <<  entry.first << " " << entry.second << std::endl;
    }
		std::cout << std::endl;
		*/

		int hiq_ring = -1;
		int mrfitid = 20000011;
		  int ipp = -1;
              
     for (int ifit=0; ifit<fqnmrfit; ++ifit) {
        if (std::abs(fqmrifit[ifit]) == 20000011) {
            ipp = ifit;
        	} 
        }
     if (ipp < 0) {
         throw std::runtime_error("t2ksk_eventSelections: ERROR! Couldn't find FiTQun ee multi-ring result. I need to run on files with all multi-ring results written out.");
     }
		
		int part = 0;
		int pos_in_map = 0;
		for (auto const& entry: pnu_map){	
			//ordered index of particles from numnu,
			part = entry.second;
			if (part > npart-1){
				continue;
			}

			if (-1.0*fqpi0nll[0]+fq1rnll[0][1] < 100) {
				if (mode<30&&mode>-30) {
					//CC
					mom_CC_reject_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
					mom_CC_tot_histo->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight) ;
				}else {
					if (mode==31||mode==32||mode==-31||mode==-32||mode==36||mode==-36){
						//NCpi0
						mom_NCpi0_reject_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
						mom_NCpi0_tot_histo->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight) ;
					} else {
						//NCbg
						mom_NCbg_reject_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
						mom_NCbg_tot_histo->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight) ;
					}
				}
				

				} else {
					//acc
				if (mode<30&&mode>-30) {
					//CC
					mom_CC_acc_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
					mom_CC_tot_histo->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight) ;
				}else {
					if (mode==31||mode==32||mode==-31||mode==-32||mode==36||mode==-36){
						//NCpi0
						mom_NCpi0_acc_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
						mom_NCpi0_tot_histo->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight) ;
					} else {
						//NCbg
						mom_NCbg_acc_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
						mom_NCbg_tot_histo->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight) ;
					}
				}
				}
				pos_in_map += 1;
			}
	}

		double leg_x1 = 0.7;
		double leg_y1 = 0.4;
		double leg_x2 = 0.9;
		double leg_y2 = 0.9;

		
	THStack *mom_tot_stack = new THStack("mom_tot_stack", "mom_rj"); 
  mom_tot_stack->Add(mom_CC_tot_histo);
	mom_tot_stack->Add(mom_NCbg_tot_histo);
	mom_tot_stack->Add(mom_NCpi0_tot_histo);	
	

	auto c_mom_tot = new TCanvas();
	mom_tot_stack->Draw("hist pfc");
  mom_tot_stack->GetXaxis()->SetTitle("pnu-ChThresh (GeV)");
  mom_tot_stack->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  mom_tot_stack->SetTitle(Form("%s total e/pi0 events ", horn_current.c_str()));
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c_mom_tot->Update();
	c_mom_tot->SaveAs(Form("%smom_tot.png", odir.c_str()));



	for (int i=0; i<npart; i++){


		THStack *mom_rj_stack = new THStack("mom_rj_stack", "mom_rj"); 
	
		THStack *mom_ac_stack = new THStack("mom_ac_stack", "mom_ac"); 
		
		mom_rj_stack->Add(mom_CC_reject_histo[i]);
		mom_rj_stack->Add(mom_NCbg_reject_histo[i]);
		mom_rj_stack->Add(mom_NCpi0_reject_histo[i]);
		
		mom_ac_stack->Add(mom_CC_acc_histo[i]);
		mom_ac_stack->Add(mom_NCbg_acc_histo[i]);
		mom_ac_stack->Add(mom_NCpi0_acc_histo[i]);
		
	auto c_mom_rj = new TCanvas();
	mom_rj_stack->Draw("hist pfc");
  mom_rj_stack->GetXaxis()->SetTitle("pnu-ChThresh (GeV)");
  mom_rj_stack->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  mom_rj_stack->SetTitle(Form("%s rejected e/pi0 events %d", horn_current.c_str(), i));
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c_mom_rj->Update();
	c_mom_rj->SaveAs(Form("%smom_%d_rj.png", odir.c_str(), i));

	auto c_mom_ac = new TCanvas();
	mom_ac_stack->Draw("hist pfc");
  mom_ac_stack->GetXaxis()->SetTitle("pnu-ChThresh (GeV)");
  mom_ac_stack->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  mom_ac_stack->SetTitle(Form("%s accepted e/pi0 events %d", horn_current.c_str(), i));
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c_mom_ac->Update();
	c_mom_ac->SaveAs(Form("%smom_%d_acc.png", odir.c_str(), i));


}
/*	auto c_mom_2_rj = new TCanvas();
	mom_2_rj_stack->Draw("hist pfc");
  mom_2_rj_stack->GetXaxis()->SetTitle("pnu-ChThresh");
  mom_2_rj_stack->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{2Rother}/L_{ee}) vs.#pi^{0} momentum", horn_current.c_str()));
  mom_2_rj_stack->SetTitle("");
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c_mom_2_rj->Update();
	c_mom_2_rj->SaveAs(Form("%smom_2_rj.png", odir.c_str()));

	auto c_mom_2_rj = new TCanvas();
	mom_2_rj_stack->Draw("hist pfc");
  mom_2_rj_stack->GetXaxis()->SetTitle("pnu-ChThresh");
  mom_2_rj_stack->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{2Rother}/L_{ee}) vs.#pi^{0} momentum", horn_current.c_str()));
  mom_2_rj_stack->SetTitle("");
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c_mom_2_rj->Update();
	c_mom_2_rj->SaveAs(Form("%smom_2_rj.png", odir.c_str()));


	auto c_mom_2_ac = new TCanvas();
	mom_2_ac_stack->Draw("hist pfc");
  mom_2_ac_stack->GetXaxis()->SetTitle("pnu-ChThresh");
  mom_2_ac_stack->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{2Rother}/L_{ee}) vs.#pi^{0} momentum", horn_current.c_str()));
  mom_2_ac_stack->SetTitle("");
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c_mom_2_ac->Update();
	c_mom_2_ac->SaveAs(Form("%smom_2_ac.png", odir.c_str()));
*/
	
}
