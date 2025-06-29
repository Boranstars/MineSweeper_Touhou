//
// Created by 杨博元 on 25-6-15.
//

#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <QPixmap>
#include <QDebug>
#include <QDir>
#include <QFile>
#include "constants.h"
namespace MineSweeperTouHou {
    class ResourceLoader {
        static QString currentTheme;

    public:
        static void setTheme(const QString& theme);
        static QString getTheme();

        static QPixmap getCoverImage();
        static QPixmap getUncoverImage();
        static QPixmap getMineImage();
        static QPixmap getNumberImage(int number);
        static QPixmap getFlagImage();
        static const QVector<QPixmap> &getNumberImages();
    private:
        static QPixmap loadPixmap(const QString& path);
        static QVector<QPixmap> loadNumberImages();
    };
}



#endif //RESOURCELOADER_H
