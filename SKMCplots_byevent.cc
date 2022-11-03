

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
	float thresh = 0;
	if (pid == 11) thresh =  0.583; //electron
	if (pid == 13) thresh = 120.5; //muon
	if (pid == 111) thresh = 0; //pi0 or is generator photon??
	if (pid == 211) thresh = 159.2; //pipm
	if (pid == 221) thresh = 0; //eta
	if (pid == 2212) thresh = 1070; //P
	if (pid == 2112) thresh = 0; 

	return thresh;
}

enum VisibleTopology{
  kVisTop1Electron,
  kVisTop1Muon,
  kVisTop1ElectronPlusOther,
  kVisTop1MuonPlusOther,
  kVisTop1NeutralPion,
  kVisTop1ChargedHadron,
  kVisTopOther,
  nVisTop,
};

enum TrueTopology{
  kTrueTop1Electron,
  kTrueTop1ElectronPlus1ChargedPion,
  kTrueTop1ElectronPlusNChargedPion,
  kTrueTop1ElectronPlus1NeutralPion,
  kTrueTop1ElectronPlusOther,
  kTrueTop1Muon,
  kTrueTop1MuonPlus1ChargedPion,
  kTrueTop1MuonPlusNChargedPion,
  kTrueTop1MuonPlus1NeutralPion,
  kTrueTop1MuonPlusOther,
  kTrueTopOther,
  nTrueTop
};
double GetMassFromPDG(int PDG) {
    // *****************************

    switch (abs(PDG)) {

    case 11:
      return 0.511E-3;
      break;
    case 13:
      return 105.658E-3;
      break;
    case 15:
      return 1.77682;
      break;
    case 22:
      return 0.;
      break;
    case 211:
      return 139.57E-3;
      break;
    case 111:
      return 134.98E-3;
      break;
    case 2112:
      return 939.565E-3;
      break;
    case 2212:
      return 938.27E-3;
      break;
    //Oxygen nucleus
    case 1000080160:
      return 14.89926;
      break;
	//eta
	case 221:
	  return 547.862E-3;
	  break;
	  //K^0 (s or l)
	case 311:
	case 130:
	case 310:
	  return 497.611E-3;
	  break;
	case 321:
	  return 493.677E-3;
	  break;
	// Lamda baryon
	case 3122:
	  return 1115.683E-3;
	  break;
    case 12:
    case 14:
    case 16:
      return 0.0;
      break;
    default:
      std::cerr << "Haven't got a saved mass for PDG " << PDG << std::endl;
      std::cerr << "Please implement me! " << __FILE__ << ":" << __LINE__ << std::endl;
      throw;
    } // End switch

    std::cerr << "Warning, didn't catch a saved mass" << std::endl;
    return 0;
  }
float CherenkovThresh_mass(float mass) {
	//mass in MeV/c2
	float n = 1.33;
	float thresh = mass / sqrt(n*n - 1);
	return thresh;
}


