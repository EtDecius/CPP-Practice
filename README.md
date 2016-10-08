# CPP-Practice
Personal solutions for exercises in Programming Principles and Practice Using C++ by Bjarne Stroustrup (2nd edition)

---

###Setup:
* Microsoft Windows 10
* Microsoft Visual Studio 2015 Community
* Microsoft Visual C++ 2015

---

###Notes:
Most projects include the std_lib_facilities.h header by Bjarne Stroustrup, which provides a simplified interface to some C++ features such as exceptions. The file is stored in the root directory. To access it, projects include the file by "stepping back" several folders: *#include "../../../std_lib_facilities.h"*

Chapters 2 - 8 exercises were frequently short or involved code that built on a previous exercise. Many were combined into a single file with functions named for each exercise. The appropriate exercise code can be executed via a simple modification to main() to call the desired function.  
Ex: *Exercise10();  // run Exercise 10 code*

Chapters 12 - 16 utilize FLTK graphic library, available at http://www.fltk.org/index.php. The projects also use several files by Bjarne that implement a simple interface to FLTK. Like the std_lib_facilties.h header, these files are stored in the root directory and accessed by stepping back to the root folder. For my setup, I also needed to add those files to my project as resources in order for the code to compile.
