#ifndef NUMERICPHRASE_H
#define NUMERICPHRASE_H

#include "fieldphrase.h"
#include <type_traits>

NUT_BEGIN_NAMESPACE

#define SPECIALIZATION_NUMERIC_MEMBER(type, op, cond)                          \
    ConditionalPhrase operator op(const QVariant &other)                       \
{                                                                              \
    return ConditionalPhrase(this, cond, other);                               \
}

template <typename T>
class FieldPhrase<T, typename std::enable_if<
            std::is_floating_point<T>::value || std::is_integral<T>::value
        >::type>
        : public AbstractFieldPhrase
{
public:
    constexpr FieldPhrase(const char *className, const char *s) :
        AbstractFieldPhrase(className, s)
    {}

    AssignmentPhrase operator =(const QVariant &other) {
        return AssignmentPhrase(this, other);
    }
    AssignmentPhrase operator =(ConditionalPhrase &&other) {
        return AssignmentPhrase(new PhraseData(data, PhraseData::Equal, other.data));
    }
    ConditionalPhrase between(const QVariant &min, const QVariant &max)
    {
        return ConditionalPhrase(this, PhraseData::Between,
                                 QVariantList() << min << max);
    }
    ConditionalPhrase operator ++()
    {
        return ConditionalPhrase(this, PhraseData::Add, 1);
    }
    ConditionalPhrase operator --()
    {
        return ConditionalPhrase(this, PhraseData::Minus, 1);
    }
    ConditionalPhrase operator ++(int)
    {
        return ConditionalPhrase(this, PhraseData::Add, 1);
    }
    ConditionalPhrase operator --(int)
    {
        return ConditionalPhrase(this, PhraseData::Minus, 1);
    }

    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less)
    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual)
    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater)
    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual)
    SPECIALIZATION_NUMERIC_MEMBER(type, %,  PhraseData::Mod)

    SPECIALIZATION_NUMERIC_MEMBER(type, +,  PhraseData::Add)
    SPECIALIZATION_NUMERIC_MEMBER(type, -,  PhraseData::Minus)
    SPECIALIZATION_NUMERIC_MEMBER(type, *,  PhraseData::Multiple)
    SPECIALIZATION_NUMERIC_MEMBER(type, /,  PhraseData::Divide)
};

#define SPECIALIZATION_NUMERIC_TYPE(type) \
    template<> \
    class FieldPhrase<type> : public NumericPhrase \
{ \
public: \
FieldPhrase(const char *className, const char *s) : \
    NumericPhrase(className, s) \
{} \
};

//SPECIALIZATION_NUMERIC_TYPE(qint8)
//SPECIALIZATION_NUMERIC_TYPE(qint16)
//SPECIALIZATION_NUMERIC_TYPE(qint32)
//SPECIALIZATION_NUMERIC_TYPE(qint64)

//SPECIALIZATION_NUMERIC_TYPE(quint8)
//SPECIALIZATION_NUMERIC_TYPE(quint16)
//SPECIALIZATION_NUMERIC_TYPE(quint32)
//SPECIALIZATION_NUMERIC_TYPE(quint64)

//SPECIALIZATION_NUMERIC_TYPE(qreal)

NUT_END_NAMESPACE

#endif // NUMERICPHRASE_H
