#define SKMCdataTree_cxx
#include "SKMCdataTree.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
//#include "Prob3/BargerPropagator.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <THStack.h>
#include "SetT2KStyle.H"
void SKMCdataTree::LoopSelection(std::string horn_current, std::string osc_sample)
{

	FileFlavor InFileFlav;

	if(osc_sample == "numu_x_numu") InFileFlav =NUMU;
	if(osc_sample == "numubar_x_numubar")  InFileFlav =NUMUBAR;
	if(osc_sample == "nue_x_nue")  InFileFlav =NUE;
	if(osc_sample == "nuebar_x_nuebar")  InFileFlav =NUEBAR;
	if(osc_sample == "numu_x_nue")  InFileFlav =NUMUTONUE;
	if(osc_sample == "numubar_x_nuebar")  InFileFlav =NUMUBARTONUEBAR;
	
	
	TFile * file = TFile::Open(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/output/NCpi0_2RingPID_t2ksk19b.fqv4r0.%s.%s.root", horn_current.c_str(), osc_sample.c_str()), "recreate");
   	TTree * tree = fChain->CloneTree(0);


	
	IDCenterY = 0.0;
	IDRadius = 1690.0;
	IDHalfLength = 1810.0;

//   In a ROOT session, you can do:
//      root> .L SKMCdataTree.C
//      root> SKMCdataTree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
 

	ev_towall = 0.;
	ev_dwall = 0.;

	if (fChain == 0) return;
	mainEventIndex = 0;
	int secondEventIndex = 0;
	float maxCharge = 0.;
	float secondCharge = 0.;
	int maxSubEvent = 0.;
	Long64_t nSelected = 0;
	int nTwoRingSelected = 0;
	int nSelecSignal = 0;
	int nTotalSignal = 0;
	int nSelecBackground = 0;

	Long64_t nentries = fChain->GetEntries();

	Long64_t nbytes = 0, nb = 0;
	
	double nFC =0;
	double nFV =0;
	double nnring =0;
	double nPID1 =0;
	double nePi0 =0;
	double nfqnse =0;
	double nErec =0;
	double n1rmom = 0;
	double nPID2 =0;

	double flux_weight, osc_weight, event_weight;
	
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
    	Long64_t ientry = LoadTree(jentry);
    	if (ientry < 0) break;
   		nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    	  
    	mainEventIndex = 0;
    	maxCharge=0.;
 		if (fqnse > maxSubEvent){
			maxSubEvent = fqnse;
		}
		
		double secondCharge =0.;
		int secondEventIndex=0;
		
		maxCharge = fqtotq[0];
		secondCharge = fqtotq[0];
    	for(int i=1; i<fqnse; i++){
        	if(fqtotq[i]>maxCharge){
				secondCharge = maxCharge;
				secondEventIndex = mainEventIndex;
            	maxCharge = fqtotq[i];
				mainEventIndex = i;
    		} 
			else if (fqtotq[i]>secondCharge && maxCharge !=fqtotq[i])
			{
				secondCharge = fqtotq[i];
				secondEventIndex = i;
			}
		}




//		printf("1: %d, 2: %d \n", mainEventIndex, secondEventIndex);
    	float x = fq1rpos[mainEventIndex][1][0];
    	float y = fq1rpos[mainEventIndex][1][1];
    	float z = fq1rpos[mainEventIndex][1][2];
		float dx = fq1rdir[mainEventIndex][1][0];
		float dy = fq1rdir[mainEventIndex][1][1];
		float dz = fq1rdir[mainEventIndex][1][2];

		ev_towall = ComputeToWall(x, y, z, dx, dy, dz);

    	ev_dwall =  ComputeDWall(x, y, z);
		
		float EcosBeam = ComputeCosBeam(mainEventIndex, ELECTRON);
		float Erec = ComputeErec(fq1rmom[mainEventIndex][ELECTRON], ELECTRON, EcosBeam);
//cuts//

	
	//Official selection	
	//FC
	if (nhitac < 16 and  evclass==1 and fq1rmom[mainEventIndex][1]>30.){
		nFC += 1;
		//FV
		if (ev_dwall > 80. and ev_towall>170.){
			nFV += 1;
			if (fq1rmom[mainEventIndex][1] > 100.){ 
				n1rmom += 1;
				//fqnse
				if(fqnse == 1){
					nfqnse += 1;
					//nring 
					if (fqmrnring[0] == 2){
						nnring += 1;
						//PID 1st ring
					//	if (fq1rnll[mainEventIndex][2]-fq1rnll[mainEventIndex][1]>0.2*fq1rmom[mainEventIndex][1]) {
						//if (fq1rnll[0][2]-fq1rnll[0][1]>0.2*fq1rmom[0][1]) {
						if (fqmrpid[0][0] == 1) {
							nPID1 +=1;
							if (fqmrpid[0][1] == 1) {
						//	if (fq1rnll[1][2]-fq1rnll[1][1]>0.2*fq1rmom[1][1]) {
								nPID2 += 1;
								//Erec
							//	if (Erec <1250.) {
							//		nErec += 1;

									//!!Pi0
									if (this->IsfQPi0()){
										nePi0+= 1;

										nTwoRingSelected += 1;
										tree->Fill();
										
										if  (abs(Neutmode)==31 || abs(Neutmode)==32 || abs(Neutmode) == 36){
											nSelecSignal += 1;
										}
										else nSelecBackground ++;
									
									}
							//	}
							}
						}
					}
				}
			}
		}
	}
		
	if  (abs(Neutmode)==31 || abs(Neutmode)==32 ){
		nTotalSignal += 1;
	}
  
    }
  
  std::cout << "Entries:" <<tree->GetEntries() << std::endl;

	std::cout 	<<"FC :		"<< nFC							<< std::endl 
				<<"	+FV:		"<< nFV							<< std::endl
				<<"	+2ring: 	"<< nnring							<< std::endl
				<<"	+elike1:	"<<	nPID1				<< std::endl
				<<"	+elike2:	"<<	nPID2				<< std::endl
				<<"	+Evis : 	"<< n1rmom				<< std::endl
				<<"	+0dcye: 	"<< nfqnse		<< std::endl
				<<"	+Erec : 	"<< nErec		<< std::endl
				<<"	+!!pi0 :	"<< nePi0	<< std::endl;

   printf("Two ring sample selected: %d \n", nTwoRingSelected); 
   printf("Two ring sample selected signal: %d \n", nSelecSignal); 
   printf("Two ring sample selected Background: %d \n", nSelecBackground); 
   printf("Total signal: %d \n", nTotalSignal); 
   printf("Files: %s , %s \n Total Entries: %lld \n Max sub events: %d (Should be less than 10)\n", horn_current.c_str(), osc_sample.c_str(), nentries, maxSubEvent);
  
  tree->Write(); 
  file->Write();
  file->Close();
}




