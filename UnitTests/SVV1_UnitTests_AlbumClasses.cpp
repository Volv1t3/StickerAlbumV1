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
#include <array>
#include <vector>
#include <algorithm>
#include <random>

int main()
{
    //! Unit test complete - creating cards using methods already defined then creating albums, appending cards to it from the shuffled
    //! set of packs
    {
        using namespace std;
        int numberOfAlbums{0};
        cout << "Enter how many albums you want to fill out... "; cin >> numberOfAlbums;
        //! Define holders
        const std::array<std::string, 25> CardNames{"Planck", "Bethe",
                                                    "Heisenberg", "Goeppert"
                ,"Kaku","Einstein", "Randall", "Rubin", "Curie","Hawking","Joule",
                                                    "Teller","Sommerfeld","Noether","Hilbert","Pointcare","Laplace","Cauchy",
                                                    "Euler", "Turing","Riemann","Fermat","Germain","Jayam","Godel"};

        std::vector<SVV1_GeneralSticker> stickers;
        //? Define working constants
        auto amountOfPacks = numberOfAlbums * 5;
        auto amountOfStickers = numberOfAlbums * 25;
        //? Create the stickers using amount of stickers
        int counter{0};
        for(size_t repetition = 0; repetition < 25; repetition +=1)
        {
            for(size_t index = 0; index < numberOfAlbums; index +=1)
            {
                stickers.push_back(SVV1_GeneralSticker(
                        repetition + 1,
                        CardNames[repetition % 25], CardNames[repetition % 25]));
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
        size_t packSize = 5;
        for(size_t packNum =0; packNum < stickers.size() / packSize; packNum +=1)
        {
            stickerPacks.push_back(SVV1_StickerPack());
            for(size_t i = 0; i < packSize; i +=1)
            {
                size_t actualIndex = packNum*packSize + i;
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
                        std::cout << "Error occured when filling up albums" << std::endl;
                        std::cout << e.what() << std::endl;
                    }
                }

            }
        }

        //! Printing Values inside of each album

        for(auto const& value: albums)
        {
            std::cout << value.serializingAlbum();
        }
    }
}