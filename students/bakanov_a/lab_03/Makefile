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

obj/utils.o : src/utils.cpp $(INCDIR)/utils.h
	$(CXX) $(CXXFLAGS) -c src/utils.cpp -o obj/utils.o

obj/main.o : src/utils.cpp $(INCDIR)/utils.h src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

main : obj/utils.o obj/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RMDIR) obj
	$(RM_EXECS)
