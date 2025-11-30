# Rock Paper Scissors 
<b>RPS</b> is a the classic version of Rock Paper Scissors that logs output to a csv file.  

This is a very simple program that only has one mode, User vs Computer. 
It was designed to provide a random data set to be used with other projects.

<b>RPS</b> was written in C to be able to complie for cross platform.

<b>Main files:</b>
There are three executible files in the main folder, they were compiled using GCC. Written for a Debian based linux machine, not tested on any other OS.
- rps_cli = executible file for the linux command line interface
- rps_cli-01 = executible file for the linux command line interface with ncurses GUI
- rps_gui = executible file for the graphical user interface using GTK3 
  
<b>Source:</b>
There are three source files in the "src" folder.
- rps_cli.c = source file for use in a linux based command line interface
    - compile with: $ gcc rps_cli.c -o rps_cli 
    - run with: $./rps_cli 
      
- rps_cli-01.c = source file for use in a linux based command line interface with basic GUI with ncurses
    - compile with: $ gcc rps_cli-01.c -o rps_cli-01 -lncurses
    - run with: $./rps_cli-01
      
- rps_gui.c = source file for a graphical user interface in linux using GTK3
    - compile with: $ gcc rps_gui.c -o rps_gui `pkg-config --cflags --libs gtk+-3.0`
    - run with: $./rps_gui

<b>Logging:</b>
CSV logs are placed in the "logs" folder to provide a single point for references when parsing the data is needed. 
Two csv files are located in the logs folder that complement the version of the program that uses it.
- rps.csv = used by both of the the command line interface versions
- rps_gui.csv = used by the graphical used interface version
