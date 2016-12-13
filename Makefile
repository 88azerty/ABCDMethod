ROOTGLIBS =`root-config --glibs --libs` -lMinuit
LIBS = -L/usr/X11R6/lib -lm -ldl -lstdc++ -Wl,--no-as-needed $(ROOTGLIBS) -lTreePlayer

CXXFLAGS = -O3 -Wall --exceptions `root-config --ldflags --cflags` -I./

process: processHFTrees.cxx
	$(CXX) processHFTrees.cxx -o processHFTrees $(CXXFLAGS) $(LIBS)

clean:
	rm -f processHFTrees
	rm -f *~
