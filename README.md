# Music Shop Win32 based Application
What started as a computer shop, ended up to be a Indian Music Instrument Shop. 
The code is pretty raw, written in the initial stages, while learning Win32, but runs successfuly. I realized later the need of rc file. Even the data is stored in the code as struct, for which a database should have been used. 
Will clean the code accordingly as soon as possible. 

# APPLICATION LAYOUT
1. The initial screen displayed is a splash screen. // Font rework is required here, but placement is complete.
2. Next is the main screen, where all the options are selected. The selection of first level of Combo Box will trigger generation of second level of combo box. // Here instead of CreateWindow, rc file could have been used, also as mentioned earlier, a database could be used to access data.
3. Last is the receipt screen.

