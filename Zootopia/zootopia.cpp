/*********************************************************************
*                                                                    *
*                             Authors                                *
*                          Thomas Langseth                           *
*                                                                    *
*********************************************************************/

#include "zootopia.h"
#include "ui_zootopia.h"
#include <iostream>
#include "zootopiaLogic.h"
using namespace std;
/*
 * Every group member have contributed more or less on this.
*/

Zootopia::Zootopia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Zootopia)
{
    //this->temporaryOwner = nullptr;
    /* Landing page in the application,
     * shows a form used to enter information
     * about a pet and its owner that are
     * checking in*/
    QVBoxLayout *mainPageLayout = new QVBoxLayout;
    ownerHeaderLabel = new QLabel(tr("Owner info"));
    petHeaderLabel = new QLabel(tr("Pet info"));

    searchInput = new QLineEdit;
    searchInput->setPlaceholderText("Search by email");
    //searchInput->setValidator(Namevalidator);
    search = new QPushButton("Search", this);;
    connect(search, SIGNAL(released()), this, SLOT(searchButton()));

    QHBoxLayout *searchRow = new QHBoxLayout;
    searchRow->addWidget(searchInput);
    searchRow->addWidget(search);

        /*Regular expressions used to control input fields*/
    const QString Phone = "^((\\+?(\\d{2}))\\s?)?((\\d{2})|(\\((\\d{2})\\))\\s?)?(\\d{3,15})(\\-(\\d{3,15}))?$";
    QRegularExpression Phonerx(Phone);
    QValidator *Phonevalidator = new QRegularExpressionValidator(Phonerx, this);

    const QString Email = "^[A-Z0-9a-z._-]{1,}@(\\w+)(\\.(\\w+))(\\.(\\w+))?(\\.(\\w+))?$";
    QRegularExpression Emailrx(Email);
    QValidator *Emailvalidator = new QRegularExpressionValidator(Emailrx, this);

    const QString Name = "^[a-zA-Z-][a-zA-Z-\\s]+$";
    QRegularExpression Namerx(Name);
    QValidator *Namevalidator = new QRegularExpressionValidator(Namerx, this);

        /* QLabels and QLineEdits for input
         * of owners name and phone used in input form */
    ownerNameLabel = new QLabel(tr("Name:"));
    ownerNameLineEdit = new QLineEdit;
    ownerNameLineEdit->setValidator(Namevalidator);

    ownerPhoneLabel = new QLabel(tr("Phone: "));
    ownerPhoneLineEdit = new QLineEdit;
    ownerPhoneLineEdit->setValidator(Phonevalidator);

        /* QHBoxLayout containing QWidgets for name
         * and phone numbers used in input form */
    QHBoxLayout *ownerNameRow = new QHBoxLayout;
    ownerNameRow->addWidget(ownerNameLabel);
    ownerNameRow->addStretch();
    ownerNameRow->addWidget(ownerNameLineEdit);
    ownerNameRow->addStretch();
    ownerNameRow->addWidget(ownerPhoneLabel);
    ownerNameRow->addStretch();
    ownerNameRow->addWidget(ownerPhoneLineEdit);

        /* QLabels and QLineEdits for input of
         * owners address and email used in input form */
    ownerAddressLabel = new QLabel(tr("Address: "));
    ownerAddressLineEdit = new QLineEdit;

    ownerEmailLabel = new QLabel(tr("Email: "));
    ownerEmailLineEdit = new QLineEdit;
    ownerEmailLineEdit->setValidator(Emailvalidator);

        /* QHBoxLayout containing QWidgets for
         * owners address and email */
    QHBoxLayout *ownerAddressRow = new QHBoxLayout;
    ownerAddressRow->addWidget(ownerAddressLabel);
    ownerAddressRow->addStretch();
    ownerAddressRow->addWidget(ownerAddressLineEdit);
    ownerAddressRow->addStretch();
    ownerAddressRow->addWidget(ownerEmailLabel);
    ownerAddressRow->addStretch();
    ownerAddressRow->addWidget(ownerEmailLineEdit);

    /*Pet dropdown*/
    petList = new QComboBox;
    QHBoxLayout *petListRow = new QHBoxLayout;
    petListRow->addWidget(petList);
    connect(petList,SIGNAL(activated(int)),this,SLOT(changePetInfo(int)));

        /* QLabels and QLineEdit for pets name
         * and species used on input form */
    petNameLabel = new QLabel(tr("Name: "));
    petNameLineEdit = new QLineEdit;
    petNameLineEdit->setValidator(Namevalidator);

    petSpeciesLabel = new QLabel(tr("Species: "));
    //petSpeciesLineEdit = new QLineEdit;
    petSpeciesBox = new QComboBox;
    setSpeciesDropdown();
    /*
    for ( int speciesInt = Cat; speciesInt != Last; speciesInt++ ){
        petSpeciesBox->addItem(QString::number(speciesInt));
    }*/
    petSpeciesBox->itemText(12);
        /* QHBoxLayout containing QWidgets for pets
         * name and species, placed in input form */
    QHBoxLayout *petNameRow = new QHBoxLayout;
    petNameRow->addWidget(petNameLabel);
    petNameRow->addStretch();
    petNameRow->addWidget(petNameLineEdit);
    petNameRow->addStretch();
    petNameRow->addWidget(petSpeciesLabel);
    petNameRow->addStretch();
    petNameRow->addWidget(petSpeciesBox);

        /* QLabels, QLineEdits and QCombobox for
         * information about pets breed and chip status */
    petChippedLabel = new QLabel(tr("Chipped: "));
    petChippedCheckBox = new QCheckBox;

    chipNumLabel = new QLabel(tr("Chip no: "));
    chipNumLineEdit = new QLineEdit;
    chipNumLineEdit->setDisabled(true);

    petBreedLabel = new QLabel(tr("Breed: "));
    petBreedLineEdit = new QLineEdit;

        /* QHBoxLayout containing QWidgets for
         * pets chipped status and breed. Placed on input form */
    QHBoxLayout *petChippedRow = new QHBoxLayout;
    petChippedRow->addWidget(petChippedLabel);
    petChippedRow->addStretch();
    petChippedRow->addWidget(petChippedCheckBox);
    petChippedRow->addStretch();
    petChippedRow->addWidget(petBreedLabel);
    petChippedRow->addStretch();
    petChippedRow->addWidget(petBreedLineEdit);

        /* QLabel and QTextEdit for information about
         * special considerations that must be taken with
         * registerd pet, used on input form */
    petConsiderationsLabel = new QLabel(tr("Considerations that must be taken: "));
    petConsiderationsTextEdit = new QTextEdit;;

        /* QHBoxLayout containing QWidgets for pets chip number.
         * Placed on input form. */
    QHBoxLayout *chipNumRow = new QHBoxLayout;
    chipNumRow->addWidget(chipNumLabel);
    chipNumRow->addWidget(chipNumLineEdit);
    connect(petChippedCheckBox, SIGNAL(toggled(bool)),
           chipNumLineEdit, SLOT(setEnabled(bool)));

        /* Save button for saving information to data storage */
    QPushButton *saveInfo = new QPushButton("Register", this);
    connect(saveInfo, SIGNAL(released()), this, SLOT (saveButton()));

        /* Placing all QHBoxLayouts and QWidgets that are used on
         * input form to the correct QFrame placed inside a QStackedWidget*/
    QFrame* line1 = new QFrame();
    QFrame* line2 = new QFrame();
    QFrame* line3 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    line3->setFrameShape(QFrame::HLine);
    line3->setFrameShadow(QFrame::Sunken);
    mainPageLayout->addWidget(ownerHeaderLabel);
    mainPageLayout->addLayout(searchRow);
    mainPageLayout->addWidget(line1);
    mainPageLayout->addLayout(ownerNameRow);
    mainPageLayout->addLayout(ownerAddressRow);
    mainPageLayout->addWidget(line2);
    mainPageLayout->addLayout(petListRow);
    mainPageLayout->addWidget(petHeaderLabel);
    mainPageLayout->addLayout(petNameRow);
    mainPageLayout->addLayout(petChippedRow);
    mainPageLayout->addLayout(chipNumRow);
    mainPageLayout->addWidget(petConsiderationsLabel);
    mainPageLayout->addWidget(petConsiderationsTextEdit);
    mainPageLayout->addWidget(saveInfo);
    mainPageLayout->addWidget(line3);
    setLayout(mainPageLayout);
}

