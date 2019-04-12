/**************************************************************************
**
** This file is part of Nut project.
** https://github.com/HamedMasafi/Nut
**
** Nut is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Nut is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Nut.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#ifndef ABSTRACTFIELDPHRASE_H
#define ABSTRACTFIELDPHRASE_H

#include "../defines.h"

#include "assignmentphrase.h"
#include "conditionalphrase.h"
#include "phraselist.h"

#include <QSharedPointer>

NUT_BEGIN_NAMESPACE

class PhraseData;
class NUT_EXPORT AbstractFieldPhrase
{
public:
    QSharedPointer<PhraseData> data;
    explicit AbstractFieldPhrase(PhraseData *d);
    constexpr AbstractFieldPhrase(const char *className, const char *fieldName)
//        :data(QSharedPointer PhraseData{className, fieldName})
    {
//        data.reset(new PhraseData{className, fieldName});
    }
    AbstractFieldPhrase(const AbstractFieldPhrase &other);
    AbstractFieldPhrase(AbstractFieldPhrase &&other);

    virtual ~AbstractFieldPhrase();

    PhraseList operator |(const AbstractFieldPhrase &other);

    template<typename T>
    ConditionalPhrase in(QList<T> list)
    {
        QVariantList vlist;
        foreach (T t, list)
            vlist.append(QVariant::fromValue(t));

        return ConditionalPhrase(this, PhraseData::In, vlist);
    }
#ifdef Q_COMPILER_INITIALIZER_LISTS
    template<typename T>
    ConditionalPhrase in(std::initializer_list<T> list) {
        QVariantList vlist;
        typename std::initializer_list<T>::iterator it;
        for (it = list.begin(); it != list.end(); ++it)
            vlist.append(*it);
        return ConditionalPhrase(this, PhraseData::In, vlist);
    }
#endif

    ConditionalPhrase isNull();

    ConditionalPhrase operator ==(const QVariant &other);
    ConditionalPhrase operator ==(const ConditionalPhrase &other);
    //why?
    ConditionalPhrase operator !=(const QVariant &other);

    ConditionalPhrase operator ==(const AbstractFieldPhrase &other);
    ConditionalPhrase operator !=(const AbstractFieldPhrase &other);
    ConditionalPhrase operator <(const AbstractFieldPhrase &other);
    ConditionalPhrase operator >(const AbstractFieldPhrase &other);
    ConditionalPhrase operator <=(const AbstractFieldPhrase &other);
    ConditionalPhrase operator >=(const AbstractFieldPhrase &other);

    AbstractFieldPhrase operator ~();
    AbstractFieldPhrase operator !();
    AssignmentPhrase operator =(const QVariant &other);
    AssignmentPhrase operator =(const ConditionalPhrase &other);
    AssignmentPhrase operator <<(const QVariant &other);
};

NUT_END_NAMESPACE

#endif // ABSTRACTFIELDPHRASE_H
