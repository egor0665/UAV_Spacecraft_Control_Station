#include "cantreadwritefileexception.h"

const QString &CantReadWriteFileException::getText() const
{
    return text;
}

CantReadWriteFileException::CantReadWriteFileException(QString text)
{
    this->text = text;
}

CantReadWriteFileException::CantReadWriteFileException()
{

}
