
/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: Unit Tests of All Sticker Classes
?3. Directions: Add different tests here
-----------------------------------------------**/
#include <iostream>
#include <string>
#include "./../source/Headers/SVV1_StickerPack.hpp"
#include "./../source/Headers/SVV1_GeneralSticker.hpp"
#include "./../source/Headers/SVV1_Album.hpp"
#include "./../source/Implementations/SVV1_GeneralSticker.cpp"
#include "./../source/Implementations/SVV1_StickerPack.cpp"
#include "./../source/Implementations/SVV1_Album.cpp"
#include "./../source/values/SVV1_ExecutionConstants.hpp"
#include "./../source/Headers/SVV1_Utilities.hpp"
#include "./../source/Implementations/SVV1_Utilities.cpp"
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
int main()
{
    //! Unit test complete - creating cards using methods already defined then creating albums, appending cards to it from the shuffled
    //! set of packs
    {
        using namespace std;
        int numberOfAlbums{0};
        cout << "Enter how many albums you want to fill out... "; cin >> numberOfAlbums;
        //! Define holders

        std::vector<SVV1_GeneralSticker> stickers;
        //? Define working constants
        auto amountOfPacks = numberOfAlbums * SVV1_ExecutionConstants::PACK_MAX_STICKERS;
        auto amountOfStickers = numberOfAlbums * SVV1_ExecutionConstants::STICKER_MAX_VALUE;
        //? Create the stickers using amount of stickers
        int counter{0};
        for(size_t repetition = 0; repetition < SVV1_ExecutionConstants::STICKER_MAX_VALUE; repetition +=1)
        {
            for(size_t index = 0; index < numberOfAlbums; index +=1)
            {
                stickers.push_back(SVV1_GeneralSticker(
                        repetition + 1,
                        SVV1_CardNames::CardNames[repetition % SVV1_ExecutionConstants::STICKER_MAX_VALUE],
                        SVV1_CardNames::CardNames[repetition % SVV1_ExecutionConstants::STICKER_MAX_VALUE]));
                counter +=1;
            }
        }
        std::cout << "Total stickers created: " << counter << std::endl;
        for(auto const& value: stickers)
        {
            std::cout << value.createSerializedString() << std::endl;
        }
        std::shuffle(stickers.begin(), stickers.end(), std::mt19937(std::random_device()()));

        //! print set of cards
        for(auto const& value: stickers)
        {
            std::cout << value.createSerializedString() << std::endl;
        }
        //Creating packs out of the Values given.
        std::vector<SVV1_StickerPack> stickerPacks;
        for(size_t packNum =0; packNum < stickers.size() / SVV1_ExecutionConstants::PACK_MAX_STICKERS; packNum +=1)
        {
            stickerPacks.push_back(SVV1_StickerPack());
            for(size_t i = 0; i < SVV1_ExecutionConstants::PACK_MAX_STICKERS; i +=1)
            {
                size_t actualIndex = packNum*SVV1_ExecutionConstants::PACK_MAX_STICKERS + i;
                stickerPacks[packNum].addStickerToPack(stickers.at(actualIndex));
            }
        }

        for(const auto& value: stickerPacks)
        {
            std::cout << value.getSerializedPack() << std::endl;
        }

        //! Creating a holder for the albums to be created
        std::vector<SVV1_Album> albums;
        for(size_t index = 0; index < numberOfAlbums; index +=1)
        {
            std::shuffle(stickerPacks.begin(), stickerPacks.end(), std::mt19937(std::random_device()()));
            albums.push_back(SVV1_Album());
            for(size_t i = 0; i < stickerPacks.size(); i +=1)
            {
                for(const auto& value: stickerPacks.at(i))
                {
                    try {
                        albums.at(index).emplaceAStickerOnAlbum(value);
                    }
                    catch(std::exception &e)
                    {
                        ;
                    }
                }

            }
        }

        //! Printing Values inside of each album

        for(auto const& value: albums)
        {
            std::cout << value.serializingAlbum();
        }


        std::ofstream outputOfCreation(SVV1_ExecutionConstants::FILE_NAME, std::ios::out);

        //? Defining the amount of albums the user created
        outputOfCreation << numberOfAlbums << "\n";
        //? Serializing the data inside album first;
        for(auto const& value: albums)
        {
            outputOfCreation << value.serializingAlbum();
            outputOfCreation << value.serializingRepeatedStickers();
        }


        outputOfCreation << UtilReturnLineOnScreen();
        //? Serializing the data inside pack
        outputOfCreation << amountOfPacks << "\n";
        for(auto const& value: stickerPacks)
        {
            outputOfCreation << value.getSerializedPack();
        }

        //? With the data created I would like to open the file and read from it to the screen so Im going to send a system cls first
        outputOfCreation.close();
        //? Now I would like to open the file and read from it to the screen
        try {
            std::ifstream  inputOfCreation(SVV1_ExecutionConstants::FILE_NAME, std::ios::in);

        std::string line;
        std::getline(inputOfCreation, line);
        //? Reading the first line which is the amount of albums created
        auto amount_albums = std::stoi(line);
        std::cout << "Amount of albums created: " << amount_albums << std::endl;
        std::vector<SVV1_Album> abumsRead;
        for (size_t index = 0; index < amount_albums; index +=1) { abumsRead.emplace_back(); }
        //? Reading the data inside of the albums

        for (size_t j =0; j < amount_albums; j +=1)
        {
            for (size_t index = 1; index <= SVV1_ExecutionConstants::LINE_JUMPS_FOR_ALBUM_STICKERS; index += 1) {
                std::getline(inputOfCreation, line);
                if (std::equal(line.begin(), line.end(), "A")) {
                    continue;
                }
                std::cout << line << std::endl;
                abumsRead.at(j).emplaceAStickerOnAlbum(SVV1_GeneralSticker(line));
            }
        }

        for (auto const& value: abumsRead)
        {
            std::cout << "DESERIALIZED ALBUM" << std::endl;
            std::cout << value.serializingAlbum() << std::endl;
        }
        //? Reading the amount of packs created
        std::getline(inputOfCreation, line);
        std::cout << line << std::endl;
        auto amount_packs = std::stoi(line);
        std::cout << "Amount of packs created: " << amount_packs << std::endl;
        std::vector<SVV1_StickerPack> packsRead;
        for (size_t index = 0; index < amount_packs; index +=1) { packsRead.emplace_back(); }
        //? Reading the data inside of the packs
        for (size_t j =0; j < amount_packs; j +=1)
        {
            for (size_t index = 0; index < SVV1_ExecutionConstants::LINE_JUMPS_FOR_PACK_STICKERS; index += 1) {
                std::getline(inputOfCreation, line);
                if (std::equal(line.begin(), line.end(), "P")) {
                    continue;
                }
                packsRead.at(j).addStickerToPack(SVV1_GeneralSticker(line));
            }
        }
            //?Printing generated packs
            for(auto const& value: packsRead)
            {
                std::cout << "DESERIALIZED PACK" << std::endl;
                std::cout << value.getSerializedPack() << std::endl;
            }
        }
        catch(...)
        {
            std::cout << "Errors when reading the file, it must have been corrupted, we have to delete it for the program to work" << std::endl;
        }


    }
}

