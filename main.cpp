/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: Main Application Entry Point
?3. Directions: Every File must be added here, there is no need for implementations since it is managed by Cmake
-----------------------------------------------**/
//----------------Preprocessing Directives--------------
#include "./source/Headers/SVV1_Album.hpp"
#include "./source/Implementations/SVV1_Album.cpp"
#include "./source/Headers/SVV1_StickerPack.hpp"
#include "./source/Implementations/SVV1_StickerPack.cpp"
#include "./source/Headers/SVV1_GeneralSticker.hpp"
#include "./source/Implementations/SVV1_GeneralSticker.cpp"
#include "./source/Headers/SVV1_Utilities.hpp"
#include "./source/Implementations/SVV1_Utilities.cpp"
#include "./source/Values/SVV1_ExecutionConstants.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
//------------------------------------------------------

int main() {

    //? Define local variables for holding: stickers, packs, albums
    std::vector<SVV1_GeneralSticker> stickerHolder;
    std::vector<SVV1_StickerPack> stickerPacksHolder;
    std::vector<SVV1_Album> stickerAlbumsHolder;

    //? Initial Presentation Section
    UtilPrintLineOnScreen();
    UtilPrintingApplicationInformation();
    system("pause");
    system("cls");
    UtilPrintLineOnScreen();
    UtilPrintTextWithinScreen("Universidad San Francisco de Quito");
    UtilPrintTextWithinScreen("StickerAlbumV1");

    //?File Checking section
    std::ifstream file("text.txt", std::ios::in);
    if (!file.is_open())
    {
        std::cerr <<"file not  opened" << std::endl;
    }
    //Call to CLass or Function that Loads the FIle
}
