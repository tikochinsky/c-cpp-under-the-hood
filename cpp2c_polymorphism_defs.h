#ifndef __CPP2C_POLYMORPHISM_H__
#define __CPP2C_POLYMORPHISM_H__

#include "stdio.h"

/* global inline

inline void printFunc(const char* fname)
{
    printf("%-60s | ", fname);
}*/

typedef void(*funcPtr_pvRv)(void*);
typedef void(*funcPtr_pvlcRv)(const void *const, long, char);
typedef char(*funcPtr_pvRc)(const void *const);
typedef void(*funcPtr_pvpRv)(const void *const, const char*);


/*vTables*/
extern funcPtr_pvRv TextFormatterVTable[];
extern funcPtr_pvRv DefaultTextFormatterVTable[];
extern funcPtr_pvRv PrePostFixerVTable[];
extern funcPtr_pvRv PrePostDollarFixerVTable[];
extern funcPtr_pvRv PrePostHashFixerVTable[];
extern funcPtr_pvRv PrePostFloatDollarFixerVTable[];
extern funcPtr_pvRv PrePostCheckerVTable[];
extern funcPtr_pvRv MultiplierVTable[];


enum Functions{
    _Z4DtorEPKs,
    _Z5printEKPc,
    _Z5printElc,
    _Z13defaultSymbolE
};


/* 1---TextFormatter--- */
typedef struct _TextFormatter{
    funcPtr_pvRv* m_vptr;
}TextFormatter;


/*TextFormatter ctor is inline*/
void _ZNC13TextFormatterEPKs(void *const this);

/* 2---DefaultTextFormatter--- */
typedef struct DefaultTextFormatter{
    TextFormatter m_textFormatterBase;
    int m_id;
}DefaultTextFormatter;

void _ZNC20DefaultTextFormatterEPKs(DefaultTextFormatter *const this);
void _ZNC20DefaultTextFormatterEPKsKPKs(DefaultTextFormatter *const this, const DefaultTextFormatter *const other);
DefaultTextFormatter* const _ZNC20DefaultTextFormatter10copyAssignEPKsKPKs(DefaultTextFormatter *const this, const DefaultTextFormatter *const other);
/*virtual*/void _ZND20DefaultTextFormatterEPKv(void *const this);
/*virtual*/void _ZN20DefaultTextFormatter5printEKPKvKPc(const void *const this, const char* text);

/*---struct Ider omitted---*/
extern int _ZN20DefaultTextFormatter4Ider7next_idE;

DefaultTextFormatter* generateFormatterArray();


/* 3---PrePostFixer--- */
typedef struct _PrePostFixer{
    DefaultTextFormatter m_defaultTextFormatterBase;
    const char* m_pre;
    const char* m_post;
}PrePostFixer;


void _ZNC12PrePostFixerEPKsKPcKPc(PrePostFixer *const this, const char* prefix, const char* postfix);
/*made of compiler:*/void _ZNC12PrePostFixerEPKsKPK12PrePostFixer(PrePostFixer *const this, const PrePostFixer *const other);
/*virtual*/void _ZND12PrePostFixerEPKv(void *const this);
/*virtual*/void _ZN12PrePostFixer5printEKPKvKPc(const void *const this, const char* text);
/*virtual*/void _ZN12PrePostFixer5printEKPKvlc(const void *const this, long num, char symbol);/*default symbol is: '\0'*/
/*virtual*/char _ZN12PrePostFixer16getDefaultSymbolEKPKv(const void *const this);

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

extern const char _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE;

void _ZNC18PrePostDollarFixerEPKsKPcKPc(PrePostDollarFixer *const this, const char* prefix, const char* postfix);
void _ZNC18PrePostDollarFixerEPKsKPK18PrePostDollarFixer(PrePostDollarFixer *const this, const PrePostDollarFixer *const other);
void _ZND18PrePostDollarFixerEPKv(void *const this);

