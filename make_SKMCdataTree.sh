
g++ -g  -o SKMCplots -Wall -L. -L/usr/lib64/root -I/usr/include/root SKMCplots.cc -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -lm -ldl


g++ -g  -o SKMCfomPlots -Wall -L. -L/usr/lib64/root -I/usr/include/root SKMCfomPlots.cc -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -lm -ldl

#g++ -g  -o SKMCdataTree_NCpi0Sel -I. -I./Prob3 -Wall -fPIC -L. -L./Prob3 -L/usr/lib64/root  -rdynamic -pthread -std=c++11 -m64 -I/usr/include/root SKMCdataTree.cc SKMCdataTree_NCpi0Sel.cc -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf    3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -lThreeProb_2.10 -lm -ldl