void Zootopia::saveButton(){

    Owner * owner = new Owner();
    owner->email = this->ownerEmailLineEdit->text();
    owner->name = this->ownerNameLineEdit->text();
    owner->adress = this->ownerAddressLineEdit->text();
    owner->phone = this->ownerPhoneLineEdit->text().toInt();

    Pet * pet = new Pet();
    pet->name = this->petNameLineEdit->text();
    pet->species = static_cast<Species>(this->petSpeciesBox->currentIndex());
    //pet->species = Reptilian;
    pet->breed = this->petBreedLineEdit->text();
    pet->chip = this->chipNumLineEdit->text();
    pet->otherinfo = this->petConsiderationsTextEdit->toPlainText();

    saveOwnerAndPetInfo(*owner, *pet);
}
void Zootopia::searchButton() {
    try {
        temporaryOwner = getOwnerAndPetInfo(searchInput->text());

        fillOwnerLineEdits(temporaryOwner);
        if (temporaryOwner.pets.size() > 0) fillPetLineEdits(temporaryOwner.pets);
    }
    catch (exception e){
        // skal erstattes av en label
        cout << e.what() << endl;
    }
}
void Zootopia::changePetInfo(const int index) {
    petNameLineEdit->setText(temporaryOwner.pets[index].name);
    petSpeciesBox->setCurrentIndex(temporaryOwner.pets[index].species);
    petBreedLineEdit->setText(temporaryOwner.pets[index].breed);
    chipNumLineEdit->setText(temporaryOwner.pets[index].chip);
    petConsiderationsTextEdit->setText(temporaryOwner.pets[index].otherinfo);
}
void Zootopia::fillOwnerLineEdits(const Owner &owner){
    clearPetLineEdits();
    ownerNameLineEdit->setText(owner.name);
    ownerPhoneLineEdit->setText(QString::number(owner.phone));
    ownerAddressLineEdit->setText(owner.adress);
    ownerEmailLineEdit->setText(owner.email);
}
void Zootopia::fillPetLineEdits(vector<Pet> &pets){

    petNameLineEdit->setText(pets[0].name);
    petSpeciesBox->setCurrentIndex(pets[0].species);
    petBreedLineEdit->setText(pets[0].breed);
    chipNumLineEdit->setText(pets[0].chip);
    petConsiderationsTextEdit->setText(pets[0].otherinfo);

    for (Pet &pet : pets) petList->addItem(pet.name);
}
void Zootopia::clearPetLineEdits(){
    petList->clear();
    petNameLineEdit->clear();
    //petSpeciesLineEdit->setText("");
    petBreedLineEdit->clear();
    chipNumLineEdit->clear();
    petConsiderationsTextEdit->clear();
}
void Zootopia::setSpeciesDropdown(){

    vector<QString> speciesMap;
    speciesMap.push_back("Cat");
    speciesMap.push_back("Dog");
    speciesMap.push_back("Bird");
    speciesMap.push_back("Rodent");
    speciesMap.push_back("Reptilian");

    for (int i = 0; i < speciesMap.size(); i++)
        this->petSpeciesBox->addItem(speciesMap[i]);

}


Zootopia::~Zootopia()
{
    delete ui;
}

