#ifndef CANTREADWRITEFILEEXCEPTION_H
#define CANTREADWRITEFILEEXCEPTION_H

#include <QException>

class CantReadWriteFileException: public QException
{
    QString text;
public:
    CantReadWriteFileException(QString text);
    CantReadWriteFileException();
    void raise() const override { throw *this; }
    CantReadWriteFileException *clone() const override { return new CantReadWriteFileException; }
    const QString &getText() const;
};

#endif // CANTREADWRITEFILEEXCEPTION_H
