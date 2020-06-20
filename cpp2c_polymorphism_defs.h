#ifndef __CPP2C_POLYMORPHISM_H__
#define __CPP2C_POLYMORPHISM_H__

#include "stdio.h"

/* global inline

inline void printFunc(const char* fname)
{
    printf("%-60s | ", fname);
}*/


enum Functions{
    _Z4DtorEPKs,
    _Z5printEKPc,
    _Z5printElc,
    _Z13defaultSymbolE
};


/* 1---TextFormatter--- */
typedef struct _TextFormatter{
    void(**m_vptr)(void);
}TextFormatter;


void TextFormatter_ctor(TextFormatter *const this, void(**vTable)(void));/*defualt: TextFormatterVTable*/
void TextFormatter_dtor(TextFormatter *const this);
void TextFormatter_print(const TextFormatter *const this, const char* text);


/* 2---DefaultTextFormatter--- */
typedef struct DefaultTextFormatter{
    TextFormatter m_textFormatterBase;
    int m_id;
}DefaultTextFormatter;

void DefaultTextFormatter_ctor(DefaultTextFormatter *const this, void(**vTable)(void));/*defualt: DefaultTextFormatterVTable*/
void DefaultTextFormatter_copy_ctor(DefaultTextFormatter *const this, const DefaultTextFormatter *const other, void(**vTable)(void));/*defualt: DefaultTextFormatterVTable*/
DefaultTextFormatter* const DefaultTextFormatter_copy_assign(DefaultTextFormatter *const this, const DefaultTextFormatter *const other);
void DefaultTextFormatter_dtor(DefaultTextFormatter *const this);
void DefaultTextFormatter_print(const DefaultTextFormatter *const this, const char* text);

extern DefaultTextFormatter_Ider_next_id;

typedef struct _DefaultTextFormatter_Ider{/*in mangling... needed??*/
    char c;
}DefaultTextFormatter_Ider;

/*DefaultTextFormatter_Ider inlines:
    static int getId() { return next_id++; }
*/

DefaultTextFormatter* generateFormatterArray();



/* 3---PrePostFixer--- */
typedef struct _PrePostFixer{
    DefaultTextFormatter m_defaultTextFormatterBase;
    const char* m_pre;
    const char* m_post;
}PrePostFixer;


void PrePostFixer_ctor(PrePostFixer *const this, const char* prefix, const char* postfix, void(**vTable)(void));/*defualt: PrePostFixerVTable*/
/*I declared:*/void PrePostFixer_copy_ctor(PrePostFixer *const this, const PrePostFixer *const other, void(**vTable)(void));/*defualt: PrePostFixerVTable*/
void PrePostFixer_dtor(PrePostFixer *const this);

void PrePostFixer_print_cc(const PrePostFixer *const this, const char* text);
void PrePostFixer_print_l_c(const PrePostFixer *const this, long num, char symbol);/*default '\0'*/

char PrePostFixer_getDefaultSymbol(const PrePostFixer *const this);

/* PrePostFixer inlines:
inline const char* PrePostFixer::getPrefix() const
{
return pre;
}

inline const char* PrePostFixer::getPostfix() const
{
return post;
}

inline void PrePostFixer::print_num(long num) const
{
printFunc("[PrePostFixer::print_num(long)]");
printf("%s%ld%s\n", pre, num, post);
}

inline void PrePostFixer::print_num(long num, char symbol) const
{
printFunc("[PrePostFixer::print_num(long, char)]");
printf("%s%c%ld%s\n", pre, symbol, num, post);
}
*/


/* 4---PrePostDollarFixer--- */
typedef struct _PrePostDollarFixer{
    PrePostFixer m_PrePostFixerBase;
}PrePostDollarFixer;

extern const char PrePostDollarFixer_DEFAULT_SYMBOL;

