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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/nbproject/ArbreAbstrait.o \
	${OBJECTDIR}/nbproject/Interpreteur.o \
	${OBJECTDIR}/nbproject/Lecteur.o \
	${OBJECTDIR}/nbproject/Symbole.o \
	${OBJECTDIR}/nbproject/SymboleValue.o \
	${OBJECTDIR}/nbproject/TableSymboles.o \
	${OBJECTDIR}/nbproject/main.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp5m3105

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp5m3105: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp5m3105 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/nbproject/ArbreAbstrait.o: nbproject/ArbreAbstrait.cpp 
	${MKDIR} -p ${OBJECTDIR}/nbproject
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/ArbreAbstrait.o nbproject/ArbreAbstrait.cpp

${OBJECTDIR}/nbproject/Interpreteur.o: nbproject/Interpreteur.cpp 
	${MKDIR} -p ${OBJECTDIR}/nbproject
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/Interpreteur.o nbproject/Interpreteur.cpp

${OBJECTDIR}/nbproject/Lecteur.o: nbproject/Lecteur.cpp 
	${MKDIR} -p ${OBJECTDIR}/nbproject
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/Lecteur.o nbproject/Lecteur.cpp

${OBJECTDIR}/nbproject/Symbole.o: nbproject/Symbole.cpp 
	${MKDIR} -p ${OBJECTDIR}/nbproject
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/Symbole.o nbproject/Symbole.cpp

${OBJECTDIR}/nbproject/SymboleValue.o: nbproject/SymboleValue.cpp 
	${MKDIR} -p ${OBJECTDIR}/nbproject
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/SymboleValue.o nbproject/SymboleValue.cpp

${OBJECTDIR}/nbproject/TableSymboles.o: nbproject/TableSymboles.cpp 
	${MKDIR} -p ${OBJECTDIR}/nbproject
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/TableSymboles.o nbproject/TableSymboles.cpp

${OBJECTDIR}/nbproject/main.o: nbproject/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/nbproject
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/main.o nbproject/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp5m3105

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
