### USEFEUL info

When including <sqlite3.h> 

for windows visual studio 19, do the following:

download the amalgmation files but also the dll files 
use https://sqlite.org/2021/sqlite-dll-win32-x86-3360000.zip, 
which gives a .dll and a .def file. 
Copy them to your project directory and then open up a 
Visual Studio command prompt (terminal in the View menu). 
Browse to the directory that you've copied the files to and 
type LIB /DEF:sqlite3.def. 
This will create a library file for VS to use. 
Add this file to your project dependencies at 
Project Properties -> Configuration Properties -> Linker -> Input -> Additional Dependencies 
(you'll have to type it in manually as you can't browse). 
Compiling in Visual Studio should now work successfully.

For linux
sudo apt-get install sqlite3
