#ifndef __CPP2C_POLYMORPHISM_H__
#define __CPP2C_POLYMORPHISM_H__

#include "stdio.h"

/* global inline

inline void printFunc(const char* fname)
{
    printf("%-60s | ", fname);
}*/

typedef void(*void_func_ptr)(void);
typedef void(*void_long_char_func_ptr)(const void *const, long, char);

/*vTables*/
extern void(*TextFormatterVTable[2])(void) ;
extern void(*DefaultTextFormatterVTable[2])(void) ;
extern void(*PrePostFixerVTable[4])(void) ;
extern void(*PrePostDollarFixerVTable[4])(void) ;

enum Functions{
    _Z4DtorEPKs,
    _Z5printEKPc,
    _Z5printElc,
    _Z13defaultSymbolE
};


/* 1---TextFormatter--- */
typedef struct _TextFormatter{
    void_func_ptr* m_vptr;
}TextFormatter;


void TextFormatter_ctor(TextFormatter *const this, void(**vTable)(void));/*defualt: TextFormatterVTable*/
void TextFormatter_dtor(TextFormatter *const this);
void TextFormatter_print(const TextFormatter *const this, const char* text);


/* 2---DefaultTextFormatter--- */
typedef struct DefaultTextFormatter{
    TextFormatter m_textFormatterBase;
    int m_id;
}DefaultTextFormatter;

void DefaultTextFormatter_ctor(DefaultTextFormatter *const this, void_func_ptr* vTable);/*defualt: DefaultTextFormatterVTable*/
void DefaultTextFormatter_copy_ctor(DefaultTextFormatter *const this, const DefaultTextFormatter *const other, void_func_ptr* vTable);/*defualt: DefaultTextFormatterVTable*/
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


void PrePostFixer_ctor(PrePostFixer *const this, const char* prefix, const char* postfix, void_func_ptr* vTable);/*defualt: PrePostFixerVTable*/
/*I declared:*/void PrePostFixer_copy_ctor(PrePostFixer *const this, const PrePostFixer *const other, void_func_ptr* vTable);/*defualt: PrePostFixerVTable*/
void PrePostFixer_dtor(PrePostFixer *const this);

void PrePostFixer_print_cc(const void *const this, const char* text);
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

void PrePostDollarFixer_ctor_cc_cc(PrePostDollarFixer *const this, const char* prefix, const char* postfix, void_func_ptr* vTable);/*defualt: PrePostDollarFixer*/
void PrePostDollarFixer_copy_ctor(PrePostDollarFixer *const this, const PrePostDollarFixer *const other, void_func_ptr* vTable);/*defualt: PrePostDollarFixer*/
void PrePostDollarFixer_dtor(PrePostDollarFixer *const this);

/*default symbol is PrePostDollarFixer_DEFAULT_SYMBOL*/
void PrePostDollarFixer_print_i_c(const PrePostDollarFixer *const this, int num, char symbol);
void PrePostDollarFixer_print_l_c(const PrePostDollarFixer *const this, long num, char symbol);/*vitrual*/
void PrePostDollarFixer_print_d_c(const PrePostDollarFixer *const this, double num, char symbol);
char PrePostDollarFixer_getDefaultSymbol(const PrePostDollarFixer *const this);

/* PrePostDollarFixer inlines:
 * no inlines*/


/* 5 ---PrePostHashFixer--- */
typedef struct _PrePostHashFixer{
    PrePostDollarFixer m_PrePostDollarFixerBase;
    int m_precision;
}PrePostHashFixer;

extern const char PrePostHashFixer_DEFAULT_SYMBOL;

void PrePostHashFixer_ctor(PrePostHashFixer *const this, int prc, void_func_ptr* vTable);/*default prc: 4*/
void PrePostHashFixer_dtor(PrePostHashFixer *const this);

/*default symbol is PrePostHashFixer_DEFAULT_SYMBOL*/
void PrePostHashFixer_print_i_c(const PrePostHashFixer *const this, int num, char symbol);
void PrePostHashFixer_print_l_c(const PrePostHashFixer *const this, long num, char symbol);
char PrePostHashFixer_getDefaultSymbol(const PrePostHashFixer *const this);


/* PrePostHashFixer inlines:
inline void PrePostHashFixer::print(double num, char symbol) const
{
printFunc("[PrePostHashFixer::print(double, char)]");

printf("%s[%c%.*f]%s\n", getPrefix(), symbol, precision, num, getPostfix());
}

*/



/*6 ---PrePostFloatDollarFixer--- */
typedef struct _PrePostFloatDollarFixer{
    PrePostDollarFixer m_PrePostDollarFixerBase;
}PrePostFloatDollarFixer;

extern const char PrePostFloatDollarFixer_DEFAULT_SYMBOL;

void PrePostFloatDollarFixer_ctor(PrePostFloatDollarFixer *const this, const char* prefix, const char* postfix, void_func_ptr* vTable);/*default is PrePostFloatDollarFixerVTable*/
void PrePostFloatDollarFixer_dtor(PrePostFloatDollarFixer *const this);
void PrePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer *const this, float num);
void PrePostFloatDollarFixer_print_f_c(const PrePostFloatDollarFixer *const this, float num, char symbol);
char PrePostFloatDollarFixer_getDefaultSymbol(const PrePostFloatDollarFixer *const this);

/* PrePostFloatDollarFixer inlines:
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
*/
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



#endif