void PrePostDollarFixer_ctor_cc_cc(PrePostDollarFixer *const this, const char* prefix, const char* postfix, void(**vTable)(void));/*defualt: PrePostDollarFixer*/
void PrePostDollarFixer_copy_ctor(PrePostDollarFixer *const this, const PrePostDollarFixer *const other, void(**vTable)(void));/*defualt: PrePostDollarFixer*/
void PrePostDollarFixer_dtor(PrePostDollarFixer *const this);

/*default symbol is PrePostDollarFixer_DEFAULT_SYMBOL*/
void PrePostDollarFixer_print_i_c(const PrePostDollarFixer *const this, int num, char symbol);
void PrePostDollarFixer_print_l_c(const PrePostDollarFixer *const this, long num, char symbol);/*vitrual*/
void PrePostDollarFixer_print_d_c(const PrePostDollarFixer *const this, double num, char symbol);
char PrePostDollarFixer_getDefaultSymbol(const PrePostDollarFixer *const this);

/* PrePostDollarFixer inlines:
 * no inlines*/




/*---------------------------------------------source------------------------------------------------
 * --------------------------------------------------------------------------------------------------
 * --------------------------------------------------------------------------------------------------*/


/* TextFormatter

class TextFormatter
{
public:
    virtual ~TextFormatter() { };    
    virtual void print(const char* text) const = 0;
};


//// DefaultTextFormatter ////////////

class DefaultTextFormatter: public TextFormatter
{
public:
    DefaultTextFormatter();
    DefaultTextFormatter(const DefaultTextFormatter&);
    DefaultTextFormatter& operator=(const DefaultTextFormatter&);
    ~DefaultTextFormatter();

    virtual void print(const char* text) const;

private: 
    class Ider
    {
    private:
        static int next_id;
    public:
        static int getId() { return next_id++; }
    };

    const int id;
};

DefaultTextFormatter* generateFormatterArray();


//// PrePostFixer ////////////

class PrePostFixer: public DefaultTextFormatter
{
public:
    PrePostFixer(const char* prefix, const char* postfix);
    ~PrePostFixer();

    virtual void print(const char* text) const;
    virtual void print(long num, char symbol = '\0') const;

    virtual char getDefaultSymbol() const;

protected:
    const char* getPrefix() const;
    const char* getPostfix() const;

private:
    void print_num(long num) const;
    void print_num(long num, char symbol) const;

    const char* pre;
    const char* post;
};

//// PrePostFixer Defs ////////////

inline const char* PrePostFixer::getPrefix() const
{
    return pre;
}

inline const char* PrePostFixer::getPostfix() const
{
    return post;
}

inline char PrePostFixer::getDefaultSymbol() const
{
    return '\0';
}

inline void PrePostFixer::print(long num, char symbol) const
{
    printFunc("[PrePostFixer::print(long, char)]");
    printf("-->\n");
    
    if (symbol)    
        print_num(num, symbol);
    else
        print_num(num);
}

inline void PrePostFixer::print_num(long num) const
{
    printFunc("[PrePostFixer::print_num(long)]"); 
    printf("%s%ld%s\n", pre, num, post);
}

inline void PrePostFixer::print_num(long num, char symbol) const
{
    printFunc("[PrePostFixer::print_num(long, char)]"); 
    printf("%s%c%ld%s\n", pre, symbol, num, post);
}


//// PrePostDollarFixer ////////////

class PrePostDollarFixer: public PrePostFixer
{
protected:
    static const char DEFAULT_SYMBOL = '$';

public:
    PrePostDollarFixer(const char* prefix, const char* postfix);
    PrePostDollarFixer(const PrePostDollarFixer& other);
    ~PrePostDollarFixer();

    void print(int num, char symbol = DEFAULT_SYMBOL) const;
    void print(long num, char symbol = DEFAULT_SYMBOL) const;
    void print(double num, char symbol = DEFAULT_SYMBOL) const;
    char getDefaultSymbol() const;
};

//// PrePostDollarFixer Defs ////////////

inline char PrePostDollarFixer::getDefaultSymbol() const
{
    return DEFAULT_SYMBOL;
}
*/

