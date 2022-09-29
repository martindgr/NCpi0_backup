#!/bin/sh

#g++ -g  -o SKEffPlot -I. -I./Prob3 -Wall -fPIC -L. -L./Prob3 -L/usr/lib64/root  -rdynamic -pthread -std=c++11 -m64 -I/usr/include/root SKMCdataTree_SKEff.cc SKEff_plots.cc -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -lThreeProb_2.10 -lm -ldl

g++ -g  -o SKMCdataTree_NCpi0Sel -I. -I./Prob3 -Wall -fPIC -L. -L./Prob3 -L/usr/lib64/root  -rdynamic -pthread -std=c++11 -m64 -I/usr/include/root SKMCdataTree.cc SKMCdataTree_NCpi0Sel.cc -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -lThreeProb_2.10 -lm -ldl


#g++ -g  -o SKMCfomPlots -I. -Wall -fPIC -L. -L/usr/lib64/root  -rdynamic -pthread -std=c++11 -m64 -I/usr/include/root SKMCfomPlots.cc -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame  -lm -ldl
