
enum class Sign
{
    sign
};

enum class Type
{
    type
};

class C {};

/** Value type */
class ValueType {
public:
    ValueType(enum Sign s, enum Type t)
    {
        enum Sign sign = Sign::sign;
        class C c = C();
    }
};
