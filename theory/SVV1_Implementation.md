<h1 style="text-align: center; color: darkseagreen; font-family: 'Segoe UI', sans-serif; font-size: 14pt">
Universidad San Francisco de Quito</h1>
<h2 style="text-align: center; color: darkseagreen; font-family: 'Segoe UI', sans-serif; font-size: 12pt">
Ingenieria en Ciencias de la Computacion - Programacion Avanzada en C++
</h2>

***
<h6  style="color: antiquewhite; font-family: 'Segoe UI', sans-serif; text-align: justify"> Datos Principales </h6>
<ul style=" list-style: lower-latin">
<li>
    <b>Integrantes:</b> <br>
Leonardo Olmedo: 327960;<br>
Santiago Arellano: 328370
</li>
<li>
    <b>Fecha de Entrega</b> : <code> 10 de Dic. 2023</code>
</li>
<li>
    <b>Descripción del Proyecto:</b> Realizar una implementación en base de OOP de un álbum de cromos, en donde el usuario pueda
salir y regresar a la aplicación y los datos perduren a través de diferentes sesiones.
</li>
</ul>

***
<h6  style="color: antiquewhite; font-family: 'Segoe UI', sans-serif; text-align: justify"> Descripción del Presente Archivo
</h6>
<p>El presente archivo muestra el proceso de pensamiento detrás de la implementación realizada para el proyecto, 
decisiones tomadas en el mismo, pruebas de código y diversos argumentos que fueron considerados para cada sección importante del 
desarrollo de este proyecto.
<br> Con esto en mente el documento se divide en ciertas secciones, las cuales contienen el análisis realizado para una de las secciones requeridas para el 
proyecto. <br><br> Con motivo de presentar un archivo que pueda ser fácil de comprender y compartir, se ha decidido continuar el proceso de escritura en ingles, 
lo que facilita la escritura de código y comentarios en MarkDown</p>

***
<h6  style="color: antiquewhite; font-family: 'Segoe UI', sans-serif; text-align: center"> Sticker Representation </h6>
<p>As defined within the strcuture file sent out for this project, we are to design from stracth a way to represent the stickers, deciding their type and their way of storing name and value. 
<br> In this sense we are given compete freedom to decide the topic of the album and the way we are to store the values that will be analized through the program. In light of this it becomes important to ask, what the operations 
will be done with the stickers, will they need any overlaods, etc. For this reason, the most basic look at operations that must be done is the following</p>
<ul>
<li>
<b> Append:</b> Our stickers must not be too complicated in nature since they are to be appended into either <code> std::vector</code> or <code> Stickers[]</code>
arrays that will keep track of them for the user.
</li>
<br>
<li>
<b> Comparison: </b> At some point during execution we will have to create a set of Stickers, and these will have to be comparable, since a sticker album does not allow for repeated ones, 
there must exist a way for them to be easily comparable, be it through code, name or data, which will allow us to find this value quick inside the aforementioned structure holders.
 </li><br>
