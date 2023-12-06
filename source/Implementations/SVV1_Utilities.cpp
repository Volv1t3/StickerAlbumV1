/**-----------------------------------------------
!                Estructura General
?1. Author : Santiago Arellano,
?2. Definition: General Utilities Modules For Printing, Debugging, Generation, defined implementations
?3. Directions: Functional programming module, more functions will be added here as the project progresses
-----------------------------------------------**/
#include <string>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "./../Headers/SVV1_Utilities.hpp"



//! Metdho for printing a 120 character line on the screen
[[maybe_unused]] void UtilPrintLineOnScreen()
{
    std::cout << std::setw(119) << std::setfill('=') << ""<< "\n";
}

[[maybe_unused]] void UtilPrintTextWithinScreen(const std::string& MessageToPrint)
{
    int totalWidth = 120;
    int messageLength = MessageToPrint.length();
    int extraChars = 6; // for "| " and " |" and spaces
    int equalSignsLength = (totalWidth - messageLength - extraChars) / 2;
    if (MessageToPrint.length() %2 == 0)
    {
        std::cout << std::setw(equalSignsLength +1) << std::setfill('=') << ""
                  << "| " << MessageToPrint << " |"
                  << std::setw(equalSignsLength) << std::setfill('=') << "" << "\n";
    }
    else
    {
        int adjustmentChars = (totalWidth - messageLength - extraChars) % 2;
        std::cout << std::setw(equalSignsLength +1) << std::setfill('=') << ""
                  << "| " << MessageToPrint << " |"
                  << std::setw(equalSignsLength + adjustmentChars) << std::setfill('=') << "" << "\n";
    }
}
[[maybe_unused]] void UtilPrintingApplicationInformation()
{
    UtilPrintTextWithinScreen("Universidad San Francisco de Quito");
    UtilPrintTextWithinScreen("Ingenieria en Ciencias de la Computacion - Programacion Avanzada en C++");
    UtilPrintTextWithinScreen("Proyecto 2 - StickerAlbumV1");
    UtilPrintTextWithinScreen("Version 1.0 | Minor 0.1 | Patch | 0.01 ");
    UtilPrintTextWithinScreen("Autores: Santiago Arellano, Leonardo Olmedo");
    UtilPrintLineOnScreen();
    UtilPrintTextWithinScreen("Instrucciones Generales:");
    UtilPrintLongMessageOnPredefLength("El presente programa muestra una abstraccion de un album de cromos"
                                       "desarrollado en C++ a traves de programacion orientada a objetos y programacion funcaional."
                                       "Dentro de este programa se podra evidenciar el trabajo realizado en tanto al desarrollo de una aplicacion robusta "
                                       "y con capacidad de amplicacion a futuro, asi como conceptos especificos desarrollados en "
                                       "la clase como manejo de archivos.\n"
                                       "Para utilizar el siguiente programa no hace falta realizar un registro del usuario, el programa se encarga de crear una partida "
                                       "de dato generales para cada usuario basado en lo que realice dentro de la aplicacion, datos que se pueden volver a cargar en cualquier momento.");
}


[[maybe_unused]] void UtilPrintLongMessageOnPredefLength(std::string MessageToPrint)
{
        int totalWidth = 120;
        int extraChars = 6; // for "| " and " |" and spaces
        int maxMessageWidth = totalWidth - extraChars;

        // Split the message into words
        std::vector<std::string> words;
        std::string word;
        for (char c : MessageToPrint) {
            if (c == ' ') {
                words.push_back(word);
                word.clear();
            } else {
                word += c;
            }
        }
        words.push_back(word); // push the last word

        // Construct lines
        std::vector<std::string> lines;
        std::string line = words[0];
        for (int i = 1; i < words.size(); ++i) {
            if (line.length() + 1 + words[i].length() > maxMessageWidth) {
                lines.push_back(line);
                line = words[i];
            } else {
                line += " " + words[i];
            }
        }
        lines.push_back(line); // push the last line

        // Print lines in box
        std::cout << std::string(totalWidth, '=');
        for (const std::string& line : lines)
        {
            std::cout << line << "\n";
        }
    }
