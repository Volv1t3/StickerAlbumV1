/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: Unit Test for: General Utilities Modules For Printing, Debugging, Generation, ETC
?3. Directions: Add more tests here if needed
-----------------------------------------------**/

#include "./../source/Headers/SVV1_Utilities.hpp"
#include "./../source/Implementations/SVV1_Utilities.cpp"


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    UtilPrintLineOnScreen();
    UtilPrintTextWithinScreen("EVEN");
    UtilPrintTextWithinScreen("ODD");
    UtilPrintTextWithinScreen("Universidad San Francisco de Quito");
    UtilPrintingApplicationInformation();
    UtilPrintLongMessageOnPredefLength("This function will print the message in a box of 120 characters in width. The message will be split into words, and each line will contain as many words as can fit within the width. If a word is too long to fit on a line, it will be moved to the next line. The height of the box will depend on the length of the message. If you want to truncate the message when it’s too long, you’ll need to add extra code for that. Let me know if you need help with that too");
}