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

#ifndef PHRASEDATA_H
#define PHRASEDATA_H

#include "../defines.h"

NUT_BEGIN_NAMESPACE

class NUT_EXPORT PhraseData
{
public:
    enum Condition {
        NotAssign = 0,
        Equal,
        Less,
        LessEqual,
        Null,
        In,
        Like,

        Not = 10,
        NotEqual,
        GreaterEqual,
        Greater,
        NotNull,
        NotIn,
        NotLike,

        And = 20,
        Or,

        Add,
        Minus,
        Multiple,
        Divide,
        Mod,

        Between,

        //date and time
        AddYears,
        AddMonths,
        AddDays,
        AddHours,
        AddMinutes,
        AddSeconds,

        DatePartYear,
        DatePartMonth,
        DatePartDay,
        DatePartHour,
        DatePartMinute,
        DatePartSecond,
        DatePartMilisecond
//        // special types
//        Distance
    };

    enum Type { Field, WithVariant, WithOther, WithoutOperand };

    const char *className;
    const char *fieldName;

    Type type;

    Condition operatorCond;

    PhraseData *left;
    PhraseData *right;

    QVariant *operand;
    bool isNot;
    quint16 parents;

    PhraseData();
    constexpr PhraseData(const char *className, const char *fieldName) :
        className(className), fieldName(fieldName),
        type(Field), operatorCond(NotAssign),
        left(nullptr), right(nullptr), operand(nullptr), isNot(false), parents(1)
    { }
    constexpr PhraseData(PhraseData *l, Condition o)
        : className(nullptr), fieldName(nullptr),
          type(WithoutOperand), operatorCond(o),
          left(l), right(nullptr), operand(nullptr), isNot(false), parents(1)
    {
        l->parents++;
    }
    PhraseData(PhraseData *l, Condition o, PhraseData *r);
    PhraseData(PhraseData *l, Condition o, QVariant r);
//    explicit PhraseData(const PhraseData &other);
//    explicit PhraseData(const PhraseData *other);

    PhraseData *operator =(PhraseData *other);
    PhraseData &operator =(PhraseData &other);

    QString toString() const;

    ~PhraseData() = default;

    void cleanUp();
private:
    void cleanUp(PhraseData *d);
};

NUT_END_NAMESPACE

#endif // PHRASEDATA_H
