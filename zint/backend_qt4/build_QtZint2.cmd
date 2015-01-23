rem start Visual Studio Command Prompt
qmake backend_vcx.pro
msbuild QtZint2.vcxproj /t:Rebuild /p:Configuration=Release