int returnSKEventTopology(bool Visible, bool ConsiderSecondaries, int Npvc, int Ipvc[200], int Ichvc[200], int Iflvc[200], float abspvc[200], int nscndprt, int lmecscnd[200], float tscnd[200], int iprtscnd[200], int iprntprt[200], float pscnd[200][3]) {

  //Cherenkov threshold to look for visible final states
  //MeV
  double pthres_e  = 0.57;
  double pthres_mu = 118.;
  double pthres_pi = 156.;
  double pthres_p  = 1051.;
  double pthres_gm = 20.;

  //Get number of electrons, pions etc.
  int n_charged_pions =0;
  int n_pi0s = 0;
  int n_mu = 0;
  int n_e = 0;
  int n_gm = 0;
  int n_p = 0;
  int n_n = 0;
  int n_other = 0;

  //Now loop over all primary particles in an event
  for(int n_part = 0 ; n_part < Npvc ; n_part++){
    //Iflvc is to check if the particle survived
    //0 - determined later procedure
    //2 - Escape from the detector
    if(Ichvc[n_part] == 0 || !(Iflvc[n_part] == 0 || Iflvc[n_part] == 2)){
      continue;
    }else{
      switch(abs(Ipvc[n_part])){
        case(211):
          if(Visible) {
            if (abspvc[n_part] > pthres_pi){
              n_charged_pions++;
            }
          }
          else{
            n_charged_pions++;
          }
          break;
        case(11):
          if(Visible) {
            if (abspvc[n_part] > pthres_e){
              n_e++;
            }
          }
          else{
            n_e++;
          }
          break;
        case(13):
          if(Visible) {
            if (abspvc[n_part] > pthres_mu){
              n_mu++;
            }
          }
          else{
            n_mu++;
          }
          break;
        case(22):
          if(Visible) {
            if (abspvc[n_part] > pthres_gm){
              n_gm++;
            }
          }
          else{
            n_gm++;
          }
          break;
        case(111):
          n_pi0s++;
          break;
        case(2212):
          if(Visible) {
            if (abspvc[n_part] > pthres_p){
              n_p++;
            }
          }
          else{
            n_p++;
          }
          break;
        case(2112):
          if(!Visible){
            n_n++;
          }
          break;
        default:
          if(abs(Ipvc[n_part]) > 99){
            int id = abs(Ipvc[n_part]);
            if (id== 3332) id= 3334;
            if (id==-3332) id=-3334;
            double pmom = abspvc[n_part];
            Double_t mass = GetMassFromPDG(id); // mass
            bool OverChThr = (pmom/TMath::Sqrt(pmom*pmom+mass*mass)>0.75188);
            if (Visible) {
              if (OverChThr) {
                n_other++;
              }
            }
            else {
              n_other++;
            }
          }
          break;
      }
    }
  }

  //Now loop over any secondaries
  if (ConsiderSecondaries) {
    for ( Int_t i=0 ; i<nscndprt ; i++ ) {
      //Ignore some interaction types
      switch (lmecscnd[i]) {
        case 6: // pair production
        case 7: // compton
        case 8: // photoelectric
        case 9: // bremstralung
          //case 12: // hadronic interaction
          //case 13: // coherent scattering
        case 30: // below threshold
          continue;
      }
      if (tscnd[i]>10.) continue; // decay near vertex
      if ((abs(iprtscnd[i])==211) && iprtscnd[i]==iprntprt[i]) continue;
      Double_t pmom = TMath::Sqrt(pscnd[i][0]*pscnd[i][0]+pscnd[i][1]*pscnd[i][1]+pscnd[i][2]*pscnd[i][2]);
      switch (abs(iprtscnd[i])) {
        case(211):
          if(Visible) {
            if (pmom > pthres_pi){
              n_charged_pions++;
            }
          }
          else{
            n_charged_pions++;
          }
          break;
        case(11):
          if (Visible) {
            if (pmom > pthres_e){
              n_e++;
            }
          }
          else {
            n_e++;
          }
          break;
        case(13):
          if(Visible) {
            if (pmom > pthres_mu){
              n_mu++;
            }
          }
          else{
            n_mu++;
          }
          break;
        case(22):
          if(Visible) {
            if (pmom > pthres_gm){
              n_gm++;
            }
          }
          else{
            n_gm++;
          }
          break;
        case(111):
          n_pi0s++;
          break;
        case(2212):
          if(Visible) {
            if (pmom > pthres_p){
              n_p++;
            }
          }
          else{
            n_p++;
          }
          break;
        case(2112):
          if(!Visible){
            n_n++;
          }
          break;
        default:
          if(abs(iprtscnd[i]) > 99){
            int id = abs(iprtscnd[i]);
            if (id== 3332) id= 3334;
            if (id==-3332) id=-3334;
            Double_t mass = GetMassFromPDG(id); // mass
            bool OverChThr = (pmom/TMath::Sqrt(pmom*pmom+mass*mass)>0.75188);
            if (Visible) {
              if (OverChThr ){
                n_other++;
              }
            }
            else {
              n_other++;
            }
          }
          break;
      }
    }
  }

  // Remove two gammas from pi0 decay
  // there might be exceptions: e.g., one of the gammas from pi0 decay is below cherenkov threshold
  // or, pi0 doesn't decay to 2 gammas, in both cases n_gm is underestimated
  n_gm -= 2*n_pi0s;

  int Topology;

  if (Visible) {
    if ( ( (n_e == 1 && n_gm == 0) || (n_e == 0 && n_gm == 1) )
         && n_mu == 0 && n_p == 0 && n_charged_pions == 0 && n_pi0s == 0 && n_other == 0 ) {Topology = int(kVisTop1Electron);} // 1e only or 1gamma only

    else if ( n_mu == 1
           && n_e == 0 && n_gm == 0 && n_p == 0 && n_charged_pions == 0 && n_pi0s == 0 && n_other == 0 ) {Topology = int(kVisTop1Muon);} // 1mu only

    else if ( ( (n_e == 1 && n_gm == 0) || (n_e == 0 && n_gm == 1) )
         && n_mu == 0 && (n_p > 0 || n_charged_pions > 0 || n_pi0s > 0 || n_other > 0) ) {Topology = int(kVisTop1ElectronPlusOther);} // 1e only or 1gamma only + other (no mu)

    else if ( n_mu == 1
           && n_e == 0 && (n_gm > 0 || n_p > 0 || n_charged_pions > 0 || n_pi0s > 0 || n_other > 0) ) {Topology = int(kVisTop1MuonPlusOther);} // 1mu only + other (including gamma, no e)

    else if ( n_pi0s == 1
           && n_mu == 0 && n_e == 0 && n_gm == 0 && n_p == 0 && n_charged_pions == 0 && n_other == 0 ) {Topology = int(kVisTop1NeutralPion);} // 1pi0 only

    else if ( ( (n_charged_pions == 1 && n_p == 0) || (n_charged_pions == 0 && n_p == 1) )
           && n_mu == 0 && n_e == 0 && n_gm == 0 && n_pi0s == 0 && n_other == 0 ) {Topology = int(kVisTop1ChargedHadron);} // 1 charged hadron only
    else {Topology = int(kVisTopOther);} // all other cases
  } else {
    if (n_e == 1 && n_mu == 0 && n_charged_pions == 0 && n_pi0s == 0 && n_other == 0)      {Topology = int(kTrueTop1Electron);}
    else if (n_e == 1 && n_mu == 0 && n_charged_pions == 1 && n_pi0s == 0 && n_other == 0) {Topology = int(kTrueTop1ElectronPlus1ChargedPion);}
    else if (n_e == 1 && n_mu == 0 && n_charged_pions >  1 && n_pi0s == 0 && n_other == 0) {Topology = int(kTrueTop1ElectronPlusNChargedPion);}
    else if (n_e == 1 && n_mu == 0 && n_charged_pions == 0 && n_pi0s == 1 && n_other == 0) {Topology = int(kTrueTop1ElectronPlus1NeutralPion);}
    else if (n_e == 1)                                                                     {Topology = int(kTrueTop1ElectronPlusOther);}
    else if (n_mu == 1 && n_e == 0 && n_charged_pions == 0 && n_pi0s == 0 && n_other == 0) {Topology = int(kTrueTop1Muon);}
    else if (n_mu == 1 && n_e == 0 && n_charged_pions == 1 && n_pi0s == 0 && n_other == 0) {Topology = int(kTrueTop1MuonPlus1ChargedPion);}
    else if (n_mu == 1 && n_e == 0 && n_charged_pions >  1 && n_pi0s == 0 && n_other == 0) {Topology = int(kTrueTop1MuonPlusNChargedPion);}
    else if (n_mu == 1 && n_e == 0 && n_charged_pions == 0 && n_pi0s == 1 && n_other == 0) {Topology = int(kTrueTop1MuonPlus1NeutralPion);}
    else if (n_mu == 1)                                                                    {Topology = int(kTrueTop1MuonPlusOther);}
    else {Topology = int(kTrueTopOther);}
  }


  return Topology;
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
   Int_t           nev;
   Int_t           nsub;
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
   Float_t           fqpi0mass[2];
	 Int_t           Npvc;
   Int_t           Ipvc[100];   //[Npvc]
   Int_t           Ichvc[100];   //[Npvc]
   Int_t           Iorgvc[100];   //[Npvc]
   Int_t           Iflvc[100];   //[Npvc]
   Float_t         Abspvc[100];   //[Npvc]
   Float_t         Pvc[100][3];   //[Npvc]
   Int_t           nscndprt;
   Int_t           itrkscnd[1000];   //[nscndprt]
   Int_t           istakscnd[1000];   //[nscndprt]
   Float_t         vtxscnd[1000][3];   //[nscndprt]
   Float_t         pscnd[1000][3];   //[nscndprt]
   Int_t           iprtscnd[1000];   //[nscndprt]
   Float_t         tscnd[1000];   //[nscndprt]
   Int_t           iprntprt[1000];   //[nscndprt]
   Int_t           lmecscnd[1000];   //[nscndprt]
   
	 TBranch        *b_numnu;   //!
    TBranch        *b_nsub;   //!
    TBranch        *b_nev;   //!
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
	 TBranch        *b_fqpi0mass;   //!
   TBranch        *b_Npvc;   //!
   TBranch        *b_Ipvc;   //!
   TBranch        *b_Ichvc;   //!
   TBranch        *b_Iorgvc;   //!
   TBranch        *b_Iflvc;   //!
   TBranch        *b_Abspvc;   //!
   TBranch        *b_Pvc;   //!
   TBranch        *b_nscndprt;   //!
   TBranch        *b_itrkscnd;   //!
   TBranch        *b_istakscnd;   //!
   TBranch        *b_vtxscnd;   //!
   TBranch        *b_pscnd;   //!
   TBranch        *b_iprtscnd;   //!
   TBranch        *b_tscnd;   //!
   TBranch        *b_iprntprt;   //!
   TBranch        *b_lmecscnd;   //!
 
	 chain->SetBranchAddress("fqpi0nll", fqpi0nll, &b_fqpi0nll);
	 chain->SetBranchAddress("nsub", &nsub, &b_nsub);
	 chain->SetBranchAddress("nev", &nev, &b_nev);
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
   chain->SetBranchAddress("fqpi0mass", &fqpi0mass, &b_fqpi0mass);
   chain->SetBranchAddress("Npvc", &Npvc, &b_Npvc);
   chain->SetBranchAddress("Ipvc", Ipvc, &b_Ipvc);
   chain->SetBranchAddress("Ichvc", Ichvc, &b_Ichvc);
   chain->SetBranchAddress("Iorgvc", Iorgvc, &b_Iorgvc);
   chain->SetBranchAddress("Iflvc", Iflvc, &b_Iflvc);
   chain->SetBranchAddress("Abspvc", Abspvc, &b_Abspvc);
   chain->SetBranchAddress("Pvc", Pvc, &b_Pvc);
   chain->SetBranchAddress("nscndprt", &nscndprt, &b_nscndprt);
   chain->SetBranchAddress("itrkscnd", itrkscnd, &b_itrkscnd);
   chain->SetBranchAddress("istakscnd", istakscnd, &b_istakscnd);
   chain->SetBranchAddress("vtxscnd", vtxscnd, &b_vtxscnd);
   chain->SetBranchAddress("pscnd", pscnd, &b_pscnd);
   chain->SetBranchAddress("iprtscnd", iprtscnd, &b_iprtscnd);
   chain->SetBranchAddress("tscnd", tscnd, &b_tscnd);
   chain->SetBranchAddress("iprntprt", iprntprt, &b_iprntprt);
   chain->SetBranchAddress("lmecscnd", lmecscnd, &b_lmecscnd);



	int NBins = 100;
	int lo_x = -1;
	int hi_x = 2;
	const static int npart = 5;
	TH1F* mom_CC_reject_histo[npart] ={0}; 
	TH1F* mom_NCpi0_reject_histo[npart] ={0};  
	TH1F* mom_NCbg_reject_histo[npart] ={0}; 

	TH1F* mom_CC_acc_histo[npart] ={0}; 
	TH1F* mom_NCpi0_acc_histo[npart] ={0};
	TH1F* mom_NCbg_acc_histo[npart] ={0}; 
					  										
	TH1F* mom_nu_rj_histo[npart] = {0}; 
	TH1F* mom_e_rj_histo[npart] = {0}; 
	TH1F* mom_mu_rj_histo[npart] = {0}; 
	TH1F* mom_p_rj_histo[npart] = {0}; 
	TH1F* mom_n_rj_histo[npart] = {0}; 
	TH1F* mom_pi0_rj_histo[npart]= {0}; 
	TH1F* mom_pipm_rj_histo[npart]= {0}; 
	TH1F* mom_other_rj_histo[npart]= {0}; 
	
	TH1F* mom_nu_acc_histo[npart] = {0}; 
	TH1F* mom_e_acc_histo[npart] = {0}; 
	TH1F* mom_mu_acc_histo[npart] = {0}; 
	TH1F* mom_p_acc_histo[npart] = {0}; 
	TH1F* mom_n_acc_histo[npart] = {0}; 
	TH1F* mom_pi0_acc_histo[npart]= {0}; 
	TH1F* mom_pipm_acc_histo[npart]= {0}; 
	TH1F* mom_other_acc_histo[npart]= {0}; 

	for (int i=0; i<npart; i++){
		mom_CC_reject_histo[i] = new TH1F(Form("pnu_%d_rj_CC", i), "" ,NBins, lo_x, hi_x);
		mom_NCpi0_reject_histo[i] = new TH1F(Form("pnu_%d_rj_pi0", i), "" ,NBins, lo_x, hi_x);
		mom_NCbg_reject_histo[i] = new TH1F(Form("pnu_%d_rj_NCbg", i), "" ,NBins, lo_x, hi_x);
		mom_CC_acc_histo[i] = new TH1F(Form("pnu_%d_ac_CC", i), "" ,NBins, lo_x, hi_x);
		mom_NCpi0_acc_histo[i] = new TH1F(Form("pnu_%d_ac_pi0", i), "" ,NBins, lo_x, hi_x);
		mom_NCbg_acc_histo[i] = new TH1F(Form("pnu_%d_ac_NCbg", i), "" ,NBins, lo_x, hi_x);
		
		mom_nu_rj_histo[i] = new TH1F(Form("nu_%d_rj", i), "" ,NBins, lo_x, hi_x);
		mom_e_rj_histo[i] = new TH1F(Form("e_%d_rj", i), "" ,NBins, lo_x, hi_x);
		mom_mu_rj_histo[i] = new TH1F(Form("mu_%d_rj", i), "" ,NBins, lo_x, hi_x);
		mom_p_rj_histo[i] = new TH1F(Form("p_%d_rj", i), "" ,NBins, lo_x, hi_x);
		mom_n_rj_histo[i] = new TH1F(Form("n_%d_rj", i), "" ,NBins, lo_x, hi_x);
		mom_pi0_rj_histo[i] = new TH1F(Form("pi0_%d_rj", i), "" ,NBins, lo_x, hi_x);
		mom_pipm_rj_histo[i] = new TH1F(Form("pipm_%d_rj", i), "" ,NBins, lo_x, hi_x);
		mom_other_rj_histo[i] = new TH1F(Form("other_%d_rj", i), "" ,NBins, lo_x, hi_x);


		mom_nu_acc_histo[i] = new TH1F(Form("nu_%d_ac", i), "" ,NBins, lo_x, hi_x);
		mom_e_acc_histo[i] = new TH1F(Form("e_%d_ac", i), "" ,NBins, lo_x, hi_x);
		mom_mu_acc_histo[i] = new TH1F(Form("mu_%d_ac", i), "" ,NBins, lo_x, hi_x);
		mom_p_acc_histo[i] = new TH1F(Form("p_%d_ac", i), "" ,NBins, lo_x, hi_x);
		mom_n_acc_histo[i] = new TH1F(Form("n_%d_ac", i), "" ,NBins, lo_x, hi_x);
		mom_pi0_acc_histo[i] = new TH1F(Form("pi0_%d_ac", i), "" ,NBins, lo_x, hi_x);
		mom_pipm_acc_histo[i] = new TH1F(Form("pipm_%d_ac", i), "" ,NBins, lo_x, hi_x);
		mom_other_acc_histo[i] = new TH1F(Form("other_%d_ac", i), "" ,NBins, lo_x, hi_x);
}

	TH1F* mom_CC_tot_histo = new TH1F("pnu_%d_tot_CC", "" ,NBins, lo_x, hi_x);
	TH1F* mom_NCpi0_tot_histo = new TH1F("pnu_%d_tot_NCpi0", "" ,NBins, lo_x, hi_x);
	TH1F* mom_NCbg_tot_histo = new TH1F("pnu_%d_tot_NCbg", "" ,NBins, lo_x, hi_x);

	NBins = 100;
	lo_x = 0;
	hi_x = 600;

	TH1F* mass_CC_rj_histo = new TH1F("mass_rj_CC", "" ,NBins, lo_x, hi_x);
	TH1F* mass_NCpi0_rj_histo = new TH1F("mass_rj_NCpi0", "" ,NBins, lo_x, hi_x);
	TH1F* mass_NCbg_rj_histo = new TH1F("mass_rj_NCbg", "" ,NBins, lo_x, hi_x);
	TH1F* mass_CC_acc_histo = new TH1F("mass_acc_CC", "" ,NBins, lo_x, hi_x);
	TH1F* mass_NCpi0_acc_histo = new TH1F("mass_acc_NCpi0", "" ,NBins, lo_x, hi_x);
	TH1F* mass_NCbg_acc_histo = new TH1F("mass_acc_NCbg", "" ,NBins, lo_x, hi_x);

//by visible topology
  
	TH1F* mass_1e_rj_histo = new TH1F("rj_1e", "" ,NBins, lo_x, hi_x);
	TH1F* mass_1mu_rj_histo = new TH1F("rj_1mu", "" ,NBins, lo_x, hi_x);
	TH1F* mass_1eo_rj_histo = new TH1F("rj_1eo", "" ,NBins, lo_x, hi_x);
	TH1F* mass_1muo_rj_histo = new TH1F("rj_1muo", "" ,NBins, lo_x, hi_x);
	TH1F* mass_1pi0_rj_histo = new TH1F("rj_1pi0", "" ,NBins, lo_x, hi_x);
	TH1F* mass_1pipmP_rj_histo = new TH1F("rj_1pipmP", "" ,NBins, lo_x, hi_x);
	TH1F* mass_Other_rj_histo = new TH1F("rj_Other", "" ,NBins, lo_x, hi_x);
	
	TH1F* mass_1e_ac_histo = new TH1F("ac_1e", "" ,NBins, lo_x, hi_x);
	TH1F* mass_1mu_ac_histo = new TH1F("ac_1mu", "" ,NBins, lo_x, hi_x);
	TH1F* mass_1eo_ac_histo = new TH1F("ac_1eo", "" ,NBins, lo_x, hi_x);
	TH1F* mass_1muo_ac_histo = new TH1F("ac_1muo", "" ,NBins, lo_x, hi_x);
	TH1F* mass_1pi0_ac_histo = new TH1F("ac_1pi0", "" ,NBins, lo_x, hi_x);
	TH1F* mass_1pipmP_ac_histo = new TH1F("ac_1pipmP", "" ,NBins, lo_x, hi_x);
	TH1F* mass_Other_ac_histo = new TH1F("ac_Other", "" ,NBins, lo_x, hi_x);


  const static int NSigVars = 2;
  const static int NBkgVars = 14;
  const static int NVars = 16;
	const static int NVisTop = 7;

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
		bool considerSecondaries = false;
		int EvTop = returnSKEventTopology(true,considerSecondaries,Npvc,Ipvc,Ichvc,Iflvc,Abspvc,nscndprt,lmecscnd,tscnd,iprtscnd,iprntprt,pscnd);
		//std::cout << EvTop << std::endl;
		for (int i=2; i<numnu; i++) {
			int pidnum = std::abs(ipnu[i]);
		//	if (pidnum!=11&&pidnum!=12&&pidnum!=111&&pidnum!=211&&pidnum!=2212&&pidnum!=2112){
		//		std::cout << i << " " << numnu << " " << ipnu[i] << std::endl;
		//		}
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
		

		if (-1.0*fqpi0nll[0]+fq1rnll[0][1] < 100) {
			if (mode<30&&mode>-30) {
			mass_CC_rj_histo->Fill(fqpi0mass[0], totweight); 
			}else {
				if (mode==31||mode==32||mode==-31||mode==-32||mode==36||mode==-36){	
					mass_NCpi0_rj_histo->Fill(fqpi0mass[0], totweight); 
				} else {
					mass_NCbg_rj_histo->Fill(fqpi0mass[0], totweight); 
				}
			}

		} else {
		
			if (mode<30&&mode>-30) {
			mass_CC_acc_histo->Fill(fqpi0mass[0], totweight); 
			}else {
				if (mode==31||mode==32||mode==-31||mode==-32||mode==36||mode==-36){	
					mass_NCpi0_acc_histo->Fill(fqpi0mass[0], totweight); 
				} else {
					mass_NCbg_acc_histo->Fill(fqpi0mass[0], totweight); 
				}
			}
		}

		int part = 0;
		int pos_in_map = 0;
		for (auto const& entry: pnu_map){	
			//ordered index of particles from numnu,
			int pid = std::abs(ipnu[part]);
			part = entry.second;
			if (part > npart-1){
				continue;
			}

			if (-1.0*fqpi0nll[0]+fq1rnll[0][1] < 100) {
				if (mode<30&&mode>-30) {
					//CC
					//std::cout << nsub << " " << nev << std::endl;
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

				//by pid
				if (pid==12||pid==14) mom_nu_rj_histo[pos_in_map]    ->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==11) mom_e_rj_histo[pos_in_map]     ->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==13) mom_mu_rj_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==2212) mom_p_rj_histo[pos_in_map]  ->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==2112) mom_n_rj_histo[pos_in_map]  ->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==111) mom_pi0_rj_histo[pos_in_map] ->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==211) mom_pipm_rj_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid!=12&&pid!=11&&pid!=13&&pid!=14&&pid!=2212&&pid!=2112&&pid!=111&&pid!=211) mom_other_rj_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);		

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

				//by pid
				if (pid==12||pid==14) mom_nu_acc_histo[pos_in_map]    ->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==11) mom_e_acc_histo[pos_in_map]     ->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==13) mom_mu_acc_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==2212) mom_p_acc_histo[pos_in_map]  ->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==2112) mom_n_acc_histo[pos_in_map]  ->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==111) mom_pi0_acc_histo[pos_in_map] ->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid==211) mom_pipm_acc_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);
				if (pid!=12&&pid!=11&&pid!=13&&pid!=14&&pid!=2212&&pid!=2112&&pid!=111&&pid!=211) mom_other_acc_histo[pos_in_map]->Fill(pnu[part]-ChThresh(ipnu[part])/1000., totweight);		

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
	
	THStack *mass_rj_stack = new THStack("mass_rj_stack", "mom_rj"); 
  mass_rj_stack->Add(mass_CC_rj_histo);
	mass_rj_stack->Add(mass_NCbg_rj_histo);
	mass_rj_stack->Add(mass_NCpi0_rj_histo);	
	
	THStack *mass_acc_stack = new THStack("mass_acc_stack", "mom_rj"); 
  mass_acc_stack->Add(mass_CC_acc_histo);
	mass_acc_stack->Add(mass_NCbg_acc_histo);
	mass_acc_stack->Add(mass_NCpi0_acc_histo);	

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

	auto c_mass_rj = new TCanvas();
	mass_rj_stack->Draw("hist pfc");
  mass_rj_stack->GetXaxis()->SetTitle("mass (MeV)");
  mass_rj_stack->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  mass_rj_stack->SetTitle(Form("%s total e/pi0 events ", horn_current.c_str()));
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c_mass_rj->Update();
	c_mass_rj->SaveAs(Form("%smass_rj.png", odir.c_str()));


	auto c_mass_acc = new TCanvas();
	mass_acc_stack->Draw("hist pfc");
  mass_acc_stack->GetXaxis()->SetTitle("mass (MeV)");
  mass_acc_stack->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  mass_acc_stack->SetTitle(Form("%s total e/pi0 events ", horn_current.c_str()));
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c_mass_acc->Update();
	c_mass_acc->SaveAs(Form("%smass_acc.png", odir.c_str()));

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

	
//by pid
	THStack *mom_pid_rj_stack = new THStack("mom_pid_rj_stack", "mom_rj"); 
	THStack *mom_pid_ac_stack = new THStack("mom_pid_ac_stack", "mom_ac"); 
	

		mom_pid_rj_stack->Add(mom_nu_rj_histo[i]);
		mom_pid_rj_stack->Add(mom_e_rj_histo[i]); 
		mom_pid_rj_stack->Add(mom_mu_rj_histo[i]);
		mom_pid_rj_stack->Add(mom_p_rj_histo[i]); 
		mom_pid_rj_stack->Add(mom_n_rj_histo[i]); 
		mom_pid_rj_stack->Add(mom_pi0_rj_histo[i]);
		mom_pid_rj_stack->Add(mom_pipm_rj_histo[i]);
		mom_pid_rj_stack->Add(mom_other_rj_histo[i]); 

		mom_pid_ac_stack->Add(mom_nu_acc_histo[i]);
		mom_pid_ac_stack->Add(mom_e_acc_histo[i]); 
		mom_pid_ac_stack->Add(mom_mu_acc_histo[i]);
		mom_pid_ac_stack->Add(mom_p_acc_histo[i]); 
		mom_pid_ac_stack->Add(mom_n_acc_histo[i]); 
		mom_pid_ac_stack->Add(mom_pi0_acc_histo[i]);
		mom_pid_ac_stack->Add(mom_pipm_acc_histo[i]);
		mom_pid_ac_stack->Add(mom_other_acc_histo[i]); 
	
	auto c_mom_pid_rj = new TCanvas();
	mom_pid_rj_stack->Draw("hist pfc");
  mom_pid_rj_stack->GetXaxis()->SetTitle("pnu-ChThresh (GeV)");
  mom_pid_rj_stack->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  mom_pid_rj_stack->SetTitle(Form("%s rejected e/pi0 events %d", horn_current.c_str(), i));
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c_mom_pid_rj->Update();
	c_mom_pid_rj->SaveAs(Form("%smom_pid_%d_rj.png", odir.c_str(), i));

	auto c_mom_pid_ac = new TCanvas();
	mom_pid_ac_stack->Draw("hist pfc");
  mom_pid_ac_stack->GetXaxis()->SetTitle("pnu-ChThresh (GeV)");
  mom_pid_ac_stack->GetYaxis()->SetTitleOffset(1.75);
  gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
  //nllr_pi0mom_2Ree_sig_hist[DrawCut]->GetZaxis()->SetRangeUser(0, nll_z_hi);
  mom_pid_ac_stack->SetTitle(Form("%s accepted e/pi0 events %d", horn_current.c_str(), i));
  //arw1->DrawLine( 0, 180,175 , 0);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.12);
	c_mom_pid_ac->Update();
	c_mom_pid_ac->SaveAs(Form("%smom_pid_%d_acc.png", odir.c_str(), i));


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
