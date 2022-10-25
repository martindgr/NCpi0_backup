
//#define SKMCdataTree_cxx
#include "SKMCdataTree.h"

//#include "SetT2KStyle.H"
#include <TFileCollection.h>
#include <THashList.h>
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
//#include "BargerPropagator.h"

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

/* To run use root -l, .L MakeHistograms.C, run() */
int main(int argc, char* argv[]){
	
	int nFiles = 0;
	std::string horn_current = argv[1];
	std::string osc_sample = argv[2];

    std::string idir = Form("/vols/t2k/users/dmartin/NCpi0/t2kmc_19b/root/%s/%s/", horn_current.c_str(), osc_sample.c_str());

	std::string workdir = "/vols/t2k/users/dmartin/NCpi0/code/selection/";
    TChain *ch_files;
    ch_files = new TChain("h1");
	
	typedef enum{
		NUMU = 0, 
		NUE,
		NUMUBAR,
		NUEBAR,
		NUMUTONUE, 
		NUMUBARTONUEBAR
	} FileFlavor;
	
	vector<int> fileFlavor;
	
	if (osc_sample == "all"){
		
		
			
		std::string ifilename;
		if (horn_current == "fhc") {
			ifilename = "ifile_fhc.txt";
		}
		else {
			ifilename = "ifile_rhc.txt";
		}

		
		std::ifstream infiles (Form("%s%s",workdir.c_str(), ifilename.c_str()));

		int preventries = 0;
		std::string line;
		if (infiles.is_open()) {
			while ( getline (infiles,line) ) {
				FileFlavor flavtmp;
				if(line.find("numu_x_numu")!=string::npos) flavtmp=NUMU;
				if(line.find("nue_x_nue")!=string::npos) flavtmp=NUE;
				if(line.find("numubar_x_numubar")!=string::npos) flavtmp=NUMUBAR;
				if(line.find("nuebar_x_nuebar")!=string::npos) flavtmp=NUEBAR;
				if(line.find("numu_x_nue")!=string::npos) flavtmp=NUMUTONUE;
				if(line.find("numubar_x_nuebar")!=string::npos) flavtmp=NUMUBARTONUEBAR;
				//printf("Loaded %s, flavour %d\n", line.c_str(), flavtmp);		    
				ch_files->AddFile(line.c_str());
				int entriestmp = ch_files->GetEntries();
				for(int i=0; i<(entriestmp-preventries); i++) fileFlavor.push_back(flavtmp);
				preventries = entriestmp;
				nFiles += 1;
			}
			infiles.close();
		}
		

		printf("Processing %d Files: %s %s \n", nFiles,  horn_current.c_str(), osc_sample.c_str());
	}
	else {
		
		
    	TFileCollection filelist("files", "");
		std::string idir = Form("/vols/t2k/users/dmartin/NCpi0/t2kmc_19b/root/%s/%s/", horn_current.c_str(), osc_sample.c_str());
		filelist.Add(Form("%s*.root", idir.c_str() ));

    	ch_files->AddFileInfoList(filelist.GetList());
	
	
		printf("Processing: %s %s \nNumber of files: %lld \n", horn_current.c_str(), osc_sample.c_str(), filelist.GetNFiles());

	}
	//filelist.Add(Form("%s/numu_x_numu/*.root", idir.c_str() ));
	//filelist.Add(Form("%s/numu_x_nue/*.root", idir.c_str() ));
	//filelist.Add(Form("%s/nuebar_x_nuebar/*.root", idir.c_str() ));
	//filelist.Add(Form("%s/nue_x_nue/*.root", idir.c_str() ));
	//filelist.Add(Form("%s/numubar_x_nuebar/*.root", idir.c_str() ));
	//filelist.Add(Form("%s/numubar_x_numubar/*.root", idir.c_str() ));

//SKMCdataTree::fileFlavorInt = fileFlavor;	

	  typedef enum{
    NCPi0 = 0,
    _1RePi0,
    _1dcyePi0,
    noemupid,
  } SelType;
	

    SelType sel = _1dcyePi0;
    //SelType sel = _1RePi0;
    //SelType sel = NCPi0;
    //SelType sel = noemupid;
    SKMCdataTree m(ch_files);
	  m.AddFileFlavorInt(fileFlavor);
    
//    m.LoopSelection(horn_current, osc_sample);
    m.LoopNCHistos(horn_current, osc_sample, sel);
    return 1;
   }                             
