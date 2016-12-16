ROOTGLIBS =`root-config --glibs --libs` -lMinuit -lTreePlayer
LIBS = -L/usr/X11R6/lib -lm -ldl -lstdc++ -Wl,--no-as-needed $(ROOTGLIBS)

CXXFLAGS = -O3 -Wall --exceptions `root-config --ldflags --cflags` -I./

process: processHFTrees.cxx
	$(CXX) processHFTrees.cxx -o processHFTrees.out $(CXXFLAGS) $(LIBS)

clean:
	rm -f processHFTrees.out
	rm -f *~
