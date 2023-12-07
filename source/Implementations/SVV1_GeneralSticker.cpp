/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: General Sticker Class Definition
?3. Directions: New methods must be added in their corresponding sections, consider headings defined by //!
-----------------------------------------------**/
#include <string>
#include <sstream>
#include <iomanip>
#include "../Headers/SVV1_GeneralSticker.hpp"
#include "../values/SVV1_ExecutionConstants.hpp"

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

bool SVV1_GeneralSticker::operator==(const SVV1_GeneralSticker &OtherInstance) const {
    bool resultOfComparison = false;
    bool resultOfDescriptionCheck = std::equal(this->DescriptionOfSticker.begin(),
                                               this->DescriptionOfSticker.end(),
                                               OtherInstance.getDescriptionOfSticker().begin());
    bool resultOfNameCheck = std::equal(this->NameOfSticker.begin(),
                                        this->NameOfSticker.end(),
                                        OtherInstance.getNameOfSticker().begin());
    bool resultOfValueCheck = {(this->ValueOfSticker == OtherInstance.getValueOfSticker()) ? true : false};

    if (resultOfDescriptionCheck && resultOfNameCheck && resultOfValueCheck) {resultOfComparison = true;}

    return resultOfComparison;
}
void SVV1_GeneralSticker::operator=(const SVV1_GeneralSticker &OtherInstance)
{
    this->updateDescriptionOfSticker(OtherInstance.getDescriptionOfSticker());
    this->updateNameOfSticker(OtherInstance.getNameOfSticker());
    this->updateValueOfSticker(OtherInstance.getValueOfSticker());
}

//! Method for Returning Serialized String

[[maybe_unused]] std::string SVV1_GeneralSticker::createSerializedString() const
{
    std::stringstream SerializedString;
    SerializedString << SVV1_GeneralSticker::STICKER_INDICATOR
    <<  std::setw(SVV1_ExecutionConstants::STICKER_NAME_LENGTH) << std::right << this->NameOfSticker
    << std::setw(SVV1_ExecutionConstants::STICKER_DESCRIPTION_LENGTH) << std::right << this->DescriptionOfSticker
    << std::setw(SVV1_ExecutionConstants::STICKER_VALUE_LENGTH) << std::right << this->ValueOfSticker
    << "\n";
    return SerializedString.str();
}

//! Implementation of Protected methods

SVV1_GeneralSticker& SVV1_GeneralSticker::updateDescriptionOfSticker(const std::string &NewDescriptionOfSticker)
{
    if (NewDescriptionOfSticker.length() > 0 && NewDescriptionOfSticker.length() <= SVV1_ExecutionConstants::STICKER_DESCRIPTION_LENGTH) {
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
    if  (NewValueOfSticker >= 0 && NewValueOfSticker <= SVV1_ExecutionConstants::STICKER_MAX_VALUE)
    { this->ValueOfSticker = NewValueOfSticker;}
    else {this->ValueOfSticker = 0;}

    return *this;
}

SVV1_GeneralSticker &SVV1_GeneralSticker::updateNameOfSticker(const std::string &NewStickerName)
{
    if (NewStickerName.length() > 0 && NewStickerName.length() <= SVV1_ExecutionConstants::STICKER_NAME_LENGTH)
    { this->NameOfSticker = NewStickerName;}
    else {this->NameOfSticker = "No Name";}

    return *this;
}

void SVV1_GeneralSticker::ReadFromSerializedString(const std::string &SerializedPartialString)
{
    if (SerializedPartialString.empty())
    {
        this->updateNameOfSticker("No Name");
        this->updateDescriptionOfSticker("No Description");
        this->updateValueOfSticker(0);
    }
    else {
        std::string ReadNameOfSticker = SerializedPartialString.substr(1, SVV1_ExecutionConstants::STICKER_NAME_LENGTH);
        this->updateNameOfSticker(ReadNameOfSticker);
        std::string ReadDescriptionOfSticker = SerializedPartialString.substr(21,
                                                                              SVV1_ExecutionConstants::STICKER_DESCRIPTION_LENGTH);
        this->updateDescriptionOfSticker(ReadDescriptionOfSticker);
        std::string ReadValueOfSticker = SerializedPartialString.substr(71,
                                                                        SVV1_ExecutionConstants::STICKER_VALUE_LENGTH);
        this->updateValueOfSticker(std::stoi(ReadValueOfSticker));
    }
}


