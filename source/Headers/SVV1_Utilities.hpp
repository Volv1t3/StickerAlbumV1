/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: General Utilities Modules For Printing, Debugging, Generation, ETC
?3. Directions: Functional programming module, more functions will be added here as the project progresses
-----------------------------------------------**/
#include <string>

#ifndef STICKERALBUMV1_SVV1_UTILITIES_HPP
#define STICKERALBUMV1_SVV1_UTILITIES_HPP


/*Function to print a general 120 character line on the screen*/
[[maybe_unused]] void UtilPrintLineOnScreen();
/*Function to print a general 120 character line in the screen with a message centered along it*/
[[maybe_unused]] void UtilPrintTextWithinScreen(const std::string& MessageToPrint);
/*Function to print initial message and general program information*/
[[maybe_unused]] void UtilPrintingApplicationInformation();
[[maybe_unused]] void UtilPrintLongMessageOnPredefLength(std::string MessageToPrint);
[[maybe_unused, nodiscard]] std::string UtilReturnLineOnScreen();


#endif //STICKERALBUMV1_SVV1_UTILITIES_HPP
