#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QtXml/QtXml>
#include <QFile>
#include <QString>
#include <map>
/*
 * Every group member have contributed more or less on this.
*/
using namespace std;

enum Species {
    Cat,
    Dog,
    Bird,
    Rodent,
    Reptilian
};

struct Pet {
    QString name;
    QString breed;
    Species species;
    QString chip;
    QString otherinfo;
};

struct Owner {
    int phone;
    QString name;
    QString email;
    QString adress;
    vector<Pet> pets;

};

constexpr char pathToXMLFile[] = "foo.xml";

void saveOwnerAndPetInfo(const Owner owner, const Pet pet);
Owner getOwnerAndPetInfo(const QString &ownerEmail);
vector<Pet> getAllPetsOfOwner(const QDomElement &ownerElement);

QDomElement fetchOwnerIfExists(const QDomElement & root, QString  const &ownerEmail);
QDomElement fetchPetIfExists(const QDomElement & ownerElement, QString  const &petName);
QDomElement createOwnerElement(QDomDocument & document, const Owner & owner);
QDomElement createPetElement(QDomDocument & document, const Pet & pet);
void updateOwnerAttributes(QDomElement & ownerElement, const Owner & owner);
void updatePetAttributes(QDomElement & petElement, const Pet & pet);

QDomDocument createXMLfile();
QDomDocument getContentOfFile();
void insertToXMLfile(const QDomDocument & document);
bool fileExists();

#endif // XMLHANDLER_H

