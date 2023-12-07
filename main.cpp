/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: Main Application Entry Point
?3. Directions: Every File must be added here, there is no need for implementations since it is managed by Cmake
-----------------------------------------------**/
//----------------Preprocessing Directives--------------
#include "./source/Headers/SVV1_Album.hpp"
#include "./source/Headers/SVV1_StickerPack.hpp"
#include "./source/Headers/SVV1_GeneralSticker.hpp"
#include "./source/Headers/SVV1_Utilities.hpp"
#include "./source/Values/SVV1_ExecutionConstants.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
#include <limits>
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

    std::string FILEPATH = SVV1_ExecutionConstants::FILE_NAME;
    //?File Checking section
    std::cout << FILEPATH << std::endl;
    std::fstream inputModelAlbumData(FILEPATH, std::ios::in);
    if (inputModelAlbumData.is_open()){
        if (std::fstream::traits_type::eof() == inputModelAlbumData.peek()) {
            UtilPrintTextWithinScreen("Archivo de Registro no Detectado");
            UtilPrintLongMessageOnPredefLength(
                    "No hemos detectado un registro de una partida anterior para poder cargarla en el programa. Sim embargo, usted puede jugar y sus datos se guardaran automaticamente para una proxima ejecucion");
            UtilPrintTextWithinScreen("Presione cualquier tecla para continuar");
            system("pause");
            system("cls");
        } else {
            UtilPrintTextWithinScreen("Archivo de Registro Detectado");
            UtilPrintLongMessageOnPredefLength("Hemos detectado un registro de una partida anterior para poder cargarla en el programa. Si desea realizar este cargo de datos, seleccion 1, si no quiere hacerlo seleccione 2.\n"
                                               "1. Cargar Archivo De Registro (1). \n"
                                               "2. No Cargar Archivo de Registro (2).\n"
                                               "\nSu eleccion: ");
            unsigned int userSelectionForFileLoading{0};
            //? User input for files
            do {
                while (!(std::cin >> userSelectionForFileLoading))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    UtilPrintLongMessageOnPredefLength("Favor ingrese un valor numerico para esta seleccion, el programa no continuara hasta recibir un input valido.\n");
                }
            }
            while (userSelectionForFileLoading != 1 && userSelectionForFileLoading != 2);

            //? Switch case for user input
            switch(userSelectionForFileLoading)
            {
                case 1 /* User Wants to Load in the File*/:
                {
                    //?Method Already Defined inside of Unit Tests Imported Here
                    try {
                        std::string line;
                        std::getline(inputModelAlbumData, line);
                        //? Reading the first line which is the amount of albums created
                        auto amount_albums = std::stoi(line);
                        std::cout << "Amount of albums created: " << amount_albums << std::endl;
                        std::vector<SVV1_Album> abumsRead;
                        for (size_t index = 0; index < amount_albums; index +=1) { abumsRead.emplace_back(); }
                        //? Reading the data inside of the albums

                        for (size_t j =0; j < amount_albums; j +=1)
                        {
                            std::getline(inputModelAlbumData, line);
                            if (std::equal(line.begin(), line.end(), "A")) {;}
                            while (line.at(0) == 'S')
                            {
                                std::cout << line << std::endl;
                                abumsRead.at(j).emplaceAStickerOnAlbum(SVV1_GeneralSticker(line));
                                std::getline(inputModelAlbumData, line);
                            }
                        }

                        for (auto const& value: abumsRead)
                        {
                            std::cout << "DESERIALIZED ALBUM" << std::endl;
                            std::cout << value.serializingAlbum() << std::endl;
                        }
//                        //? Reading the amount of packs created
//                        std::getline(inputModelAlbumData, line);
//                        std::cout << line << std::endl;
//                        auto amount_packs = std::stoi(line);
//                        std::cout << "Amount of packs created: " << amount_packs << std::endl;
//                        std::vector<SVV1_StickerPack> packsRead;
//                        for (size_t index = 0; index < amount_packs; index +=1) { packsRead.emplace_back(); }
//                        //? Reading the data inside of the packs
//                        for (size_t j =0; j < amount_packs; j +=1)
//                        {
//                            for (size_t index = 0; index < SVV1_ExecutionConstants::LINE_JUMPS_FOR_PACK_STICKERS; index += 1) {
//                                std::getline(inputModelAlbumData, line);
//                                if (std::equal(line.begin(), line.end(), "P")) {
//                                    continue;
//                                }
//                                packsRead.at(j).addStickerToPack(SVV1_GeneralSticker(line));
//                            }
//                        }
//                        //?Printing generated packs
//                        for(auto const& value: packsRead)
//                        {
//                            std::cout << "DESERIALIZED PACK" << std::endl;
//                            std::cout << value.getSerializedPack() << std::endl;
//                        }
                    }
                    catch(...)
                    {
                        std::cout << "Errors when reading the file, it must have been corrupted, we have to delete it for the program to work" << std::endl;
                    }
                }
            }
        }
    }

    //Call to CLass or Function that Loads the FIle
}
