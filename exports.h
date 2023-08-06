//  exports.h
//
//	Simple header to instruct the linker to forward function exports to another library.
//

//Below is an example of a forward the Windows Image loader can use to look for the required function 
// 1. Use DLL Export Viewer to load modded DWK.dll from QuocBao Hack
// 2. We want to proxy this modded DWK.dll file, let rename it to another name not suspicious, to hide it from reverse engineer attention,
//      hence we rename it to d3dx9_help.dll
// 3. From DLL Export Viewer, we can proxy like below
//#pragma comment(linker,"/export:FunctionNameA=TARGETMODULE.FunctionNameA,@1")
#define TARGET_MODULE_DLL "d3dx9_help.dll"

#pragma comment(linker,"/export:InstallDWK=d3dx9_help.InstallDWK,@3")
#pragma comment(linker,"/export:TMethodImplementationIntercept=d3dx9_help.TMethodImplementationIntercept,@1")
#pragma comment(linker,"/export:UninstallDWK=d3dx9_help.UninstallDWK,@2")

