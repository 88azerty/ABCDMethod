#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <stdlib.h>
#include <TStyle.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TColor.h>
#include <math.h>
#include <THnSparse.h>
#include <TChain.h>
#include <map>
#include <string>
#include <vector>
#include <TRandom3.h>
#include "THnSparse.h"
#include "TF1.h"
#include "TSystem.h"
#include "THStack.h"
#include "TCut.h"
#include <TTree.h>
#include <TTreeReader.h>

using namespace std;

int main (){
  vector<string> filenames;
  vector<float> weights;

  ifstream list( "list.txt", ios::in );
  while( list.good() ){
    string n, w;
    list >> n >> ws >> w;
    if( n.length() == 0 )             continue;
    if( n.compare( 0,1,"#" ) == 0 )   continue;
    filenames.push_back(n);
    weights.push_back( atof( w.c_str() ) );
  }

  TChain *mychain = new TChain("RecoData"); //create a chain with all the files
  for( unsigned int i=0; i<filenames.size(); i++){
    const char *j = filenames.at(i).c_str();
    mychain->Add( j );
    delete j;
  }

  cout<<"TChain has "<<mychain->GetEntries()<< " entries."<<endl;

  return 0;
}
