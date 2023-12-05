/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: Unit Tests of GeneralSticker
?3. Directions: Add different tests here
-----------------------------------------------**/
#include "./../source/Headers/SVV1_GeneralSticker.hpp"
#include "./../source/Implementations/SVV1_GeneralSticker.cpp"
#include <string>
#include <iostream>
#include <vector>

int main()
{
    {
        SVV1_GeneralSticker stickerOne(0, "Santiago", "Santiago");
        SVV1_GeneralSticker stickerTwo(1, "Santiago", "Santiago");
        SVV1_GeneralSticker stickerThree(0, "Santiago", "Santiago");

        if (stickerOne == stickerTwo) {std::cout << "Sticker 1 and 2 are EQUAL";}
        if (stickerOne == stickerThree) {std::cout << "Sticker 1 and 3 are EQUAL";}
        if (stickerTwo == stickerThree) {std::cout << "Sticker 2 and 3 are EQUAL";}
    }
    //! Test Cases of Implementation and Instantiation
    {
        std::string name = "Santiago";
        SVV1_GeneralSticker testSticker(4,  name, name);
        std::cout << testSticker.createSerializedString() << std::endl;
        SVV1_GeneralSticker testSticker2(testSticker.createSerializedString());
        std::cout << testSticker2.createSerializedString() << std::endl;
    }
    //! Test case for funcionatily in holders
    {
        std::vector<SVV1_GeneralSticker> testStickers;
        std::vector<std::string> testNames{"Euler", "Ruffini", "Stewart", "Green", "Lagrange", "Djisktra", "Newton", "Oppenhemier", "Russo", "Fermi"};
        for(size_t index = 0; index < 10; index +=1)
        {
            testStickers.push_back(SVV1_GeneralSticker(index, "ABCDEFG", testNames.at(index)));
        }

        for(const auto& value : testStickers)
        {
            std::cout << value.createSerializedString() << std::endl;
        }
    }
    //! Test case for operator overloaded

}