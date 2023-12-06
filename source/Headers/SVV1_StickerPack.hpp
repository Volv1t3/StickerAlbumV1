/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: General Sticker Class Definition
?3. Directions: Class has been implemented, new methods have to be unit and integration tested
-----------------------------------------------**/
#include <string>
#include <vector>
#include "SVV1_GeneralSticker.hpp"
#ifndef STICKERALBUMV1_SVV1_STICKERPACK_HPP
#define STICKERALBUMV1_SVV1_STICKERPACK_HPP


class SVV1_StickerPack
{
private:
    /* Data member to hold the cards assigned to an instance*/
    std::vector<SVV1_GeneralSticker> DataValueArrayHolder;
    /* Data member to keep track of instantiation index, given by outside methods defined in later sections*/
    unsigned int StickerPackIndex{0};
public:
    /* Public Constructor which will not take any values except for the initial index of instantiation*/
    [[maybe_unused]] explicit SVV1_StickerPack() = default;
    /* Method to Add cards into the pack */
    [[maybe_unused]] SVV1_StickerPack& addStickerToPack(const SVV1_GeneralSticker& OtherStickerInstance);
    /*Method for accessing the data value vector for visualization*/
    [[maybe_unused, nodiscard]] std::vector<SVV1_GeneralSticker> getDataArray() const;
    /*Method for returning a certain instance inside the vector*/
    [[maybe_unused, nodiscard]] SVV1_GeneralSticker getStickerAtLocationInVector(size_t indexOfSticker);
    /*Method for Serializing the pack and its contents*/
    [[maybe_unused, nodiscard ]] std::string getSerializedPack() const ;

    /*Iterators */
    typename std::vector<SVV1_GeneralSticker>::const_iterator begin();
    typename std::vector<SVV1_GeneralSticker>::iterator  end();

    static const char PACK_INDICATOR;
};


#endif //STICKERALBUMV1_SVV1_STICKERPACK_HPP
