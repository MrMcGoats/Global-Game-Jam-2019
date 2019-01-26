ANGEL_DISABLE_FMOD := $(shell sed -rn 's/^[[:space:]]*\#define[[:space:]]+ANGEL_DISABLE_FMOD[[:space:]]+([[:digit:]])[[:space:]]*$$/\1/p' ../angel2d/Code/Angel/AngelConfig.h)
ANGEL_DISABLE_DEVIL := $(shell sed -rn 's/^[[:space:]]*\#define[[:space:]]+ANGEL_DISABLE_DEVIL[[:space:]]+([[:digit:]])[[:space:]]*$$/\1/p' ../angel2d/Code/Angel/AngelConfig.h)
CXX = g++
TARGET = ClientGame
ANGEL_FLAGS = -D ANGEL_RELEASE
ARCH := $(shell uname -m)
ALLEGRO_LIBS := $(shell allegro-config --libs 2>/dev/null)
CWD := $(shell pwd)
CODE_DIR := $(shell dirname "$(CWD)")
LIBANGEL = ../angel2d/Code/Angel/libangel.a
LUA = $(CWD)/../angel2d/Code/Angel/Libraries/angel-lua-build/lua
WRAPPER = ../angel2d/Code/Angel/Scripting/Interfaces/AngelLuaWrapping.cpp

INCLUDE = 							\
	-I../angel2d/Code/Angel						\
	-I../angel2d/Code/Angel/Libraries/glfw-3.0.3/include			\
	-I../angel2d/Code/Angel/Libraries/Box2D-2.2.1			\
	-I../angel2d/Code/Angel/Libraries/FTGL/include			\
	-I../angel2d/Code/Angel/Libraries/lua-5.2.1/src			\
	-I/usr/include/freetype2
ifneq ($(ANGEL_DISABLE_FMOD), 1)
	INCLUDE += -I../angel2d/Code/Angel/Libraries/FMOD/inc
endif

LIBS = 									\
	$(LIBANGEL)							\
	../angel2d/Code/Angel/Libraries/glfw-3.0.3/src/libglfw3.a			\
	../angel2d/Code/Angel/Libraries/Box2D-2.2.1/Build/Box2D/libBox2D.a		\
	../angel2d/Code/Angel/Libraries/FTGL/unix/src/.libs/libftgl.a		\
	../angel2d/Code/Angel/Libraries/gwen/lib/linux/gmake/libgwen_static.a	\
	../angel2d/Code/Angel/Libraries/angel-lua-build/liblua.a

ifneq ($(ANGEL_DISABLE_FMOD), 1)
	ifeq ($(ARCH),x86_64)
		LIBS += ../angel2d/Code/Angel/Libraries/FMOD/lib/libfmodex64.so
	else
		LIBS += ../angel2d/Code/Angel/Libraries/FMOD/lib/libfmodex.so
	endif
endif

SHLIBS = -lGL -lGLU -ldl -lfreetype -lXrandr -lX11 -lpthread -lrt -lXxf86vm -lXi
SHLIBS += $(ALLEGRO_LIBS)
ifeq ($(ANGEL_DISABLE_FMOD), 1)
	SHLIBS += -lopenal -lvorbisfile
endif
ifneq ($(ANGEL_DISABLE_DEVIL),1)
	SHLIBS += -lIL -lILU -lILUT
else
	SHLIBS += -lpng
endif

SYSSRCS = 							\
	$(WRAPPER)

SRCS =								\
	stdafx.cpp						\
	Main.cpp

SYSOBJS = $(patsubst %.cpp,%.o,$(SYSSRCS))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: clean all SWIG-Wrapper

%.o: %.cpp
	$(CXX) -c $(INCLUDE) -Wno-write-strings -Wno-deprecated -o $@ $^

all: $(TARGET)

publish: $(TARGET)
	cd ../angel2d/Code/ClientGame && $(LUA) ../Tools/BuildScripts/publish_linux.lua -i $(CWD) -e ClientGame

SWIG-Wrapper:
	cd ../angel2d/Code/ClientGame && $(LUA) ../Tools/BuildScripts/swig_wrap.lua -p "$(CODE_DIR)"

$(WRAPPER): SWIG-Wrapper

$(TARGET): $(LIBANGEL) $(OBJS) $(SYSOBJS) $(WRAPPER)
	$(CXX) -o $@ $(OBJS) $(SYSOBJS) $(LIBS) $(SHLIBS) $(ANGEL_FLAGS)
	cp -p ../angel2d/Code/Angel/Scripting/EngineScripts/*.lua Resources/Scripts

clean:
	rm -f $(OBJS) $(SYSOBJS) $(TARGET) $(WRAPPER)

$(LIBANGEL):
	cd ../angel2d/Code/Angel && make
