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
	${OBJECTDIR}/src/addins/script/managedScript.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

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
LDLIBSOPTIONS=-Wl,-rpath,libs -Wl,-rpath,libs/mysqlconnector64bit/lib libs/v8_64bit/out/x64.release/obj.target/tools/gyp/libv8_base.a libs/v8_64bit/out/x64.release/obj.target/tools/gyp/libv8_snapshot.a libs/mysqlconnector64bit/lib/libmysqlcppconn.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk bin/neptunjsx64

bin/neptunjsx64: libs/v8_64bit/out/x64.release/obj.target/tools/gyp/libv8_base.a

bin/neptunjsx64: libs/v8_64bit/out/x64.release/obj.target/tools/gyp/libv8_snapshot.a

bin/neptunjsx64: libs/mysqlconnector64bit/lib/libmysqlcppconn.so

bin/neptunjsx64: ${OBJECTFILES}
	${MKDIR} -p bin
	g++ -pthread -lrt -ldl -o bin/neptunjsx64 ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/abstractNative.o: nbproject/Makefile-${CND_CONF}.mk src/abstractNative.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/abstractNative.o src/abstractNative.cpp

${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper.o: nbproject/Makefile-${CND_CONF}.mk src/addins/outputBuffer/outputBufferMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/outputBuffer
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper.o src/addins/outputBuffer/outputBufferMapper.cpp

${OBJECTDIR}/src/addins/file/managedFile.o: nbproject/Makefile-${CND_CONF}.mk src/addins/file/managedFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/file
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/file/managedFile.o src/addins/file/managedFile.cpp

${OBJECTDIR}/src/main.o: nbproject/Makefile-${CND_CONF}.mk src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/addins/script/script.o: nbproject/Makefile-${CND_CONF}.mk src/addins/script/script.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/script
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/script/script.o src/addins/script/script.cpp

${OBJECTDIR}/src/addins/basicAddin/BasicAddin.o: nbproject/Makefile-${CND_CONF}.mk src/addins/basicAddin/BasicAddin.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/basicAddin
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/basicAddin/BasicAddin.o src/addins/basicAddin/BasicAddin.cpp

${OBJECTDIR}/src/Permission.o: nbproject/Makefile-${CND_CONF}.mk src/Permission.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Permission.o src/Permission.cpp

${OBJECTDIR}/src/addins/mysql/sqlMapper.o: nbproject/Makefile-${CND_CONF}.mk src/addins/mysql/sqlMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/mysql
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/mysql/sqlMapper.o src/addins/mysql/sqlMapper.cpp

${OBJECTDIR}/src/addins/file/fileMapper.o: nbproject/Makefile-${CND_CONF}.mk src/addins/file/fileMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/file
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/file/fileMapper.o src/addins/file/fileMapper.cpp

${OBJECTDIR}/src/mapper/PermissionChecks.o: nbproject/Makefile-${CND_CONF}.mk src/mapper/PermissionChecks.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/mapper
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/mapper/PermissionChecks.o src/mapper/PermissionChecks.cpp

${OBJECTDIR}/src/etc/SysFunctions.o: nbproject/Makefile-${CND_CONF}.mk src/etc/SysFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/etc
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/etc/SysFunctions.o src/etc/SysFunctions.cpp

${OBJECTDIR}/src/addins/outputBuffer/outputBuffer.o: nbproject/Makefile-${CND_CONF}.mk src/addins/outputBuffer/outputBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/outputBuffer
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/outputBuffer/outputBuffer.o src/addins/outputBuffer/outputBuffer.cpp

${OBJECTDIR}/src/addins/permission/permissionMapper.o: nbproject/Makefile-${CND_CONF}.mk src/addins/permission/permissionMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/permission
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/permission/permissionMapper.o src/addins/permission/permissionMapper.cpp

${OBJECTDIR}/src/addins/mysql/managedSql.o: nbproject/Makefile-${CND_CONF}.mk src/addins/mysql/managedSql.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/mysql
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/mysql/managedSql.o src/addins/mysql/managedSql.cpp

${OBJECTDIR}/src/addins/script/managedScript.o: nbproject/Makefile-${CND_CONF}.mk src/addins/script/managedScript.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/script
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/script/managedScript.o src/addins/script/managedScript.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/managedFileTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/managedFileTest.o: tests/managedFileTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -MMD -MP -MF $@.d -o ${TESTDIR}/tests/managedFileTest.o tests/managedFileTest.cpp


${OBJECTDIR}/src/abstractNative_nomain.o: ${OBJECTDIR}/src/abstractNative.o src/abstractNative.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/abstractNative.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/abstractNative_nomain.o src/abstractNative.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/abstractNative.o ${OBJECTDIR}/src/abstractNative_nomain.o;\
	fi

${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper_nomain.o: ${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper.o src/addins/outputBuffer/outputBufferMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/outputBuffer
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper_nomain.o src/addins/outputBuffer/outputBufferMapper.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper.o ${OBJECTDIR}/src/addins/outputBuffer/outputBufferMapper_nomain.o;\
	fi

${OBJECTDIR}/src/addins/file/managedFile_nomain.o: ${OBJECTDIR}/src/addins/file/managedFile.o src/addins/file/managedFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/file
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/addins/file/managedFile.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/file/managedFile_nomain.o src/addins/file/managedFile.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/addins/file/managedFile.o ${OBJECTDIR}/src/addins/file/managedFile_nomain.o;\
	fi

${OBJECTDIR}/src/main_nomain.o: ${OBJECTDIR}/src/main.o src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main_nomain.o src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/main_nomain.o;\
	fi

${OBJECTDIR}/src/addins/script/script_nomain.o: ${OBJECTDIR}/src/addins/script/script.o src/addins/script/script.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/script
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/addins/script/script.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/script/script_nomain.o src/addins/script/script.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/addins/script/script.o ${OBJECTDIR}/src/addins/script/script_nomain.o;\
	fi

${OBJECTDIR}/src/addins/basicAddin/BasicAddin_nomain.o: ${OBJECTDIR}/src/addins/basicAddin/BasicAddin.o src/addins/basicAddin/BasicAddin.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/basicAddin
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/addins/basicAddin/BasicAddin.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/basicAddin/BasicAddin_nomain.o src/addins/basicAddin/BasicAddin.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/addins/basicAddin/BasicAddin.o ${OBJECTDIR}/src/addins/basicAddin/BasicAddin_nomain.o;\
	fi

${OBJECTDIR}/src/Permission_nomain.o: ${OBJECTDIR}/src/Permission.o src/Permission.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Permission.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Permission_nomain.o src/Permission.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Permission.o ${OBJECTDIR}/src/Permission_nomain.o;\
	fi

${OBJECTDIR}/src/addins/mysql/sqlMapper_nomain.o: ${OBJECTDIR}/src/addins/mysql/sqlMapper.o src/addins/mysql/sqlMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/mysql
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/addins/mysql/sqlMapper.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/mysql/sqlMapper_nomain.o src/addins/mysql/sqlMapper.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/addins/mysql/sqlMapper.o ${OBJECTDIR}/src/addins/mysql/sqlMapper_nomain.o;\
	fi

${OBJECTDIR}/src/addins/file/fileMapper_nomain.o: ${OBJECTDIR}/src/addins/file/fileMapper.o src/addins/file/fileMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/file
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/addins/file/fileMapper.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/file/fileMapper_nomain.o src/addins/file/fileMapper.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/addins/file/fileMapper.o ${OBJECTDIR}/src/addins/file/fileMapper_nomain.o;\
	fi

${OBJECTDIR}/src/mapper/PermissionChecks_nomain.o: ${OBJECTDIR}/src/mapper/PermissionChecks.o src/mapper/PermissionChecks.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/mapper
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/mapper/PermissionChecks.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/mapper/PermissionChecks_nomain.o src/mapper/PermissionChecks.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/mapper/PermissionChecks.o ${OBJECTDIR}/src/mapper/PermissionChecks_nomain.o;\
	fi

${OBJECTDIR}/src/etc/SysFunctions_nomain.o: ${OBJECTDIR}/src/etc/SysFunctions.o src/etc/SysFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/etc
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/etc/SysFunctions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/etc/SysFunctions_nomain.o src/etc/SysFunctions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/etc/SysFunctions.o ${OBJECTDIR}/src/etc/SysFunctions_nomain.o;\
	fi

${OBJECTDIR}/src/addins/outputBuffer/outputBuffer_nomain.o: ${OBJECTDIR}/src/addins/outputBuffer/outputBuffer.o src/addins/outputBuffer/outputBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/outputBuffer
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/addins/outputBuffer/outputBuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/outputBuffer/outputBuffer_nomain.o src/addins/outputBuffer/outputBuffer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/addins/outputBuffer/outputBuffer.o ${OBJECTDIR}/src/addins/outputBuffer/outputBuffer_nomain.o;\
	fi

${OBJECTDIR}/src/addins/permission/permissionMapper_nomain.o: ${OBJECTDIR}/src/addins/permission/permissionMapper.o src/addins/permission/permissionMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/permission
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/addins/permission/permissionMapper.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/permission/permissionMapper_nomain.o src/addins/permission/permissionMapper.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/addins/permission/permissionMapper.o ${OBJECTDIR}/src/addins/permission/permissionMapper_nomain.o;\
	fi

${OBJECTDIR}/src/addins/mysql/managedSql_nomain.o: ${OBJECTDIR}/src/addins/mysql/managedSql.o src/addins/mysql/managedSql.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/mysql
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/addins/mysql/managedSql.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/mysql/managedSql_nomain.o src/addins/mysql/managedSql.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/addins/mysql/managedSql.o ${OBJECTDIR}/src/addins/mysql/managedSql_nomain.o;\
	fi

${OBJECTDIR}/src/addins/script/managedScript_nomain.o: ${OBJECTDIR}/src/addins/script/managedScript.o src/addins/script/managedScript.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/addins/script
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/addins/script/managedScript.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -I. -Ilibs/boost_1_51_0 -Ilibs/mysqlconnector64bit/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/addins/script/managedScript_nomain.o src/addins/script/managedScript.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/addins/script/managedScript.o ${OBJECTDIR}/src/addins/script/managedScript_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} bin/neptunjsx64

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
