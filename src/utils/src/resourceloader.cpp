//
// Created by 杨博元 on 25-6-15.
//

#include "resourceloader.h"

namespace MineSweeperTouHou {
    QString ResourceLoader::currentTheme = "default";
    void ResourceLoader::setTheme(const QString &theme) {
        currentTheme = theme;
    }

    QString ResourceLoader::getTheme() {
        return currentTheme;
    }

    QPixmap ResourceLoader::getCoverImage() {
        return loadPixmap(QString(":/theme/%1/images/covers/cover.png").arg(currentTheme));
    }

    QPixmap ResourceLoader::getUncoverImage() {
        return loadPixmap(QString(":/theme/%1/images/covers/uncover.png").arg(currentTheme));
    }

    QPixmap ResourceLoader::getMineImage() {
        return loadPixmap(QString(":/theme/%1/images/mines/kiruno.png").arg(currentTheme));
    }

    QPixmap ResourceLoader::getNumberImage(int number) {
        static QVector<QPixmap> numbers = loadNumberImages();
        if (number >= 1 && number <= 8) {
            return numbers[number - 1];
        } else {
            qDebug() << "ResourceLoader::getNumberImage: number out of range";
            return {};
        }
    }

    const QVector<QPixmap> & ResourceLoader::getNumberImages() {
        static QVector<QPixmap> numbers = loadNumberImages();
        return numbers;
    }

    QPixmap ResourceLoader::loadPixmap(const QString &path) {
        QPixmap pixmap(path);
        if (pixmap.isNull()) {
            qDebug() << "Failed to load pixmap: " << path;
        }
        return pixmap;
    }

    QVector<QPixmap> ResourceLoader::loadNumberImages() {
        QVector<QPixmap> numbers(8);
        QString numberDirPath = QString(":/theme/%1/images/numbers").arg(currentTheme);
        QDir dir(numberDirPath);
        QStringList files = dir.entryList(QStringList("number_*.png"), QDir::Files);

        for (const auto & file: files) {
            bool isOK = false;
            const int num  = file.mid(7, 1).toInt(&isOK); // 提取文件名中的数字
            if (isOK && num >= 1 && num <= 8) {
                numbers[num - 1] = loadPixmap(dir.filePath(file));
            }
        }

        return numbers;
    }
}
