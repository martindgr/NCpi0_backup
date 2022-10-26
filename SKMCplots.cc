
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
//#include "Prob3/BargerPropagator.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <THStack.h>
#include <TArrow.h>
#include <iostream>

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

void DrawHist(THStack* histo, std::string outpath, std::string title){

auto c_hist = new TCanvas();
  histo->Draw("hist pfc");
	gPad->BuildLegend(0.7,0.5,0.9,0.9,"", "f");
	gPad->SetLeftMargin(0.12);
  histo->GetXaxis()->SetTitle(title.c_str());
	histo->SetTitle("");
	FormatHist(histo, 1, 2);
  c_hist->SaveAs(Form( "%s", outpath.c_str()));
}


int main(int argc, char ** argv){


//void SKMCplots(std::string horn_current, std::string select){	
//  std::string idir = "/home/dm3315/Documents/T2K-SK/NCpi0/figs/selection_plots/";
 // std::string horn_current = "fhc";
	//std::string select = "1ringPID";
	//std::string select = "noemuPID";
	//std::string ifile = "NCpi0_MC_histos_t2ksk19b.fqv4r0.fhc.all_merged.root";
 	///home/dm3315/Documents/T2K-SK/NCpi0/figs/selection_plots 
	//"dir", "fhc", "1Remunll"
	//NCpi0_MC_histos_1ringPID_t2ksk19b.fqv4r0.fhc.all.root
	std::string idir = argv[1];
  std::string horn_current = argv[2];
	std::string select = argv[3];
	std::cout << idir <<" " << horn_current << " " << select << std::endl;
	

	std::string ifilename = Form("NCpi0_MC_histos_%s_t2ksk19b.fqv4r0.%s.all.root", select.c_str(), horn_current.c_str());
	//std::string odir = Form("%s%s/", idir.c_str(), select.c_str());
	std::string odir = idir;


  TFile* ifile = new TFile(Form("%s%s", idir.c_str(), ifilename.c_str()));


  const static int NSigVars = 2;
  const static int NBkgVars = 14;
  const static int NVars = 16;
  std::string SignalName[NSigVars] = {"NC1pi0", "NCCoh"}; 
  std::string BkgName[NBkgVars] = {"CCqe", "CC1pi", "CCCoh", "CCmultipi", "CCDis", "NC1pipm", "NCOther", "CC2p2h", "NC1gamma", "CCmisc"} ; 
	std::string AllName[NVars] = {"CCqe", "CC1pi", "CCCoh", "CCmultipi", "CCDis", "NC1pi0", "NC1pipm", "NCCoh", "NCOther", "CC2p2h", "NC1gamma", "CCmisc", "NCmpi", "NCEta", "NCDIS", "NCElastic"} ; 
  int DrawReorder[NVars] =  {0, 1, 2, 3, 4, 9, 11, 6, 8, 10, 12, 13, 14, 15, 7, 5} ; 
  int DrawPallette[NVars] = {kRed+3, kRed-6, kRed+1, kPink, kMagenta+3, kMagenta, kViolet, kTeal-5, kCyan+1, kCyan+3, kAzure+7, kAzure, kAzure+2, kBlue+4, kGreen, kGreen+1} ; 

	const static int NCuts = 10;

	TH1D* nhitac_histo[NCuts][NVars] = {{0}};
	TH1F* evis_histo[NCuts][NVars] = {{0}};
	TH1F* towall_histo[NCuts][NVars] = {{0}};
	TH1F* dwall_histo[NCuts][NVars] = {{0}};
	TH1D* nring_histo[NCuts][NVars] = {{0}};
	TH1D* pid1_histo[NCuts][NVars] = {{0}};
	TH1D* pid2_histo[NCuts][NVars] = {{0}};
	TH1D* fqnse_histo[NCuts][NVars] = {{0}};
	TH1F* fq1rmom_histo[NCuts][NVars] = {{0}};
	TH1F* Erec_histo[NCuts][NVars] = {{0}};
	TH1F* apfitEvis_histo[NCuts][NVars] = {{0}};
	TH2F* fqpi0nll_histo[NCuts][NVars] = {{0}};
	TH2F* fqemunll_histo[NCuts][NVars] = {{0}};
	TH2F* fqpi0nll_highmass_histo[NCuts][NVars] = {{0}};
	TH1F* fqpi0mass_histo[NCuts][NVars] = {{0}};
	TH1F* trueE_histo[NCuts][NVars] = {{0}};
	TH1F* Q2_histo[NCuts][NVars] = {{0}};
	TH2F* mom_dir_histo[NCuts][NVars] = {{0}};
	TH2F* x_y_histo[NCuts][NVars] = {{0}};
	TH2F* r2_z_histo[NCuts][NVars] = {{0}};
	TH1F* ring_2_mom_histo[NCuts][NVars] = {{0}};
  TH1F* fq1Remunll_histo[NCuts][NVars] = {{0}};
  TH1F* nllr_2Rother_ee_histo[NCuts][NVars] = {{0}};
  TH2F* nllr_pi0mom_2Ree_histo[NCuts][NVars] = {{0}};
  TH1F* pi0mom_histo[NCuts][NVars] = {{0}};
  TH1F* NCbg_histo[NCuts][NVars] = {{0}};
  TH1F* fqpi0nll_1D_histo[NCuts][NVars] = {{0}};
  TH1F* pi0momR1_histo[NCuts][NVars] = {{0}};
  TH1F* pi0momR2_histo[NCuts][NVars] = {{0}};
  TH1F* fqtotq_histo[NCuts][NVars] = {{0}};
  

	THStack *nhitac_stack_hist[NCuts] = {0}; 
	THStack *evis_stack_hist[NCuts] = {0}; 
	THStack *towall_stack_hist[NCuts] = {0}; 
	THStack *dwall_stack_hist[NCuts] = {0}; 
	THStack *nring_stack_hist[NCuts] = {0}; 
	THStack *pid1_stack_hist[NCuts] = {0}; 
	THStack *pid2_stack_hist[NCuts] = {0}; 
	THStack *fq1rmom_stack_hist[NCuts] = {0}; 
	THStack *fqnse_stack_hist[NCuts] = {0}; 
	THStack *Erec_stack_hist[NCuts] = {0}; 
	THStack *apfitEvis_stack_hist[NCuts] = {0}; 
	THStack *fqpi0mass_stack_hist[NCuts] = {0}; 
	THStack *trueE_stack_hist[NCuts] = {0}; 
	THStack *Q2_stack_hist[NCuts] = {0}; 
	THStack *mom_dir_stack_hist[NCuts] = {0}; 
	THStack *fq1Remunll_stack_hist[NCuts] = {0}; 
	THStack *nllr_2Rother_ee_stack_hist[NCuts] = {0}; 
	THStack *pi0mom_stack_hist[NCuts] = {0}; 
	THStack *NCbg_stack_hist[NCuts] = {0}; 
	THStack *NCbg_towall_stack_hist[NCuts] = {0}; 
	THStack *NCbg_dwall_stack_hist[NCuts] = {0}; 
	THStack *fqpi0nll_1D_stack_hist[NCuts] = {0}; 
	THStack *pi0momR1_stack_hist[NCuts] = {0}; 
	THStack *pi0momR2_stack_hist[NCuts] = {0}; 
	THStack *fqtotq_stack_hist[NCuts] = {0}; 
	
	TH2F* fqpi0nll_sig_hist[NCuts] = {0};
	TH2F* fqpi0nll_bg_hist[NCuts] = {0};
	TH2F* nllr_pi0mom_2Ree_sig_hist[NCuts] = {0};
	TH2F* nllr_pi0mom_2Ree_bg_hist[NCuts] = {0};

	for (int i=0; i<NCuts; i++){

		nhitac_stack_hist[i] = new THStack(Form("nhitac_stack_%d", i), "nhitac"); 
		evis_stack_hist[i] = new THStack(Form("evis_stack_%d", i), "evis"); 
		towall_stack_hist[i] = new THStack(Form("towall_stack_%d", i), "towall"); 
		dwall_stack_hist[i] = new THStack(Form("dwall_stack_%d", i), "dwall"); 
		nring_stack_hist[i] = new THStack(Form("nring_stack_%d", i), "nring"); 
		pid1_stack_hist[i] = new THStack(Form("pid1_stack_%d", i), "pid1"); 
		pid2_stack_hist[i] = new THStack(Form("pid2_stack_%d", i), "pid2"); 
		fq1rmom_stack_hist[i] = new THStack(Form("fq1rmom_stack_%d", i), "fq1rmom"); 
		fqnse_stack_hist[i] = new THStack(Form("fqnse_stack_%d", i), "fqnse"); 
		Erec_stack_hist[i] = new THStack(Form("Erec_stack_%d", i), "Erec"); 
		apfitEvis_stack_hist[i] = new THStack(Form("apfitEvis_stack_%d", i), "apfitEvis"); 
		fqpi0mass_stack_hist[i] = new THStack(Form("fqpi0mass_stack_%d", i), "fqpi0mass"); 
		trueE_stack_hist[i] = new THStack(Form("trueE_stack_%d", i), "trueE"); 
		Q2_stack_hist[i] = new THStack(Form("Q2_stack_%d", i), "Q2"); 
		mom_dir_stack_hist[i] = new THStack(Form("mom_dir_stack_%d", i), "mom_dir"); 
		fq1Remunll_stack_hist[i] = new THStack(Form("fq1Remunll_stack_%d", i), "fq1Remunll"); 
		nllr_2Rother_ee_stack_hist[i] = new THStack(Form("nllr_2Rother_ee_stack_%d", i), "fq1Remunll"); 
		pi0mom_stack_hist[i] = new THStack(Form("pi0mom_stack_%d", i), "pi0mom"); 
		NCbg_stack_hist[i] = new THStack(Form("NCbg_stack_%d", i), "NCbg"); 
		NCbg_towall_stack_hist[i] = new THStack(Form("NCbg_stack_%d", i), "NCbg"); 
		NCbg_dwall_stack_hist[i] = new THStack(Form("NCbg_stack_%d", i), "NCbg"); 
		fqpi0nll_1D_stack_hist[i] = new THStack(Form("fqpi0nll_1D_stack_%d", i), "NCbg"); 
		pi0momR1_stack_hist[i] = new THStack(Form("pi0momR1_stack_%d", i), "R1"); 
		pi0momR2_stack_hist[i] = new THStack(Form("pi0momR2_stack_%d", i), "R2"); 
		fqtotq_stack_hist[i] = new THStack(Form("fqtotq_stack_%d", i), "R2"); 

		for (int j=0;j<NVars; j++){
	//	  printf(	"%s_nhitac_histo_%d\n", AllName[j].c_str(), i);		
			nhitac_histo[i][j] = (TH1D*)ifile->Get(Form("%s_nhitac_histo_%d", AllName[j].c_str(), i));
			evis_histo[i][j] = (TH1F*)ifile->Get(Form("%s_evis_histo_%d", AllName[j].c_str(), i));
			towall_histo[i][j] = (TH1F*)ifile->Get(Form("%s_towall_histo_%d", AllName[j].c_str(), i));
			dwall_histo[i][j] = (TH1F*)ifile->Get(Form("%s_dwall_histo_%d", AllName[j].c_str(), i));
			nring_histo[i][j] = (TH1D*)ifile->Get(Form("%s_nring_histo_%d", AllName[j].c_str(), i));
			pid1_histo[i][j] = (TH1D*)ifile->Get(Form("%s_pid1_histo_%d", AllName[j].c_str(), i));
			pid2_histo[i][j] = (TH1D*)ifile->Get(Form("%s_pid2_histo_%d", AllName[j].c_str(), i));
			fqnse_histo[i][j] = (TH1D*)ifile->Get(Form("%s_fqnse_histo_%d", AllName[j].c_str(), i));
			fq1rmom_histo[i][j] = (TH1F*)ifile->Get(Form("%s_fq1rmom_histo_%d", AllName[j].c_str(), i));
			Erec_histo[i][j] = (TH1F*)ifile->Get(Form("%s_Erec_histo_%d", AllName[j].c_str(), i));
			apfitEvis_histo[i][j] = (TH1F*)ifile->Get(Form("%s_apfitEvis_histo_%d", AllName[j].c_str(), i));
			fqpi0nll_histo[i][j] = (TH2F*)ifile->Get(Form("%s_fqpi0nll_histo_%d", AllName[j].c_str(), i));
			fqpi0nll_1D_histo[i][j] = (TH1F*)ifile->Get(Form("%s_fqpi0nll_1D_histo_%d", AllName[j].c_str(), i));
			fqemunll_histo[i][j] = (TH2F*)ifile->Get(Form("%s_fq1Remunll_histo_%d", AllName[j].c_str(), i));
			fqpi0nll_highmass_histo[i][j] = (TH2F*)ifile->Get(Form("%s_fqpi0nll_highmass_histo_%d", AllName[j].c_str(), i));
			fqpi0mass_histo[i][j] = (TH1F*)ifile->Get(Form("%s_fqpi0mass_histo_%d", AllName[j].c_str(), i));
			trueE_histo[i][j] = (TH1F*)ifile->Get(Form("%s_trueE_histo_%d", AllName[j].c_str(), i));
			
			Q2_histo[i][j] = (TH1F*)ifile->Get(Form("%s_Q2_histo_%d", AllName[j].c_str(), i));
			mom_dir_histo[i][j] = (TH2F*)ifile->Get(Form("%s_mom_dir_histo_%d", AllName[j].c_str(), i));
			x_y_histo[i][j] = (TH2F*)ifile->Get(Form("%s_x_y_histo_%d", AllName[j].c_str(), i));
			r2_z_histo[i][j] = (TH2F*)ifile->Get(Form("%s_r2_z_histo_%d", AllName[j].c_str(), i));
			ring_2_mom_histo[i][j] = (TH1F*)ifile->Get(Form("%s_ring_2_mom_histo_%d", AllName[j].c_str(), i));
			fq1Remunll_histo[i][j] = (TH1F*)ifile->Get(Form("%s_fq1Remunll_histo_%d", AllName[j].c_str(), i));
			nllr_2Rother_ee_histo[i][j] = (TH1F*)ifile->Get(Form("%s_nllr_2Rother_ee_histo_%d", AllName[j].c_str(), i));
			nllr_pi0mom_2Ree_histo[i][j] = (TH2F*)ifile->Get(Form("%s_nllr_pi0mom_2Ree_histo_%d", AllName[j].c_str(), i));
			pi0mom_histo[i][j] = (TH1F*)ifile->Get(Form("%s_pi0mom_histo_%d", AllName[j].c_str(), i));
			pi0momR1_histo[i][j] = (TH1F*)ifile->Get(Form("%s_pi0momR1_histo_%d", AllName[j].c_str(), i));
			pi0momR2_histo[i][j] = (TH1F*)ifile->Get(Form("%s_pi0momR2_histo_%d", AllName[j].c_str(), i));
			fqtotq_histo[i][j] = (TH1F*)ifile->Get(Form("%s_fqtotq_histo_%d", AllName[j].c_str(), i));
		}
	}

	//efficiencies and purities:
	
	double sel_sig = 0;
	double sel_bg = 0;
	sel_sig += nring_histo[9][5]->Integral();
	sel_sig += nring_histo[9][7]->Integral();

	for (int i=0; i<NVars; i++){
//		std::cout << i <<nring_histo[9][i]->Integral() << std::endl;
		if (i != 5 and i != 7){
			sel_bg += nring_histo[9][i]->Integral();
		}
	}

	double tot_sig = 0;
	tot_sig += nring_histo[0][5]->Integral();
	tot_sig += nring_histo[0][7]->Integral();
	
	double sel_tot = sel_sig + sel_bg;
	double Eff = sel_sig / tot_sig;
	double Pur = sel_sig / sel_tot;
	
	std::cout.precision(3);
	std::cout << horn_current.c_str() << " " << select.c_str() << std::endl;
	std::cout << "Total events selected     = " << sel_tot << std::endl;
	std::cout << "Total signal selected     = " << sel_sig  << std::endl;
	std::cout << "Total background selected = " << sel_bg  << std::endl;
	std::cout << "Total signal              = " << tot_sig  << std::endl;
	std::cout << "Efficiency                = " << Eff  << std::endl;
	std::cout << "Purity                    = " << Pur  << std::endl;

	std::cout << "Mode " << "Events " << "Fraction " << std::endl;
	for (int var2=0; var2<NCuts; var2++){
	for (int var=0; var<NVars; var++){
		std::cout << AllName[var] << " " << nring_histo[var2][var]->Integral() << " " << nring_histo[var2][var]->Integral() / sel_tot << std::endl;
	}
}


	int fillColour = 0;
	for (int i=0; i<NCuts; i++){
		 fqpi0nll_sig_hist[i] = (TH2F*) fqpi0nll_histo[i][0]->Clone(0); 
		 fqpi0nll_bg_hist[i] = (TH2F*) fqpi0nll_histo[i][0]->Clone(0);
		 nllr_pi0mom_2Ree_sig_hist[i] = (TH2F*) nllr_pi0mom_2Ree_histo[i][0]->Clone(0); 
		 nllr_pi0mom_2Ree_bg_hist[i] = (TH2F*) nllr_pi0mom_2Ree_histo[i][0]->Clone(0); 
		

		for (int j=0; j<NVars; j++){
			
			//Merge stack colours for presentation
/*			if ((j==7)) {
				fillColour = 30;
			nhitac_histo[i][5]->Add(nhitac_histo[i][j]);
			evis_histo[i][5]->Add(evis_histo[i][j]);
			towall_histo[i][5]->Add(towall_histo[i][j]);
			dwall_histo[i][5]->Add(dwall_histo[i][j]);
			nring_histo[i][5]->Add(nring_histo[i][j]);
			pid1_histo[i][5]->Add(pid1_histo[i][j]);
			pid2_histo[i][5]->Add(pid2_histo[i][j]);
			fqnse_histo[i][5]->Add(fqnse_histo[i][j]);
			fq1rmom_histo[i][5]->Add(fq1rmom_histo[i][j]);
			Erec_histo[i][5]->Add(Erec_histo[i][j]);
			apfitEvis_histo[i][5]->Add(apfitEvis_histo[i][j]);
			fqpi0mass_histo[i][5]->Add(fqpi0mass_histo[i][j]);
			trueE_histo[i][5]->Add(trueE_histo[i][j]);
			Q2_histo[i][5]->Add(Q2_histo[i][j]);
			fq1Remunll_histo[i][5]->Add(fq1Remunll_histo[i][j]);
			
			nhitac_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			evis_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			towall_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			dwall_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			nring_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			pid1_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			pid2_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			fqnse_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			fq1rmom_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			Erec_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			apfitEvis_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			fqpi0mass_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			trueE_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			Q2_histo[i][5]->SetTitle("NC1pi0 + NCCoh");
			fq1Remunll_histo[i][5]->SetTitle("NC1pi0 + NCCoh");

			} else if ((j==10)||(j==8)) {
				fillColour = 38;

			nhitac_histo[i][6]->Add(nhitac_histo[i][j]);
			evis_histo[i][6]->Add(evis_histo[i][j]);
			towall_histo[i][6]->Add(towall_histo[i][j]);
			dwall_histo[i][6]->Add(dwall_histo[i][j]);
			nring_histo[i][6]->Add(nring_histo[i][j]);
			pid1_histo[i][6]->Add(pid1_histo[i][j]);
			pid2_histo[i][6]->Add(pid2_histo[i][j]);
			fqnse_histo[i][6]->Add(fqnse_histo[i][j]);
			fq1rmom_histo[i][6]->Add(fq1rmom_histo[i][j]);
			Erec_histo[i][6]->Add(Erec_histo[i][j]);
			apfitEvis_histo[i][6]->Add(apfitEvis_histo[i][j]);
			fqpi0mass_histo[i][6]->Add(fqpi0mass_histo[i][j]);
			trueE_histo[i][6]->Add(trueE_histo[i][j]);
			Q2_histo[i][6]->Add(Q2_histo[i][j]);
			fq1Remunll_histo[i][6]->Add(fq1Remunll_histo[i][j]);
		

			nhitac_histo[i][6]->SetTitle("NCOther");
			evis_histo[i][6]->SetTitle("NCOther");
			towall_histo[i][6]->SetTitle("NCOther");
			dwall_histo[i][6]->SetTitle("NCOther");
			nring_histo[i][6]->SetTitle("NCOther");
			pid1_histo[i][6]->SetTitle("NCOther");
			pid2_histo[i][6]->SetTitle("NCOther");
			fqnse_histo[i][6]->SetTitle("NCOther");
			fq1rmom_histo[i][6]->SetTitle("NCOther");
			Erec_histo[i][6]->SetTitle("NCOther");
			apfitEvis_histo[i][6]->SetTitle("NCOther");
			fqpi0mass_histo[i][6]->SetTitle("NCOther");
			trueE_histo[i][6]->SetTitle("NCOther");
			Q2_histo[i][6]->SetTitle("NCOther");
			fq1Remunll_histo[i][6]->SetTitle("NCOther");
		

		} else if ((j==1)||(j==2)||(j==3)||(j==4)||(j==9)||(j==11)){
				fillColour = 46;

			nhitac_histo[i][0]->Add(nhitac_histo[i][j]);
			evis_histo[i][0]->Add(evis_histo[i][j]);
			towall_histo[i][0]->Add(towall_histo[i][j]);
			dwall_histo[i][0]->Add(dwall_histo[i][j]);
			nring_histo[i][0]->Add(nring_histo[i][j]);
			pid1_histo[i][0]->Add(pid1_histo[i][j]);
			pid2_histo[i][0]->Add(pid2_histo[i][j]);
			fqnse_histo[i][0]->Add(fqnse_histo[i][j]);
			fq1rmom_histo[i][0]->Add(fq1rmom_histo[i][j]);
			Erec_histo[i][0]->Add(Erec_histo[i][j]);
			apfitEvis_histo[i][0]->Add(apfitEvis_histo[i][j]);
			fqpi0mass_histo[i][0]->Add(fqpi0mass_histo[i][j]);
			trueE_histo[i][0]->Add(trueE_histo[i][j]);
			Q2_histo[i][0]->Add(Q2_histo[i][j]);
			fq1Remunll_histo[i][0]->Add(fq1Remunll_histo[i][j]);
		

			nhitac_histo[i][0]->SetTitle("CC");
			evis_histo[i][0]->SetTitle("CC");
			towall_histo[i][0]->SetTitle("CC");
			dwall_histo[i][0]->SetTitle("CC");
			nring_histo[i][0]->SetTitle("CC");
			pid1_histo[i][0]->SetTitle("CC");
			pid2_histo[i][0]->SetTitle("CC");
			fqnse_histo[i][0]->SetTitle("CC");
			fq1rmom_histo[i][0]->SetTitle("CC");
			Erec_histo[i][0]->SetTitle("CC");
			apfitEvis_histo[i][0]->SetTitle("CC");
			fqpi0mass_histo[i][0]->SetTitle("CC");
			trueE_histo[i][0]->SetTitle("CC");
			Q2_histo[i][0]->SetTitle("CC");
			fq1Remunll_histo[i][0]->SetTitle("CC");
		}
	*/		


///////////////////////////////////////////////////////////////////////////////////////////////
//Unmerged plots
				nhitac_stack_hist[i]->Add(nhitac_histo[i][DrawReorder[j]]);
				evis_stack_hist[i]->Add(evis_histo[i][DrawReorder[j]]);
				towall_stack_hist[i]->Add(towall_histo[i][DrawReorder[j]]);
				dwall_stack_hist[i]->Add(dwall_histo[i][DrawReorder[j]]);
				nring_stack_hist[i]->Add(nring_histo[i][DrawReorder[j]]);
				pid1_stack_hist[i]->Add(pid1_histo[i][DrawReorder[j]]);
				pid2_stack_hist[i]->Add(pid2_histo[i][DrawReorder[j]]);
				fqnse_stack_hist[i]->Add(fqnse_histo[i][DrawReorder[j]]);
				fq1rmom_stack_hist[i]->Add(fq1rmom_histo[i][DrawReorder[j]]);
				Erec_stack_hist[i]->Add(Erec_histo[i][DrawReorder[j]]);
				apfitEvis_stack_hist[i]->Add(apfitEvis_histo[i][DrawReorder[j]]);
				//fqpi0nll_highmass_stack_hist[i]->Add(fqpionll_highmass_histo[i][DrawReorder[j]]);
				fqpi0mass_stack_hist[i]->Add(fqpi0mass_histo[i][DrawReorder[j]]);
				trueE_stack_hist[i]->Add(trueE_histo[i][DrawReorder[j]]);
				Q2_stack_hist[i]->Add(Q2_histo[i][DrawReorder[j]]);
				mom_dir_stack_hist[i]->Add(mom_dir_histo[i][DrawReorder[j]]);
				//x_y_stack_hist[i]->Add(x_y_histo[i][DrawReorder[j]]);
				//r2_z_stack_hist[i]->Add(r2_z_histo[i][DrawReorder[j]]);
				//ring_2_mom_stack_hist[i]->Add(ring_2_histo[i][DrawReorder[j]]);
				fq1Remunll_stack_hist[i]->Add(fq1Remunll_histo[i][DrawReorder[j]]);
				nllr_2Rother_ee_stack_hist[i]->Add(nllr_2Rother_ee_histo[i][DrawReorder[j]]);
				pi0mom_stack_hist[i]->Add(pi0mom_histo[i][DrawReorder[j]]);
    		fqpi0nll_1D_stack_hist[i]->Add(fqpi0nll_1D_histo[i][DrawReorder[j]]);
    		pi0momR1_stack_hist[i]->Add(pi0momR1_histo[i][DrawReorder[j]]);
    		pi0momR2_stack_hist[i]->Add(pi0momR2_histo[i][DrawReorder[j]]);
    		fqtotq_stack_hist[i]->Add(fqtotq_histo[i][DrawReorder[j]]);

			if ((j == 5) || (j == 7)){
				fqpi0nll_sig_hist[i]->Add(fqpi0nll_histo[i][j]);
				nllr_pi0mom_2Ree_sig_hist[i]->Add(nllr_pi0mom_2Ree_histo[i][j]);
				
				NCbg_towall_stack_hist[i]->Add(towall_histo[i][j]);
				NCbg_dwall_stack_hist[i]->Add(dwall_histo[i][j]);

			} else {
				fqpi0nll_bg_hist[i]->Add(fqpi0nll_histo[i][j]);
				nllr_pi0mom_2Ree_bg_hist[i]->Add(nllr_pi0mom_2Ree_histo[i][j]);
			}
	/*		
			if ((j != 5) && (j != 7)) {
				nhitac_stack_hist[i]->Add(nhitac_histo[i][j]);
				evis_stack_hist[i]->Add(evis_histo[i][j]);
				towall_stack_hist[i]->Add(towall_histo[i][j]);
				dwall_stack_hist[i]->Add(dwall_histo[i][j]);
				nring_stack_hist[i]->Add(nring_histo[i][j]);
				pid1_stack_hist[i]->Add(pid1_histo[i][j]);
				pid2_stack_hist[i]->Add(pid2_histo[i][j]);
				fqnse_stack_hist[i]->Add(fqnse_histo[i][j]);
				fq1rmom_stack_hist[i]->Add(fq1rmom_histo[i][j]);
				Erec_stack_hist[i]->Add(Erec_histo[i][j]);
				apfitEvis_stack_hist[i]->Add(apfitEvis_histo[i][j]);
				//fqpi0nll_highmass_stack_hist[i]->Add(fqpionll_highmass_histo[i][j]);
				fqpi0mass_stack_hist[i]->Add(fqpi0mass_histo[i][j]);
				trueE_stack_hist[i]->Add(trueE_histo[i][j]);
				Q2_stack_hist[i]->Add(Q2_histo[i][j]);
				mom_dir_stack_hist[i]->Add(mom_dir_histo[i][j]);
				//x_y_stack_hist[i]->Add(x_y_histo[i][j]);
				//r2_z_stack_hist[i]->Add(r2_z_histo[i][j]);
				//ring_2_mom_stack_hist[i]->Add(ring_2_histo[i][j]);
				fq1Remunll_stack_hist[i]->Add(fq1Remunll_histo[i][j]);
				nllr_2Rother_ee_stack_hist[i]->Add(nllr_2Rother_ee_histo[i][j]);
				pi0mom_stack_hist[i]->Add(pi0mom_histo[i][j]);
    		fqpi0nll_1D_stack_hist[i]->Add(fqpi0nll_1D_histo[i][j]);
*/
				//NC bg plot
				if ((j==6)||(j==8)||(j==10)) NCbg_stack_hist[i]->Add(fqpi0mass_histo[i][j]);
				if ((j==6)||(j==8)||(j==10)) NCbg_towall_stack_hist[i]->Add(towall_histo[i][j]);
				if ((j==6)||(j==8)||(j==10)) NCbg_dwall_stack_hist[i]->Add(dwall_histo[i][j]);
				//NCbg_stack_hist[i]->Add(fqpi0mass_histo[i][j]);
		//	}		

		}
	
/*				
				nhitac_stack_hist[i]->Add(nhitac_histo[i][7]);
				evis_stack_hist[i]->Add(evis_histo[i][7]);
				towall_stack_hist[i]->Add(towall_histo[i][7]);
				dwall_stack_hist[i]->Add(dwall_histo[i][7]);
				nring_stack_hist[i]->Add(nring_histo[i][7]);
				pid1_stack_hist[i]->Add(pid1_histo[i][7]);
				pid2_stack_hist[i]->Add(pid2_histo[i][7]);
				fqnse_stack_hist[i]->Add(fqnse_histo[i][7]);
				fq1rmom_stack_hist[i]->Add(fq1rmom_histo[i][7]);
				Erec_stack_hist[i]->Add(Erec_histo[i][7]);
				apfitEvis_stack_hist[i]->Add(apfitEvis_histo[i][7]);
				//fqpi0nll_highmass_stack_hist[i]->Add(fqpionll_highmass_histo[i][7]);
				fqpi0mass_stack_hist[i]->Add(fqpi0mass_histo[i][7]);
				trueE_stack_hist[i]->Add(trueE_histo[i][7]);
				Q2_stack_hist[i]->Add(Q2_histo[i][7]);
				mom_dir_stack_hist[i]->Add(mom_dir_histo[i][7]);
				//x_y_stack_hist[i]->Add(x_y_histo[i][7]);
				//r2_z_stack_hist[i]->Add(r2_z_histo[i][7]);
				//ring_2_mom_stack_hist[i]->Add(ring_2_histo[i][7]);
				fq1Remunll_stack_hist[i]->Add(fq1Remunll_histo[i][7]);
				nllr_2Rother_ee_stack_hist[i]->Add(nllr_2Rother_ee_histo[i][7]);
				pi0mom_stack_hist[i]->Add(pi0mom_histo[i][7]);
    		fqpi0nll_1D_stack_hist[i]->Add(fqpi0nll_1D_histo[i][7]);


				nhitac_stack_hist[i]->Add(nhitac_histo[i][5]);
				evis_stack_hist[i]->Add(evis_histo[i][5]);
				towall_stack_hist[i]->Add(towall_histo[i][5]);
				dwall_stack_hist[i]->Add(dwall_histo[i][5]);
				nring_stack_hist[i]->Add(nring_histo[i][5]);
				pid1_stack_hist[i]->Add(pid1_histo[i][5]);
				pid2_stack_hist[i]->Add(pid2_histo[i][5]);
				fqnse_stack_hist[i]->Add(fqnse_histo[i][5]);
				fq1rmom_stack_hist[i]->Add(fq1rmom_histo[i][5]);
				Erec_stack_hist[i]->Add(Erec_histo[i][5]);
				apfitEvis_stack_hist[i]->Add(apfitEvis_histo[i][5]);
				//fqpi0nll_highmass_stack_hist[i]->Add(fqpionll_highmass_histo[i][5]);
				fqpi0mass_stack_hist[i]->Add(fqpi0mass_histo[i][5]);
				trueE_stack_hist[i]->Add(trueE_histo[i][5]);
				Q2_stack_hist[i]->Add(Q2_histo[i][5]);
				mom_dir_stack_hist[i]->Add(mom_dir_histo[i][5]);
				//x_y_stack_hist[i]->Add(x_y_histo[i][5]);
				//r2_z_stack_hist[i]->Add(r2_z_histo[i][5]);
				//ring_2_mom_stack_hist[i]->Add(ring_2_histo[i][5]);
				fq1Remunll_stack_hist[i]->Add(fq1Remunll_histo[i][5]);
				nllr_2Rother_ee_stack_hist[i]->Add(nllr_2Rother_ee_histo[i][5]);
				pi0mom_stack_hist[i]->Add(pi0mom_histo[i][5]);
    		fqpi0nll_1D_stack_hist[i]->Add(fqpi0nll_1D_histo[i][5]);

*/
//merged plots
/*			nhitac_stack_hist[i]->Add(nhitac_histo[i][0]);
			evis_stack_hist[i]->Add(evis_histo[i][0]);
			towall_stack_hist[i]->Add(towall_histo[i][0]);
			dwall_stack_hist[i]->Add(dwall_histo[i][0]);
			nring_stack_hist[i]->Add(nring_histo[i][0]);
			pid1_stack_hist[i]->Add(pid1_histo[i][0]);
			pid2_stack_hist[i]->Add(pid2_histo[i][0]);
			fqnse_stack_hist[i]->Add(fqnse_histo[i][0]);
			fq1rmom_stack_hist[i]->Add(fq1rmom_histo[i][0]);
			Erec_stack_hist[i]->Add(Erec_histo[i][0]);
			apfitEvis_stack_hist[i]->Add(apfitEvis_histo[i][0]);
			//fqpi0nll_highmass_stack_hist[i]->Add(fqpionll_highmass_histo[i][0]);
			fqpi0mass_stack_hist[i]->Add(fqpi0mass_histo[i][0]);
			trueE_stack_hist[i]->Add(trueE_histo[i][0]);
			Q2_stack_hist[i]->Add(Q2_histo[i][0]);
			mom_dir_stack_hist[i]->Add(mom_dir_histo[i][0]);
			//x_y_stack_hist[i]->Add(x_y_histo[i][0]);
			//r2_z_stack_hist[i]->Add(r2_z_histo[i][0]);
			//ring_2_mom_stack_hist[i]->Add(ring_2_histo[i][0]);
			fq1Remunll_stack_hist[i]->Add(fq1Remunll_histo[i][0]);
			nhitac_stack_hist[i]->Add(nhitac_histo[i][6]);
			evis_stack_hist[i]->Add(evis_histo[i][6]);
			towall_stack_hist[i]->Add(towall_histo[i][6]);
			dwall_stack_hist[i]->Add(dwall_histo[i][6]);
			nring_stack_hist[i]->Add(nring_histo[i][6]);
			pid1_stack_hist[i]->Add(pid1_histo[i][6]);
			pid2_stack_hist[i]->Add(pid2_histo[i][6]);
			fqnse_stack_hist[i]->Add(fqnse_histo[i][6]);
			fq1rmom_stack_hist[i]->Add(fq1rmom_histo[i][6]);
			Erec_stack_hist[i]->Add(Erec_histo[i][6]);
			apfitEvis_stack_hist[i]->Add(apfitEvis_histo[i][6]);
			//fqpi0nll_highmass_stack_hist[i]->Add(fqpionll_highmass_histo[i][6]);
			fqpi0mass_stack_hist[i]->Add(fqpi0mass_histo[i][6]);
			trueE_stack_hist[i]->Add(trueE_histo[i][6]);
			Q2_stack_hist[i]->Add(Q2_histo[i][6]);
			mom_dir_stack_hist[i]->Add(mom_dir_histo[i][6]);
			//x_y_stack_hist[i]->Add(x_y_histo[i][6]);
			//r2_z_stack_hist[i]->Add(r2_z_histo[i][6]);
			//ring_2_mom_stack_hist[i]->Add(ring_2_histo[i][6]);
			fq1Remunll_stack_hist[i]->Add(fq1Remunll_histo[i][6]);
		  
			nhitac_stack_hist[i]->Add(nhitac_histo[i][5]);
			evis_stack_hist[i]->Add(evis_histo[i][5]);
			towall_stack_hist[i]->Add(towall_histo[i][5]);
			dwall_stack_hist[i]->Add(dwall_histo[i][5]);
			nring_stack_hist[i]->Add(nring_histo[i][5]);
			pid1_stack_hist[i]->Add(pid1_histo[i][5]);
			pid2_stack_hist[i]->Add(pid2_histo[i][5]);
			fqnse_stack_hist[i]->Add(fqnse_histo[i][5]);
			fq1rmom_stack_hist[i]->Add(fq1rmom_histo[i][5]);
			Erec_stack_hist[i]->Add(Erec_histo[i][5]);
			apfitEvis_stack_hist[i]->Add(apfitEvis_histo[i][5]);
			//fqpi0nll_highmass_stack_hist[i]->Add(fqpionll_highmass_histo[i][5]);
			fqpi0mass_stack_hist[i]->Add(fqpi0mass_histo[i][5]);
			trueE_stack_hist[i]->Add(trueE_histo[i][5]);
			Q2_stack_hist[i]->Add(Q2_histo[i][5]);
			mom_dir_stack_hist[i]->Add(mom_dir_histo[i][5]);
			//x_y_stack_hist[i]->Add(x_y_histo[i][5]);
			//r2_z_stack_hist[i]->Add(r2_z_histo[i][5]);
			//ring_2_mom_stack_hist[i]->Add(ring_2_histo[i][5]);
			fq1Remunll_stack_hist[i]->Add(fq1Remunll_histo[i][5]);

*/

		


	/*		nhitac_histo[i][j]->SetFillColor(fillColour);
			evis_histo[i][j]->SetFillColor(fillColour);
			towall_histo[i][j]->SetFillColor(fillColour);
			dwall_histo[i][j]->SetFillColor(fillColour);
			nring_histo[i][j]->SetFillColor(fillColour);
			pid1_histo[i][j]->SetFillColor(fillColour);
			pid2_histo[i][j]->SetFillColor(fillColour);
			fqnse_histo[i][j]->SetFillColor(fillColour);
			fq1rmom_histo[i][j]->SetFillColor(fillColour);
			Erec_histo[i][j]->SetFillColor(fillColour);
			apfitEvis_histo[i][j]->SetFillColor(fillColour);
			fqpi0mass_histo[i][j]->SetFillColor(fillColour);
			trueE_histo[i][j]->SetFillColor(fillColour);
			Q2_histo[i][j]->SetFillColor(fillColour);
			fq1Remunll_histo[i][j]->SetFillColor(fillColour);
		*/	
	
	
	}


	TArrow *arw1 = new TArrow();
    TArrow *arw2 = new TArrow();
    arw1->SetLineColor(kBlack);
    arw2->SetLineColor(kBlack);
    arw1->SetLineWidth(3);
    arw2->SetLineWidth(3);
		
	//small
/*		double leg_x1 = 0.55;
		double leg_y1 = 0.65;
		double leg_x2 = 0.9;
		double leg_y2 = 0.9;
  */
//large

		double leg_x1 = 0.7;
		double leg_y1 = 0.4;
		double leg_x2 = 0.9;
		double leg_y2 = 0.9;

	int DrawCut = 0;
	std::string savename = "";

   Int_t palette[5];
   palette[0] = kGreen+2;
   palette[1] = kBlue+1;
   palette[2] = kGreen+1;
   palette[3] = kBlue+2;
   palette[4] = kBlue+3;
	

	Int_t lrg_palette[16];
	lrg_palette[0] = kRed+3;
	lrg_palette[1] = kRed+1;
	lrg_palette[2] = kAzure+3;
	lrg_palette[3] = kRed-6;
	lrg_palette[4] = kRed;
	lrg_palette[5] = kAzure+2;
	lrg_palette[6] = kPink+10;
	lrg_palette[7] = kAzure+3;
	lrg_palette[8] = kAzure;
	lrg_palette[9] = kRed - 1;
	lrg_palette[10] = kBlue+4;
	lrg_palette[11] = kBlue-2;
	lrg_palette[12] = kBlue-7;
	lrg_palette[13] = kAzure+2;
	lrg_palette[14] = kSpring;
	lrg_palette[15] = kSpring-1;
	
	//Set pallette
	//gStyle->SetPalette(kRainBow);
	gStyle->SetPalette(16, DrawPallette);
  //gStyle->SetPalette(5,palette);
	
	DrawCut = 0;
	auto c_hist = new TCanvas();
	nhitac_stack_hist[DrawCut]->Draw("hist pfc");
	nhitac_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 25.);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  nhitac_stack_hist[DrawCut]->GetXaxis()->SetTitle("OD hits");
	nhitac_stack_hist[DrawCut]->SetTitle("");
	arw1->DrawLine( 16, 0,16 , nhitac_stack_hist[0]->GetMaximum());
	arw1->DrawArrow(16,nhitac_stack_hist[0]->GetMaximum(),14,nhitac_stack_hist[0]->GetMaximum(),0.05,">");
	FormatHist(nhitac_stack_hist[DrawCut], 1, 2);
	c_hist->SaveAs(Form("%scut_%d_nhitac_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );


	DrawCut = 0;
	auto c_fq1rmom = new TCanvas();
	fq1rmom_stack_hist[DrawCut]->Draw("hist pfc");
	fq1rmom_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  fq1rmom_stack_hist[DrawCut]->GetXaxis()->SetTitle("Visible energy");
	fq1rmom_stack_hist[DrawCut]->SetTitle("");
	arw1->DrawLine( 30, 0,30 , fq1rmom_stack_hist[DrawCut]->GetMaximum());
	arw1->DrawArrow(30,fq1rmom_stack_hist[DrawCut]->GetMaximum(),35,fq1rmom_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	FormatHist(fq1rmom_stack_hist[DrawCut], 1, 2);
	c_fq1rmom->SaveAs(Form("%scut_%d_fq1rmom_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );

	DrawCut = 1;
	auto c_towall = new TCanvas();
	towall_stack_hist[DrawCut]->Draw("hist pfc");
//	towall_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  towall_stack_hist[DrawCut]->GetXaxis()->SetTitle("ToWall");
	towall_stack_hist[DrawCut]->SetTitle("");
	arw1->DrawLine( 170, 0,170 , towall_stack_hist[DrawCut]->GetMaximum());
	arw1->DrawArrow(170,towall_stack_hist[DrawCut]->GetMaximum(),300,towall_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	FormatHist(towall_stack_hist[DrawCut], 1, 2);
	c_towall->SaveAs(Form("%scut_%d_towall_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );



	DrawCut = 1;
	auto c_dwall = new TCanvas();
	dwall_stack_hist[DrawCut]->Draw("hist pfc");
//	dwall_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  dwall_stack_hist[DrawCut]->GetXaxis()->SetTitle("ToWall");
	dwall_stack_hist[DrawCut]->SetTitle("");
	arw1->DrawLine( 80, 0,80 , dwall_stack_hist[DrawCut]->GetMaximum());
	arw1->DrawArrow(80,dwall_stack_hist[DrawCut]->GetMaximum(),150,dwall_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	FormatHist(dwall_stack_hist[DrawCut], 1, 2);
	c_dwall->SaveAs(Form("%scut_%d_dwall_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );



	DrawCut = 2;
	auto c_fq1rmom2 = new TCanvas();
	fq1rmom_stack_hist[DrawCut]->Draw("hist pfc");
//	fq1rmom_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  fq1rmom_stack_hist[DrawCut]->GetXaxis()->SetTitle("Visible Energy");
	fq1rmom_stack_hist[DrawCut]->SetTitle("");
	arw1->DrawLine( 100, 0,100 , fq1rmom_stack_hist[DrawCut]->GetMaximum());
	arw1->DrawArrow(100,fq1rmom_stack_hist[DrawCut]->GetMaximum(),200,fq1rmom_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	FormatHist(fq1rmom_stack_hist[DrawCut], 1, 2);
	c_fq1rmom2->SaveAs(Form("%scut_%d_fq1rmom_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );


	DrawCut = 3;
	int dcyecut = 1;
	auto c_fqnse = new TCanvas();
	fqnse_stack_hist[DrawCut]->Draw("hist pfc");
//	fqnse_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  fqnse_stack_hist[DrawCut]->GetXaxis()->SetTitle("Number of sub-events");
	fqnse_stack_hist[DrawCut]->SetTitle("");
	arw1->DrawLine( dcyecut, 0,dcyecut , fqnse_stack_hist[DrawCut]->GetMaximum());
	arw2->DrawLine( dcyecut+1, 0,dcyecut+1 , fqnse_stack_hist[DrawCut]->GetMaximum());
	arw1->DrawArrow(dcyecut,fqnse_stack_hist[DrawCut]->GetMaximum(),dcyecut+0.25,fqnse_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	arw2->DrawArrow(dcyecut+1,fqnse_stack_hist[DrawCut]->GetMaximum(),dcyecut+ 0.75,fqnse_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	FormatHist(fqnse_stack_hist[DrawCut], 1, 2);
	c_fqnse->SaveAs(Form("%scut_%d_fqnse_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );


	DrawCut = 4;
	int nringcut = 2;
	auto c_nring = new TCanvas();
	nring_stack_hist[DrawCut]->Draw("hist pfc");
//	nring_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  nring_stack_hist[DrawCut]->GetXaxis()->SetTitle("Number of rings");
	nring_stack_hist[DrawCut]->SetTitle("");
	arw1->DrawLine( nringcut, 0,nringcut , nring_stack_hist[DrawCut]->GetMaximum());
	arw2->DrawLine( nringcut+1, 0,nringcut+1 , nring_stack_hist[DrawCut]->GetMaximum());
	arw1->DrawArrow(nringcut,nring_stack_hist[DrawCut]->GetMaximum(),nringcut+0.25,nring_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	arw2->DrawArrow(nringcut+1,nring_stack_hist[DrawCut]->GetMaximum(),nringcut+0.75,nring_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	FormatHist(nring_stack_hist[DrawCut], 1, 2);
	c_nring->SaveAs(Form("%scut_%d_nring_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );

/*
	DrawCut = 5;
	auto c_pid1 = new TCanvas();
	pid1_stack_hist[DrawCut]->Draw("hist pfc");
//	pid1_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  pid1_stack_hist[DrawCut]->GetXaxis()->SetTitle("1st ring PID");
	pid1_stack_hist[DrawCut]->SetTitle("");
	arw1->DrawLine( 1, 0,1 , pid1_stack_hist[DrawCut]->GetMaximum());
	arw2->DrawLine( 2, 0,2 , pid1_stack_hist[DrawCut]->GetMaximum());
	arw2->DrawArrow(1,pid1_stack_hist[DrawCut]->GetMaximum(),1.25,pid1_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	arw1->DrawArrow(2,pid1_stack_hist[DrawCut]->GetMaximum(),1.75,pid1_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	FormatHist(pid1_stack_hist[DrawCut], 1, 2);
	c_pid1->SaveAs(Form("%scut_%d_pid1_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );


	DrawCut = 6;
	auto c_pid2 = new TCanvas();
	pid2_stack_hist[DrawCut]->Draw("hist pfc");
//	pid2_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  pid2_stack_hist[DrawCut]->GetXaxis()->SetTitle("2nd ring PID");
	pid2_stack_hist[DrawCut]->SetTitle("");
	arw1->DrawLine( 1, 0,1 , pid2_stack_hist[DrawCut]->GetMaximum());
	arw2->DrawLine( 2, 0,2 , pid2_stack_hist[DrawCut]->GetMaximum());
	arw2->DrawArrow(2,pid2_stack_hist[DrawCut]->GetMaximum(),1.75,pid2_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	arw1->DrawArrow(1,pid2_stack_hist[DrawCut]->GetMaximum(),1.25,pid2_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	FormatHist(pid2_stack_hist[DrawCut], 1, 2);
	c_pid2->SaveAs(Form("%scut_%d_pid2_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );
*/
//////////////////////////

	DrawCut = 5;
	auto c_nllr_2Rother_ee = new TCanvas();
	//gStyle->SetPalette(kRainBow);
	nllr_2Rother_ee_stack_hist[DrawCut]->Draw("hist pfc");
//	nllr_2Rother_ee_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
  //nllr_2Rother_ee_stack_hist[DrawCut]->SetTitle(Form("%s cut %d ln(L_{2Rother}/L_{ee}) ", horn_current.c_str(), DrawCut));
	gPad->BuildLegend(0.7,0.5,0.9,0.9,"", "f");
	//gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  nllr_2Rother_ee_stack_hist[DrawCut]->GetXaxis()->SetTitle("ln(L_{2Rother}/L_{ee})");
	FormatHist(nllr_2Rother_ee_stack_hist[DrawCut], 1, 2);
  arw1->DrawLine( 100, 0, 100, nllr_2Rother_ee_stack_hist[DrawCut]->GetMaximum());
  arw1->DrawArrow( 100, nllr_2Rother_ee_stack_hist[DrawCut]->GetMaximum(), 0, nllr_2Rother_ee_stack_hist[DrawCut]->GetMaximum(), 0.05, ">");
	c_nllr_2Rother_ee->SaveAs(Form("%scut_%d_nllr_2Rother_ee_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );

	DrawCut = 6;
	TCanvas c6("c6","PID1_hists",10,10,700,900);
	gStyle->SetPalette(kRainBow);
	//gPad->SetLogy();
//	fqpi0nll_bg_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
  fqpi0nll_bg_hist[DrawCut]->SetStats(0);
  fqpi0nll_bg_hist[DrawCut]->GetXaxis()->SetTitle("Reconstructed pi^{0} mass (MeV)");
  fqpi0nll_bg_hist[DrawCut]->GetYaxis()->SetTitle("ln(L_{#pi}/L_{e})");
  fqpi0nll_bg_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //fqpi0nll_bg_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //fqpi0nll_bg_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi}/L_{e}) vs.#pi^{0} mass", horn_current.c_str()));
  fqpi0nll_bg_hist[DrawCut]->SetTitle("");
	fqpi0nll_bg_hist[DrawCut]->Draw("colz");
  //gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c6.Update();
	c6.SaveAs(Form("%scut_%d_fqpi0nll_bg_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 6;
	TCanvas c7("c7","PID1_hists",30,10,800,900);
	gStyle->SetPalette(kRainBow);

	//gPad->SetLogy();
//	fqpi0nll_sig_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
  fqpi0nll_sig_hist[DrawCut]->SetStats(0);
  fqpi0nll_sig_hist[DrawCut]->GetXaxis()->SetTitle("Reconstructed pi^{0} mass (MeV)");
  fqpi0nll_sig_hist[DrawCut]->GetYaxis()->SetTitle("ln(L_{#pi}/L_{e})");
  fqpi0nll_sig_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
	fqpi0nll_sig_hist[DrawCut]->Draw("colz");
  //fqpi0nll_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //fqpi0nll_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi}/L_{e}) vs.#pi^{0} mass", horn_current.c_str()));
  fqpi0nll_sig_hist[DrawCut]->SetTitle("");
  arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c7.Update();
	c7.SaveAs(Form("%scut_%d_fqpi0nll_sig_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 6;
	TCanvas cfqepi01D("cfqepi01D","PID1_hists",30,10,800,900);
	gStyle->SetPalette(16, DrawPallette);
	//gPad->SetLogy();
//	fqpi0nll_1D_stack_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
	fqpi0nll_1D_stack_hist[DrawCut]->Draw("hist pfc");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  fqpi0nll_1D_stack_hist[DrawCut]->GetYaxis()->SetTitle("Events");
  fqpi0nll_1D_stack_hist[DrawCut]->GetXaxis()->SetTitle("ln(L_{#pi^0}/L_{e})");
  fqpi0nll_1D_stack_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //fqpi0nll_1D_stack_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  fqpi0nll_1D_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0, 400);
  fqpi0nll_1D_stack_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi^0}/L_{e}) ", horn_current.c_str()));
  fqpi0nll_1D_stack_hist[DrawCut]->SetTitle("");
  arw1->DrawLine( 100, 0, 100, fqpi0nll_1D_stack_hist[DrawCut]->GetMaximum());
  arw1->DrawArrow( 100, fqpi0nll_1D_stack_hist[DrawCut]->GetMaximum(), 150, fqpi0nll_1D_stack_hist[DrawCut]->GetMaximum(), 0.05, ">");
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	FormatHist(fqpi0nll_1D_stack_hist[DrawCut], 1, 2);
	cfqepi01D.Update();
	cfqepi01D.SaveAs(Form("%scut_%d_epi0PID_1D_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 5;
	TCanvas c2("c1","1Remunll_hists",10,10,700,900);
//	gStyle->SetPalette(kRainBow);
	//gPad->SetLogy();
	fq1Remunll_stack_hist[DrawCut]->Draw("hist pfc");
	fq1Remunll_stack_hist[DrawCut]->SetTitle("");
  fq1Remunll_stack_hist[DrawCut]->GetXaxis()->SetTitle("ln(L_{2Rother}/L_{ee})");
  fq1Remunll_stack_hist[DrawCut]->GetYaxis()->SetTitle("Events");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	arw1->DrawLine( 0, 0,0 , fq1Remunll_stack_hist[DrawCut]->GetMaximum());
	arw1->DrawArrow(0,fq1Remunll_stack_hist[DrawCut]->GetMaximum(),10,fq1Remunll_stack_hist[DrawCut]->GetMaximum(),0.05,">");
	//gPad->SetLeftMargin(0.12);
	c2.SaveAs(Form("%scut_%d_1Remunll_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 5;
	TCanvas c2Reepid("c2Reepid","2Reepid_hists",10,10,700,900);
	gStyle->SetPalette(kRainBow);
	//gPad->SetLogy();
//	fqpi0nll_bg_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
  nllr_pi0mom_2Ree_bg_hist[DrawCut]->SetStats(0);
  nllr_pi0mom_2Ree_bg_hist[DrawCut]->GetXaxis()->SetTitle("fqmrmom[pi0]");
  nllr_pi0mom_2Ree_bg_hist[DrawCut]->GetYaxis()->SetTitle("ln(L_{2Rother}/L_{ee})");
  nllr_pi0mom_2Ree_bg_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //nllr_pi0mom_2Ree_bg_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_pi0mom_2Ree_bg_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi}/L_{e}) vs.#pi^{0} mass", horn_current.c_str()));
  nllr_pi0mom_2Ree_bg_hist[DrawCut]->SetTitle("");
	nllr_pi0mom_2Ree_bg_hist[DrawCut]->Draw("colz");
  //gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
 // arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c2Reepid.Update();
	c2Reepid.SaveAs(Form("%scut_%d_pi0mom_2Ree_bg_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 5;
	TCanvas c2Reepid2("c2Reepid2","PID1_hists",30,10,800,900);
	gStyle->SetPalette(kRainBow);

	//gPad->SetLogy();
//	nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
	nllr_pi0mom_2Ree_sig_hist[DrawCut]->Draw("colz");
  nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetStats(0);
  nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetXaxis()->SetTitle("fqmrmom[pi0]");
  nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetYaxis()->SetTitle("ln(L_{2Rother}/L_{ee})");
  nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{2Rother}/L_{ee}) vs.#pi^{0} momentum", horn_current.c_str()));
  nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle("");
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c2Reepid2.Update();
	c2Reepid2.SaveAs(Form("%scut_%d_pi0mom_2Ree_sig_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );



	DrawCut = 1;
	auto cNCtowall = new TCanvas();
	gStyle->SetPalette(5, palette);

	//gPad->SetLogy();
//	nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
  //pi0mom_stack_hist[DrawCut]->SetStats(0);
	NCbg_towall_stack_hist[DrawCut]->Draw("hist pfc");
  NCbg_towall_stack_hist[DrawCut]->GetXaxis()->SetTitle("towall");
  NCbg_towall_stack_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{2Rother}/L_{ee}) vs.#pi^{0} momentum", horn_current.c_str()));
  NCbg_towall_stack_hist[DrawCut]->SetTitle("");
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	cNCtowall->Update();
	cNCtowall->SaveAs(Form("/home/dm3315/Documents/T2K-SK/NCpi0/figs/selection_plots/NCbackground/cut_%d_NCtowall_%s_%s.pdf", DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 1;
	auto cNCdwall = new TCanvas();
	gStyle->SetPalette(5, palette);

	//gPad->SetLogy();
//	nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
  //pi0mom_stack_hist[DrawCut]->SetStats(0);
	NCbg_dwall_stack_hist[DrawCut]->Draw("hist pfc");
  NCbg_dwall_stack_hist[DrawCut]->GetXaxis()->SetTitle("dwall");
  NCbg_dwall_stack_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{2Rother}/L_{ee}) vs.#pi^{0} momentum", horn_current.c_str()));
  NCbg_dwall_stack_hist[DrawCut]->SetTitle("");
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	cNCdwall->Update();
	cNCdwall->SaveAs(Form("/home/dm3315/Documents/T2K-SK/NCpi0/figs/selection_plots/NCbackground/cut_%d_NCdwall_%s_%s.pdf", DrawCut,  horn_current.c_str(), select.c_str()) );




	/////////////////////////////////////////////     FINAL SAMPLE PLOTS        /////////////////////////////////////////////////////

	DrawCut = 9;
	auto c_trueE = new TCanvas();

	gStyle->SetPalette(16, DrawPallette);
	trueE_stack_hist[DrawCut]->Draw("hist pfc");
//	trueE_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  trueE_stack_hist[DrawCut]->GetXaxis()->SetTitle("True Energy (GeV)");
	trueE_stack_hist[DrawCut]->SetTitle("");
	FormatHist(trueE_stack_hist[DrawCut], 1, 2);
	c_trueE->SaveAs(Form("%scut_%d_trueE_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );


	DrawCut = 9;
	auto c_Q2 = new TCanvas();
	Q2_stack_hist[DrawCut]->Draw("hist pfc");
//	Q2_stack_hist[DrawCut]->GetXaxis()->SetRangeUser(0., 1000.);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLogy();
	//gPad->SetLeftMargin(0.12);
  Q2_stack_hist[DrawCut]->GetXaxis()->SetTitle("Q^{2} (GeV)^{2}");
	Q2_stack_hist[DrawCut]->SetTitle("");
	FormatHist(Q2_stack_hist[DrawCut], 1, 2);
	c_Q2->SaveAs(Form("%scut_%d_Q2_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );

	DrawCut = 9;
	TCanvas c1("c1","fqpi0mass_hists",10,10,700,900);
	//gStyle->SetPalette(kRainBow);
	//gPad->SetLogy();
	
	fqpi0mass_stack_hist[DrawCut]->Draw("hist pfc");
	fqpi0mass_stack_hist[DrawCut]->SetTitle("");
	//fqpi0mass_stack_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqpi0mass with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  fqpi0mass_stack_hist[DrawCut]->GetXaxis()->SetTitle("Reconstructed #pi^{0} mass (MeV)");
	FormatHist(fqpi0mass_stack_hist[DrawCut], 1, 2);
	c1.SaveAs(Form("%scut_%d_fqpi0mass_%s_%s.pdf", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );
	c1.SaveAs(Form("%scut_%d_fqpi0mass_%s_%s.png", odir.c_str(), DrawCut, horn_current.c_str(), select.c_str()) );



	DrawCut = 9;
	TCanvas c3("c3","PID0_hists",10,10,700,900);
	//gStyle->SetPalette(kRainBow);
	//gPad->SetLogy();
	pid1_stack_hist[DrawCut]->Draw("hist pfc");
	//pid1_stack_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 0 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
	pid1_stack_hist[DrawCut]->SetTitle("");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//arw1->DrawLine( 16, 0,16 , nhitac_stack_hist[0]->GetMaximum());
	//arw1->DrawArrow(16,nhitac_stack_hist[0]->GetMaximum(),10,nhitac_stack_hist[0]->GetMaximum(),0.05,">");
	gPad->SetLeftMargin(0.12);
	c3.SaveAs(Form("%scut_%d_PID0_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 9;
	TCanvas c5("c4","PID1_hists",10,10,700,900);
	//gStyle->SetPalette(kRainBow);
	//gPad->SetLogy();
	pid2_stack_hist[DrawCut]->Draw("hist pfc");
	pid2_stack_hist[DrawCut]->SetTitle("");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//arw1->DrawLine( 16, 0,16 , nhitac_stack_hist[0]->GetMaximum());
	//arw1->DrawArrow(16,nhitac_stack_hist[0]->GetMaximum(),10,nhitac_stack_hist[0]->GetMaximum(),0.05,">");
	c5.SaveAs(Form("%scut_%d_PID1_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );
	

	DrawCut = 9;
	TCanvas c2Reepid3("c2Reepid3","PID1_hists",30,10,800,900);
	gStyle->SetPalette(16, DrawPallette);	
	//gPad->SetLogy();
//	nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
	nllr_2Rother_ee_stack_hist[DrawCut]->Draw("hist pfc");
 // nllr_2Rother_ee_stack_hist[DrawCut]->SetStats(0);
  nllr_2Rother_ee_stack_hist[DrawCut]->GetXaxis()->SetTitle("ln(L_{2Rother}/L_{ee})");
  nllr_2Rother_ee_stack_hist[DrawCut]->GetYaxis()->SetTitle("Events");
  nllr_2Rother_ee_stack_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //nllr_2Rother_ee_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_2Rother_ee_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{2Rother}/L_{ee}) vs.#pi^{0} momentum", horn_current.c_str()));
  nllr_2Rother_ee_stack_hist[DrawCut]->SetTitle("");
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c2Reepid3.Update();
	c2Reepid3.SaveAs(Form("%scut_%d_pi0mom_2Ree_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );

	DrawCut = 9;
	TCanvas c9Reepid("c9Reepid","2Reepid_hists",10,10,700,900);
	gStyle->SetPalette(kRainBow);
	//gPad->SetLogy();
//	fqpi0nll_bg_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
  nllr_pi0mom_2Ree_bg_hist[DrawCut]->SetStats(0);
  nllr_pi0mom_2Ree_bg_hist[DrawCut]->GetXaxis()->SetTitle("fqmrmom[pi0]");
  nllr_pi0mom_2Ree_bg_hist[DrawCut]->GetYaxis()->SetTitle("ln(L_{2Rother}/L_{ee})");
  nllr_pi0mom_2Ree_bg_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //nllr_pi0mom_2Ree_bg_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_pi0mom_2Ree_bg_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi}/L_{e}) vs.#pi^{0} mass", horn_current.c_str()));
  nllr_pi0mom_2Ree_bg_hist[DrawCut]->SetTitle("");
	nllr_pi0mom_2Ree_bg_hist[DrawCut]->Draw("colz");
  //gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
 // arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c9Reepid.Update();
	c9Reepid.SaveAs(Form("%scut_%d_pi0mom_2Ree_bg_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 9;
	TCanvas c9Reepid2("c9Reepid2","PID1_hists",30,10,800,900);
	gStyle->SetPalette(kRainBow);

	//gPad->SetLogy();
//	nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
	nllr_pi0mom_2Ree_sig_hist[DrawCut]->Draw("colz");
  nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetStats(0);
  nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetXaxis()->SetTitle("fqmrmom[pi0]");
  nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetYaxis()->SetTitle("ln(L_{2Rother}/L_{ee})");
  nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{2Rother}/L_{ee}) vs.#pi^{0} momentum", horn_current.c_str()));
  nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle("");
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c9Reepid2.Update();
	c9Reepid2.SaveAs(Form("%scut_%d_pi0mom_2Ree_sig_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 9;
	TCanvas cfqpi0nllbg9("cfqpi0nllbg9","PID1_hists",10,10,700,900);
	gStyle->SetPalette(kRainBow);

	//gPad->SetLogy();
//	fqpi0nll_bg_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
  fqpi0nll_bg_hist[DrawCut]->SetStats(0);
  fqpi0nll_bg_hist[DrawCut]->GetXaxis()->SetTitle("Reconstructed pi^{0} mass (MeV)");
  fqpi0nll_bg_hist[DrawCut]->GetYaxis()->SetTitle("ln(L_{#pi}/L_{e})");
  fqpi0nll_bg_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //fqpi0nll_bg_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //fqpi0nll_bg_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi}/L_{e}) vs.#pi^{0} mass", horn_current.c_str()));
  fqpi0nll_bg_hist[DrawCut]->SetTitle("");
	fqpi0nll_bg_hist[DrawCut]->Draw("colz");
  //gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	cfqpi0nllbg9.Update();
	cfqpi0nllbg9.SaveAs(Form("%scut_%d_fqpi0nll_bg_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 9;
	TCanvas cfqpi0nllsig9("cfqpi0nllsig9","PID1_hists",30,10,800,900);
	gStyle->SetPalette(kRainBow);

	//gPad->SetLogy();
//	fqpi0nll_sig_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
  fqpi0nll_sig_hist[DrawCut]->SetStats(0);
  fqpi0nll_sig_hist[DrawCut]->GetXaxis()->SetTitle("Reconstructed pi^{0} mass (MeV)");
  fqpi0nll_sig_hist[DrawCut]->GetYaxis()->SetTitle("ln(L_{#pi}/L_{e})");
  fqpi0nll_sig_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
	fqpi0nll_sig_hist[DrawCut]->Draw("colz");
  //fqpi0nll_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //fqpi0nll_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi}/L_{e}) vs.#pi^{0} mass", horn_current.c_str()));
  fqpi0nll_sig_hist[DrawCut]->SetTitle("");
  arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	cfqpi0nllsig9.Update();
	cfqpi0nllsig9.SaveAs(Form("%scut_%d_fqpi0nll_sig_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );

		DrawCut = 9;
	auto cpi0mom = new TCanvas();
	gStyle->SetPalette(16, DrawPallette);

	//gPad->SetLogy();
//	nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
  //pi0mom_stack_hist[DrawCut]->SetStats(0);
	pi0mom_stack_hist[DrawCut]->Draw("hist pfc");
  pi0mom_stack_hist[DrawCut]->GetXaxis()->SetTitle("fqmrmom[pi0]");
  pi0mom_stack_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->SetTitle(Form("%s ln(L_{2Rother}/L_{ee}) vs.#pi^{0} momentum", horn_current.c_str()));
  pi0mom_stack_hist[DrawCut]->SetTitle("");
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	cpi0mom->Update();
	cpi0mom->SaveAs(Form("%scut_%d_pi0mom_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


	DrawCut = 9;
	TCanvas cfqepi01D9("cfqepi01D9","PID1_hists",30,10,800,900);
	gStyle->SetPalette(16, DrawPallette);
	//gPad->SetLogy();
//	fqpi0nll_1D_stack_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
	fqpi0nll_1D_stack_hist[DrawCut]->Draw("hist pfc");
	//fqpi0nll_1D_stack_hist[DrawCut]->GetXaxis()->SetRange(-400, 400);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  fqpi0nll_1D_stack_hist[DrawCut]->GetYaxis()->SetTitle("Events");
  fqpi0nll_1D_stack_hist[DrawCut]->GetXaxis()->SetTitle("ln(L_{#pi^0}/L_{e})");
  fqpi0nll_1D_stack_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //fqpi0nll_1D_stack_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  fqpi0nll_1D_stack_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi^0}/L_{e}) ", horn_current.c_str()));
  fqpi0nll_1D_stack_hist[DrawCut]->SetTitle("");
  arw1->DrawLine( 100, 0, 100, fqpi0nll_1D_stack_hist[DrawCut]->GetMaximum());
  arw1->DrawArrow( 100, fqpi0nll_1D_stack_hist[DrawCut]->GetMaximum(), 150, fqpi0nll_1D_stack_hist[DrawCut]->GetMaximum(), 0.05, ">");
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	FormatHist(fqpi0nll_1D_stack_hist[DrawCut], 1, 2);
	cfqepi01D9.Update();
	cfqepi01D9.SaveAs(Form("%scut_%d_epi0PID_1D_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );

//ring1 mom
	DrawCut = 9;
	TCanvas cpi0momR19("cpi0momR19","pi0momR1_hists",30,10,800,900);
	gStyle->SetPalette(16, DrawPallette);
	//gPad->SetLogy();
//	fqpi0nll_1D_stack_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
	pi0momR1_stack_hist[DrawCut]->Draw("hist pfc");
	//fqpi0nll_1D_stack_hist[DrawCut]->GetXaxis()->SetRange(-400, 400);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  pi0momR1_stack_hist[DrawCut]->GetYaxis()->SetTitle("Events");
  pi0momR1_stack_hist[DrawCut]->GetXaxis()->SetTitle("fqpi0mom1[0]");
  pi0momR1_stack_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //fqpi0nll_1D_stack_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  pi0momR1_stack_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi^0}/L_{e}) ", horn_current.c_str()));
  pi0momR1_stack_hist[DrawCut]->SetTitle("");
  //arw1->DrawLine( 100, 0, 100, pi0momR1_stack_hist[DrawCut]->GetMaximum());
  //arw1->DrawArrow( 100, pi0momR1_stack_hist[DrawCut]->GetMaximum(), 150, fqpi0nll_1D_stack_hist[DrawCut]->GetMaximum(), 0.05, ">");
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	FormatHist(pi0momR1_stack_hist[DrawCut], 1, 2);
	cpi0momR19.Update();
	cpi0momR19.SaveAs(Form("%scut_%d_pi0momR1_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );


//ring2 mom
	DrawCut = 9;
	TCanvas cpi0momR29("cpi0momR29","pi0momR2_hists",30,10,800,900);
	gStyle->SetPalette(16, DrawPallette);
	//gPad->SetLogy();
//	fqpi0nll_1D_stack_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
	pi0momR2_stack_hist[DrawCut]->Draw("hist pfc");
	//fqpi0nll_1D_stack_hist[DrawCut]->GetXaxis()->SetRange(-400, 400);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  pi0momR2_stack_hist[DrawCut]->GetYaxis()->SetTitle("Events");
  pi0momR2_stack_hist[DrawCut]->GetXaxis()->SetTitle("fqpi0mom1[0]");
  pi0momR2_stack_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //fqpi0nll_1D_stack_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  pi0momR2_stack_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi^0}/L_{e}) ", horn_current.c_str()));
  pi0momR2_stack_hist[DrawCut]->SetTitle("");
  //arw1->DrawLine( 100, 0, 100, pi0momR2_stack_hist[DrawCut]->GetMaximum());
  //arw1->DrawArrow( 100, pi0momR2_stack_hist[DrawCut]->GetMaximum(), 150, fqpi0nll_1D_stack_hist[DrawCut]->GetMaximum(), 0.05, ">");
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	FormatHist(pi0momR2_stack_hist[DrawCut], 1, 2);
	cpi0momR29.Update();
	cpi0momR29.SaveAs(Form("%scut_%d_pi0momR2_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );

//deposited charge
	DrawCut = 9;
	TCanvas cfqtotq9("cfqtotq9","fqtotq_hists",30,10,800,900);
	gStyle->SetPalette(16, DrawPallette);
	gPad->SetLogy();
//	fqpi0nll_1D_stack_hist[DrawCut]->SetTitle(Form("Cut %d, %s fqmrpid 1 with %s selection", DrawCut, horn_current.c_str(), select.c_str()));
	fqtotq_stack_hist[DrawCut]->Draw("hist pfc");
	//fqpi0nll_1D_stack_hist[DrawCut]->GetXaxis()->SetRange(-400, 400);
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  fqtotq_stack_hist[DrawCut]->GetYaxis()->SetTitle("Events");
  fqtotq_stack_hist[DrawCut]->GetXaxis()->SetTitle("fqtotq[0]");
  fqtotq_stack_hist[DrawCut]->GetYaxis()->SetTitleOffset(1.75);
  //fqpi0nll_1D_stack_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  //fqtotq_stack_hist[DrawCut]->SetTitle(Form("%s ln(L_{#pi^0}/L_{e}) ", horn_current.c_str()));
  fqtotq_stack_hist[DrawCut]->SetTitle("");
  //arw1->DrawLine( 100, 0, 100, fqtotq_stack_hist[DrawCut]->GetMaximum());
  //arw1->DrawArrow( 100, fqtotq_stack_hist[DrawCut]->GetMaximum(), 150, fqpi0nll_1D_stack_hist[DrawCut]->GetMaximum(), 0.05, ">");
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	FormatHist(fqtotq_stack_hist[DrawCut], 1, 2);
	cfqtotq9.Update();
	cfqtotq9.SaveAs(Form("%scut_%d_fqtotq_%s_%s.pdf", odir.c_str(), DrawCut,  horn_current.c_str(), select.c_str()) );





//////////////////////////////////////////// EVOLUTION PLOTS /////////////////////////////////////

 
	TCanvas cNCbg("cNCbg","NCbg_hists",10,10,700,900);
	for (int Cut=0; Cut<NCuts; Cut++){
	//	gStyle->SetPalette(kRainBow);
		//gPad->SetLogy();
		NCbg_stack_hist[Cut]->Draw("hist pfc");
		NCbg_stack_hist[Cut]->GetXaxis()->SetTitle("fqpi0mass[0]");
		NCbg_stack_hist[Cut]->GetYaxis()->SetTitle("Events");
		gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
		//arw1->DrawLine( 16, 0,16 , nhitac_stack_hist[0]->GetMaximum());
		//arw1->DrawArrow(16,nhitac_stack_hist[0]->GetMaximum(),10,nhitac_stack_hist[0]->GetMaximum(),0.05,">");
		gPad->SetLeftMargin(0.12);
		//cNCbg.SaveAs(Form("/home/dm3315/Documents/T2K-SK/NCpi0/figs/selection_plots/NCbackground/cut_%d_NCbg_%s_%s.pdf", Cut,  horn_current.c_str(), select.c_str()) );
	}

///// 2D mode plots
	TCanvas c2dvar2Ree("c2dvar2Ree","2ReeVar_hists",10,10,700,900);
	for (int Var=0; Var<NVars; Var++){
		DrawCut = 5;
		gStyle->SetPalette(kRainBow);
		//gPad->SetLogy();
		nllr_pi0mom_2Ree_histo[DrawCut][Var]->Draw("colz");
		nllr_pi0mom_2Ree_histo[DrawCut][Var]->GetXaxis()->SetTitle("pi0mom");
		nllr_pi0mom_2Ree_histo[DrawCut][Var]->SetTitle(Form("cut %d %s", DrawCut, AllName[Var].c_str()));
		nllr_pi0mom_2Ree_histo[DrawCut][Var]->GetYaxis()->SetTitle("nllr");
//		gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
		//arw1->DrawLine( 16, 0,16 , nhitac_stack_hist[0]->GetMaximum());
		//arw1->DrawArrow(16,nhitac_stack_hist[0]->GetMaximum(),10,nhitac_stack_hist[0]->GetMaximum(),0.05,">");
		gPad->SetLeftMargin(0.12);
		c2dvar2Ree.SaveAs(Form("/home/dm3315/Documents/T2K-SK/NCpi0/figs/selection_plots/NCbackground/cut_%d_nllr_pi0mom_2Ree_%s_%s_%s.pdf", DrawCut, AllName[Var].c_str(), horn_current.c_str(), select.c_str()) );
	}

	TCanvas c2dvarpi0nll("c2dvarpi0nll","pi0nll_hists",10,10,700,900);
	for (int Var=0; Var<NVars; Var++){
		DrawCut = 6;
		gStyle->SetPalette(kRainBow);
		//gPad->SetLogy();
		fqpi0nll_histo[DrawCut][Var]->Draw("colz");
		fqpi0nll_histo[DrawCut][Var]->SetTitle(Form("cut %d %s", DrawCut, AllName[Var].c_str()));
		fqpi0nll_histo[DrawCut][Var]->GetXaxis()->SetTitle("pi0mass");
		fqpi0nll_histo[DrawCut][Var]->GetYaxis()->SetTitle("nllr");
	//	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
		//arw1->DrawLine( 16, 0,16 , nhitac_stack_hist[0]->GetMaximum());
		//arw1->DrawArrow(16,nhitac_stack_hist[0]->GetMaximum(),10,nhitac_stack_hist[0]->GetMaximum(),0.05,">");
		gPad->SetLeftMargin(0.12);
		c2dvarpi0nll.SaveAs(Form("/home/dm3315/Documents/T2K-SK/NCpi0/figs/selection_plots/NCbackground/cut_%d_nllr_pi0mom_2Ree_%s_%s_%s.pdf", DrawCut, AllName[Var].c_str(), horn_current.c_str(), select.c_str()) );
	}



	ifile->Close();


}




void DrawHist2D(TH2F* histo, std::string outpath){
  auto c_hist = new TCanvas();
  histo->Draw("colz");
  c_hist->SaveAs(Form("%s", outpath.c_str()));
}


void FormatHist2D(TH2F* h){
    h->SetStats(0);
    h->GetXaxis()->SetTitleFont(132);
    h->GetYaxis()->SetTitleFont(132);
    h->GetXaxis()->SetTitleSize(0.04);
    h->GetYaxis()->SetTitleSize(0.04);
    h->GetXaxis()->SetLabelFont(132);
    h->GetYaxis()->SetLabelFont(132);
    h->GetXaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetTitleOffset(1.3);


}

void FormatHist(TH1D* h, int linecolor, int linestyle){
    h->SetStats(0);
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

  h->SetLineWidth(2);
  h->SetLineColor(linecolor);
  h->SetLineStyle(linestyle);
}








