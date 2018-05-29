/*********************************************************************
*                                                                    *
*                             Authors                                *
*                          Thomas Langseth                           *
*                                                                    *
*********************************************************************/

#ifndef ZOOTOPIA_H
#define ZOOTOPIA_H

#include <QWidget>
#include <QStackedWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QtWidgets>
#include <QCheckBox>
#include <string>
#include <vector>
#include <zootopiaLogic.h>
/*
 * Every group member have contributed more or less on this.
*/
namespace Ui {
class Zootopia;
}

class Zootopia : public QWidget
{
    Q_OBJECT

public:
    explicit Zootopia(QWidget *parent = 0);
    ~Zootopia();
    Owner temporaryOwner;

private slots:
    void saveButton();
    void searchButton();
    void changePetInfo(const int index);

private:
    void fillOwnerLineEdits(const Owner &owner);
    void fillPetLineEdits(vector<Pet> &pets);
    void clearPetLineEdits();
    void setSpeciesDropdown();

    Ui::Zootopia *ui;
    QVBoxLayout *mainPageLayout;

    //Owner labels
    QLineEdit *searchInput;
    QPushButton *search;
    QLabel *ownerHeaderLabel;
    QLabel *ownerNameLabel;
    QLabel *ownerPhoneLabel;
    QLabel *ownerAddressLabel;
    QLabel *ownerEmailLabel;

    //Owner info
    QLineEdit *ownerNameLineEdit;
    QLineEdit *ownerPhoneLineEdit;
    QLineEdit *ownerAddressLineEdit;
    QLineEdit *ownerEmailLineEdit;

    //Pet labels
    QComboBox *petList;
    QLabel *petHeaderLabel;
    QLabel *petNameLabel;
    QLabel *petSpeciesLabel;
    QLabel *petChippedLabel;
    QLabel *chipNumLabel;
    QLabel *petBreedLabel;
    QLabel *petConsiderationsLabel;

    //Pet inputs
    QLineEdit *petNameLineEdit;
    QLineEdit *petSpeciesLineEdit;
    QComboBox *petSpeciesBox;
    QLineEdit *petBreedLineEdit;
    QLineEdit *chipNumLineEdit;
    QCheckBox *petChippedCheckBox;
    QTextEdit *petConsiderationsTextEdit;

    //Buttons
    QPushButton *saveInfo;
    QPushButton *ExitButton;
};


#endif // ZOOTOPIA_H
