/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: Album CLass Definition
?3. Directions: Class has been implemented, new methods have to be unit and integration tested
-----------------------------------------------**/
#include <string>
#include <vector>
#include <array>
#include "SVV1_GeneralSticker.hpp"
#include "SVV1_StickerPack.hpp"
#ifndef STICKERALBUMV1_SVV1_ALBUM_HPP
#define STICKERALBUMV1_SVV1_ALBUM_HPP

class SVV1_Album
{
private:
    /*Area to store the cards that take part of the Album*/
    std::array<unsigned int , 25> Album{};
    std::vector<SVV1_GeneralSticker> AlbumStickerObjects;
    /*Area to store the cards that have been repeated for this album*/
    std::vector<SVV1_GeneralSticker> RepeatedStickers;
    /* Area to store boolean to tell if the album its full, helpful to stop iterative calls if the album has already been filled */
    bool isComplete = false;
public:
    /*Main Constructor, will not take argument since it can only generate its own structures*/
    [[maybe_unused]] SVV1_Album()=default;
    /*Method to add a Cart to the album, it itself will check if it's already there*/
    [[maybe_unused]] SVV1_Album& emplaceAStickerOnAlbum(const SVV1_GeneralSticker& StickerInstance);
    /*Method for Serializing the Album*/
    [[maybe_unused, nodiscard]] std::string serializingAlbum() const ;
   // [[maybe_unused]] void deserializingAlbum(std::string SerializedAlbumEntryString);
    /*Public Constant such that we have a way to know this is an Album Class*/
    const static char ALBUM_INDICATOR;
    /*Method for Data Visualizatnio in form of a table of numbers and names */
    // [[maybe_unused]] void printingAlbumData();
};
#endif //STICKERALBUMV1_SVV1_ALBUM_HPP
