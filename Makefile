CXX = clang
LIBS = -lglfw3 -lopengl32 -luser32 -lgdi32 -lkernel32 -lshell32 -lvcruntime -lmsvcrtd -l libcmt
LDFLAGS = -L lib/

SRC := $(wildcard src/*.cpp) 
SRC += $(wildcard src/*.hpp) 
SRC += $(wildcard src/*.c)
SRC += $(wildcard src/*.h)

#DEP += $(filter %.c, $(SRC))
DEP := $(filter %.cpp, $(SRC))
DEP += $(filter %.c, $(SRC))

OBJFILES := $(patsubst %.cpp, %.o, $(DEP))
OBJFILES += $(patsubst %.c, %.o, $(DEP))

OBJFILES := $(filter %.o, $(OBJFILES))

HEADERFILES := $(filter %.hpp, $(SRC))

ALLFILES := $(patsubst %.hpp, %.hpp.gch, $(HEADERFILES))
ALLFILES += $(OBJFILES)

#git rm --cached src/*.gch


run: main
	a.exe

main: $(HEADERFILES) $(OBJFILES)
	$(CXX) $(OBJFILES) -I include $(LDFLAGS) $(LIBS)

%.o : %.c
	$(CXX) -I include -c $< -o $@

%.o : %.cpp
	$(CXX) -I include -c $< -o $@

clean:
	rm -rf $(ALLFILES)