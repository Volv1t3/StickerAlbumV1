/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: General Sticker Class Definition
?3. Directions: Class has already been implemented new methods must have unit tests and integration tests
-----------------------------------------------**/
#include <string>
#ifndef STICKERALBUMV1_SVV1_GENERALSTICKER_HPP
#define STICKERALBUMV1_SVV1_GENERALSTICKER_HPP


class SVV1_GeneralSticker {
private /* The following section will hold initial data*/:
    std::string DescriptionOfSticker; //Will be updated in instantiation
    unsigned int ValueOfSticker{0}; //Will be updated in instantiation and
    // can be considered as if it were the index of said Sticker
    std::string NameOfSticker; // Will be updated instantiation
public /* The following section wil hold abstract functionality and the initial constructors*/:
    /* Default Constructor*/
    [[maybe_unused]] explicit SVV1_GeneralSticker(const std::string &SerializedDataMember);
    [[maybe_unused]] SVV1_GeneralSticker(unsigned int EnteredValueOfSticker, const std::string& EnteredDescriptionOfSticker, const std::string& EnteredStickerName);
    [[maybe_unused]] ~SVV1_GeneralSticker()=default;
    /* Method for Returning Description of Sticker (Debug and Test Only)*/
    [[maybe_unused, nodiscard]] std::string getDescriptionOfSticker() const;
    /*Method for Returning Value of Sticker (Debug and Test Only)*/
    [[maybe_unused, nodiscard]] unsigned int getValueOfSticker() const ;
    /* Method for Returning Name of The Sticker (Debug and Test Only)*/
    [[maybe_unused, nodiscard]] std::string getNameOfSticker() const ;
    /*Operator overloading for ==*/
    bool operator==(const SVV1_GeneralSticker& OtherInstance) const;
    /* Method for Returning Serialized String*/
    [[maybe_unused, nodiscard]] std::string createSerializedString() const;
    static const char STICKER_INDICATOR;
protected:
    /*Method for Description Update */
    [[maybe_unused]] SVV1_GeneralSticker& updateDescriptionOfSticker(const std::string &NewDescriptionOfSticker);
    /*Method for Value Update*/
    [[maybe_unused]] SVV1_GeneralSticker& updateValueOfSticker(unsigned int NewValueOfSticker);
    [[maybe_unused]] SVV1_GeneralSticker& updateNameOfSticker(const std::string &NewStickerName);
    /* Method from reading data from serialized string*/
    [[maybe_unused]] void ReadFromSerializedString(const std::string &SerializedPartialString);
};


#endif //STICKERALBUMV1_SVV1_GENERALSTICKER_HPP
