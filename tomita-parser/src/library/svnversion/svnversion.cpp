#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define FROM_IMPL
#include "svnversion.h"

#ifndef IGNORE_SVNVERSION
#   include "svnversion_data.h"
#endif

extern "C" const char* GetProgramSvnVersion() {
#if defined(REVISION)
    // for package systems generating from svn export but providing REVISION macro
#   define REVISION2(x) #x
#   define REVISION3(x) REVISION2(x)
#   define REVISION4 REVISION3(REVISION)
#   define REVISIONINFO "r" REVISION4
#   if defined(PROGRAM_VERSION)
        return PROGRAM_VERSION "\n\n" REVISIONINFO;
#   else
        return REVISIONINFO" "__DATE__" "__TIME__;
#   endif
#elif defined(GIT_TAG)
#   if defined(PROGRAM_VERSION)
        return PROGRAM_VERSION "\n\n" GIT_TAG;
#   else
        return GIT_TAG" "__DATE__" "__TIME__;
#   endif
#elif defined(PROGRAM_VERSION)
    return PROGRAM_VERSION;
#else
    return "No program version found";
#endif
}

extern "C" const char* GetProgramVersionTag() {
#if defined(SVN_REVISION)
    return SVN_REVISION;
#elif defined(GIT_TAG)
    return GIT_TAG;
#endif
}

extern "C" void PrintProgramSvnVersion() {
    puts(GetProgramSvnVersion());
}

extern "C" void PrintSvnVersionAndExit0() {
    PrintProgramSvnVersion();
    exit(0);
}

extern "C" const char* GetArcadiaSourcePath() {
#if defined(ARCADIA_SOURCE_PATH)
    return ARCADIA_SOURCE_PATH;
#else
    return "";
#endif
}

extern "C" const char* GetArcadiaSourceUrl() {
#if defined(ARCADIA_SOURCE_URL)
    return ARCADIA_SOURCE_URL;
#else
    return "";
#endif
}

extern "C" const char* GetArcadiaLastChange() {
#if defined(ARCADIA_SOURCE_LAST_CHANGE)
    return ARCADIA_SOURCE_LAST_CHANGE;
#else
    return "";
#endif
}

extern "C" const char* GetArcadiaLastAuthor() {
#if defined(ARCADIA_SOURCE_LAST_AUTHOR)
    return ARCADIA_SOURCE_LAST_AUTHOR;
#else
    return "";
#endif
}

extern "C" int GetProgramSvnRevision() {
#if defined(ARCADIA_SOURCE_REVISION)
    return atoi(ARCADIA_SOURCE_REVISION);
#else
    return 0;
#endif
}

extern "C" const char* GetProgramScmData() {
#if defined(SCM_DATA)
    return SCM_DATA;
#else
    return "";
#endif
}

extern "C" const char* GetProgramBuildUser() {
#if defined(BUILD_USER)
    return BUILD_USER;
#else
    return "";
#endif
}

extern "C" const char* GetProgramBuildHost() {
#if defined(BUILD_HOST)
    return BUILD_HOST;
#else
    return "";
#endif
}

extern "C" const char* GetProgramBuildDate() {
#if defined(BUILD_DATE)
    return BUILD_DATE;
#else
    return "";
#endif
}

extern "C" void PrintSvnVersionAndExit(int argc, char *argv[]) {
    if (argc == 2 && !strcmp(argv[1], "--version")) {
        PrintSvnVersionAndExit0();
    }
}

#undef FROM_IMPL
