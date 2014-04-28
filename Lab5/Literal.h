// Phillip Day, Jackson Curless, Dylan Coyle
//
//  Literal.h
//  Lab5
//
#ifndef _LITERAL_H
#define _LITERAL_H


template <class T>
class Literal
{
public:
    enum LiteralType
    {
        IntegerLit,
        RealLit,
        StringLit
    };


    explicit Literal() {}


    virtual ~Literal() {}


    virtual LiteralType getType() = 0;


    inline const T &getLiteralData() const
    {
        return theData;
    }


    inline void setLiteralData(const T &data)
    {
        theData = data;
    }

private:

    T theData;
};

#endif
