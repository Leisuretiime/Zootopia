#include <QtXml/QtXml>
#include <iostream>
#include <string>
#include <QString>
#include <qDebug>
#include <QFileInfo>
#include <zootopiaLogic.h>
using namespace std;
/*
 * Every group member have contributed more or less on this.
*/

void saveOwnerAndPetInfo(const Owner owner, const Pet pet){

    QDomDocument document = (fileExists()) ? getContentOfFile() : createXMLfile();
    QDomElement root = document.firstChildElement();

    QDomElement ownerElement;
    QDomElement petElement;
    try{
        ownerElement = fetchOwnerIfExists(root, owner.email);
        updateOwnerAttributes(ownerElement, owner);
        try{
            petElement = fetchPetIfExists(ownerElement, pet.name);
            updatePetAttributes(petElement, pet);
        }
        catch (exception petDoesntExist){
            petElement = createPetElement(document, pet);
        }
    }
    catch(exception ownerDoesntExist){
        ownerElement = createOwnerElement(document, owner);
        petElement = createPetElement(document, pet);
    }

    ownerElement.appendChild(petElement);
    root.appendChild(ownerElement);
    insertToXMLfile(document);

}
Owner getOwnerAndPetInfo(const QString & ownerEmail){

    QDomDocument document = (fileExists()) ? getContentOfFile() : createXMLfile();
    QDomElement root = document.firstChildElement();

    QDomElement ownerElement = fetchOwnerIfExists(root, ownerEmail);
    Owner owner;
    owner.email = ownerElement.attribute("Email");
    owner.name = ownerElement.attribute("Name");
    owner.phone = ownerElement.attribute("Phone").toInt();
    owner.adress = ownerElement.attribute("Adress");

    owner.pets = getAllPetsOfOwner(ownerElement);
    return owner;
}
vector<Pet> getAllPetsOfOwner(const QDomElement & ownerElement){

    vector<Pet> listOfPets;
    for (QDomElement petInLoop = ownerElement.firstChildElement(); !petInLoop.isNull(); petInLoop = petInLoop.nextSiblingElement()){
        listOfPets.push_back(Pet());
        listOfPets.back().name = petInLoop.attribute("Name");
        listOfPets.back().species = static_cast<Species>(petInLoop.attribute("Species").toInt());
        listOfPets.back().breed = petInLoop.attribute("Breed");
        listOfPets.back().chip = petInLoop.attribute("Chip");
        listOfPets.back().otherinfo = petInLoop.attribute("OtherInfo");
    }
    return listOfPets;
}

QDomElement fetchOwnerIfExists(const QDomElement & root, QString const &ownerEmail){

    QDomElement ownerInLoop;
    for (ownerInLoop = root.firstChildElement(); !ownerInLoop.isNull(); ownerInLoop = ownerInLoop.nextSiblingElement()){
        if (ownerInLoop.attribute("Email") == ownerEmail)
            return ownerInLoop;
    }
    throw invalid_argument("Pet doesn't exist");
    return ownerInLoop;
}
QDomElement fetchPetIfExists(const QDomElement & ownerElement, QString  const &petName){

    QDomElement petInLoop;
    for (petInLoop = ownerElement.firstChildElement(); !petInLoop.isNull(); petInLoop = petInLoop.nextSiblingElement()){
        if (petInLoop.attribute("Name") == petName){
            return petInLoop;
        }
    }
    throw invalid_argument("Pet doesn't exist");
    return petInLoop;
}
QDomElement createOwnerElement(QDomDocument & document, const Owner & owner){
    QDomElement newOwnerElement = document.createElement("Owner");
    newOwnerElement.setAttribute("Email", owner.email);
    newOwnerElement.setAttribute("Name", owner.name);
    newOwnerElement.setAttribute("Adress", owner.adress);
    newOwnerElement.setAttribute("Phone", owner.phone);
    return newOwnerElement;
}
QDomElement createPetElement(QDomDocument & document, const Pet & pet){
    QDomElement newPetElement = document.createElement("Pet");
    newPetElement.setAttribute("Name", pet.name);
    newPetElement.setAttribute("Breed", pet.breed);
    newPetElement.setAttribute("Species", pet.species);
    newPetElement.setAttribute("Chip", pet.chip);
    newPetElement.setAttribute("OtherInfo", pet.otherinfo);
    return newPetElement;
}
void updateOwnerAttributes(QDomElement & ownerElement, const Owner & owner){

    ownerElement.setAttribute("Email", owner.email);
    ownerElement.setAttribute("Name", owner.name);
    ownerElement.setAttribute("Adress", owner.adress);
    ownerElement.setAttribute("Phone", owner.phone);
}
void updatePetAttributes(QDomElement & petElement, const Pet & pet){

    petElement.setAttribute("Name", pet.name);
    petElement.setAttribute("Breed", pet.breed);
    petElement.setAttribute("Species", pet.species);
    petElement.setAttribute("Chip", pet.chip);
    petElement.setAttribute("OtherInfo", pet.otherinfo);

}

QDomDocument createXMLfile(){
    QFile file(pathToXMLFile);
    QDomDocument document;
    QDomElement root = document.createElement("DayCare");
    document.appendChild(root);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "File failed to open for writing";
    }
    else {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "finished";
    }
    return document;
}
QDomDocument getContentOfFile(){

    QDomDocument document;
    QFile file(pathToXMLFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "File failed to open for writing";
    }
    else {
        document.setContent(&file);
        file.close();
    }
    return document;
}
void insertToXMLfile(const QDomDocument & document){

    QFile file(pathToXMLFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "File faled to open for writing";
    }
    else {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "finished";
    }
}
bool fileExists() {
    QFileInfo check_file(pathToXMLFile);
    return check_file.exists() && check_file.isFile();
}
