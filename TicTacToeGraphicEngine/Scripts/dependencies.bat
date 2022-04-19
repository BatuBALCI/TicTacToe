REM Create directories.
if not exist "..\x64" mkdir "..\x64"
if not exist "..\x64\Debug" mkdir "..\x64\Debug"
if not exist "..\x64\Release" mkdir "..\x64\Release"

mklink "..\x64\Debug\TicTacToeEngine.lib" "..\..\ThreeTEngine\TicTacToeEngine\x64\Debug\TicTacToeEngine.lib"
mklink "..\x64\Release\TicTacToeEngine.lib" "..\..\ThreeTEngine\TicTacToeEngine\x64\Release\TicTacToeEngine.lib"

