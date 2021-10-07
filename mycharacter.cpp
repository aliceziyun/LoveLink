#include "mycharacter.h"

void MyCharacter::setPix(Muse chara)
{
    QPixmap charaPix;
    QString fileString;
    fileString.sprintf(":/chara/chara/%d.png",chara + 1);
    charaPix.load(fileString);
    charaPix = charaPix.scaled(QSize(kIconSize,kIconSize));
    setPixmap(charaPix);
}
