pacerr
======

*PACERR is an arduino based robot that takes commands from a Bluetooth source and translates them into other messages (motor movements).*

Pacerr can take commands from any Bluetooth terminal as well as the Blackberry 10 app included in the downloads. The app is just a polished version of the simple bluetoothchat example released by Blackberry themselves. I have also included the code for two possible Android apps you can use. They are in the trunk folder of the source. I have not compiled them and you need to do that on your own. 

In the GCode project, I will include the necessary bare basic code required to only MOVE the rover. I will also include several different codes you can apply. You can, by all means, use the codes and build upon them or just use them as is to make your own Pacerr. I will also include files such as .pcb and other schematic for the project as I want to make it as easy as possible to have fun with arduino and BT without going through many hassles. All I ask for is a bit of credit :)

Note: All code is MOSTLY my own the very basic code will most likely be found floating around in other places simply because it is super basic. Some of the code has been created by looking around at different examples and building upon them (as I hope you will do). Nonetheless, the original owner of these specific pieces of code is me.

Make sure you read the wiki pages for information on the project.

As well as reading the wiki pages. Make sure you also do some other reading on Arduino as these tutorials are NOT meant to make you super arduino experts.

If you have any questions, don't hesitate to email the owner of the project.

==Note:==

The BlackBerry app can be found here: http://appworld.blackberry.com/webstore/content/26018872/

It now has button control as well as terminal control. The commands for the button control are:

F - Forward
B - Backward
L - Left
R - Right
S - Stop
H - Horn 

http://pacerr.googlecode.com/files/Pacerr1.jpg
http://pacerr.googlecode.com/files/Pacerr2.jpg