//// PrePostHashFixer ////////////

class PrePostHashFixer: public PrePostDollarFixer
{
private:
    static const char DEFAULT_SYMBOL = '#';
public:
    PrePostHashFixer(int prc = 4);
    ~PrePostHashFixer();

    void print(int num, char symbol = DEFAULT_SYMBOL) const;
    void print(long num, char symbol = DEFAULT_SYMBOL) const;
    void print(double num, char symbol = DEFAULT_SYMBOL) const;
    char getDefaultSymbol() const;

private:
    int precision;
};

//// PrePostHashFixer Defs ////////////

inline void PrePostHashFixer::print(double num, char symbol) const
{
    printFunc("[PrePostHashFixer::print(double, char)]"); 

    printf("%s[%c%.*f]%s\n", getPrefix(), symbol, precision, num, getPostfix());
}

inline char PrePostHashFixer::getDefaultSymbol() const
{
    return DEFAULT_SYMBOL;
}


//// PrePostFloatDollarFixer ////////////

class PrePostFloatDollarFixer: public PrePostDollarFixer
{
protected:
    static const char DEFAULT_SYMBOL = '@';

public:
    PrePostFloatDollarFixer(const char* prefix, const char* postfix);
    ~PrePostFloatDollarFixer();
    void print(float num) const;
    void print(float num, char symbol) const;
    char getDefaultSymbol() const;
};

//// PrePostFloatDollarFixer Defs ////////////

inline char PrePostFloatDollarFixer::getDefaultSymbol() const
{
    return DEFAULT_SYMBOL;
}

//// PrePostChecker ////////////

class PrePostChecker: public PrePostFloatDollarFixer
{
public:
    PrePostChecker();
    ~PrePostChecker();
    
    void printThisSymbolUsingFunc() const;
    void printThisSymbolDirectly() const;    
    void printDollarSymbolByCastUsingFunc() const;
    void printDollarSymbolByScopeUsingFunc() const;
    void printDollarSymbolByCastDirectly() const;
    void printDollarSymbolByScopeDirectly() const;
};


//// Multiplier ////////////

class Multiplier: public DefaultTextFormatter
{
public:
    Multiplier(int t = 2);
    ~Multiplier();

    void print(const char*) const;
    int getTimes() const;
    void setTimes(int);
private:
    int times;
}; 

//// Multiplier Defs ////////////

inline Multiplier::Multiplier(int t)
:   times(t)
{
    printf("--- Multiplier CTOR: times = %d\n", times);
}

inline Multiplier::~Multiplier()
{
    printf("--- Multiplier DTOR: times = %d\n", times);
}
    
inline int Multiplier::getTimes() const
{
    return times;
}

inline void Multiplier::setTimes(int t)
{
    times = t;
}
/*--------------------------------------------end of source-----------------------------------------------
 * -------------------------------------------------------------------------------------------------------
 * ------------------------------------------------------------------------------------------------------*/


typedef void (*func_ptr)(void);

/*vTables*/
void(*TextFormatterVTable[2])(void)  = {(func_ptr)TextFormatter_dtor, (func_ptr)TextFormatter_print};
void(*DefaultTextFormatterVTable[2])(void)  = {(func_ptr)DefaultTextFormatter_dtor, (func_ptr)DefaultTextFormatter_print};
void(*PrePostFixerVTable[4])(void)  = {(func_ptr)PrePostFixer_dtor, (func_ptr)PrePostFixer_print_cc, (func_ptr)PrePostFixer_print_l_c, (func_ptr)PrePostFixer_getDefaultSymbol};
void(*PrePostDollarFixerVTable[4])(void)  = {(func_ptr)PrePostDollarFixer_dtor, (func_ptr)PrePostFixer_print_cc, (func_ptr)PrePostDollarFixer_print_l_c, (func_ptr)PrePostDollarFixer_getDefaultSymbol};


#endif

