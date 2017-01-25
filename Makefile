ROOTGLIBS =`root-config --glibs --libs` -lMinuit -lTreePlayer
LIBS = -L/usr/X11R6/lib -lm -ldl -lstdc++ -Wl,--no-as-needed $(ROOTGLIBS)

CXXFLAGS = -O3 -Wall --exceptions `root-config --ldflags --cflags` -I./

process: processHFTrees.cxx
	$(CXX) processHFTrees.cxx -o processHFTrees.out $(CXXFLAGS) $(LIBS)

check: checkPVLeadingJet_pt.cxx
	$(CXX) checkPVLeadingJet_pt.cxx -o checkPVLeadingJet_pt.out $(CXXFLAGS) $(LIBS)

basic: basicHandlingFullROOT.cxx
	$(CXX) basicHandlingFullROOT.cxx -o basicHandlingFullROOT.out $(CXXFLAGS) $(LIBS)

clean:
	rm -f *.out
	rm -f *~
