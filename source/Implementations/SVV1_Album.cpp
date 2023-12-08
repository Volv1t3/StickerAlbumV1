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
#include <iostream>
#include <algorithm>
#include <utility>
#include <iomanip>

//! Implementing class constant
const char SVV1_Album::ALBUM_INDICATOR = 'A';

//! Implementing  sticker adding methods

SVV1_Album &SVV1_Album::emplaceAStickerOnAlbum(const SVV1_GeneralSticker& StickerInstance)
{
        //? Base step, check if the size of the album is still less than 25 or else raise an error
        if (this->AlbumStickerObjects.size() < SVV1_ExecutionConstants::ALBUM_MAX_STICKERS) {
            bool InitialCheckResult = false;
            //? Inductive Step 1: Check if the card is there by iterating over the length of the vector.
            for (size_t index = 0; index < this->Album.size(); index += 1) {
                if (this->Album.at(index) == StickerInstance.getValueOfSticker()) {
                    InitialCheckResult = true;
                    break;
                }
            }
            if (!InitialCheckResult) {
                //? Inductive Step 2: Since the card has not been pushed inside of the vector we emplace it on the back
                this->Album.at(StickerInstance.getValueOfSticker() - 1) = StickerInstance.getValueOfSticker();
                this->AlbumStickerObjects.push_back(StickerInstance);
            } else {
                this->FrecuencyOfRepeatedValues.at(StickerInstance.getValueOfSticker() - 1) += 1;
                RepeatedStickers.push_back(StickerInstance);
            }
        }
        else {
            RepeatedStickers.push_back(StickerInstance);
        }
    return *this;
}

SVV1_Album &SVV1_Album::emplaceRepeatedSticker(const SVV1_GeneralSticker &StickerInstance)
{
    this->FrecuencyOfRepeatedValues.at(StickerInstance.getValueOfSticker() - 1) += 1;
    this->RepeatedStickers.push_back(StickerInstance);
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

std::string SVV1_Album::serializingRepeatedStickers() const
{
    std::stringstream  SerializedRepeatedStream;
    SerializedRepeatedStream << "R" << "\n";
    for(size_t index = 0 ; index < this->RepeatedStickers.size(); ++index)
    {
        SerializedRepeatedStream << RepeatedStickers.at(index).createSerializedString();
    }
    return SerializedRepeatedStream.str();
}

//! Implementing a method to determine if album is full
bool SVV1_Album::isFull() const
{
    bool ResultCheck = false;
    if(this->AlbumStickerObjects.size() == SVV1_ExecutionConstants::ALBUM_MAX_STICKERS) {ResultCheck = true;}
    else {ResultCheck = false;}

    return ResultCheck;
}


//! Implementing a Method to Print the Album
void  SVV1_Album::printingAlbumData() const
{
    //?To do this we can also use the already defined values in the internal array. Using these we can also use that to print
    //? each value for the stickers that are stoed, and use said index to gather the name from constants file!!
        std::cout << "| Sticker Name |\t| Sticker Value |" << std::endl;
        for (size_t index = 0; index < this->Album.size(); ++index) {
            if (this->Album.at(index) == index + 1) // If index of array has a value corresponding to a card
            {
                std::cout << "|" << std::setw(16) << std::setfill(' ') << std::right
                          << SVV1_CardNames::CardNames.at(index)
                          << "|\t|"
                          << std::setw(15) << std::right << index + 1 << "|" << std::endl;
            }
            else
            {
                std::cout << "|" << std::setw(16) << std::setfill(' ') << std::right
                << "Falta Sticker" << "|\t|"
                << std::setw(15) << std::right << 0 << "|" << std::endl;
            }
        }
    }

    //! Method for printing frecuency of repeated values

void SVV1_Album::printingRepeatedFrecuency() const
{
    std::cout << "| Sticker Name |\t| Sticker Value |" << std::endl;
    for (size_t index = 0; index < this->FrecuencyOfRepeatedValues.size(); ++index) {
        std::cout << "|" << std::setw(16) << std::setfill(' ') << std::right
                  << SVV1_CardNames::CardNames.at(index)
                  << "|\t|"
                  << std::setw(15) << std::right << this->FrecuencyOfRepeatedValues.at(index)<< "|" << std::endl;
    }
}