void SKMCdataTree::LoopNCHistos(std::string horn_current, std::string osc_sample, int sel)
{

	FileFlavor InFileFlav;

	if(osc_sample == "numu_x_numu") InFileFlav =NUMU;
	if(osc_sample == "numubar_x_numubar")  InFileFlav =NUMUBAR;
	if(osc_sample == "nue_x_nue")  InFileFlav =NUE;
	if(osc_sample == "nuebar_x_nuebar")  InFileFlav =NUEBAR;
	if(osc_sample == "numu_x_nue")  InFileFlav =NUMUTONUE;
	if(osc_sample == "numubar_x_nuebar")  InFileFlav =NUMUBARTONUEBAR;
	
	
//   	TTree * tree = fChain->CloneTree(0);


	
	IDCenterY = 0.0;
	IDRadius = 1690.0;
	IDHalfLength = 1810.0;

//   In a ROOT session, you can do:
//      root> .L SKMCdataTree.C
//      root> SKMCdataTree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
 

	ev_towall = 0.;
	ev_dwall = 0.;

	if (fChain == 0) return;
	mainEventIndex = 0;
	int secondEventIndex = 0;
	float maxCharge = 0.;
	float secondCharge = 0.;
	int maxSubEvent = 0.;
/*	int max_nring = 0;
	int max_nmue = 0;
	int max_Rnring = 0;
	int max_ri_nring = 0;
	int max_npar = 0;
	int max_npar2 = 0;
	int max_numnu = 0;
	int max_nscndprt = 0;
	int max_Npvcscnd = 0;
	int max_Npne = 0;
	int max_Npvc = 0;
	int max_Nvert = 0;
	int max_Nvcvert = 0;
	int max_fqntwnd = 0;
	int max_fqnmrfit = 0;
	int max_fqmsnfit = 0;
*/
	Long64_t nSelected = 0;
	Long64_t nTwoRingSelected = 0;
	int nSelecSignal = 0;
	int nTotalSignal = 0;
	int nSelecBackground = 0;

	Long64_t nentries = fChain->GetEntries();

	Long64_t nbytes = 0, nb = 0;
	
	double nFC =0;
	double nFV =0;
	double nnring =0;
	double nPID1 =0;
	double nePi0 =0;
	double nfqnse =0;
	double nErec =0;
	double n1rmom = 0;
	double nPID2 =0;

	SetT2KStyle(1);	
	InitNCHistos();

	//Osc weight
	ProbSK();

	//Flux Weight
	double flux_weight = 1.;

	if (horn_current == "fhc"){
		if(osc_sample == "numu_x_numu") flux_weight =fhcfileWeights[0];
		if(osc_sample == "nue_x_nue")  flux_weight = fhcfileWeights[1];
		if(osc_sample == "numubar_x_numubar")  flux_weight = fhcfileWeights[2];
		if(osc_sample == "nuebar_x_nuebar")  flux_weight = fhcfileWeights[3];
		if(osc_sample == "numu_x_nue")  flux_weight = fhcfileWeights[4];
		if(osc_sample == "numubar_x_nuebar")  flux_weight = fhcfileWeights[5];
	}
	else {

		if(osc_sample == "numu_x_numu") flux_weight =rhcfileWeights[0];
		if(osc_sample == "nue_x_nue")  flux_weight = rhcfileWeights[1];
		if(osc_sample == "numubar_x_numubar")  flux_weight = rhcfileWeights[2];
		if(osc_sample == "nuebar_x_nuebar")  flux_weight = rhcfileWeights[3];
		if(osc_sample == "numu_x_nue")  flux_weight = rhcfileWeights[4];
		if(osc_sample == "numubar_x_nuebar")  flux_weight = rhcfileWeights[5];
	}
	
	//POT weight 
	double pot_fhc = 1.9664;
	double pot_rhc = 1.634556;
	double pot_weight = 1.;

	if (horn_current == "fhc" ) {
		pot_weight = pot_fhc;
	}
	else {
		pot_weight = pot_rhc;
	}
	
	
//	printf("Flux weight *pot : %f\n", flux_weight*pot_weight);
//
	
	printf("FHC weights: pot weight = %f \n", pot_fhc);
	std::cout 	<<"Channel			channel weight		channel weight*POT weight"	<< std::endl 
				<<"numu_x_numu 		"	 << fhcfileWeights[0] << "		" << fhcfileWeights[0]*pot_fhc	<< std::endl
				<<"nue_x_nue 		"	 << fhcfileWeights[1] << "		" << fhcfileWeights[1]*pot_fhc	<< std::endl
				<<"numubar_x_numubar	"<< fhcfileWeights[2] << "		" << fhcfileWeights[2]*pot_fhc	<< std::endl
				<<"nuebar_x_nuebar		"<<	fhcfileWeights[3] << "		" << fhcfileWeights[3]*pot_fhc	<< std::endl
				<<"numu_x_nue 		"	 << fhcfileWeights[4] << "		" << fhcfileWeights[4]*pot_fhc	<< std::endl
				<<"numubar_x_nuebar 	"<< fhcfileWeights[5] << "		" << fhcfileWeights[5]*pot_fhc	<< std::endl;

	printf("RHC weights: pot weight = %f \n", pot_rhc);
	std::cout 	<<"Channel			channel weight		channel weight*POT weight"	<< std::endl 
				<<"numu_x_numu 		"	 << rhcfileWeights[0] << "		" << rhcfileWeights[0]*pot_rhc	<< std::endl
				<<"nue_x_nue 		"	 << rhcfileWeights[1] << "		" << rhcfileWeights[1]*pot_rhc	<< std::endl
				<<"numubar_x_numubar	"<< rhcfileWeights[2] << "		" << rhcfileWeights[2]*pot_rhc	<< std::endl
				<<"nuebar_x_nuebar		"<<	rhcfileWeights[3] << "		" << rhcfileWeights[3]*pot_rhc	<< std::endl
				<<"numu_x_nue 		"	 << rhcfileWeights[4] << "		" << rhcfileWeights[4]*pot_rhc	<< std::endl
				<<"numubar_x_nuebar 	"<< rhcfileWeights[5] << "		" << rhcfileWeights[5]*pot_rhc	<< std::endl;

	
	//Event by event weight	
	
	TFile *	ev_weight_file;
	if (horn_current == "fhc"){
		ev_weight_file = new  TFile("/vols/t2k/users/dmartin/NCpi0/code/selection/weights/sk_tuned13av7p1_13anom_run1-10b_numode_138.root");
	} 
	else {
		ev_weight_file = new  TFile("/vols/t2k/users/dmartin/NCpi0/code/selection/weights/sk_tuned13av7p1_13anom_run5c-9d_antinumode_138.root");
	}

	TH1F* ev_weigh_hist_numu = (TH1F*)ev_weight_file->Get("enu_sk_tuned13a_numu_ratio");
	TH1F* ev_weigh_hist_numub = (TH1F*)ev_weight_file->Get("enu_sk_tuned13a_numub_ratio");
	TH1F* ev_weigh_hist_nue = (TH1F*)ev_weight_file->Get("enu_sk_tuned13a_nue_ratio");
	TH1F* ev_weigh_hist_nueb = (TH1F*)ev_weight_file->Get("enu_sk_tuned13a_nueb_ratio");

	
	CCqe_tot = 0;
	CC1pi_tot = 0;
	CCOther_tot = 0;
	NC1pi0_tot = 0;
	NC1pipm_tot = 0;
	NCOther_tot = 0;
	CC2p2h_tot = 0;
	CCmisc_tot = 0;
	CCCoh_tot = 0;
	CCmpi_tot = 0;
	CCdis_tot = 0;
	NCCoh_tot = 0;
	NC1gamma_tot = 0;
  
	int numNCskipped = 0;

	double osc_weight = 1.;
  double totweight = 0;
  TFile * weightfile;
  
  switch(sel){
		case 0: //ncpi0
      std::cout << "Running main NCpi0 selection" << std::endl;
      weightfile = TFile::Open(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/output/NCpi0_tuned_13av7p1_t2ksk19b.fqv4r0.%s.%s_cut6.root", horn_current.c_str(), osc_sample.c_str()), "recreate");
      break;
		case 1: //1re
      std::cout << "Running 1 ring elike NCpi0 selection" << std::endl;
      weightfile = TFile::Open(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/output/NCpi0_1RePi0_13av7p1_t2ksk19b.fqv4r0.%s.%s.root", horn_current.c_str(), osc_sample.c_str()), "recreate");
      break;
		case 2: //1dcye
      std::cout << "Running 1 dcye elike NCpi0 selection" << std::endl;
      weightfile = TFile::Open(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/output/NCpi0_1dcyePi0_13av7p1_t2ksk19b.fqv4r0.%s.%s.root", horn_current.c_str(), osc_sample.c_str()), "recreate");
      break;
 		case 3: //noemupid
      std::cout << "Running noemupid NCpi0 selection" << std::endl;
      weightfile = TFile::Open(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/output/NCpi0_1dcyePi0_13av7p1_t2ksk19b.fqv4r0.%s.%s.root", horn_current.c_str(), osc_sample.c_str()), "recreate");
      break; }


  TTree * weighttree = fChain->CloneTree(0);
  weighttree->Branch("totweight",&totweight,"totweight/D");
//  fChain->SetBranchAddress("totweight",&totweight, &bweight);
	
	
  /////////////////////////////// LOOP ///////////////////////////
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
    	if (ientry < 0) break;
   		nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    	
    	//Skip NC event in numu_x_nue and numubar_x_nuebar

		if (abs(Neutmode)>30) {
			if (osc_sample == "all") {
				if(fileFlavorInt[jentry] == 4 || fileFlavorInt[jentry] == 5) {
					numNCskipped += 1;
					//printf(" 1 %d\n", numNCskipped);
					continue;
				}
			}
			else {
				if(osc_sample == "numu_x_nue" || osc_sample == "numubar_x_nuebar"){
			//		printf(" 2 %d\n", numNCskipped);
					numNCskipped += 1;
					continue;
				}	
			}
		}	
    	
		
		mainEventIndex = 0;
    	maxCharge=0.;
 /*		if (fqnse > maxSubEvent) maxSubEvent = fqnse;
 		if (nring > max_nring) max_nring = nring;
 		if (nmue > max_nmue) max_nmue = nmue;
 		if (Rnring > max_Rnring) max_Rnring = Rnring;
 		if (ri_nring > max_ri_nring) max_ri_nring = ri_nring;
 		if (npar > max_npar) max_npar = npar;
 		if (npar2 > max_npar2) max_npar2 = npar2;
 		if (numnu > max_numnu) max_numnu = numnu;
 		if (nscndprt > max_nscndprt) max_nscndprt = nscndprt;
 		if (Npvcscnd > max_Npvcscnd) max_Npvcscnd = Npvcscnd;
 		if (Npne > max_Npne) max_Npne = Npne;
 		if (Npvc > max_Npvc) max_Npvc = Npvc;
 		if (Nvert > max_Nvert) max_Nvert = Nvert;
 		if (Nvcvert > max_Nvcvert) max_Nvcvert = Nvcvert;
 		if (fqntwnd > max_fqntwnd) max_fqntwnd = fqntwnd;
 		if (fqnmrfit > max_fqnmrfit) max_fqnmrfit = fqnmrfit;
 		if (fqmsnfit > max_fqmsnfit) max_fqmsnfit = fqmsnfit;
*/
		
		double secondCharge =0.;
		int secondEventIndex=0;
		
		maxCharge = fqtotq[0];
		secondCharge = fqtotq[0];
    	for(int i=1; i<fqnse; i++){
        	if(fqtotq[i]>maxCharge){
				secondCharge = maxCharge;
				secondEventIndex = mainEventIndex;
            	maxCharge = fqtotq[i];
				mainEventIndex = i;
    		} 
			else if (fqtotq[i]>secondCharge && maxCharge !=fqtotq[i])
			{
				secondCharge = fqtotq[i];
				secondEventIndex = i;
			}
		}

/////////////////////////////////////////     WEIGHTS ///////////////////////////
		//For all files, load flux weight from file 
		if (osc_sample == "all") {
			if (horn_current == "fhc"){
				flux_weight = fhcfileWeights[fileFlavorInt[jentry]]; 
			}
			else {
				flux_weight = rhcfileWeights[fileFlavorInt[jentry]]; 
			}
    	}
		
        
		//osc weight Changes depends on ipnu selection
		if (ipnu[0] < 0	){
			SetAntiNeutrino(1);
		}
		else {
			SetAntiNeutrino(0);
		}
	
		int initNuSpecies = 0;
		int finalNuSpecies = 0;
		if (ipnu[0] == 12 || ipnu[0]==-12) finalNuSpecies = 1; 
		if (ipnu[0] == 14 || ipnu[0]==-14) finalNuSpecies = 2; 
		if (ipnu[0] == 16|| ipnu[0]==-16) finalNuSpecies = 3; 
	
		
		
		if (osc_sample == "all") {
			if(fileFlavorInt[jentry] == 0) initNuSpecies = 2;
			if(fileFlavorInt[jentry] == 1) initNuSpecies = 2 ;
			if(fileFlavorInt[jentry] == 2)  initNuSpecies = 1;
			if(fileFlavorInt[jentry] == 3) initNuSpecies = 1 ;
			if(fileFlavorInt[jentry] == 4)  initNuSpecies = 2;
			if(fileFlavorInt[jentry] == 5)  initNuSpecies = 2;
		}
		else {
			if(osc_sample == "numu_x_numu") initNuSpecies = 2;
			if(osc_sample == "numubar_x_numubar")  initNuSpecies = 2;
			if(osc_sample == "nue_x_nue")  initNuSpecies = 1;
			if(osc_sample == "nuebar_x_nuebar")  initNuSpecies = 1;
			if(osc_sample == "numu_x_nue")  initNuSpecies = 2;
			if(osc_sample == "numubar_x_nuebar") initNuSpecies = 2;
		}

		if (initNuSpecies==0 or finalNuSpecies==0){
			printf("Neutrino Flavour Error\n init: %d\n final: %d\n ipnu: %d\n sample: %d\n", initNuSpecies, finalNuSpecies, abs(ipnu[0]), fileFlavorInt[jentry]);
			break;
		}

		if (abs(Neutmode) > 30 ){
			osc_weight = 1.;
		}
		else {
			osc_weight = GetOscProb(initNuSpecies, finalNuSpecies, pnu[0]) ;
		}

		
		//printf("init: %d final: %d ipnu: %d \n energy: %f osc_weight: %f osc_weight 2: %f\n", initNuSpecies, finalNuSpecies, ipnu[0], pnu[0], osc_weight, other_osc_weight);



		//Event by event weight
		double ev_weight = 1.;
		if (ipnu[0] == 14) ev_weight=ev_weigh_hist_numu->GetBinContent(ev_weigh_hist_numu->FindBin(pnu[0]));
		if (ipnu[0] == -14) ev_weight=ev_weigh_hist_numub->GetBinContent(ev_weigh_hist_numub->FindBin(pnu[0]));
		if (ipnu[0] == 12) ev_weight=ev_weigh_hist_nue->GetBinContent(ev_weigh_hist_nue->FindBin(pnu[0]));
		if (ipnu[0] == -12) ev_weight=ev_weigh_hist_nueb->GetBinContent(ev_weigh_hist_nueb->FindBin(pnu[0]));
		
		
		//printf("neut flav: %d, energy: %f, bin num: %d, weight: %f \n", ipnu[0], pnu[0], ev_weigh_hist_nueb->FindBin(pnu[0]), ev_weight);

		//total weight
		weight = osc_weight*flux_weight*pot_weight*ev_weight;

     
		//printf("%f,  %f, %d \n", flux_weight, pot_weight,fileFlavorInt[jentry]);

//		printf("1: %d, 2: %d \n", mainEventIndex, secondEventIndex);

    	ev_dwall =  GetRecoDWall_pi0();
      ev_towall = GetRecoToWall_pi0();
		
		float EcosBeam = ComputeCosBeam(mainEventIndex, ELECTRON);
		float Erec = ComputeErec(fq1rmom[mainEventIndex][ELECTRON], ELECTRON, EcosBeam);


/////////////////////////////////////// CUTS     /////////////////////////////////////////////////////////////////
    	
		//Official selection	
		//FC
    if (sel == NCPi0){
      AddEventToHisto(0, weight);
      if (nhitac < 16 and  evclass==1 and fq1rmom[mainEventIndex][1]>30.){
        nFC += weight;
        AddEventToHisto(1, weight);
        //FV
        if (ev_dwall > 80. and ev_towall>170.){
          nFV += weight;
          AddEventToHisto(2, weight);
          //nring 
          if (fq1rmom[mainEventIndex][1] > 100.){ 
            n1rmom += weight;
            AddEventToHisto(3, weight);
            //fqnse
            if(fqnse == 1){
              nfqnse += weight;
              AddEventToHisto(4, weight);
              if (fqmrnring[0] == 2){
                nnring += weight;
                AddEventToHisto(5, weight);
                //PID 1st ring
                //if (fqmrpid[0][0] == 1) {
                //if (this->electron_muon_PID() > 0){
                //if (this->nllr_2Rother_ee() < 590 - 3.22 * fqpi0mass[0]) { //Tuned against pi0mass
                //if ( fqpi0mass[0] < 300) { //Just pi0mass cut
                //if (this->nllr_2Rother_ee() < 160 - 0.15 * this->ifitPi0mom()) { //tuned against pi0mom
                if (this->nllr_2Rother_ee() < 100){ //1D PID  
                  nPID1 += weight;
                  AddEventToHisto(6, weight);
                //	if (fqmrpid[0][1] == 1) {
                    //if (fq1rnll[1][2]-fq1rnll[1][1]>0.2*fq1rmom[1][1]) {
                  //	nPID2 += weight;
                    //AddEventToHisto(7, weight);
                    //Erec
        //						if (Erec <1250.) {
                    //	nErec += weight;
              //				AddEventToHisto(8, weight);

                      //!!Pi0
                      //if (this->IsfQPi0tuned()){ //pi0mass 2D cut
                       weighttree->Fill();
                      if(-1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][ELECTRON] > 100) { //1D PID
                        nePi0+= weight;
                        AddEventToHisto(9, weight);
                        nTwoRingSelected += weight;
                        totweight = weight;
                        if (totweight > 100.){
                          std::cout << weight << std::endl;
                        }
    //										NCpi0_2R_pi0e_pi0mass_hist->Fill(fqpi0mass[0], fq1rnll[mainEventIndex][ELECTRON]-fqpi0nll[mainEventIndex]);
                         // bweight->Fill();
                        
                                      
                        if  (abs(Neutmode)==31 || abs(Neutmode)==32 || abs(Neutmode) == 36){
                          nSelecSignal += weight;
                        }
                        else nSelecBackground += weight ;
                      
                      }
                    }
              //		}
              //	}
              }
            }
          }
        }
      }
    }
  


		//1 ring pi0 like selection	
		//FC
    if (sel == _1RePi0){

    	float x = fq1rpos[mainEventIndex][1][0];
    	float y = fq1rpos[mainEventIndex][1][1];
    	float z = fq1rpos[mainEventIndex][1][2];
		  float dx = fq1rdir[mainEventIndex][1][0];
		  float dy = fq1rdir[mainEventIndex][1][1];
		  float dz = fq1rdir[mainEventIndex][1][2];

		  ev_towall = ComputeToWall(x, y, z, dx, dy, dz);
    	ev_dwall =  ComputeDWall(x, y, z);
      AddEventToHisto(0, weight);
      
      if (nhitac < 16 and  evclass==1 and fq1rmom[mainEventIndex][1]>30.){
        nFC += weight;
        AddEventToHisto(1, weight);
        //FV
        if (ev_dwall > 80. and ev_towall>170.){
          nFV += weight;
          AddEventToHisto(2, weight);
          //nring 
          if (fq1rmom[mainEventIndex][1] > 100.){ 
            n1rmom += weight;
            AddEventToHisto(3, weight);
            //fqnse
            if(fqnse == 1){
              nfqnse += weight;
              AddEventToHisto(4, weight);
              //nring
              if (fqmrnring[0] == 1){
                nnring += weight;
                AddEventToHisto(5, weight);
                //PID 1st ring
                //if (fqmrpid[0][0] == 1) {
                if (this->electron_muon_PID() > 0){
                //if (this->nllr_2Rother_ee() < 590 - 3.22 * fqpi0mass[0]) { //Tuned against pi0mass
                //if ( fqpi0mass[0] < 300) { //Just pi0mass cut
                //if (this->nllr_2Rother_ee() < 160 - 0.15 * this->ifitPi0mom()) { //tuned against pi0mom
                //if (this->nllr_2Rother_ee() < 100){ //1D PID  
                  nPID1 += weight;
                  AddEventToHisto(6, weight);
                //	if (fqmrpid[0][1] == 1) {
                    //if (fq1rnll[1][2]-fq1rnll[1][1]>0.2*fq1rmom[1][1]) {
                  //	nPID2 += weight;
                    //AddEventToHisto(7, weight);
                    //Erec
        //						if (Erec <1250.) {
                    //	nErec += weight;
              //				AddEventToHisto(8, weight);

                      //!!Pi0
                      if (this->IsfQPi0()){ // Official pi0mass 2D cut
                      //if(-1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][ELECTRON] > 150) { //1D PID
                        nePi0+= weight;
                        AddEventToHisto(9, weight);
                        nTwoRingSelected += weight;
                        totweight = weight;
                        if (totweight > 100.){
                          std::cout << weight << std::endl;
                        }
    //										NCpi0_2R_pi0e_pi0mass_hist->Fill(fqpi0mass[0], fq1rnll[mainEventIndex][ELECTRON]-fqpi0nll[mainEventIndex]);
                         // bweight->Fill();
                          weighttree->Fill();
                        
                                      
                        if  (abs(Neutmode)==31 || abs(Neutmode)==32 || abs(Neutmode) == 36){
                          nSelecSignal += weight;
                        }
                        else nSelecBackground += weight ;
                      
                      }
                    }
              //		}
              //	}
              }
            }
          }
        }
      }
    }


		//1 decay electron  pi0 like selection	
		//FC
    if (sel == _1dcyePi0){
      AddEventToHisto(0, weight);
      if (nhitac < 16 and  evclass==1 and fq1rmom[mainEventIndex][1]>30.){
        nFC += weight;
        AddEventToHisto(1, weight);
        //FV
        if (ev_dwall > 80. and ev_towall>170.){
          nFV += weight;
          AddEventToHisto(2, weight);
         //evis
         if (fq1rmom[mainEventIndex][1] > 100.){ 
            n1rmom += weight;
            AddEventToHisto(3, weight);
            //nring 
            if (fqmrnring[0] == 2){
              nnring += weight;
              AddEventToHisto(4, weight);
              //fqnse
              if(fqnse > 1){
                nfqnse += weight;
                AddEventToHisto(5, weight);
                //PID 1st ring
                //if (fqmrpid[0][0] == 1) {
                //if (this->electron_muon_PID() > 0){
                //if (this->nllr_2Rother_ee() < 590 - 3.22 * fqpi0mass[0]) { //Tuned against pi0mass
                //if ( fqpi0mass[0] < 300) { //Just pi0mass cut
                //if (this->nllr_2Rother_ee() < 160 - 0.15 * this->ifitPi0mom()) { //tuned against pi0mom
                if (this->nllr_2Rother_ee() < 100){ //1D PID  
                  nPID1 += weight;
                  AddEventToHisto(6, weight);
      

                      //!!Pi0
                      //if (this->IsfQPi0tuned()){ //pi0mass 2D cut
                      if(-1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][ELECTRON] > 100) { //1D PID
                        nePi0+= weight;
                        AddEventToHisto(9, weight);
                        nTwoRingSelected += weight;
                        totweight = weight;
                        if (totweight > 100.){
                          std::cout << weight << std::endl;
                        }
    //										NCpi0_2R_pi0e_pi0mass_hist->Fill(fqpi0mass[0], fq1rnll[mainEventIndex][ELECTRON]-fqpi0nll[mainEventIndex]);
                         // bweight->Fill();
                          weighttree->Fill();
                        
                                      
                        if  (abs(Neutmode)==31 || abs(Neutmode)==32 || abs(Neutmode) == 36){
                          nSelecSignal += weight;
                        }
                        else nSelecBackground += weight ;
                      
                      }
                    }
              //		}
              //	}
              }
            }
          }
        }
      }
    }
		//Charlies selection	
		//FC
    if (sel == noemupid){
      AddEventToHisto(0, weight);
      if (nhitac < 16 and  evclass==1 and fq1rmom[mainEventIndex][1]>30.){
        nFC += weight;
        AddEventToHisto(1, weight);
        //FV
        if (ev_dwall > 80. and ev_towall>170.){
          nFV += weight;
          AddEventToHisto(2, weight);
          //nring 
          if (fq1rmom[mainEventIndex][1] > 100.){ 
            n1rmom += weight;
            AddEventToHisto(3, weight);
            //fqnse
            if(fqnse == 1){
              nfqnse += weight;
              AddEventToHisto(4, weight);
              if (fqmrnring[0] == 2){
                nnring += weight;
                AddEventToHisto(5, weight);
                //PID 1st ring
                //if (fqmrpid[0][0] == 1) {
                //if (this->electron_muon_PID() > 0){
                //if (this->nllr_2Rother_ee() < 590 - 3.22 * fqpi0mass[0]) { //Tuned against pi0mass
                //if ( fqpi0mass[0] < 300) { //Just pi0mass cut
                //if (this->nllr_2Rother_ee() < 160 - 0.15 * this->ifitPi0mom()) { //tuned against pi0mom
              //  if (this->nllr_2Rother_ee() < 100){ //1D PID  
                  nPID1 += weight;
                  AddEventToHisto(6, weight);
                //	if (fqmrpid[0][1] == 1) {
                    //if (fq1rnll[1][2]-fq1rnll[1][1]>0.2*fq1rmom[1][1]) {
                  //	nPID2 += weight;
                    //AddEventToHisto(7, weight);
                    //Erec
        //						if (Erec <1250.) {
                    //	nErec += weight;
              //				AddEventToHisto(8, weight);

                      //!!Pi0
                      if (this->IsfQPi0()){ //pi0mass 2D cut
                   //   if(-1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][ELECTRON] > 100) { //1D PID
                        nePi0+= weight;
                        AddEventToHisto(9, weight);
                        nTwoRingSelected += weight;
                        totweight = weight;
                        if (totweight > 100.){
                          std::cout << weight << std::endl;
                        }
    //										NCpi0_2R_pi0e_pi0mass_hist->Fill(fqpi0mass[0], fq1rnll[mainEventIndex][ELECTRON]-fqpi0nll[mainEventIndex]);
                         // bweight->Fill();
                          weighttree->Fill();
                        
                                      
                        if  (abs(Neutmode)==31 || abs(Neutmode)==32 || abs(Neutmode) == 36){
                          nSelecSignal += weight;
                        }
                        else nSelecBackground += weight ;
                      
                      }
                   // }
              //		}
              //	}
              }
            }
          }
        }
      }
    }
  
        if  (abs(Neutmode)==31 || abs(Neutmode)==32 || abs(Neutmode) == 36){
        nTotalSignal += weight;
      }
    }
  

	
	//    file->Write();
	weightfile->Write();
  weightfile->Close();
  
  TFile * file;
  switch(sel){
		case 0: //ncpi0
      file = TFile::Open(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/figs/selection_plots/NCpi0_MC_histos_tuned_t2ksk19b.fqv4r0.%s.%s.root", horn_current.c_str(), osc_sample.c_str()), "recreate");
      break;
		case 1: //1re
      file = TFile::Open(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/figs/selection_plots/NCpi0_MC_histos_1RePi0_t2ksk19b.fqv4r0.%s.%s.root", horn_current.c_str(), osc_sample.c_str()), "recreate");
      break;
		case 2: //1dcye
      file = TFile::Open(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/figs/selection_plots/NCpi0_MC_histos_1dcyePi0_t2ksk19b.fqv4r0.%s.%s.root", horn_current.c_str(), osc_sample.c_str()), "recreate");
      break;
		case 3: //noemupid
      file = TFile::Open(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/figs/selection_plots/NCpi0_MC_histos_noemupid_t2ksk19b.fqv4r0.%s.%s.root", horn_current.c_str(), osc_sample.c_str()), "recreate");
      break;
  }   

	for (int Cut=0; Cut<numCuts; Cut++){
		for (int Hist=0; Hist<numHist; Hist++){
//			printf("%d, %d\n", Cut, Hist);
			nhitac_histo[Cut][Hist]->Write();
			evis_histo[Cut][Hist]->Write();
			towall_histo[Cut][Hist]->Write();
			dwall_histo[Cut][Hist]->Write();
			nring_histo[Cut][Hist]->Write();
			pid1_histo[Cut][Hist]->Write();
			pid2_histo[Cut][Hist]->Write();
			fqnse_histo[Cut][Hist]->Write();
			fq1rmom_histo[Cut][Hist]->Write();
			Erec_histo[Cut][Hist]->Write();
			apfitEvis_histo[Cut][Hist]->Write();
			fqpi0mass_histo[Cut][Hist]->Write();
			trueE_histo[Cut][Hist]->Write();
			Q2_histo[Cut][Hist]->Write();
			fqpi0nll_histo[Cut][Hist]->Write();
			fq1Remunll_histo[Cut][Hist]->Write();
			r2_z_histo[Cut][Hist]->Write();
			x_y_histo[Cut][Hist]->Write();
      fqpi0nll_highmass_histo[Cut][Hist]->Write();
      nllr_2Rother_ee_histo[Cut][Hist]->Write();
      nllr_pi0mom_2Ree_histo[Cut][Hist]->Write();
      pi0mom_histo[Cut][Hist]->Write();
      fqpi0nll_1D_histo[Cut][Hist]->Write();
      pi0momR1_histo[Cut][Hist]->Write();
      pi0momR2_histo[Cut][Hist]->Write();
      fqtotq_histo[Cut][Hist]->Write();
      nllr_ee_pi0_histo[Cut][Hist]->Write();

		}
	}

	file->Close();

//	printf("int: %f, w: %f \n", CC0pi_int_tot, CC0pi_tot);
  float totSig = totSel[0][0];
  float totBkg = totSel[1][0];
  float totAll = totSig + totBkg;
  float totFCFV = totSel[0][2];

	std::cout << "cut    "   << "  Selected"   << "     Efficiency" << "       From FCFV"         << "       From last"              << "        Purity" << "      In peak" <<std::endl
        <<"FC :	   "<< nFC		<< "  " <<  totSel[0][1]/totSig  << "  -      "                 << "      " << " -      "               << "      " <<totSel[0][1] / (totSel[1][1] + totSel[0][1])<<"     " <<peakSel[0][1] / (peakSel[1][1] + peakSel[0][1])<<std::endl 
				<<"+FV:		 "<< nFV		<< "  " <<  totSel[0][2]/totSig  << "  " << totSel[0][2]/totFCFV<< "      " <<totSel[0][2]/totSel[0][1] << "      " <<totSel[0][2] / (totSel[1][2] + totSel[0][2])<<"     " <<peakSel[0][2] / (peakSel[1][2] + peakSel[0][2])<<std::endl
				<<"+Evis :   "<< n1rmom << "  " <<  totSel[0][3]/totSig  << "  " << totSel[0][3]/totFCFV<< "      " <<totSel[0][3]/totSel[0][2] << "      " <<totSel[0][3] / (totSel[1][3] + totSel[0][3])<<"     " <<peakSel[0][3] / (peakSel[1][3] + peakSel[0][3])<< std::endl
				<<"+0dcye:   "<< nfqnse << "  " <<  totSel[0][4]/totSig  << "  " << totSel[0][4]/totFCFV<< "      " <<totSel[0][4]/totSel[0][3] << "      " <<totSel[0][4] / (totSel[1][4] + totSel[0][4])<<"     " <<peakSel[0][4] / (peakSel[1][4] + peakSel[0][4])<< std::endl
				<<"+2ring:   "<< nnring << "  " <<  totSel[0][5]/totSig  << "  " << totSel[0][5]/totFCFV<< "      " <<totSel[0][5]/totSel[0][4] << "      " <<totSel[0][5] / (totSel[1][5] + totSel[0][5])<<"     " <<peakSel[0][5] / (peakSel[1][5] + peakSel[0][5])<< std::endl
				<<"+elike1:  "<<	nPID1	<< "  " <<  totSel[0][6]/totSig  << "  " << totSel[0][6]/totFCFV<< "      " <<totSel[0][6]/totSel[0][5] << "      " <<totSel[0][6] / (totSel[1][6] + totSel[0][6])<<"     " <<peakSel[0][6] / (peakSel[1][6] + peakSel[0][6])<<std::endl
	  //		<<"+elike2:"<<	nPID2	<< "  " <<  totSel[0][7]/totSig  << "  " << totSel[0][7]/totFCFV<<     "  " <<totSel[0][7]/totSel[0][6] << "      " <<totSel[0][7] / (totSel[1][7] + totSel[0][7])<<"     " <<peakSel[0][7] / (peakSel[1][7] + peakSel[0][7])<<std::endl
				<<"+!!pi0 :   "<< nePi0	<< "  " <<  totSel[0][9]/totSig  << "  " << totSel[0][9]/totFCFV<< "      " <<totSel[0][9]/totSel[0][6] << "      " <<totSel[0][9] / (totSel[1][9] + totSel[0][9])<<"     " <<peakSel[0][9] / (peakSel[1][9] + peakSel[0][9])<<std::endl;


	std::cout 	<<"CCqe :		"<< CCqe_tot		<< std::endl 
				<<"CC1pi: 	    "<< CC1pi_tot		<< std::endl
				<<"CCCoh: 	    "<< CCCoh_tot		<< std::endl
				<<"CCmultipi: 	"<< CCmpi_tot		<< std::endl
				<<"CCDis:   	"<< CCdis_tot		<< std::endl
				<<"NC1pi0:		"<<	NC1pi0_tot		<< std::endl
				<<"NC1pipm: 	"<< NC1pipm_tot		<< std::endl
				<<"NCCoh: 	    "<< NCCoh_tot		<< std::endl
				<<"NCOther: 	"<< NCOther_tot		<< std::endl
				<<"CC2p2h:   	"<< CC2p2h_tot		<< std::endl
				<<"NC1gamma:   	"<< NC1gamma_tot		<< std::endl
				<<"CCmisc:   	"<< CCmisc_tot		<< std::endl
				<<"NCmpi:   	"<< NCmpi_tot		<< std::endl
				<<"NCEta:   	"<< NCEta_tot		<< std::endl
				<<"NCDIS:   	"<< NCDIS_tot		<< std::endl
				<<"NCElastic:   	"<< NCElastic_tot		<< std::endl;
/*
	std::cout 	<<"int CC0pi :		"<< CC0pi_int_tot							<< std::endl 
				<<"int CC1pipm: 	"<< CC1pipm_int_tot					<< std::endl
				<<"int CC1pi0:		"<< CC1pi0_int_tot					<< std::endl
				<<"int CCOther: 	"<< CCOther_int_tot						<< std::endl
				<<"int NC1pi0:		"<<	NC1pi0_int_tot			<< std::endl
				<<"int NC1pipm: 	"<< NC1pipm_int_tot			<< std::endl
				<<"int NCOther: 	"<< NCOther_int_tot			<< std::endl;
*/
// printf("Two ring sample selected: %d \n", nTwoRingSelected); 
   //printf("Two ring sample selected signal: %d \n", nSelecSignal); 
  // printf("Two ring sample selected Background: %d \n", nSelecBackground); 
  // printf("Total signal: %d \n", nTotalSignal); 
   printf("Files: %s , %s \n Total Entries: %lld \n Selected: %lld \n Max sub events: %d (Should be less than 12)\n", horn_current.c_str(), osc_sample.c_str(), nentries, nTwoRingSelected, maxSubEvent);
   printf("NC events skipped from numu_x_nue and numubar_x_nuebar files: %d\n", numNCskipped);
/*
	printf("nring size: 10, max: %d\n", max_nring); 
	printf("nmue size: 12, max: %d\n", max_nmue); 
	printf("Rnring size: 30, max: %d\n", max_Rnring); 
	printf("ri_nring size: 10, max: %d\n", max_ri_nring); 
	printf("npar size: 50, max: %d\n", max_npar); 
	printf("npar2 size: 60, max: %d\n", max_npar2); 
	printf("numnu size: 50, max: %d\n", max_numnu); 
	printf("nscndprt size: 1000, max: %d\n", max_nscndprt); 
	printf("Npvcscnd size: 100, max: %d\n", max_Npvcscnd); 
	printf("Npne size: 100, max: %d\n", max_Npne); 
	printf("Npvc size: 100, max: %d\n", max_Npvc); 
	printf("Nvert size: 300, max: %d\n", max_Nvert); 
	printf("Nvcvert size: 900, max: %d\n", max_Nvcvert); 
	printf("fqntwnd size: 10, max: %d\n", max_fqntwnd); 
	printf("fqnmrfit size: 32, max: %d\n", max_fqnmrfit); 
	printf("fqmsnfit size: 5, max: %d\n", max_fqmsnfit); 
*/
}

void SKMCdataTree::InitNCHistos()
{
	int NBins = 0;
	double lo_x = 0;
	double hi_x = 0;
	int NBinsy = 0;
	double lo_y = 0;
	double hi_y = 0;
  
  for (int i=0; i<numCuts; i++) {
		NBins = 100;
		lo_x = 0;
		hi_x = 100;
    for (int j=0; j<numHist; j++) nhitac_histo[i][j] = new TH1D (Form("%s_nhitac_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()) ,NBins, lo_x, hi_x);

		NBins = 100;
		lo_x = 0;
		hi_x = 1000;
    for (int j=0; j<numHist; j++) evis_histo[i][j] = new TH1F (Form("%s_evis_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()) ,NBins, lo_x, hi_x);


		NBins = 200;
		lo_x = 0;
		hi_x = 3700;
    for (int j=0; j<numHist; j++) towall_histo[i][j] = new TH1F (Form("%s_towall_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()) ,NBins, lo_x, hi_x);

		NBins = 200;
		lo_x = 0;
		hi_x = 1600;
    for (int j=0; j<numHist; j++) dwall_histo[i][j] = new TH1F (Form("%s_dwall_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);

		NBins = 6;
		lo_x = 0;
		hi_x = 6;
    for (int j=0; j<numHist; j++) pid1_histo[i][j] = new TH1D (Form("%s_pid1_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);
	
		NBins = 6;
		lo_x = 0;
		hi_x = 6;
    for (int j=0; j<numHist; j++) pid2_histo[i][j] = new TH1D (Form("%s_pid2_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);
		
    NBins = 200;
		lo_x = -2000;
		hi_x = 3000;
    for (int j=0; j<numHist; j++) fq1Remunll_histo[i][j] = new TH1F (Form("%s_fq1Remunll_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);
		
    NBins = 6;
		lo_x = 0;
		hi_x = 6;
    for (int j=0; j<numHist; j++) fqnse_histo[i][j] = new TH1D (Form("%s_fqnse_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);
		
    NBins = 100;
		lo_x = 0;
		hi_x = 1500;
    for (int j=0; j<numHist; j++) fq1rmom_histo[i][j] = new TH1F (Form("%s_fq1rmom_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);
	
		NBins = 100;
		lo_x = 0;
		hi_x = 5000;	
    for (int j=0; j<numHist; j++) Erec_histo[i][j] = new TH1F (Form("%s_Erec_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);
		
		NBins = 6;
		lo_x = 0;
		hi_x = 6;
    for (int j=0; j<numHist; j++) nring_histo[i][j] = new TH1D (Form("%s_nring_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);

		
		NBins = 50;
		lo_x = 300;
		hi_x = 600;
		NBinsy = 50;
		lo_y = 0;
		hi_y = 1000; 
    for (int j=0; j<numHist; j++) fqpi0nll_highmass_histo[i][j] = new TH2F (Form("%s_fqpi0nll_highmass_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x, NBinsy, lo_y, hi_y);	
	
    
		
		NBinsy = 50;
		lo_y = 0;
		hi_y = 1000; 
		NBins = 50;
		lo_x = 0;
		hi_x = 600; 
    for (int j=0; j<numHist; j++) fqpi0nll_histo[i][j] = new TH2F (Form("%s_fqpi0nll_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x, NBinsy, lo_y, hi_y);	

		NBins = 100;
		lo_x = -200;
		hi_x = 2000; 
    for (int j=0; j<numHist; j++) fqpi0nll_1D_histo[i][j] = new TH1F (Form("%s_fqpi0nll_1D_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);	

		NBins = 100;
		lo_x = 0;
		hi_x = 700;
    for (int j=0; j<numHist; j++) fqpi0mass_histo[i][j] = new TH1F (Form("%s_fqpi0mass_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);	

		NBins = 100;
		lo_x = 0;
		hi_x = 10;
    for (int j=0; j<numHist; j++) trueE_histo[i][j] = new TH1F (Form("%s_trueE_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);	

		NBins = 100;
		lo_x = 0;
		hi_x = 10;
    for (int j=0; j<numHist; j++) Q2_histo[i][j] = new TH1F (Form("%s_Q2_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);	
		
		NBins = 100;
		lo_x = 0;
		hi_x = 1500;
    for (int j=0; j<numHist; j++) apfitEvis_histo[i][j] = new TH1F (Form("%s_apfitEvis_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);	
		
		
		NBins = 100;
		lo_x = 0;
		hi_x = 2500;
		NBinsy = 100;
		lo_y = -1.0;
		hi_y = 1.0;
    for (int j=0; j<numHist; j++) mom_dir_histo[i][j] = new TH2F (Form("%s_mom_dir_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x, NBinsy, lo_y, hi_y);		
	

		NBins = 200;
		lo_x = -2000;
		hi_x = 2000;
		NBins = 200;
		lo_y = -2000;
		hi_y = 2000;
    for (int j=0; j<numHist; j++) x_y_histo[i][j] = new TH2F (Form("%s_x_y_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x, NBinsy, lo_y, hi_y);		
	

		NBins = 100;
		lo_x = 0;
		hi_x = 3E6;
		NBinsy = 100;
		lo_y = -2000;
		hi_y = 2000;
    for (int j=0; j<numHist; j++) r2_z_histo[i][j] = new TH2F (Form("%s_r2_z_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x, NBinsy, lo_y, hi_y);		
	
	
		NBins = 100;
		lo_x = 0;
		hi_x = 3000;
    for (int j=0; j<numHist; j++) ring_2_mom_histo[i][j] = new TH1F (Form("%s_ring_2_mom_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);		


		NBins = 100;
		lo_x = -1000;
		hi_x = 1000;
    for (int j=0; j<numHist; j++) nllr_2Rother_ee_histo[i][j] = new TH1F (Form("%s_nllr_2Rother_ee_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);		
	

		NBins = 200;
		lo_x = 0;
		hi_x = 2000;
		NBinsy = 200;
		lo_y = -1000;
		hi_y = 1000;
    for (int j=0; j<numHist; j++) nllr_pi0mom_2Ree_histo[i][j] = new TH2F (Form("%s_nllr_pi0mom_2Ree_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x, NBinsy, lo_y, hi_y);		

		NBins = 100;
		lo_x = 0;
		hi_x = 4000;
    for (int j=0; j<numHist; j++) pi0mom_histo[i][j] = new TH1F (Form("%s_pi0mom_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);		

		NBins = 100;
		lo_x = 0;
		hi_x = 4000;
    for (int j=0; j<numHist; j++) pi0momR1_histo[i][j] = new TH1F (Form("%s_pi0momR1_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);		
		
    NBins = 100;
		lo_x = 0;
		hi_x = 2000;
    for (int j=0; j<numHist; j++) pi0momR2_histo[i][j] = new TH1F (Form("%s_pi0momR2_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);		
    
    NBins = 100;
		lo_x = 0;
		hi_x = 100000;
    for (int j=0; j<numHist; j++) fqtotq_histo[i][j] = new TH1F (Form("%s_fqtotq_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);		

    NBins = 100;
		lo_x = -500;
		hi_x = 500;
    for (int j=0; j<numHist; j++) nllr_ee_pi0_histo[i][j] = new TH1F (Form("%s_nllr_ee_pi0_histo_%d", varNames[j].c_str(), i), Form("%s", varNames[j].c_str()), NBins, lo_x, hi_x);		

}

}


  void SKMCdataTree::FillHistos(int cut, int mode, float w){
  
	  float x = fq1rpos[mainEventIndex][1][0];
   	float y = fq1rpos[mainEventIndex][1][1];
   	float z = fq1rpos[mainEventIndex][1][2];
	  float EcosBeam = ComputeCosBeam(mainEventIndex, ELECTRON);
	  float Erec = ComputeErec(fq1rmom[mainEventIndex][ELECTRON], ELECTRON, EcosBeam);
    
    float pi0mom = fqpi0momtot[0];

	
      nhitac_histo[cut][mode]->Fill(nhitac, w);
			evis_histo[cut][mode]->Fill(fq1rmom[mainEventIndex][1], w);
			towall_histo[cut][mode]->Fill(this->GetRecoToWall_pi0(), w);
			dwall_histo[cut][mode]->Fill(this->GetRecoDWall_pi0(), w);
			nring_histo[cut][mode]->Fill(fqmrnring[0], w);
			pid1_histo[cut][mode]->Fill(fqmrpid[0][0], w);
			pid2_histo[cut][mode]->Fill(fqmrpid[0][1], w);
			fqnse_histo[cut][mode]->Fill(fqnse, w);
			fq1rmom_histo[cut][mode]->Fill(fq1rmom[mainEventIndex][1], w);
			Erec_histo[cut][mode]->Fill(Erec, w);
			apfitEvis_histo[cut][mode]->Fill(evis, w);
			fqpi0mass_histo[cut][mode]->Fill(fqpi0mass[0], w);
			trueE_histo[cut][mode]->Fill(pnu[0], w);
			Q2_histo[cut][mode]->Fill((pnu[0]-pnu[2])*(pnu[0]-pnu[2]), w);
			fqpi0nll_histo[cut][mode]->Fill(fqpi0mass[0],-1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][1], w);
			fqpi0nll_1D_histo[cut][mode]->Fill(-1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][1], w);
			mom_dir_histo[cut][mode]->Fill(pnu[0], this->ComputeTrueCosBeam());
			r2_z_histo[cut][mode]->Fill(x*x+y*y, z);
			x_y_histo[cut][mode]->Fill(fq1rpos[mainEventIndex][1][0], fq1rpos[mainEventIndex][1][1]);
			ring_2_mom_histo[cut][mode]->Fill(fqpi0mom2[0]);
      fqpi0nll_highmass_histo[cut][mode]->Fill(fqpi0mass[0],-1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][1], w);
      fq1Remunll_histo[cut][mode]->Fill(this->electron_muon_PID(), w);
      nllr_2Rother_ee_histo[cut][mode]->Fill(this->nllr_2Rother_ee(), w);
			nllr_pi0mom_2Ree_histo[cut][mode]->Fill(fqpi0mass[0], this->nllr_2Rother_ee(), w);
			pi0mom_histo[cut][mode]->Fill(pi0mom, w);
			pi0momR1_histo[cut][mode]->Fill(fqpi0mom1[0], w);
			pi0momR2_histo[cut][mode]->Fill(fqpi0mom2[0], w);
			fqtotq_histo[cut][mode]->Fill(fqtotq[mainEventIndex], w);
			nllr_ee_pi0_histo[cut][mode]->Fill(this->nllr_pi0_ee(), w);
	}



void SKMCdataTree::AddEventToHisto(int cutID, float w)
{
 	int mach3mode = 0;	
  double peakLo = 0;
  double peakHi = 300;
  //mach3mode NCother = 8/
  //Expanded to show more NC background: 8=

  
  switch(abs(Neutmode)){
		case 1: //ccqe
			mach3mode = 0;
      FillHistos(cutID, mach3mode, w);
/*			nhitac_histo[cutID][mach3mode]->Fill(nhitac, w);
			evis_histo[cutID][mach3mode]->Fill(fq1rmom[mainEventIndex][1], w);
			towall_histo[cutID][mach3mode]->Fill(this->GetRecoToWall(), w);
			dwall_histo[cutID][mach3mode]->Fill(this->GetRecoDWall(), w);
			nring_histo[cutID][mach3mode]->Fill(fqmrnring[0], w);
			pid1_histo[cutID][mach3mode]->Fill(fqmrpid[0][0], w);
			pid2_histo[cutID][mach3mode]->Fill(fqmrpid[0][1], w);
			fqnse_histo[cutID][mach3mode]->Fill(fqnse, w);
			fq1rmom_histo[cutID][mach3mode]->Fill(fq1rmom[mainEventIndex][1], w);
			Erec_histo[cutID][mach3mode]->Fill(Erec, w);
			apfitEvis_histo[cutID][mach3mode]->Fill(evis, w);
			fqpi0mass_histo[cutID][mach3mode]->Fill(fqpi0mass[0], w);
			trueE_histo[cutID][mach3mode]->Fill(pnu[0], w);
			Q2_histo[cutID][mach3mode]->Fill((pnu[0]-pnu[2])*(pnu[0]-pnu[2]), w);
			fqpi0nll_histo[cutID][mach3mode]->Fill(fqpi0mass[0],-1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][1], w);
			mom_dir_histo[cutID][mach3mode]->Fill(pnu[0], this->ComputeTrueCosBeam());
			r2_z_histo[cutID][mach3mode]->Fill(x*x+y*y, z);
			x_y_histo[cutID][mach3mode]->Fill(fq1rpos[mainEventIndex][1][0], fq1rpos[mainEventIndex][1][1]);
			ring_2_mom_histo[cutID][mach3mode]->Fill(fqpi0mom2[0]);
      fqpi0nll_highmass_histo[cutID][mach3mode]->Fill(fqpi0mass[0],-1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][1], w);
      fq1Remunll_histo[cutID][mach3mode]->Fill(this->electron_muon_PID(), w);
	*/
      
      if (cutID==numCuts-1) CCqe_tot += w;
			break;
		case 2: //cc2p2h
			mach3mode = 9;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1) CC2p2h_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 11:
		case 12: 
		case 13: //cc1pi
			mach3mode = 1;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1) CC1pi_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 15: //ccmisc
			mach3mode = 11;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1){
				CCmisc_tot += w;
			}
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;

			break;
		case 16:	//ccCoih
			mach3mode = 2;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1) CCCoh_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 21: //ccmpi
			mach3mode = 3;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1) CCmpi_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 26: //ccdis
			mach3mode = 4;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1) CCdis_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 31:
		case 32://nc1pi0
			mach3mode = 5;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1) NC1pi0_tot += w;
      totSel[0][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[0][cutID] += w;
			break;
		case 33:
		case 34: //nc1pipm
			mach3mode = 6;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1) NC1pipm_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 35: //NCOther (diffractive)
      mach3mode = 8;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1) NCOther_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 36: //NCCoh
			mach3mode = 7;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1) NCCoh_tot += w;
      totSel[0][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[0][cutID] += w;
			break;
		case 38:
		case 39://nc1gamma
			mach3mode = 10;
      FillHistos(cutID, mach3mode, w);
			if (cutID==numCuts-1) NC1gamma_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 41:	// NCmpi (NCOther)
      mach3mode = 12;
      FillHistos(cutID, mach3mode, w);
		  if (cutID==numCuts-1) NCmpi_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 42:
		case 43: //NCEta (NCOther)
			mach3mode = 13;
      FillHistos(cutID, mach3mode, w);
		  if (cutID==numCuts-1) NCEta_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 44:
		case 45:  //NCOther (NCK)
			mach3mode = 8;
      FillHistos(cutID, mach3mode, w);
		  if (cutID==numCuts-1) NCOther_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 46: //NCDIS (NCOther)
			mach3mode = 14;
      FillHistos(cutID, mach3mode, w);
		  if (cutID==numCuts-1) NCDIS_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
		case 51:
		case 52://NCElastic (NCOther)
			mach3mode = 15;
      FillHistos(cutID, mach3mode, w);
		  if (cutID==numCuts-1) NCElastic_tot += w;
      totSel[1][cutID] += w;
      if(fqpi0mass[0]>peakLo && fqpi0mass[0]<peakHi) peakSel[1][cutID] += w;
			break;
	}

}



