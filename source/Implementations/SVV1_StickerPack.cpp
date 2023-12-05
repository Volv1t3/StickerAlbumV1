/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: General Sticker Pack Class Definition
?3. Directions: New methods must be added in their corresponding sections, consider headings defined by //!
-----------------------------------------------**/
#include <string>
#include "../Headers/SVV1_StickerPack.hpp"
#include <vector>
#include <exception>
#include <stdexcept>
#include <sstream>


const char SVV1_StickerPack::PACK_INDICATOR = 'P';

//! Definition of Constructors


//! Definition of Appending Methods
SVV1_StickerPack &SVV1_StickerPack::addStickerToPack(const SVV1_GeneralSticker& OtherStickerInstance)
{
    if (SVV1_StickerPack::DataValueArrayHolder.size() < 5)
    {
        bool checkIfPresent = false;
        for(const auto&  value : this->DataValueArrayHolder)
        {
            if (value == OtherStickerInstance) {checkIfPresent = true;}
            else {continue;}
        }

        if (checkIfPresent == false) {this->DataValueArrayHolder.push_back(OtherStickerInstance);}
        else {;}
    }
    else {throw std::out_of_range("Error Code 0x001 [Raised] - StickerPack is Full");}

    return *this;
}

//! Definition for retrieving cards and visualizing packs

std::vector<SVV1_GeneralSticker> SVV1_StickerPack::getDataArray() const {return this->DataValueArrayHolder;}

SVV1_GeneralSticker SVV1_StickerPack::getStickerAtLocationInVector(size_t indexOfSticker)
{
    if (indexOfSticker >= 0 && indexOfSticker < 5)
    {
        return this->DataValueArrayHolder[indexOfSticker];
    }
    else
    {
        throw std::out_of_range("Error Code 0x001 [Raised] - Index Out of Range");
    }
}

//! Defintion for serializing data

std::string SVV1_StickerPack::getSerializedPack()
{
    std::stringstream SerializedStream;
    //? Append formal data from pack
    SerializedStream << PACK_INDICATOR << "\n";
    for(const auto& value: this->DataValueArrayHolder)
    {
        {SerializedStream << value.createSerializedString() <<"";}
    }
    return SerializedStream.str();
}