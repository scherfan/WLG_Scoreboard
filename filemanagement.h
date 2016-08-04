#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <QObject>

class FileManagement : public QObject
{
    Q_OBJECT
public:
    explicit FileManagement(QObject *parent = 0);

signals:

public slots:
};

#endif // FILEMANAGEMENT_H