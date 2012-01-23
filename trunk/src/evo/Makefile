CPP  = i686-pc-mingw32-g++.exe
CC   = gcc.exe
RES  = 
OBJ  = ZEMain.o ADN.o ADNinit.o Affiche3d.o Camera.o GA.o GAmorpho.o GArender.o Genes.o InitGLmodes.o InitPlayfield.o MathsVector.o $(RES)
LINKOBJ  = ZEMain.o ADN.o ADNinit.o Affiche3d.o Camera.o GA.o GAmorpho.o GArender.o Genes.o InitGLmodes.o InitPlayfield.o MathsVector.o $(RES)
LIBS =  -L"../../lib" -L"." -lagl -lalleg -luser32 -lgdi32 -lopengl32 -lglu32 -lopengl32 -mwindows  
INCS =   
CXXINCS = -I"C:\cygwin\usr\i686-pc-mingw32\sys-root\mingw\include" -I"../../include/allegro442_include" -I"../../include/allegrogl_include"
BIN  = dna_evo.exe
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before dna_evo.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "dna_evo.exe" $(LIBS)

ZEMain.o: ZEMain.cpp
	$(CPP) -c ZEMain.cpp -o ZEMain.o $(CXXFLAGS)

ADN.o: ADN.cpp
	$(CPP) -c ADN.cpp -o ADN.o $(CXXFLAGS)

ADNinit.o: ADNinit.cpp
	$(CPP) -c ADNinit.cpp -o ADNinit.o $(CXXFLAGS)

Affiche3d.o: Affiche3d.cpp
	$(CPP) -c Affiche3d.cpp -o Affiche3d.o $(CXXFLAGS)

Camera.o: Camera.cpp
	$(CPP) -c Camera.cpp -o Camera.o $(CXXFLAGS)

GA.o: GA.cpp
	$(CPP) -c GA.cpp -o GA.o $(CXXFLAGS)

GAmorpho.o: GAmorpho.cpp
	$(CPP) -c GAmorpho.cpp -o GAmorpho.o $(CXXFLAGS)

GArender.o: GArender.cpp
	$(CPP) -c GArender.cpp -o GArender.o $(CXXFLAGS)

Genes.o: Genes.cpp
	$(CPP) -c Genes.cpp -o Genes.o $(CXXFLAGS)

InitGLmodes.o: InitGLmodes.cpp
	$(CPP) -c InitGLmodes.cpp -o InitGLmodes.o $(CXXFLAGS)

InitPlayfield.o: InitPlayfield.cpp
	$(CPP) -c InitPlayfield.cpp -o InitPlayfield.o $(CXXFLAGS)

MathsVector.o: MathsVector.cpp
	$(CPP) -c MathsVector.cpp -o MathsVector.o $(CXXFLAGS)
