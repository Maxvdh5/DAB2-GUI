#include "popupmessage.h"
#include <QMessageBox>

PopupMessage::PopupMessage()
{

}

void PopupMessage::loginMessage()
{
    QMessageBox messageBox;
    messageBox.critical(0,"Error","Kan geen verbinding maken met de database!");
    messageBox.setFixedSize(500,200);
}

void PopupMessage::loginIncorrect()
{
    QMessageBox messageBox;
    messageBox.critical(0,"Error","Gebruikersnaam of wachtwoord incorrect");
    messageBox.setFixedSize(500,200);
}
