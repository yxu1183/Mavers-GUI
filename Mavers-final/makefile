CXXFLAGS += -std=c++11
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

ex: project.o project_functions.o
	$(CXX) $(CXXFLAGS) -o project project.o project_functions.o $(GTKFLAGS)
project.o: project.cpp project_header.h
	$(CXX) $(CXXFLAGS) -c project.cpp $(GTKFLAGS)
project_functions.o: project_header.h project_functions.cpp
	$(CXX) $(CXXFLAGS) -c project_functions.cpp $(GTKFLAGS)
