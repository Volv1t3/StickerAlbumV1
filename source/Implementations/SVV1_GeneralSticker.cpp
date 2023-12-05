/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: General Sticker Class Definition
?3. Directions: DO NOT TOUCH
-----------------------------------------------**/
#include <string>
#include <sstream>
#include <iomanip>
#include "../Headers/SVV1_GeneralSticker.hpp"

//! Static Definitions

const char SVV1_GeneralSticker::STICKER_INDICATOR = 'S';

//! Implementacion de Constructores


SVV1_GeneralSticker::SVV1_GeneralSticker(unsigned int EnteredValueOfSticker, const std::string& EnteredDescriptionOfSticker,
                                         const std::string& EnteredStickerName)
{
    this->updateValueOfSticker(EnteredValueOfSticker);
    this->updateDescriptionOfSticker(EnteredDescriptionOfSticker);
    this->updateNameOfSticker(EnteredStickerName);
}

SVV1_GeneralSticker::SVV1_GeneralSticker(const std::string& SerializedString)
{
    this->ReadFromSerializedString(SerializedString);
}

//! Implementacion Metodos Get

std::string SVV1_GeneralSticker::getDescriptionOfSticker() const { return this->DescriptionOfSticker;}
unsigned int SVV1_GeneralSticker::getValueOfSticker() const { return this->ValueOfSticker;}
std::string SVV1_GeneralSticker::getNameOfSticker() const { return this->NameOfSticker;}

//! Implementacion Operator Overload ==

bool SVV1_GeneralSticker::operator==(SVV1_GeneralSticker &OtherInstance) {
    bool resultOfComparison = false;
    bool resultOfDescriptionCheck = std::equal(this->DescriptionOfSticker.begin(),
                                               this->DescriptionOfSticker.end(),
                                               OtherInstance.getDescriptionOfSticker().begin(),
                                               OtherInstance.getDescriptionOfSticker().end());
    bool resultOfNameCheck = std::equal(this->NameOfSticker.begin(),
                                        this->NameOfSticker.end(),
                                        OtherInstance.getNameOfSticker().begin(),
                                        OtherInstance.getNameOfSticker().end());
    bool resultOfValueCheck = this->ValueOfSticker == OtherInstance.getValueOfSticker();

    if (resultOfDescriptionCheck && resultOfNameCheck && resultOfValueCheck) {resultOfComparison = true;}

    return resultOfComparison;
}

//! Method for Returning Serialized String

[[maybe_unused]] std::string SVV1_GeneralSticker::createSerializedString() const
{
    std::stringstream SerializedString;
    SerializedString << SVV1_GeneralSticker::STICKER_INDICATOR
    <<  std::setw(20) << std::right << this->NameOfSticker
    << std::setw(50) << std::right << this->DescriptionOfSticker
    << std::setw(10) << std::right << this->ValueOfSticker
    << "\n";
    return SerializedString.str();
}

//! Implementation of Protected methods

SVV1_GeneralSticker& SVV1_GeneralSticker::updateDescriptionOfSticker(const std::string &NewDescriptionOfSticker)
{
    if (NewDescriptionOfSticker.length() > 0 && NewDescriptionOfSticker.length() <= 50) {
        this->DescriptionOfSticker = NewDescriptionOfSticker;
    }
    else
    {
        this->DescriptionOfSticker = "No Description";
    }

    return *this;
}

SVV1_GeneralSticker& SVV1_GeneralSticker::updateValueOfSticker(unsigned int NewValueOfSticker)
{
    if  (NewValueOfSticker >= 0 && NewValueOfSticker <= 25) { this->ValueOfSticker = NewValueOfSticker;}
    else {this->ValueOfSticker = 0;}

    return *this;
}

SVV1_GeneralSticker &SVV1_GeneralSticker::updateNameOfSticker(const std::string &NewStickerName)
{
    if (NewStickerName.length() > 0 && NewStickerName.length() <= 20) { this->NameOfSticker = NewStickerName;}
    else {this->NameOfSticker = "No Name";}

    return *this;
}

void SVV1_GeneralSticker::ReadFromSerializedString(const std::string &SerializedPartialString)
{
    std::string ReadNameOfSticker = SerializedPartialString.substr(1,20);
    this->updateNameOfSticker(ReadNameOfSticker);
    std::string ReadDescriptionOfSticker = SerializedPartialString.substr(21,50);
    this->updateDescriptionOfSticker(ReadDescriptionOfSticker);
    std::string ReadValueOfSticker = SerializedPartialString.substr(71,10);
    this->updateValueOfSticker(std::stoi(ReadValueOfSticker));
}

