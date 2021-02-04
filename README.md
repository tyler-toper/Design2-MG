# Design2-MG

Important for merging this big file refactor:

MinGW and SFML have changed places. It's now in the repo. You can safely delete them from your local files (C:/),
wherever you stored it

You must go to File -> Settings -> Build, Execution, Deployment -> Toolchains:

Change the environment filepath to "Design2-MG\Dependencies\mingw64"

Change the debugger filepath to "Design2_MG\Dependencies\mingw64\bin\gdb.exe"

SFML requires no changes since it's inside CMakeLists.txt

The cmake folders and makefiles are now part of gitignore so you can delete those from your branch