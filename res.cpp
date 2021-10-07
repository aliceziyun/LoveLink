#include "res.h"

IconButton *imageButton[MAX_COL*MAX_ROW]; // 图片button数组
IconButton *preIcon, *curIcon; // 记录点击的icon
IconButton *preIcon2, *curIcon2; // 记录点击的icon
FILE *gameSave; //记录存档文件

void IconButton::setPix()
{
    QPixmap iconPix;
    QString fileString;
    if(highlight)
        fileString.sprintf(":/icon/icon/%da.png", ID);
    else
        fileString.sprintf(":/icon/icon/%d.png", ID);

    iconPix.load(fileString);
    iconPix = iconPix.scaled(QSize(kIconSize,kIconSize));
    this->setPixmap(iconPix);
}

void Item::setPix()
{
    QPixmap iconPix;
    QString fileString;
    switch (gameitems) {
    case TIMEPLUS:
    {
        fileString.sprintf(":/item/item/timeplus.png");
        break;
    }
    case SHUFFLE:
    {
        fileString.sprintf(":/item/item/shuffle.png");
        break;
    }
    case HINT:
    {
        fileString.sprintf(":/item/item/hint.png");
        break;
    }
    case NONE:
    {
        break;
    }
    }
    iconPix.load(fileString);
    iconPix = iconPix.scaled(QSize(kIconSize,kIconSize));
    this->setPixmap(iconPix);
}
