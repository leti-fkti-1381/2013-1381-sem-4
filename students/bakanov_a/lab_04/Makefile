ifeq ($(OS), Windows_NT)
	MAKE_TOOL = mingw32-make
	RMDIR = rmdir /S /Q
	MAKE_OBJ_DIR = if not exist obj mkdir obj
	RM_EXECS = del /Q main.exe
else
	MAKE_TOOL = make
	RMDIR = rm -r
	MAKE_OBJ_DIR = mkdir -p obj
	RM_EXECS = rm main
endif

CXXFLAGS = -g -Wall -Wextra
INCDIR = src/include

all :
	$(MAKE_OBJ_DIR)
	$(MAKE_TOOL) main

obj/time_meter.o : src/time_meter.cpp $(INCDIR)/time_meter.h
	$(CXX) $(CXXFLAGS) -c src/time_meter.cpp -o obj/time_meter.o

obj/utils.o : src/utils.cpp $(INCDIR)/utils.h
	$(CXX) $(CXXFLAGS) -c src/utils.cpp -o obj/utils.o

obj/main.o : src/utils.cpp $(INCDIR)/utils.h $(INCDIR)/time_meter.h src/time_meter.cpp src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

main : obj/utils.o obj/main.o obj/time_meter.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RMDIR) obj
	$(RM_EXECS)