/*default symbol is PrePostDollarFixer_DEFAULT_SYMBOL*/
void _ZNK18PrePostDollarFixer5printEKPKsic(const PrePostDollarFixer *const this, int num, char symbol);
void _ZNK18PrePostDollarFixer5printEKPKslc(const void *const this, long num, char symbol);/*vitrual*/
void _ZNK18PrePostDollarFixer5printEKPKsdc(const PrePostDollarFixer *const this, double num, char symbol);
char _ZN18PrePostDollarFixer16getDefaultSymbolEKPKv(const void *const this);

/* PrePostDollarFixer inlines:
 * no inlines*/


/* 5 ---PrePostHashFixer--- */
typedef struct _PrePostHashFixer{
    PrePostDollarFixer m_PrePostDollarFixerBase;
    int m_precision;
}PrePostHashFixer;

extern const char _ZN16PrePostHashFixer14DEFAULT_SYMBOLE;

void _ZNC16PrePostHashFixerEPKsi(PrePostHashFixer *const this, int prc);/*default prc: 4*/
void _ZND16PrePostHashFixerEPKv(void *const this);

/*default symbol is PrePostHashFixer_DEFAULT_SYMBOL*/
void _ZNK16PrePostHashFixer5printEKPKsic(const PrePostHashFixer *const this, int num, char symbol);
void _ZNK16PrePostHashFixer5printEKPKslc(const void *const this, long num, char symbol);/*virtual*/
char _ZN16PrePostHashFixer16getDefaultSymbolEKPKv(const void *const this);


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

extern const char _ZN23PrePostFloatDollarFixer14DEFAULT_SYMBOLE;

void _ZNC23PrePostFloatDollarFixerEPKsKPcKPc(PrePostFloatDollarFixer *const this, const char* prefix, const char* postfix);
void _ZND23PrePostFloatDollarFixerEPKv(void *const this);
void _ZNK23PrePostFloatDollarFixer5printEKPKsf(const PrePostFloatDollarFixer *const this, float num);
void _ZNK23PrePostFloatDollarFixer5printEKPKsfc(const PrePostFloatDollarFixer *const this, float num, char symbol);
char _ZN23PrePostFloatDollarFixer16getDefaultSymbolEKPKv(const void *const this);

/* PrePostFloatDollarFixer inlines:
 * no inlines*/


/*7 ---PrePostChecker--- */
typedef struct _PrePostChecker{
    PrePostFloatDollarFixer m_PrePostFloatDollarFixerBase;
}PrePostChecker;


void _ZNC14PrePostCheckerEPKs(PrePostChecker *const this);
void _ZND14PrePostCheckerEPKv(void *const this);

void _ZNK14PrePostChecker24printThisSymbolUsingFuncEKPKs(const PrePostChecker *const this);
void _ZNK14PrePostChecker23printThisSymbolDirectlyEKPKs(const PrePostChecker *const this);
void _ZNK14PrePostChecker32printDollarSymbolByCastUsingFuncEKPKs(const PrePostChecker *const this);
void _ZNK14PrePostChecker33printDollarSymbolByScopeUsingFuncEKPKs(const PrePostChecker *const this);
void _ZNK14PrePostChecker31printDollarSymbolByCastDirectlyEKPKs(const PrePostChecker *const this);
void _ZNK14PrePostChecker32printDollarSymbolByScopeDirectlyEKPKs(const PrePostChecker *const this);



/*8 ---Multiplier--- */
typedef struct _Multiplier{
    DefaultTextFormatter m_DefaultTextFormatterBase;
    int m_times;
}Multiplier;


void _ZND10Multiplier_dtorEPKs(Multiplier *const this);
/*I declared*/void _ZNC10Multiplier_dtorEPKsKPK10Multiplier(Multiplier *const this, const Multiplier *const other);
void _ZNK10Multiplier5printEKPKvKPc(const void *const this, const char* text);


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

