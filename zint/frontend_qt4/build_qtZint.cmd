rem start Visual Studio Command Prompt
qmake frontend_vcx.pro
msbuild qtZint.vcxproj /t:Rebuild /p:Configuration=Release