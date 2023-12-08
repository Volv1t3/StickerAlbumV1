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
#include <algorithm>
#include <random>
//------------------------------------------------------

int main() {

    //? Define local variables for holding: stickers, packs, albums
    static unsigned int  amountOfPacks{0};
    static unsigned int amountOfAlbums{0};
    static unsigned int amountOfStickers{0};
    static bool HasLoadedFile = false;
    static bool HasWon = false;
    std::vector<SVV1_GeneralSticker> stickerHolder;
    std::vector<SVV1_StickerPack> UnopenedStickerPacks;
    std::vector<SVV1_StickerPack> OpenedStickerPacks;
    std::vector<SVV1_Album> stickerAlbumsHolder;
    std::vector<bool> PartialResultsOfCompletion;

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
                    "\nHemos detectado un registro de una partida anterior para poder cargarla en el programa. Si desea realizar este cargo de datos, seleccion 1, si no quiere hacerlo seleccione 2.\n"
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
                        inputModelAlbumData.seekg(0, std::ios::beg);
                        std::string line;
                        std::getline(inputModelAlbumData, line);
                        if (line.empty()) {std::getline(inputModelAlbumData,line);}
                        //? Reading the first line which is the amount of albums created
                        amountOfAlbums = std::stoi(line);
                        for (size_t index = 0;
                             index < amountOfAlbums; index += 1) { stickerAlbumsHolder.emplace_back(); }
                        //? Reading the data inside of the albums
                        /*Method has been adapted to provide for flexibility for incomplete albums, looping as long as it finds lines that
                         start with the letter S*/
                        for (size_t j = 0; j < amountOfAlbums; j += 1) {
                            bool foundStickerConstant = false;
                            while (std::getline(inputModelAlbumData, line) && !foundStickerConstant) {
                                if (!line.empty() && line.at(0) == '=') { break; }
                                if (!line.empty() && line.at(0) == 'A') { continue; }
                                if (!line.empty() && line.at(0) == 'S') {
                                    foundStickerConstant = true;
                                    stickerAlbumsHolder.at(j).emplaceAStickerOnAlbum(SVV1_GeneralSticker(line));
                                }
                            }
                            if(foundStickerConstant == false){break;}
                            while (foundStickerConstant && !line.empty() && line.at(0) == 'S') {
                                std::cout << line << std::endl;
                                stickerAlbumsHolder.at(j).emplaceAStickerOnAlbum(SVV1_GeneralSticker(line));
                                if (!std::getline(inputModelAlbumData, line)) { break; }
                                if (!line.empty() && line.at(0) != 'S') { break; }
                            }

                            //? Receiving data form repeated section
                            bool foundRepeatedConstant = false;
                            while (std::getline(inputModelAlbumData, line) && !foundRepeatedConstant) {
                                if (!line.empty() && line.at(0) == '=') { break; }
                                if (!line.empty() && line == "R") {
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
                        if (line.at(0) == '=') { std::getline(inputModelAlbumData, line);}
                        amountOfPacks = std::stoi(line);
                        for (size_t index = 0;
                             index < amountOfPacks; index += 1) { UnopenedStickerPacks.emplace_back(); }
                        //? Reading the data inside of the packs
                        for (size_t j = 0; j < amountOfPacks; j += 1) {
                            for (size_t index = 0;
                                 index < SVV1_ExecutionConstants::LINE_JUMPS_FOR_PACK_STICKERS; index += 1) {
                                std::getline(inputModelAlbumData, line);
                                if (std::equal(line.begin(), line.end(), "P")) {
                                    continue;
                                }
                                std::cout << line << std::endl;
                                UnopenedStickerPacks.at(j).addStickerToPack(SVV1_GeneralSticker(line));
                            }
                        }

                        //? Reading amount of opened packs created
                        std::getline(inputModelAlbumData, line);
                        std::cout << std::endl;
                        if (line.at(0) == 'S') {std::getline(inputModelAlbumData, line);}
                        if (line.at(0) == '=') {std::getline(inputModelAlbumData, line);}
                        auto AmountOfOpenedPacks = std::stoi(line);
                        for (size_t index = 0;
                             index < AmountOfOpenedPacks; index += 1) { OpenedStickerPacks.emplace_back(); }
                        //? Reading the data inside of the packs
                        for (size_t j = 0; j < AmountOfOpenedPacks; j += 1) {
                            for (size_t index = 0;
                                 index < SVV1_ExecutionConstants::LINE_JUMPS_FOR_PACK_STICKERS; index += 1) {
                                std::getline(inputModelAlbumData, line);
                                if (line == "P") {
                                    continue;
                                }
                                OpenedStickerPacks.at(j).addStickerToPack(SVV1_GeneralSticker(line));
                            }
                        }
                    }
                    catch (...) {
                        std::cout
                                << "Errors when reading the file, it must have been corrupted, we have to delete it for the program to work"
                                << std::endl;
                    }

                    //?Clearing old data from the file to make way for new instance
                    std::ofstream clearingFileMethod(FILEPATH, std::ios::out);
                    clearingFileMethod.close();
                    HasLoadedFile = true;
                    break;

                }
                case 2 /*User Does not Want to Load in the File*/: {
                    UtilPrintTextWithinScreen("Limpieza de Archivo Anterior");
                    UtilPrintLongMessageOnPredefLength(
                            "Como se ha solicitado no cargar el archivo anterior, se procede a limpiarlo para"
                            "poder trabajar con un archivo nuevo y sin valores que interrupan el registro de datos de"
                            "la partida actual");
                    std::ofstream clearingFileMethod(FILEPATH, std::ios::out);
                    clearingFileMethod.close();
                    break;
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
        std::ofstream NewFileOutput(FILEPATH, std::ios::out);
    }

    //! End of file instantiation methods and reading methods.
    system("cls");
    SetConsoleTitleA("StickerAlbumV1 - Matematicos Famosos");
    if (HasLoadedFile) {;}
    else
    {
        UtilPrintLongMessageOnPredefLength(
                "\nBienvenido a StickerAlbumV1 - Matematicos Famosos. Esta aplicacion se basa en la representacion de un album con 25 matematico@s de la epoca que han dejado "
                "una huella en el desarrollo de las ciencias exactas y de la ciencia en general. Con aportes de ciertos cientificos que puedes collecionar, inclusive se volvio posible"
                "la realizacion de juegos simulados en computadora. \n\nPara continuar la aplicacion, por favor ingresa el numero de albums que deseas llenar.\n\n"
                "Albumes a Generar: ");
        //? Register the amount of albums as an unsigned int variable

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
         amountOfPacks = amountOfAlbums * SVV1_ExecutionConstants::PACK_MAX_STICKERS;
         amountOfStickers = amountOfAlbums * SVV1_ExecutionConstants::STICKER_MAX_VALUE;
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
        auto formattedStickerCreationReport ="Se han generado {} stickers !" + std::to_string(counter);
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
        UtilPrintLineOnScreen();
    }
        UtilPrintLineOnScreen();
        UtilPrintTextWithinScreen("Universidad San Francisco de Quito");
        UtilPrintTextWithinScreen("StickerAlbumV1 - Matematicos Famosos");

        UtilPrintTextWithinScreen("Universidad San Francisco de Quito");
        UtilPrintTextWithinScreen("StickerAlbumV1 - Matematicos Famosos");
        auto formattedStickerCreationReport2 = "\nAhora que hemos generado aproximadamente {" + std::to_string(amountOfPacks) + "} paquetes con cinco stickers "
                                               "cada uno, podemos empezar a jugar y a completar nuestro propio album de "
                                               "matematicos! \n\nPara esto por favor selecciona una opcion del siguiente menu.\n";
        UtilPrintLongMessageOnPredefLength(formattedStickerCreationReport2);

        unsigned int GameMenuUserSelection{0};
        do
        {
            if (HasWon)
            {
                UtilPrintTextWithinScreen("Ganador!!!!! Ganador!!!!");
                UtilPrintLongMessageOnPredefLength("Usted ha completado todos los valores de los albums que ha decidido crear, felicitaciones, como el juego ha terminado los valores"
                                                   "que se han generado en esta iteracion no seran registrados en un archivo externo"
                                                   "\n\nGracias por Jugar StickerAlbumV1 - Matematicos Famosos");
                UtilPrintTextWithinScreen("Imprimiendo Cromos Repetidos");
                int counterPrintingRepeatedStickers{0};
                for(auto const& value : stickerAlbumsHolder)
                {
                    std::cout << "Stickers repetidos del Album #" << counterPrintingRepeatedStickers + 1 << " :" << std::endl;
                    std::cout << value.serializingRepeatedStickers();
                    counterPrintingRepeatedStickers +=1;
                }
                UtilPrintTextWithinScreen("Imprimiendo Sobres Abiertos");
                counterPrintingRepeatedStickers = 0;
                for(auto const& value : OpenedStickerPacks)
                {
                    std::cout << "Stickers Usados del Paquete #" << counterPrintingRepeatedStickers + 1 << " :" << std::endl;
                    std::cout << value.getStringPack();
                    counterPrintingRepeatedStickers +=1;
                }
                break;
            }
            std::cout << "1. Revisar Albums Generados (Mostrando Lugares LLenos y Vacios)\n"
                         "2. Revisar Paquetes Aun Por Usar\n"
                         "3. Abrir un Paquete Y Usar Sus Contenidos\n"
                         "4. Mostrar Listado de Cromos Repetidos Por Album Generado\n"
                         "5. Reiniciar Informacion Actual (Cuidado)\n"
                         "6. Salir Del Programa\n"
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
                    int counterAlbums{0};
                    UtilPrintLineOnScreen();
                    for(auto const& value : stickerAlbumsHolder)
                    {
                        auto CheckIfFull = value.isFull();
                        if (!CheckIfFull)
                        {
                            auto formattedStickerCreationReport5 = "Album Numero #{" + std::to_string(counterAlbums + 1) + "} esta "
                            + (CheckIfFull ? "Lleno" : "Vacio");
                            std::cout << formattedStickerCreationReport5 << std::endl;
                            value.printingAlbumData();
                        }
                        else
                        {
                            auto formattedStickerCreationReport5 = "Album Numero #{" + std::to_string( counterAlbums + 1) + "} esta lleno";
                            std::cout << formattedStickerCreationReport5 << std::endl;
                            value.printingAlbumData();
                        }
                        counterAlbums +=1;
                    }
                    UtilPrintLineOnScreen();
                    break;
                }
                case 2 /*Revisar Paquetes Aun Por Usar*/:
                {
                    UtilPrintTextWithinScreen("Revisando Paquetes Aun Por Usar");
                    int counterPacks = {0};
                    unsigned int packsPerColumn{2};
                    std::cout << "Total de Paquete en Forma de Lista." << std::endl;
                    for(auto const& value : UnopenedStickerPacks)
                    {
                        //Transform this formattte message to a string
                        auto formattedStickerCreationReport3 = "| Paquete Numero #{" + std::to_string(counterPacks + 1) + "} |";

                        std::cout << formattedStickerCreationReport3;
                        if ((counterPacks + 1) % packsPerColumn == 0 && counterPacks > 0)
                        {
                            std::cout << std::endl;
                        }
                        counterPacks ++;
                    }
                    std::cout << std::endl;
                    break;
                }
                case 3 /* Abrir un paquete y usarlo en los albums que existan*/:
                {
                    UtilPrintTextWithinScreen("Selecciona uno de los siguientes paquetes basados en su indice de la lista");
                    int counterPacks = {0};
                    unsigned int packsPerColumn{2};
                    for(auto const& value : UnopenedStickerPacks)
                    {
                        auto formattedStickerCreationReport3 = "| Paquete Numero #{" + std::to_string(counterPacks + 1) + "} |";
                        std::cout << formattedStickerCreationReport3;
                        if ((counterPacks  + 1) % packsPerColumn == 0 && counterPacks > 0)
                        {
                            std::cout << std::endl;
                        }
                        counterPacks ++;
                    }
                    std::cout << std::endl;
                    //? Ask the user for input
                    std::string message = "Por favor, basado en la numeracion anterior (1 al " + std::to_string(amountOfPacks) + ") seleccione uno de los paquetes secretos";
                    UtilPrintLongMessageOnPredefLength(message);
                    unsigned int UserSelectionForPackIndexing{0};
                    do
                    {
                        while (!(std::cin >> UserSelectionForPackIndexing))
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Ingrese por favor un valor numerico, correspondiente al indice de paquete que deseas abrir." << std::endl;
                        }
                    }
                    while ( UserSelectionForPackIndexing < 0 || UserSelectionForPackIndexing > UnopenedStickerPacks.size());

                    //? Report to the user which pack they chose
                    std::string formattedStickerCreationReport4 = "Seleccionaste el paquete #" + std::to_string(UserSelectionForPackIndexing) + " !";
                    UtilPrintTextWithinScreen(formattedStickerCreationReport4);

                    //? Open the pack and add the stickers to the albums
                    auto SelectedStickerPack = UnopenedStickerPacks.at(UserSelectionForPackIndexing - 1);
                    UtilPrintTextWithinScreen("Abriendo el Paquete!");
                    std::cout << "Paquete #" << UserSelectionForPackIndexing << std::endl;
                    std::cout << SelectedStickerPack.getStringPack();

                    UtilPrintTextWithinScreen("Paquete Abierto! Distribuyendo contenidos");
                    for(auto& value : stickerAlbumsHolder)
                    {
                        for(size_t index = 0; index < SVV1_ExecutionConstants::PACK_MAX_STICKERS; index += 1)
                        {
                            value.emplaceAStickerOnAlbum(SelectedStickerPack.getStickerAtLocationInVector(index));
                        }
                    }
                    UtilPrintTextWithinScreen("Paquete Distribuido!");
                    UnopenedStickerPacks.erase(UnopenedStickerPacks.begin() + UserSelectionForPackIndexing - 1);
                    OpenedStickerPacks.push_back(SelectedStickerPack);
                    std::shuffle(UnopenedStickerPacks.begin(), UnopenedStickerPacks.end(), std::mt19937(std::random_device()()));
                    //? Submodule for checking if the album is full or not
                    for(auto& album : stickerAlbumsHolder)
                    {
                        if (album.isFull()){PartialResultsOfCompletion.push_back(true);}
                    }
                    if (stickerAlbumsHolder.size() == PartialResultsOfCompletion.size())
                    {
                        HasWon = true;
                    }
                    break;
                }
                case 4 /*Mostrar Listado de Cromos Repetidos Por Album Generado*/:
                {
                    UtilPrintTextWithinScreen("Listado de Cromos Repetidos Por Album Generado");
                    int counterAlbums{0};
                    for(auto const& value : stickerAlbumsHolder)
                    {
                        std::string formattedStickerCreationReport6 = "Album Numero #" + std::to_string(counterAlbums + 1);
                        std::cout << (formattedStickerCreationReport6) << std::endl;
                        value.printingRepeatedFrecuency();
                    }
                    break;
                }
                case 5 /*Reiniciar Informacion Actual (Cuidado)*/:
                {
                    //? Reset de las variables generales de ejecucion.
                    UtilPrintTextWithinScreen("Reiniciando Informacion Actual - Todos los datos de la partida seran eliminados");
                    UtilPrintLineOnScreen();
                    amountOfPacks = 0;
                    amountOfAlbums = 0;
                    amountOfStickers  = 0;
                    stickerHolder.clear();
                    stickerAlbumsHolder.clear();
                    UnopenedStickerPacks.clear();
                    OpenedStickerPacks.clear();

                    //? Regeneration of data based on the same method used in the else statement above.
                    UtilPrintLongMessageOnPredefLength(
                            "\nBienvenido a StickerAlbumV1 - Matematicos Famosos. Esta aplicacion se basa en la representacion de un album con 25 matematico@s de la epoca que han dejado "
                            "una huella en el desarrollo de las ciencias exactas y de la ciencia en general. Con aportes de ciertos cientificos que puedes collecionar, inclusive se volvio posible"
                            "la realizacion de juegos simulados en computadora. \n\nPara continuar la aplicacion, por favor ingresa el numero de albums que deseas llenar.\n\n"
                            "Albumes a Generar: ");
                    //? Register the amount of albums as an unsigned int variable

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
                    amountOfPacks = amountOfAlbums * SVV1_ExecutionConstants::PACK_MAX_STICKERS;
                    amountOfStickers = amountOfAlbums * SVV1_ExecutionConstants::STICKER_MAX_VALUE;
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
                    std::string formattedStickerCreationReport = "Se han generado " + std::to_string(counter) + " stickers !";
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
                    UtilPrintLineOnScreen();
                    break;
                }
                case 6 /*Salir*/:
                {
                    UtilPrintTextWithinScreen("Saliendo del Juego");
                    UtilPrintLineOnScreen();
                    std::ofstream NewFileOutputExitOption(FILEPATH, std::ios::out);
                    //? Serialize albums
                    NewFileOutputExitOption << amountOfAlbums << "\n";
                    for(auto const& value: stickerAlbumsHolder)
                    {
                        NewFileOutputExitOption<< value.serializingAlbum();
                        NewFileOutputExitOption << value.serializingRepeatedStickers();
                    }
                    NewFileOutputExitOption << UtilReturnLineOnScreen();

                    //? Serialize Unopened Packs
                    NewFileOutputExitOption << UnopenedStickerPacks.size() << "\n";
                    for (auto const& value : UnopenedStickerPacks)
                    {
                        NewFileOutputExitOption << value.getSerializedPack();
                    }
                    NewFileOutputExitOption << UtilReturnLineOnScreen();
                    //? Serialize Opened Packs
                    NewFileOutputExitOption << OpenedStickerPacks.size() << "\n";
                    for(auto const& value:  OpenedStickerPacks)
                    {
                        NewFileOutputExitOption << value.getSerializedPack();
                    }
                    break;
                }
                default:
                {
                    UtilPrintTextWithinScreen("Opcion registrada no presente en el menu, revirtiendo al menu original");
                    system("cls");
                }
            }

        }
        while(GameMenuUserSelection != 6);
}