<li> <b>Polymorphic Instantiation: </b> Since we are going to be working with a set of different types of stickers, it would be good to have a way to polymorphically instantiate them as well as point to them, such
that memory handling can be done with the same structure and not a set of holders too.</li><br>
<li><b>Serialization: </b> Since we are to work with data that can be easily brought into the program, whether by user interaction or by default, we need to find a way to serialize
the data such that it is always available for the user and from which we can instantiate these stickers</li><br>
<li> <b>Instantiation from Serialization: </b> Based on the objectives from the project instructions file  we need to define a constructor for the stickers which can, from a serialized string
be able to read back its data and define values directly into itself, such that we can use polymorphic loops to reinstantiate them after the program has closed</li>
<br><br>
</ul>
<p>Based on the operations defined previously, one important question to asks us is if its useful to create a polymorphic structure in terms of inheritance, or if it would be better to define a 
single class and instantiate from it 25 times.
<br><br>
To contemplate this we must understand that the project requires the instantiation of at least 25 stickers per single album, which in terms of a hierarchical structure would mean a tree with
25 single leaves. If we think about this the amount of code repetition we would have to do is large. There would need to be a class define, <b> WITH NO NEW METHODS</b>, per every single abstract class
children. Therefore, there would be 25 empty files lingering around in the source file, which in terms of organization is not appropriate for a project this small.
<br> Furthermore, if we were to use this approach to use polymorphic structures we would need to overload operators for each instance of the class, or in the very least we would have to redefine that operator. And if we don not do this, by doing all of the operations inside of the base class,
we are still pushing out 25 files of useless class overwrites which do not provide any kind of usefulness to the file.
<br><br>
Rather the most ingenious solution there here its so simply create  a single class, not an abstract class but a base class for the stickers,
give it the methods we need and during execution, call a single use method which will take care of defining these class instances with a value from 0 to 25 and a name based on an array.<br>
Through this method we can not only use OOP but also functional programming and reduce the amount of overhead that the compiler has to deal with for the project.
</p>
<p style="color: antiquewhite; text-align: center; font-weight: bold; font-family: inherit"> Therefore, our best solution would be to generate one class file and instante this 25 times during the execution of our program.</p>
<br>

<p>To achieve this we would need a class that looks somewhat similar to the following definition</p>

```c++
#ifndef ...
#define ...
#include <string>
class SVV1_GeneralSticker
{
    private /* The following section will hold initial data*/:
    std::string DescriptionOfSticker; //Will be updated in instantiation
    unsigned int ValueOfSticker{0}; //Will be updated in instantiation and 
                                    // can be considered as if it were the index of said Sticker
    public /* The following section wil hold abstract functionality and the initial constructors*/:
    /*Serialized Data Constructor*/
    SVV1_GeneralSticker(std::string SerializedPartialString = "");
    /* Default Constructor*/
    SVV1_GeneralSticker(unsigned int EnteredValueOfSticker, std::string EnteredDescriptionOfSticker);
    /* Method for Returning Description of Sticker (Debug and Test Only)*/
    std::string getDescriptionOfSticker();
    /*Method for Returning Value of Sticker (Debug and Test Only)*/
    unsigned int getValueOfSticker();
    /*Operator overloading for ==*/
    bool operator==(SVV1_AbstractStickerClass& OtherInstance);
    /* Method for Returning Serialized String*/
    std::string getSerializedString();
    protected:
    /*Method for Description Update */
    SVV1_GeneralSticker& updateDescriptionOfSticker(std::string NewDescriptionOfSticker);
    /*Method for Value Update*/
    SVV1_GeneralSticker& updateValueOfSticker(unsigned int NewValueOfStricker);
    /* Method from reading data from serialized string*/
    void ReadFromSerializedString(std::SerializedPartialString);
};
```

<p> As for any new development job a few question arise about the implementation of certain methods here, mainly how we will use the <code>ReadFromSerializedString</code> to get the information needed to instantiate the class.
Since this value is passed as a single string, it certainly would prove challenging if we did not know how we were saving the data, but for our use case, the data we are saving will always follow the same structure.
<br><br> It is because of this very reason that we have the following function defined inside of the general class definition.
<code>std::string getSeralizedString()</code>. Through these method we can control the way the data is stored inside of the file through defined spacing and constant values for character lengths and even separators. A good idea
of how this function would work is defined, 
</p>

```c++
#include ...
#include <string>
std::string getSerializedString()
{
    std::stringstream SerializedString;
    SerializedString << SVV1_GeneralSticker::STICKER_INDICATOR
    <<  std::setw(20) << std::right << this->NameOfSticker
    << std::setw(50) << std::right << this->DescriptionOfSticker
    << std::setw(10) << std::right << this->ValueOfSticker
    << "\n";
    return SerializedString.str();
}
```

