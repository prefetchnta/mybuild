Zint can be built with and without PNG support.
To disable PNG support, add NO_PNG prepoocessor define into Visual Studio project files.

To enable PNG support, zlib and libpng libraries are necessary.
Download zlib source form http://zlib.net
Download libpng source code from http://www.libpng.org/pub/png/libpng.html 

Zint 2.4.1 is linked with zlib 1.2.5 and linpng 1.4.5

Unpack downloaded archives.
Open .\win32\vcx\zlib.props and .\win32\vcx\libpng.props files.
Set <LpngSrcDir> element content to unpacked libpng path (absolute or relative).
Set <ZlibSrcDir> element content to unpacked zlib path (absolute or relative).

Open Visual Studio (Express) and build zint.

Zint can be built from command line:
Start Windows SDK Command Prompt or Visual Studio Command Prompt.

cd to win32 directory

build zlib, libpng, libzint and zint:

msbuild zlib.vcxproj /t:Build /p:Configuration=Release
msbuild libpng.vcxproj /t:Build /p:Configuration=Release
msbuild libzint.vcxproj /t:Build /p:Configuration=Release
msbuild zint.vcxproj /t:Build /p:Configuration=Release

zlib125.dll, libpng14.dll, zint.dll and zint.exe are in the Relase directory.
To distribute zint.exe, all 3 dlls need to be shipped with zint.exe.
