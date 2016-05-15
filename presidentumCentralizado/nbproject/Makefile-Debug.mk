#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/BossFinal.o \
	${OBJECTDIR}/Camara.o \
	${OBJECTDIR}/ECargando.o \
	${OBJECTDIR}/ECinematica.o \
	${OBJECTDIR}/EInGame.o \
	${OBJECTDIR}/EIntro.o \
	${OBJECTDIR}/EMenu.o \
	${OBJECTDIR}/EMenuInGame.o \
	${OBJECTDIR}/Enemigo.o \
	${OBJECTDIR}/Escena.o \
	${OBJECTDIR}/Juego.o \
	${OBJECTDIR}/Jugador.o \
	${OBJECTDIR}/LevelFactory.o \
	${OBJECTDIR}/Mapa.o \
	${OBJECTDIR}/Mundo.o \
	${OBJECTDIR}/NPC.o \
	${OBJECTDIR}/Plataforma.o \
	${OBJECTDIR}/Proyectil.o \
	${OBJECTDIR}/Simpatizante.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/pruebasCarlos.o \
	${OBJECTDIR}/tinystr.o \
	${OBJECTDIR}/tinyxml.o \
	${OBJECTDIR}/tinyxmlerror.o \
	${OBJECTDIR}/tinyxmlparser.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/C/SFML/lib/libsfml-graphics-d.a /C/SFML/lib/libsfml-window-d.a /C/SFML/lib/libsfml-system-d.a /C/SFML/lib/libsfml-audio-d.a /C/SFML/lib/libsfml-main-d.a /C/SFML/lib/libsfml-network-d.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumcentralizado.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumcentralizado.exe: /C/SFML/lib/libsfml-graphics-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumcentralizado.exe: /C/SFML/lib/libsfml-window-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumcentralizado.exe: /C/SFML/lib/libsfml-system-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumcentralizado.exe: /C/SFML/lib/libsfml-audio-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumcentralizado.exe: /C/SFML/lib/libsfml-main-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumcentralizado.exe: /C/SFML/lib/libsfml-network-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumcentralizado.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumcentralizado ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/BossFinal.o: BossFinal.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BossFinal.o BossFinal.cpp

${OBJECTDIR}/Camara.o: Camara.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Camara.o Camara.cpp

${OBJECTDIR}/ECargando.o: ECargando.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ECargando.o ECargando.cpp

${OBJECTDIR}/ECinematica.o: ECinematica.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ECinematica.o ECinematica.cpp

${OBJECTDIR}/EInGame.o: EInGame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EInGame.o EInGame.cpp

${OBJECTDIR}/EIntro.o: EIntro.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EIntro.o EIntro.cpp

${OBJECTDIR}/EMenu.o: EMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EMenu.o EMenu.cpp

${OBJECTDIR}/EMenuInGame.o: EMenuInGame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EMenuInGame.o EMenuInGame.cpp

${OBJECTDIR}/Enemigo.o: Enemigo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Enemigo.o Enemigo.cpp

${OBJECTDIR}/Escena.o: Escena.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Escena.o Escena.cpp

${OBJECTDIR}/Juego.o: Juego.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Juego.o Juego.cpp

${OBJECTDIR}/Jugador.o: Jugador.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Jugador.o Jugador.cpp

${OBJECTDIR}/LevelFactory.o: LevelFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LevelFactory.o LevelFactory.cpp

${OBJECTDIR}/Mapa.o: Mapa.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mapa.o Mapa.cpp

${OBJECTDIR}/Mundo.o: Mundo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mundo.o Mundo.cpp

${OBJECTDIR}/NPC.o: NPC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NPC.o NPC.cpp

${OBJECTDIR}/Plataforma.o: Plataforma.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Plataforma.o Plataforma.cpp

${OBJECTDIR}/Proyectil.o: Proyectil.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Proyectil.o Proyectil.cpp

${OBJECTDIR}/Simpatizante.o: Simpatizante.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Simpatizante.o Simpatizante.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/pruebasCarlos.o: pruebasCarlos.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pruebasCarlos.o pruebasCarlos.cpp

${OBJECTDIR}/tinystr.o: tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinystr.o tinystr.cpp

${OBJECTDIR}/tinyxml.o: tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml.o tinyxml.cpp

${OBJECTDIR}/tinyxmlerror.o: tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxmlerror.o tinyxmlerror.cpp

${OBJECTDIR}/tinyxmlparser.o: tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxmlparser.o tinyxmlparser.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumcentralizado.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
