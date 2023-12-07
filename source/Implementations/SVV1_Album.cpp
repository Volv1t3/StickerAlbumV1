/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: Album CLass Implementation
?3. Directions: Class has been implemented, new methods have to be unit and integration tested
-----------------------------------------------**/
#include "../Headers/SVV1_Album.hpp"
#include "../values/SVV1_ExecutionConstants.hpp"
#include <exception>
#include <stdexcept>
#include <sstream>

//! Implementing class constant
const char SVV1_Album::ALBUM_INDICATOR = 'A';

//! Implementing  sticker adding methods

SVV1_Album &SVV1_Album::emplaceAStickerOnAlbum(const SVV1_GeneralSticker& StickerInstance)
{
    //? Base step, check if the size of the album is still less than 25 or else raise an error
    if (this->AlbumStickerObjects.size() < SVV1_ExecutionConstants::ALBUM_MAX_STICKERS)
    {
        bool InitialCheckResult = false;
        //? Inductive Step 1: Check if the card is there by iterating over the length of the vector.
        for(size_t index = 0; index < this->Album.size(); index +=1)
        {
            if (this->Album.at(index) == StickerInstance.getValueOfSticker())
            {
                InitialCheckResult = true;
                break;
            }
        }
        if (!InitialCheckResult)
        {
            //? Inductive Step 2: Since the card has not been pushed inside of the vector we emplace it on the back
            this->Album.at(StickerInstance.getValueOfSticker()-1) = StickerInstance.getValueOfSticker();
            this->AlbumStickerObjects.push_back(StickerInstance);
        }
        else
        {
            RepeatedStickers.push_back(StickerInstance);
        }
    }
    else
    {
        throw std::out_of_range("Error Code 0x001 [Raised] - Album is Already Full");
    }

    return *this;
}

//! Implementing serialization method

std::string SVV1_Album::serializingAlbum() const
{
    std::stringstream SerializedString;
    SerializedString << ALBUM_INDICATOR << "\n";
    for(size_t index = 0 ; index < this->AlbumStickerObjects.size() ; ++index)
    {
        SerializedString << AlbumStickerObjects.at(index).createSerializedString();
    }

    return SerializedString.str();
}

