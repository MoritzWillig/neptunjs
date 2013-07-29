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
CC=gccBLABLABLA
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/abstractNative.o \
	${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper.o \
	${OBJECTDIR}/src/addins/file/managedFile.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/addins/script/script.o \
	${OBJECTDIR}/src/addins/basicAddin/BasicAddin.o \
	${OBJECTDIR}/src/Permission.o \
	${OBJECTDIR}/src/addins/mysql/sqlMapper.o \
	${OBJECTDIR}/src/addins/file/fileMapper.o \
	${OBJECTDIR}/src/mapper/PermissionChecks.o \
	${OBJECTDIR}/src/etc/SysFunctions.o \
	${OBJECTDIR}/src/addins/outputBuffer/outputBuffer.o \
	${OBJECTDIR}/src/addins/permission/permissionMapper.o \
	${OBJECTDIR}/src/addins/mysql/managedSql.o \
	${OBJECTDIR}/src/addins/script/managedScript.o \
	${OBJECTDIR}/src/comInterface/comunicationInterface.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L'libs/v8_64bit/out/x64.release/obj.target/tools/gyp' -Wl,-Bstatic -lv8_base.x64 -lv8_snapshot -Wl,-rpath='$$ORIGIN/../libs/mysqlconnector64bit/lib' -L./libs/mysqlconnector64bit/lib -Wl,-Bdynamic -lmysqlcppconn

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk bin/neptunjs

bin/neptunjs: ${OBJECTFILES}
	${MKDIR} -p bin
	g++ -pthread -lrt -ldl -o bin/neptunjs ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/abstractNative.o: nbproject/Makefile-${CND_CONF}.mk src/abstractNative.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/abstractNative.o src/abstractNative.cpp

${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper.o: nbproject/Makefile-${CND_CONF}.mk src/addins/outputBuffer/outputBufferMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/outputBuffer
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper.o src/addins/outputBuffer/outputBufferMapper.cpp

${OBJECTDIR}/src/addins/file/managedFile.o: nbproject/Makefile-${CND_CONF}.mk src/addins/file/managedFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/file
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/file/managedFile.o src/addins/file/managedFile.cpp

${OBJECTDIR}/src/main.o: nbproject/Makefile-${CND_CONF}.mk src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/addins/script/script.o: nbproject/Makefile-${CND_CONF}.mk src/addins/script/script.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/script
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/script/script.o src/addins/script/script.cpp

${OBJECTDIR}/src/addins/basicAddin/BasicAddin.o: nbproject/Makefile-${CND_CONF}.mk src/addins/basicAddin/BasicAddin.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/basicAddin
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/basicAddin/BasicAddin.o src/addins/basicAddin/BasicAddin.cpp

${OBJECTDIR}/src/Permission.o: nbproject/Makefile-${CND_CONF}.mk src/Permission.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Permission.o src/Permission.cpp

${OBJECTDIR}/src/addins/mysql/sqlMapper.o: nbproject/Makefile-${CND_CONF}.mk src/addins/mysql/sqlMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/mysql
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/mysql/sqlMapper.o src/addins/mysql/sqlMapper.cpp

${OBJECTDIR}/src/addins/file/fileMapper.o: nbproject/Makefile-${CND_CONF}.mk src/addins/file/fileMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/file
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/file/fileMapper.o src/addins/file/fileMapper.cpp

${OBJECTDIR}/src/mapper/PermissionChecks.o: nbproject/Makefile-${CND_CONF}.mk src/mapper/PermissionChecks.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/mapper
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/mapper/PermissionChecks.o src/mapper/PermissionChecks.cpp

${OBJECTDIR}/src/etc/SysFunctions.o: nbproject/Makefile-${CND_CONF}.mk src/etc/SysFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/etc
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/etc/SysFunctions.o src/etc/SysFunctions.cpp

${OBJECTDIR}/src/addins/outputBuffer/outputBuffer.o: nbproject/Makefile-${CND_CONF}.mk src/addins/outputBuffer/outputBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/outputBuffer
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/outputBuffer/outputBuffer.o src/addins/outputBuffer/outputBuffer.cpp

${OBJECTDIR}/src/addins/permission/permissionMapper.o: nbproject/Makefile-${CND_CONF}.mk src/addins/permission/permissionMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/permission
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/permission/permissionMapper.o src/addins/permission/permissionMapper.cpp

${OBJECTDIR}/src/addins/mysql/managedSql.o: nbproject/Makefile-${CND_CONF}.mk src/addins/mysql/managedSql.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/mysql
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/mysql/managedSql.o src/addins/mysql/managedSql.cpp

${OBJECTDIR}/src/addins/script/managedScript.o: nbproject/Makefile-${CND_CONF}.mk src/addins/script/managedScript.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/script
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/script/managedScript.o src/addins/script/managedScript.cpp

${OBJECTDIR}/src/comInterface/comunicationInterface.o: nbproject/Makefile-${CND_CONF}.mk src/comInterface/comunicationInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/comInterface
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibs/boost_1_51_0 -Isrc -Ilibs/v8_64bit/include -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/comInterface/comunicationInterface.o src/comInterface/comunicationInterface.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} bin/neptunjs

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
