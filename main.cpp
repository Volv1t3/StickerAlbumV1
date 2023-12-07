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
#include <sys/file.h>
#include <windows.h>
#include <format>
#include <algorithm>
#include <random>
//------------------------------------------------------

int main() {

    //? Define local variables for holding: stickers, packs, albums
    static bool HasLoadedFile = false;
    std::vector<SVV1_GeneralSticker> stickerHolder;
    std::vector<SVV1_StickerPack> UnopenedStickerPacks;
    std::vector<SVV1_StickerPack> OpenedStickerPacks;
    std::vector<SVV1_Album> stickerAlbumsHolder;

    //? Initial Presentation Section
    UtilPrintLineOnScreen();
    UtilPrintingApplicationInformation();
    system("pause");
    system("cls");
    UtilPrintLineOnScreen();
    UtilPrintTextWithinScreen("Universidad San Francisco de Quito");
    UtilPrintTextWithinScreen("StickerAlbumV1 - Matematicos Famosos");

    std::string FILEPATH = SVV1_ExecutionConstants::FILE_NAME;
    //?File Checking section
    std::fstream inputModelAlbumData(FILEPATH, std::ios::in);
    if (inputModelAlbumData.is_open()) {
        if (std::fstream::traits_type::eof() == inputModelAlbumData.peek()) {
            UtilPrintTextWithinScreen("Archivo de Registro Vacio");
            UtilPrintLongMessageOnPredefLength(
                    "No hemos detectado valores en el registro de una partida anterior para poder cargarla en el programa. Sim embargo, usted puede jugar y sus datos se guardaran automaticamente para una proxima ejecucion");
            UtilPrintTextWithinScreen("Presione cualquier tecla para continuar");
            system("pause");
            system("cls");
        } else {
            UtilPrintTextWithinScreen("Archivo de Registro Detectado");
            UtilPrintLongMessageOnPredefLength(
                    "Hemos detectado un registro de una partida anterior para poder cargarla en el programa. Si desea realizar este cargo de datos, seleccion 1, si no quiere hacerlo seleccione 2.\n"
                    "1. Cargar Archivo De Registro (1).\n"
                    "2. No Cargar Archivo de Registro (2).\n"
                    "\nSu eleccion: ");
            unsigned int userSelectionForFileLoading{0};
            //? User input for files
            do {
                while (!(std::cin >> userSelectionForFileLoading)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ingrese por favor un valor numerico, correspondiente al menu anterior" << std::endl;
                }
            } while (userSelectionForFileLoading != 1 && userSelectionForFileLoading != 2);

            //? Switch case for user input
            switch (userSelectionForFileLoading) {
                case 1 /* User Wants to Load in the File*/: {
                    //?Method Already Defined inside of Unit Tests Imported Here
                    try {
                        std::string line;
                        std::getline(inputModelAlbumData, line);
                        //? Reading the first line which is the amount of albums created
                        auto amount_albums = std::stoi(line);
                        for (size_t index = 0;
                             index < amount_albums; index += 1) { stickerAlbumsHolder.emplace_back(); }
                        //? Reading the data inside of the albums
                        /*Method has been adapted to provide for flexibility for incomplete albums, looping as long as it finds lines that
                         start with the letter S*/
                        for (size_t j = 0; j < amount_albums; j += 1) {
                            bool foundStickerConstant = false;
                            while (std::getline(inputModelAlbumData, line) && !foundStickerConstant) {
                                if (!line.empty() && line.at(0) == 'A') { continue; }
                                if (!line.empty() && line.at(0) == 'S') {
                                    foundStickerConstant = true;
                                    stickerAlbumsHolder.at(j).emplaceAStickerOnAlbum(SVV1_GeneralSticker(line));
                                }
                            }
                            while (foundStickerConstant && !line.empty() && line.at(0) == 'S') {
                                std::cout << line << std::endl;
                                stickerAlbumsHolder.at(j).emplaceAStickerOnAlbum(SVV1_GeneralSticker(line));
                                if (!std::getline(inputModelAlbumData, line)) { break; }
                                if (!line.empty() && line.at(0) != 'S') { break; }
                            }

                            //? Receiving data form repeated section
                            bool foundRepeatedConstant = false;
                            while (std::getline(inputModelAlbumData, line) && !foundRepeatedConstant) {
                                if (!line.empty() && line.at(0) == 'R') {
                                    continue;
                                }
                                if (!line.empty() && line.at(0) == 'S') {
                                    foundRepeatedConstant = true;
                                    stickerAlbumsHolder.at(j).emplaceRepeatedSticker(SVV1_GeneralSticker(line));
                                }
                            }
                            while (foundRepeatedConstant && !line.empty() && line.at(0) == 'S') {
                                std::cout << line << std::endl;
                                stickerAlbumsHolder.at(j).emplaceRepeatedSticker(SVV1_GeneralSticker(line));
                                if (!std::getline(inputModelAlbumData, line)) { break; }
                                if (!line.empty() && line.at(0) != 'S') { break; }
                            }
                        }


                        //? Reading the amount of packs created
                        std::getline(inputModelAlbumData, line);
                        auto amount_packs = std::stoi(line);
                        for (size_t index = 0;
                             index < amount_packs; index += 1) { UnopenedStickerPacks.emplace_back(); }
                        //? Reading the data inside of the packs
                        for (size_t j = 0; j < amount_packs; j += 1) {
                            for (size_t index = 0;
                                 index < SVV1_ExecutionConstants::LINE_JUMPS_FOR_PACK_STICKERS; index += 1) {
                                std::getline(inputModelAlbumData, line);
                                if (std::equal(line.begin(), line.end(), "P")) {
                                    continue;
                                }
                                UnopenedStickerPacks.at(j).addStickerToPack(SVV1_GeneralSticker(line));
                            }
                        }
                    }
                    catch (...) {
                        std::cout
                                << "Errors when reading the file, it must have been corrupted, we have to delete it for the program to work"
                                << std::endl;
                    }
                    HasLoadedFile = true;
                    //?Clearing old data from the file to make way for new instance
                    std::ofstream clearingFileMethod(FILEPATH, std::ios::out);
                    clearingFileMethod.close();
                }
                case 2 /*User Does not Want to Load in the File*/: {
                    UtilPrintTextWithinScreen("Limpieza de Archivo Anterior");
                    UtilPrintLongMessageOnPredefLength(
                            "Como se ha solicitado no cargar el archivo anterior, se procede a limpiarlo para"
                            "poder trabajar con un archivo nuevo y sin valores que interrupan el registro de datos de"
                            "la partida actual");
                    std::ofstream clearingFileMethod(FILEPATH, std::ios::out);
                    clearingFileMethod.close();
                }
                default /*User will never get here but convention needs this*/: {
                    throw std::runtime_error(
                            "You are not meant to be at the default case of UserSelectionForFileLoading, either you messed with the code,"
                            "or we messed up. Apologies");
                }

            }
        }
    } else {
        UtilPrintTextWithinScreen("No se ha Encontrado Ningun Archivo De Registro");
        UtilPrintLongMessageOnPredefLength(
                "La busqueda realizada para encontrar el archivo de registro anterior no fue exitosa, por tanto procedemos a crear uno nuevo para esta partida.\n");
        static std::ofstream NewFileOutput(FILEPATH, std::ios::out);
    }

    //! End of file instantiation methods and reading methods.
    system("cls");
    SetConsoleTitleA("StickerAlbumV1 - Matematicos Famosos");
    if (HasLoadedFile) {}
    else {
        UtilPrintLineOnScreen();
        UtilPrintTextWithinScreen("Universidad San Francisco de Quito");
        UtilPrintTextWithinScreen("StickerAlbumV1 - Matematicos Famosos");
        UtilPrintLongMessageOnPredefLength(
                "\nBienvenido a StickerAlbumV1 - Matematicos Famosos. Esta aplicacion se basa en la representacion de un album con 25 matematico@s de la epoca que han dejado "
                "una huella en el desarrollo de las ciencias exactas y de la ciencia en general. Con aportes de ciertos cientificos que puedes collecionar, inclusive se volvio posible"
                "la realizacion de juegos simulados en computadora. \n\nPara continuar la aplicacion, por favor ingresa el numero de albums que deseas llenar.\n\n"
                "Albumes a Generar: ");
        //? Register the amount of albums as an unsigned int variable
        unsigned int amountOfAlbums{0};
        //? User input for amount of albums
        while (!(std::cin >> amountOfAlbums)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ingrese por favor un valor numerico, correspondiente al numero de albums que desea llenar."
                      << std::endl;
        }
        //? Loop for the amount of albums the user wants to create
        UtilPrintTextWithinScreen("Generando Albums !");
        for (size_t index = 0; index < amountOfAlbums; index += 1) { stickerAlbumsHolder.emplace_back(); }
        //? Having created the albums we now generate the amount of stickers we need
        UtilPrintTextWithinScreen("Generando Stickers !");
        auto amountOfPacks = amountOfAlbums * SVV1_ExecutionConstants::PACK_MAX_STICKERS;
        auto amountOfStickers = amountOfAlbums * SVV1_ExecutionConstants::STICKER_MAX_VALUE;
        //? Create the stickers using amount of stickers
        int counter{0};
        for (size_t repetition = 0; repetition < SVV1_ExecutionConstants::STICKER_MAX_VALUE; repetition += 1) {
            for (size_t index = 0; index < amountOfAlbums; index += 1) {
                stickerHolder.push_back(SVV1_GeneralSticker(
                        repetition + 1,
                        SVV1_CardNames::CardNames[repetition % SVV1_ExecutionConstants::STICKER_MAX_VALUE],
                        SVV1_CardNames::CardNames[repetition % SVV1_ExecutionConstants::STICKER_MAX_VALUE]));
                counter += 1;
            }
        }
        auto formattedStickerCreationReport = std::format("Se han generado {} stickers !", counter);
        UtilPrintTextWithinScreen(formattedStickerCreationReport);
        std::shuffle(stickerHolder.begin(), stickerHolder.end(), std::mt19937(std::random_device()()));

        //? Create the packs using amount of packs
        UtilPrintTextWithinScreen("Generando Packs de Cinco Stickers Cada Uno!");
        for (size_t index = 0; index < amountOfPacks; index += 1) { UnopenedStickerPacks.emplace_back();}
        for(size_t packNum =0; packNum < stickerHolder.size() / SVV1_ExecutionConstants::PACK_MAX_STICKERS; packNum +=1)
        {
            for(size_t i = 0; i < SVV1_ExecutionConstants::PACK_MAX_STICKERS; i +=1)
            {
                size_t actualIndex = packNum*SVV1_ExecutionConstants::PACK_MAX_STICKERS + i;
                UnopenedStickerPacks[packNum].addStickerToPack(stickerHolder.at(actualIndex));
            }
        }
        //? Haciendo un Shuffle de los packs generados.
        std::shuffle(UnopenedStickerPacks.begin(), UnopenedStickerPacks.end(), std::mt19937(std::random_device()()));
        //? Clear console and Move to Main Menu
        system("cls");
        UtilPrintLineOnScreen();
        UtilPrintTextWithinScreen("Universidad San Francisco de Quito");
        UtilPrintTextWithinScreen("StickerAlbumV1 - Matematicos Famosos");
        auto formattedStickerCreationReport2 = std::format("Ahora que hemos generado aproximadamente {} paquetes con cinco stickers "
                                                           "cada uno, podemos empezar a jugar y a completar nuestro propio album de "
                                                           "matematicos! \n\nPara esto por favor selecciona una opcion del siguiente menu.\n",amountOfPacks);
        UtilPrintLongMessageOnPredefLength(formattedStickerCreationReport2);

        unsigned int GameMenuUserSelection{0};
        do
        {
            std::cout << "1. Revisar Albums Generados (Mostrando Lugares LLenos y Vacios)\n"
                         "2. Revisar Paquetes Aun Por Usar\n"
                         "3. Abrir un Paquete Y Usar Sus Contenidos\n"
                         "4. Salir Del Programa\n"
                         "\nSu eleccion: ";
            while (!(std::cin >> GameMenuUserSelection))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ingrese por favor un valor numerico, correspondiente a la opcion que desea realizar." << std::endl;
            }

            switch(GameMenuUserSelection)
            {
                case 1 /*Revisar Albums Generados (Monstrando Lugares LLenos y Vacios)*/:
                {
                    UtilPrintLineOnScreen();
                    for(auto const& value : stickerAlbumsHolder)
                    {
                         auto returnType = value.printingAlbumData();
                         if (!returnType)
                         {
                             UtilPrintTextWithinScreen("El Album Ingresado Al Analisis Esta Vacio");
                         }
                         break;
                    }
                }
                case 2 /*Revisar Paquetes Aun Por Usar*/:
                {

                }
                default:
                {
                    UtilPrintTextWithinScreen("Opcion registrada no presente en el menu, revirtiendo al menu original");
                    system("cls");
                }
            }

        }
        while(GameMenuUserSelection != 4);




    }
}