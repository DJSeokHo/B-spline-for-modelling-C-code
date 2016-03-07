# Microsoft Developer Studio Project File - Name="3D_view_FPbody_model" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=3D_view_FPbody_model - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "3D_view_FPbody_model.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "3D_view_FPbody_model.mak" CFG="3D_view_FPbody_model - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "3D_view_FPbody_model - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "3D_view_FPbody_model - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "3D_view_FPbody_model - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "3D_view_FPbody_model - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glut32.lib glaux.lib /nologo /stack:0x3b9ac9ff /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "3D_view_FPbody_model - Win32 Release"
# Name "3D_view_FPbody_model - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3D_view_FPbody_model.cpp
# End Source File
# Begin Source File

SOURCE=.\3D_view_FPbody_model.rc
# End Source File
# Begin Source File

SOURCE=.\3D_view_FPbody_modelDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\3D_view_FPbody_modelView.cpp
# End Source File
# Begin Source File

SOURCE=.\ALTBSPLINE_XY.cpp
# End Source File
# Begin Source File

SOURCE=.\ALTBSPLINE_XZ.cpp
# End Source File
# Begin Source File

SOURCE=.\ALTBSPLINE_YZ.cpp
# End Source File
# Begin Source File

SOURCE=.\ALTCP_XY.cpp
# End Source File
# Begin Source File

SOURCE=.\ALTCP_XZ.cpp
# End Source File
# Begin Source File

SOURCE=.\ALTCP_YZ.cpp
# End Source File
# Begin Source File

SOURCE=.\BP.cpp
# End Source File
# Begin Source File

SOURCE=.\BSPLINE_XY.cpp
# End Source File
# Begin Source File

SOURCE=.\BSPLINE_XZ.cpp
# End Source File
# Begin Source File

SOURCE=.\BSPLINE_YZ.cpp
# End Source File
# Begin Source File

SOURCE=.\GET_METHOD.cpp
# End Source File
# Begin Source File

SOURCE=.\m_coordinate.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\NumForIndex.cpp
# End Source File
# Begin Source File

SOURCE=.\Operat.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VP.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3D_view_FPbody_model.h
# End Source File
# Begin Source File

SOURCE=.\3D_view_FPbody_modelDoc.h
# End Source File
# Begin Source File

SOURCE=.\3D_view_FPbody_modelView.h
# End Source File
# Begin Source File

SOURCE=.\ALTBSPLINE_XY.h
# End Source File
# Begin Source File

SOURCE=.\ALTBSPLINE_XZ.h
# End Source File
# Begin Source File

SOURCE=.\ALTBSPLINE_YZ.h
# End Source File
# Begin Source File

SOURCE=.\ALTCP_XY.h
# End Source File
# Begin Source File

SOURCE=.\ALTCP_XZ.h
# End Source File
# Begin Source File

SOURCE=.\ALTCP_YZ.h
# End Source File
# Begin Source File

SOURCE=.\BP.h
# End Source File
# Begin Source File

SOURCE=.\BSPLINE_XY.h
# End Source File
# Begin Source File

SOURCE=.\BSPLINE_XZ.h
# End Source File
# Begin Source File

SOURCE=.\BSPLINE_YZ.h
# End Source File
# Begin Source File

SOURCE=.\GET_METHOD.h
# End Source File
# Begin Source File

SOURCE=.\m_coordinate.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\NumForIndex.h
# End Source File
# Begin Source File

SOURCE=.\Operat.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VP.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\3D_view_FPbody_model.ico
# End Source File
# Begin Source File

SOURCE=.\res\3D_view_FPbody_model.rc2
# End Source File
# Begin Source File

SOURCE=.\res\3D_view_FPbody_modelDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
