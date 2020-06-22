#ifndef __CPP2C_POLYMORPHISM_H__
#define __CPP2C_POLYMORPHISM_H__

#include "stdio.h"

/* global inline

inline void printFunc(const char* fname)
{
    printf("%-60s | ", fname);
}*/

typedef void(*funcPtr_void_R_void)(void*);
typedef void(*funcPtr_pvoid_long_char_R_void)(const void *const, long, char);
typedef char(*funcPtr_pvoid_R_char)(const void *const);
typedef void(*funcPtr_pvoid_long_char)(const void *const, long, char);
typedef void(*funcPtr_pvoid_pchar_R_void)(const void *const, const char*);


/*vTables*/
extern funcPtr_void_R_void TextFormatterVTable[];
extern funcPtr_void_R_void DefaultTextFormatterVTable[];
extern funcPtr_void_R_void PrePostFixerVTable[];
extern funcPtr_void_R_void PrePostDollarFixerVTable[];
extern funcPtr_void_R_void PrePostHashFixerVTable[];
extern funcPtr_void_R_void PrePostFloatDollarFixerVTable[];
extern funcPtr_void_R_void PrePostCheckerVTable[];
extern funcPtr_void_R_void MultiplierVTable[];


enum Functions{
    _Z4DtorEPKs,
    _Z5printEKPc,
    _Z5printElc,
    _Z13defaultSymbolE
};


/* 1---TextFormatter--- */
typedef struct _TextFormatter{
    funcPtr_void_R_void* m_vptr;
}TextFormatter;


/*TextFormatter ctor is inline*/
void TextFormatter_dtor(void *const this);

/* 2---DefaultTextFormatter--- */
typedef struct DefaultTextFormatter{
    TextFormatter m_textFormatterBase;
    int m_id;
}DefaultTextFormatter;

void DefaultTextFormatter_ctor(DefaultTextFormatter *const this);
void DefaultTextFormatter_copy_ctor(DefaultTextFormatter *const this, const DefaultTextFormatter *const other);
DefaultTextFormatter* const DefaultTextFormatter_copy_assign(DefaultTextFormatter *const this, const DefaultTextFormatter *const other);
void DefaultTextFormatter_dtor(void *const this);
void DefaultTextFormatter_print(const void *const this, const char* text);

/*---struct Ider omitted---*/
extern int DefaultTextFormatter_Ider_next_id;

DefaultTextFormatter* generateFormatterArray();


/* 3---PrePostFixer--- */
typedef struct _PrePostFixer{
    DefaultTextFormatter m_defaultTextFormatterBase;
    const char* m_pre;
    const char* m_post;
}PrePostFixer;


void PrePostFixer_ctor(PrePostFixer *const this, const char* prefix, const char* postfix);
/*made of:*/void PrePostFixer_copy_ctor(PrePostFixer *const this, const PrePostFixer *const other);
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

void PrePostDollarFixer_ctor_cc_cc(PrePostDollarFixer *const this, const char* prefix, const char* postfix);
void PrePostDollarFixer_copy_ctor(PrePostDollarFixer *const this, const PrePostDollarFixer *const other);
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

void PrePostHashFixer_ctor(PrePostHashFixer *const this, int prc);/*default prc: 4*/
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

void PrePostFloatDollarFixer_ctor(PrePostFloatDollarFixer *const this, const char* prefix, const char* postfix);
void PrePostFloatDollarFixer_dtor(void *const this);
void PrePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer *const this, float num);
void PrePostFloatDollarFixer_print_f_c(const PrePostFloatDollarFixer *const this, float num, char symbol);
char PrePostFloatDollarFixer_getDefaultSymbol(const void *const this);

/* PrePostFloatDollarFixer inlines:
 * no inlines*/


/*7 ---PrePostChecker--- */
typedef struct _PrePostChecker{
    PrePostFloatDollarFixer m_PrePostFloatDollarFixerBase;
}PrePostChecker;


void PrePostChecker_ctor(PrePostChecker *const this);
void PrePostChecker_dtor(void *const this);

void PrePostChecker_printThisSymbolUsingFunc(const PrePostChecker *const this);
void PrePostChecker_printThisSymbolDirectly(const PrePostChecker *const this);
void PrePostChecker_printDollarSymbolByCastUsingFunc(const PrePostChecker *const this);
void PrePostChecker_printDollarSymbolByScopeUsingFunc(const PrePostChecker *const this);
void PrePostChecker_printDollarSymbolByCastDirectly(const PrePostChecker *const this);
void PrePostChecker_printDollarSymbolByScopeDirectly(const PrePostChecker *const this);



/*8 ---Multiplier--- */
typedef struct _Multiplier{
    DefaultTextFormatter m_DefaultTextFormatterBase;
    int m_times;
}Multiplier;


void Multiplier_dtor(Multiplier *const this);
/*I declared*/void Multiplier_copy_ctor(Multiplier *const this, const Multiplier *const other);
void Multiplier_print_cc(const void *const this, const char* text);


/* Multiplier inlines:
void Multiplier_ctor(Multiplier *const this, int t) /---default t: 2---/
{
    DefaultTextFormatter_ctor(this->m_DefaultTextFormatterBase);
    ((TextFormatter*)this)->m_vptr = MultiplierVTable;
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
#endif

