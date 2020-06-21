#ifndef __CPP2C_POLYMORPHISM_H__
#define __CPP2C_POLYMORPHISM_H__

#include "stdio.h"

/* global inline

inline void printFunc(const char* fname)
{
    printf("%-60s | ", fname);
}*/

typedef void(*func_ptr_void_R_void)(void);
typedef void(*func_ptr_pvoid_long_char_R_void)(const void *const, long, char);
typedef char(*func_ptr_pvoid_R_char)(const void *const);

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
    func_ptr_void_R_void* m_vptr;
}TextFormatter;


/*TextFormatter ctor is inline*/
void TextFormatter_dtor(void *const this);
void TextFormatter_print(const void *const this, const char* text);


/* 2---DefaultTextFormatter--- */
typedef struct DefaultTextFormatter{
    TextFormatter m_textFormatterBase;
    int m_id;
}DefaultTextFormatter;

void DefaultTextFormatter_ctor(DefaultTextFormatter *const this, func_ptr_void_R_void* vTable);/*defualt: DefaultTextFormatterVTable*/
void DefaultTextFormatter_copy_ctor(DefaultTextFormatter *const this, const DefaultTextFormatter *const other, func_ptr_void_R_void* vTable);/*defualt: DefaultTextFormatterVTable*/
DefaultTextFormatter* const DefaultTextFormatter_copy_assign(DefaultTextFormatter *const this, const DefaultTextFormatter *const other);
void DefaultTextFormatter_dtor(void *const this);
void DefaultTextFormatter_print(const void *const this, const char* text);

/*---struct Ider omitted---*/
extern DefaultTextFormatter_Ider_next_id;

DefaultTextFormatter* generateFormatterArray();


/* 3---PrePostFixer--- */
typedef struct _PrePostFixer{
    DefaultTextFormatter m_defaultTextFormatterBase;
    const char* m_pre;
    const char* m_post;
}PrePostFixer;


void PrePostFixer_ctor(PrePostFixer *const this, const char* prefix, const char* postfix, func_ptr_void_R_void* vTable);/*defualt: PrePostFixerVTable*/
/*I declared:*/void PrePostFixer_copy_ctor(PrePostFixer *const this, const PrePostFixer *const other, func_ptr_void_R_void* vTable);/*defualt: PrePostFixerVTable*/
void PrePostFixer_dtor(void *const this);

void PrePostFixer_print_cc(const void *const this, const char* text);
void PrePostFixer_print_l_c(const void *const this, long num, char symbol);/*default symbol is: '\0'*/

char PrePostFixer_getDefaultSymbol(const void *const this);

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

void PrePostDollarFixer_ctor_cc_cc(PrePostDollarFixer *const this, const char* prefix, const char* postfix, func_ptr_void_R_void* vTable);/*defualt: PrePostDollarFixer*/
void PrePostDollarFixer_copy_ctor(PrePostDollarFixer *const this, const PrePostDollarFixer *const other, func_ptr_void_R_void* vTable);/*defualt: PrePostDollarFixer*/
void PrePostDollarFixer_dtor(void *const this);

/*default symbol is PrePostDollarFixer_DEFAULT_SYMBOL*/
void PrePostDollarFixer_print_i_c(const PrePostDollarFixer *const this, int num, char symbol);
void PrePostDollarFixer_print_l_c(const void *const this, long num, char symbol);/*vitrual*/
void PrePostDollarFixer_print_d_c(const PrePostDollarFixer *const this, double num, char symbol);
char PrePostDollarFixer_getDefaultSymbol(const void *const this);

/* PrePostDollarFixer inlines:
 * no inlines*/


/* 5 ---PrePostHashFixer--- */
typedef struct _PrePostHashFixer{
    PrePostDollarFixer m_PrePostDollarFixerBase;
    int m_precision;
}PrePostHashFixer;

extern const char PrePostHashFixer_DEFAULT_SYMBOL;

void PrePostHashFixer_ctor(PrePostHashFixer *const this, int prc, func_ptr_void_R_void* vTable);/*default prc: 4*/
void PrePostHashFixer_dtor(void *const this);

/*default symbol is PrePostHashFixer_DEFAULT_SYMBOL*/
void PrePostHashFixer_print_i_c(const PrePostHashFixer *const this, int num, char symbol);
void PrePostHashFixer_print_l_c(const void *const this, long num, char symbol);/*virtual*/
char PrePostHashFixer_getDefaultSymbol(const void *const this);


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

void PrePostFloatDollarFixer_ctor(PrePostFloatDollarFixer *const this, const char* prefix, const char* postfix, func_ptr_void_R_void* vTable);/*default is PrePostFloatDollarFixerVTable*/
void PrePostFloatDollarFixer_dtor(void *const this);
void PrePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer *const this, float num);
void PrePostFloatDollarFixer_print_f_c(const PrePostFloatDollarFixer *const this, float num, char symbol);
char PrePostFloatDollarFixer_getDefaultSymbol(const void *const this);

/* PrePostFloatDollarFixer inlines:
 * no inlines*/


/* ---PrePostChecker--- */
typedef struct _PrePostChecker{
    PrePostFloatDollarFixer m_PrePostFloatDollarFixerBase;
}PrePostChecker;


void PrePostChecker_ctor(PrePostChecker *const this, func_ptr_void_R_void* vTable);/*default is PrePostCheckerVTable*/
void PrePostChecker_dtor(void *const this);

void printThisSymbolUsingFunc(const PrePostChecker *const this);
void printThisSymbolDirectly(const PrePostChecker *const this);
void printDollarSymbolByCastUsingFunc(const PrePostChecker *const this);
void printDollarSymbolByScopeUsingFunc(const PrePostChecker *const this);
void printDollarSymbolByCastDirectly(const PrePostChecker *const this);
void printDollarSymbolByScopeDirectly(const PrePostChecker *const this);



/*8 ---Multiplier--- */
typedef struct _Multiplier{
    DefaultTextFormatter m_DefaultTextFormatterBase;
    int m_times;
}Multiplier;


void Multiplier_dtor(Multiplier *const this);
void Multiplier_print_cc(const void *const this, const char* text);


/* Multiplier inlines:
void Multiplier_ctor(int t, func_ptr_void_R_void* vTable) /---default t: 2  default vTable: MultiplierVTable---/
{
    DefaultTextFormatter_ctor(this->m_DefaultTextFormatterBase, vTable);
    this->m_times = t;

    printf("--- Multiplier CTOR: times = %d\n", this->m_times);
}

inline int Multiplier::getTimes() const
{
return m_times;
}

inline void Multiplier::setTimes(int t)
{
    m_times = t;
}
*/
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
 */
/*--------------------------------------------end of source-----------------------------------------------
 * -------------------------------------------------------------------------------------------------------
 * ------------------------------------------------------------------------------------------------------*/



#endif

