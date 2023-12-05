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

}