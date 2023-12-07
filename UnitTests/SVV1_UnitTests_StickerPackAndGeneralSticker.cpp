/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: Unit Tests of Sticker Pack and Abstract Sticker Class
?3. Directions: Add different tests here
-----------------------------------------------**/
#include "./../source/Headers/SVV1_StickerPack.hpp"
#include "./../source/Headers/SVV1_GeneralSticker.hpp"
#include "./../source/Implementations/SVV1_StickerPack.cpp"
#include "./../source/Implementations/SVV1_GeneralSticker.cpp"
#include <vector>
#include <iostream>
#include <array>
#include <algorithm>
#include <random>

int main()
{
    //! Unit test One - Defining a sticker pack and appending to it
    {
        SVV1_StickerPack stickerPackAlpha;
        //? Creating six stickers and trying to push them all in the pack
        SVV1_GeneralSticker stickerOne(0, "Santiago", "Santiago");
        SVV1_GeneralSticker stickerTwo(1, "Santiago", "Santiago");
        SVV1_GeneralSticker stickerThree(0, "Santiago", "Santiago");
        SVV1_GeneralSticker stickerFour(2, "Luis", "Arellano");
        SVV1_GeneralSticker stickerFive(3, "Luis", "Arellano");
        std::vector <SVV1_GeneralSticker> stickerVector;
        stickerVector.push_back(stickerOne);
        stickerVector.push_back(stickerTwo);
        stickerVector.push_back(stickerThree);
        stickerVector.push_back(stickerFour);
        stickerVector.push_back(stickerFive);
        //? Appending the stickers to the sticker pack
        for(const auto& value : stickerVector)
        {
            stickerPackAlpha.addStickerToPack(value);
            // std::cout << value.createSerializedString() << std::endl;
        }

        //? Printing the sticker pack
        auto pack = stickerPackAlpha.getDataArray();
        for(const auto& value : pack)
        {
            std::cout << value.createSerializedString() << std::endl;
        }
        //? Retrieving one by index, lets say index 0 so returning what is here stickerOne
        auto stickerOneCopy =  stickerPackAlpha.getStickerAtLocationInVector(0);
        std::cout << stickerOneCopy.createSerializedString() << std::endl;
    }
    //! Unit test Two - serializing data from a pack
    {
        SVV1_StickerPack stickerPackAlpha;
        //? Creating six stickers and trying to push them all in the pack
        SVV1_GeneralSticker stickerOne(0, "Santiago", "Santiago");
        SVV1_GeneralSticker stickerTwo(1, "Santiago", "Santiago");
        SVV1_GeneralSticker stickerThree(0, "Santiago", "Santiago");
        SVV1_GeneralSticker stickerFour(2, "Luis", "Arellano");
        SVV1_GeneralSticker stickerFive(3, "Luis", "Arellano");
        std::vector <SVV1_GeneralSticker> stickerVector;
        stickerVector.push_back(stickerOne);
        stickerVector.push_back(stickerTwo);
        stickerVector.push_back(stickerThree);
        stickerVector.push_back(stickerFour);
        stickerVector.push_back(stickerFive);
        //? Appending the stickers to the sticker pack
        for(const auto& value : stickerVector)
        {
            stickerPackAlpha.addStickerToPack(value);
            // std::cout << value.createSerializedString() << std::endl;
        }

        //? Serializing the data
        auto serializedData = stickerPackAlpha.getSerializedPack();
        //? Printing the serialized data
        std::cout << serializedData << std::endl;
    }

    //!  Unit Test 3 - Creating the packs using a given number from the user;
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
        for(size_t repetition = 0; repetition < amountOfPacks; repetition +=1)
        {
            for(size_t index = 0; index < 5; index +=1)
            {
                stickers.push_back(SVV1_GeneralSticker(
                        repetition + 1,
                        CardNames[repetition % 25], CardNames[repetition % 25]));
                counter +=1;
            }
        }
        std::cout << "Total stickers created: " << counter << std::endl;
        std::shuffle(stickers.begin(), stickers.end(), std::mt19937(std::random_device()()));

        //! print set of cards
        for(auto const& value: stickers)
        {
            std::cout << value.createSerializedString() << std::endl;
        }
        size_t start_index = 0;
        //Creating packs out of the Values given.
        std::vector<SVV1_StickerPack> stickerPacks;
        for(size_t packNum =0; packNum < amountOfPacks; packNum +=1)
        {
            stickerPacks.push_back(SVV1_StickerPack());
            for(size_t i = 0; i < 5; i +=1)
            {
                size_t index = packNum*5 + i;
                if (index < stickers.size()) {
                    stickerPacks[packNum].addStickerToPack(stickers[index]);
                }
            }
        }

        for(const auto& value: stickerPacks)
        {
            std::cout << value.getSerializedPack() << std::endl;
        }
    }

}