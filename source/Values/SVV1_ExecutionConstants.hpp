/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: Constants for Execution, meant to declutter the main and keep everything nicely kept in their own files
?3. Directions: Add different constants needed for runtime analysis and working
-----------------------------------------------**/
#include <cstdlib>
#include <string>
#include <array>
#ifndef STICKERALBUMV1_SVV1_EXECUTIONCONSTANTS_H
#define STICKERALBUMV1_SVV1_EXECUTIONCONSTANTS_H

namespace SVV1_ExecutionConstants
{
    //? Defining the first set of constants: Values for Serialization
    static const std::size_t STICKER_NAME_LENGTH = 20;
    static const std::size_t STICKER_DESCRIPTION_LENGTH = 50;
    static const std::size_t STICKER_VALUE_LENGTH = 10;
    static const int STICKER_MAX_VALUE = 25;
    //? Defining the second set of constants : Values for Pack Generation
    static const int PACK_MAX_STICKERS = 5;
    //? Defining the third set of constants : Values for Album Generation
    static const int ALBUM_MAX_STICKERS = 25;
    //? Defining the fourth set of constants : Values for File Creation && Reading
    static const std::string FILE_NAME = "SVV1StickerAlbumV1DUMP.txt";
    static const int LINE_JUMPS_FOR_ALBUM_STICKERS = 26;
    static const int LINE_JUMPS_FOR_PACK_STICKERS = 6;
}
namespace SVV1_CardNames
{
    const std::array<std::string, 25> CardNames{"Planck", "Bethe",
                                                "Heisenberg", "Goeppert"
            ,"Kaku","Einstein", "Randall", "Rubin", "Curie","Hawking","Joule",
                                                "Teller","Sommerfeld","Noether","Hilbert","Pointcare","Laplace","Cauchy",
                                                "Euler", "Turing","Riemann","Fermat","Germain","Jayam","Godel"};
}
#endif //STICKERALBUMV1_SVV1_EXECUTIONCONSTANTS_H