<p> The body of code presented before represents an initial approach to organizing every data member
of the file regarding its type. For now the constant <code>STICKER_INDICATOR</code> references a character
which can be used to read in from the file and determine that it is a sticker and not some other structures. The following naming 
conventions will be used when it comes to storing different objects </p>
<br>
<ul>
<li> <b>S : </b> S will represent stickers, this character (in uppercase) will be read during line parsing of generated file;
</li><br>
<li> <b>A : </b> A will be used to indicate an Album, since the user can generate basically <code> n </code> number of albums we need to have
a way to store them in the file and iterate through them.
</li>
</ul>

***
<h6  style="color: antiquewhite; font-family: 'Segoe UI', sans-serif; text-align: center"> Sticker Pack Representation </h6>

<p> The observant reader might have noticed that in the last section we failed to detail which constant will be used to store any kind of 
sticker packet that the user might open again. And this is not an incident of poor attention to detail, but rather a conscious design choice. 
In the game of collecting stickers, when someone does not get a good set they usually go to another vendor or ask for another lot to choose from. This means that
humans in general do not tolerate repetition as well as a computer might do or as an iterative program might do. As such we shouldn't and really musn't store any kind of
sticker pack information since this would make the outcome of the other pack known and probably take out the fun of having a random number generator on them or shuffling randomly </p>

<p> It is because of this reason that I have chosen the following implementation details to be followed when it comes to the cards at play inside their respective packs</p>

<ul>
<li> <b> Adaptability: </b> Since our sticker cards can be instantiated on the fly either by giving them a serialized string or by giving them the data, we can create these packs on the fly too,
with a good method to generate cards the number of times the user wants we can define a method that creates these cards based on randomized numerical
inputs like <code> std::random_device </code> values using int distributions, we generate from 0 to 25 and instantiate on the fly and randomly 
the values to be stored in the packs.</li>
<li> <b> Portability and size: </b> Since our objects have to hold five stickers each, and we also have to generate an <code>n </code>number of them it follows that the structure must be as 
lightweight as possible, having only the necessary values to be stored as a private data value.</li>
<li> <b> Access and Addition of Stickers: </b> Since the previous class for stickers already has its own form to serialize its own data, we have to focus mainly on how to add those stickers in here,
since a pack also cannot hold any kind of duplicated sticker we make use of the overloaded == operator to make comparisons  between cards and decide on the fly. Furthermore we can reduce the adding and checking to a simple
method to keep the class lightweight</li>
<li> <b> Serialization of Data: </b> Based on the current structure for this class we will only need to define a constant like the list above, 
and a function to serialize it using its name, for instance pack 0, pack 1, pack 2, pack 3, etc. While we do not need that name since there is no need to 
name the packs in any way, it would be better that if we are calling them we can keep track of how many there are.</li>
</ul>
<br>
<p> As can be noted, the implementation of said class is not exactly challenging, yet the implementation is not straightforward either, we have got to analize
the effects of continuous integration between our initial data class and our sticker pack class, as such I propose th following initial class definition</p>
<br>

```c++

#include ....
#include "./../SVV1_GeneralSticker"

class SVV1_StickerPack
{
private:
    /* Data member to hold the cards assigned to an instance*/
    std::vector<SVV1_GeneralSticker> DataValueArrayHolder{};
    /* Data member to keep track of instantiation index, given by outside methods defined in later sections*/
    unsigned int StickerPackIndex{0};
    public:
    /* Public Constructor which will not take any values except for the initial index of instantiation*/
    [[maybe_unused]] explicit SVV1_StickerPack(unsigned int InstantiationIndexForPack);
    /* Method to Add cards into the pack */
    [[maybe_unused]] SVV1_StickerPack& addStickerToPack(SVV1_GeneralSticker& OtherStickerInstance);
    /*Method for Serializing the name of the pack */
    [[maybe_unused, nodiscard]] std::string SerializePack();
    /*Method for accessing the data value vector for visualization*/
    [[maybe_unused, nodiscard]] std::vector<SVV1_GeneralSticker> getDataArray() const;
    /*Method for returning a certain instance inside the vector*/
    [[maybe_unused, nodiscard]] SVV1_GeneralSticker getStickerAtLocationInVector(size_t indexOfSticker);
};
```



