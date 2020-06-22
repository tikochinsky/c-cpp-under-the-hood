#include "cpp2c_polymorphism_defs.h"
#include "stdlib.h"
#include "memory.h"

/*VTables*/
funcPtr_pvRv TextFormatterVTable[]  = {(funcPtr_pvRv)_ZNC13TextFormatterEPKs, NULL};
funcPtr_pvRv DefaultTextFormatterVTable[]  = {(funcPtr_pvRv)_ZND20DefaultTextFormatterEPKv, (funcPtr_pvRv)_ZN20DefaultTextFormatter5printEKPKvKPc};
funcPtr_pvRv PrePostFixerVTable[]  = {(funcPtr_pvRv)_ZND12PrePostFixerEPKv, (funcPtr_pvRv)_ZN12PrePostFixer5printEKPKvKPc, (funcPtr_pvRv)_ZN12PrePostFixer5printEKPKvlc, (funcPtr_pvRv)_ZN12PrePostFixer16getDefaultSymbolEKPKv};
funcPtr_pvRv PrePostDollarFixerVTable[]  = {(funcPtr_pvRv)_ZND18PrePostDollarFixerEPKv, (funcPtr_pvRv)_ZN12PrePostFixer5printEKPKvKPc, (funcPtr_pvRv)_ZNK18PrePostDollarFixer5printEKPKslc, (funcPtr_pvRv)_ZN18PrePostDollarFixer16getDefaultSymbolEKPKv};
funcPtr_pvRv PrePostHashFixerVTable[]  = {(funcPtr_pvRv)_ZND16PrePostHashFixerEPKv, (funcPtr_pvRv)_ZN12PrePostFixer5printEKPKvKPc, (funcPtr_pvRv)_ZNK16PrePostHashFixer5printEKPKslc, (funcPtr_pvRv)_ZN16PrePostHashFixer16getDefaultSymbolEKPKv};
funcPtr_pvRv PrePostFloatDollarFixerVTable[]  = {(funcPtr_pvRv)_ZND23PrePostFloatDollarFixerEPKv, (funcPtr_pvRv)_ZN12PrePostFixer5printEKPKvKPc, (funcPtr_pvRv)_ZN12PrePostFixer5printEKPKvlc, (funcPtr_pvRv)_ZN23PrePostFloatDollarFixer16getDefaultSymbolEKPKv};
funcPtr_pvRv PrePostCheckerVTable[]  = {(funcPtr_pvRv)_ZND14PrePostCheckerEPKv, (funcPtr_pvRv)_ZN12PrePostFixer5printEKPKvKPc, (funcPtr_pvRv)_ZN12PrePostFixer5printEKPKvlc, (funcPtr_pvRv)_ZN23PrePostFloatDollarFixer16getDefaultSymbolEKPKv};
funcPtr_pvRv MultiplierVTable[]  = {(funcPtr_pvRv)_ZND10Multiplier_dtorEPKs, (funcPtr_pvRv)_ZNK10Multiplier5printEKPKvKPc};



/* 1---TextFormatter--- */
void _ZNC13TextFormatterEPKs(void *const this){}


/* 2---DefaultTextFormatter_Ider_next_id--- */
int _ZN20DefaultTextFormatter4Ider7next_idE = 0;

void _ZNC20DefaultTextFormatterEPKs(DefaultTextFormatter *const this)
{
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;/*TextFormatter ctor is inline*/

    this->m_id = _ZN20DefaultTextFormatter4Ider7next_idE;
    _ZN20DefaultTextFormatter4Ider7next_idE++;

    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->m_id);
}

void _ZNC20DefaultTextFormatterEPKsKPKs(DefaultTextFormatter *const this, const DefaultTextFormatter *const other)
{
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;

    this->m_id = _ZN20DefaultTextFormatter4Ider7next_idE;
    _ZN20DefaultTextFormatter4Ider7next_idE++;

    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other->m_id, this->m_id);
}

DefaultTextFormatter* const _ZNC20DefaultTextFormatter10copyAssignEPKsKPKs(DefaultTextFormatter *const this, const DefaultTextFormatter *const other)
{
    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other->m_id, this->m_id);
    return this;
}

void _ZND20DefaultTextFormatterEPKv(void *const this)
{
    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", ((DefaultTextFormatter*)this)->m_id);

    ((TextFormatter*)this)->m_vptr = TextFormatterVTable;
    _ZNC13TextFormatterEPKs((TextFormatter *) this);
}

void _ZN20DefaultTextFormatter5printEKPKvKPc(const void *const this, const char* text)
{
    printf("%-60s | ", "[DefaultTextFormatter::print(const char*)]");
    printf("%s\n", text);
}

DefaultTextFormatter* generateFormatterArray()
{
    DefaultTextFormatter* ret = (DefaultTextFormatter*)malloc(3* sizeof(DefaultTextFormatter));
    size_t i;
    for(i=0; i<3; i++){
        _ZNC20DefaultTextFormatterEPKs(&(ret[i]));
    }

    return ret;
}


/* 3---PrePostFixer--- */
void _ZNC12PrePostFixerEPKsKPcKPc(PrePostFixer *const this, const char* prefix, const char* postfix)
{
    _ZNC20DefaultTextFormatterEPKs((DefaultTextFormatter *) this);
    ((TextFormatter*)this)->m_vptr = PrePostFixerVTable;
    this->m_pre = prefix;
    this->m_post = postfix;

    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this->m_pre, this->m_post);
}

/*I declared:*/
void _ZNC12PrePostFixerEPKsKPK12PrePostFixer(PrePostFixer *const this, const PrePostFixer *const other)
{
    _ZNC20DefaultTextFormatterEPKsKPKs((DefaultTextFormatter *) this, (DefaultTextFormatter *) other);
    memcpy(&(this->m_pre), &(other->m_pre), strlen(other->m_pre)+1);
    memcpy(&(this->m_post), &(other->m_post), strlen(other->m_post)+1);
}

void _ZND12PrePostFixerEPKv(void *const this)
{
    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;
    _ZND20DefaultTextFormatterEPKv((DefaultTextFormatter *) this);
}

void _ZN12PrePostFixer5printEKPKvKPc(const void *const this, const char* text)
{
    printf("%-60s | ", "[PrePostFixer::print(const char*)]");
    printf("%s%s%s\n", ((PrePostFixer*)this)->m_pre, text, ((PrePostFixer*)this)->m_post);
}

void _ZN12PrePostFixer5printEKPKvlc(const void *const this, long num, char symbol)/*default '\0'*/
{
    printf("%-60s | ", "[PrePostFixer::print(long, char)]");
    printf("-->\n");

    if (symbol){
        printf("%-60s | ", "[PrePostFixer::print_num(long, char)]");
        printf("%s%c%ld%s\n", ((PrePostFixer*)this)->m_pre, symbol, num, ((PrePostFixer*)this)->m_post);
    }
    else{
        printf("%-60s | ", "[PrePostFixer::print_num(long)]");
        printf("%s%ld%s\n", ((PrePostFixer*)this)->m_pre, num, ((PrePostFixer*)this)->m_post);
    }
}

char _ZN12PrePostFixer16getDefaultSymbolEKPKv(const void *const this)
{
    return '\0';
}



/*4 ---PrePostDollarFixer Defs--- */
const char _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE = '$';

void _ZNC18PrePostDollarFixerEPKsKPcKPc(PrePostDollarFixer *const this, const char* prefix, const char* postfix)
{
    _ZNC12PrePostFixerEPKsKPcKPc((PrePostFixer *) this, prefix, postfix);
    ((TextFormatter*)this)->m_vptr = PrePostDollarFixerVTable;

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void _ZNC18PrePostDollarFixerEPKsKPK18PrePostDollarFixer(PrePostDollarFixer *const this, const PrePostDollarFixer *const other)
{
    _ZNC12PrePostFixerEPKsKPK12PrePostFixer((PrePostFixer *) this, (PrePostFixer *) other);
    ((TextFormatter*)this)->m_vptr = PrePostDollarFixerVTable;

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void _ZND18PrePostDollarFixerEPKv(void *const this)
{
    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    ((TextFormatter*)this)->m_vptr = PrePostFixerVTable;
    _ZND12PrePostFixerEPKv((PrePostFixer *) this);
}

void _ZNK18PrePostDollarFixer5printEKPKsic(const PrePostDollarFixer *const this, int num, char symbol)
{
    printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");

    ((funcPtr_pvlcRv)((((TextFormatter*)this)->m_vptr)[_Z5printElc]))(this, (long)num, symbol);
}

void _ZNK18PrePostDollarFixer5printEKPKslc(const void *const this, long num, char symbol)/*vitrual*/
{
    printf("%-60s | ", "[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");

    _ZN12PrePostFixer5printEKPKvlc((PrePostFixer *) this, num, symbol);
}

void _ZNK18PrePostDollarFixer5printEKPKsdc(const PrePostDollarFixer *const this, double num, char symbol)
{
    printf("%-60s | ", "[PrePostDollarFixer::print(double, char)]");
    printf("%s%c%f%s\n", ((PrePostFixer*)this)->m_pre, symbol, num, ((PrePostFixer*)this)->m_post);
}

char _ZN18PrePostDollarFixer16getDefaultSymbolEKPKv(const void *const this)
{
    return _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE;
}




/*5 ---PrePostHashFixer--- */
const char _ZN16PrePostHashFixer14DEFAULT_SYMBOLE = '#';

void _ZNC16PrePostHashFixerEPKsi(PrePostHashFixer *const this, int prc)/*default prc: 4*/
{
    _ZNC18PrePostDollarFixerEPKsKPcKPc((PrePostDollarFixer *) this, "===> ", " <===");
    ((TextFormatter*)this)->m_vptr = PrePostHashFixerVTable;

    this->m_precision = prc;

    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post, this->m_precision);

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostFixer*)this)->m_pre, _ZN16PrePostHashFixer14DEFAULT_SYMBOLE, this->m_precision, 9999.9999, ((PrePostFixer*)this)->m_post);
}

void _ZND16PrePostHashFixerEPKv(void *const this)
{
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    ((TextFormatter*)this)->m_vptr = PrePostDollarFixerVTable;
    _ZND18PrePostDollarFixerEPKv((PrePostDollarFixer *) this);
}

void _ZNK16PrePostHashFixer5printEKPKsic(const PrePostHashFixer *const this, int num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(int, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostFixer*)this)->m_pre, symbol, this->m_precision, (double)num, ((PrePostFixer*)this)->m_post);
}

/*default symbol is PrePostHashFixer_DEFAULT_SYMBOL*/
void _ZNK16PrePostHashFixer5printEKPKslc(const void *const this, long num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(long, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostFixer*)this)->m_pre, symbol, ((PrePostHashFixer*)this)->m_precision, (double)num, ((PrePostFixer*)this)->m_post);
}

char _ZN16PrePostHashFixer16getDefaultSymbolEKPKv(const void *const this)
{
    return _ZN16PrePostHashFixer14DEFAULT_SYMBOLE;
}


/*6 ---PrePostFloatDollarFixer--- */
const char _ZN23PrePostFloatDollarFixer14DEFAULT_SYMBOLE = '@';

void _ZNC23PrePostFloatDollarFixerEPKsKPcKPc(PrePostFloatDollarFixer *const this, const char* prefix, const char* postfix)
{
    _ZNC18PrePostDollarFixerEPKsKPcKPc((PrePostDollarFixer *) this, prefix, postfix);
    ((TextFormatter*)this)->m_vptr = PrePostFloatDollarFixerVTable;
    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void _ZND23PrePostFloatDollarFixerEPKv(void *const this)
{
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    ((TextFormatter*)this)->m_vptr = PrePostDollarFixerVTable;
    _ZND18PrePostDollarFixerEPKv((PrePostDollarFixer *) this);
}

void _ZNK23PrePostFloatDollarFixer5printEKPKsf(const PrePostFloatDollarFixer *const this, float num)
{
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float)]");
    printf("-->\n");

    _ZNK23PrePostFloatDollarFixer5printEKPKsfc(this, num, _ZN23PrePostFloatDollarFixer14DEFAULT_SYMBOLE);
}

void _ZNK23PrePostFloatDollarFixer5printEKPKsfc(const PrePostFloatDollarFixer *const this, float num, char symbol)
{
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float, char)]");
    printf("%s%c%.2f%s\n", ((PrePostFixer*)this)->m_pre, symbol, num, ((PrePostFixer*)this)->m_post);
}

char _ZN23PrePostFloatDollarFixer16getDefaultSymbolEKPKv(const void *const this)
{
    return _ZN23PrePostFloatDollarFixer14DEFAULT_SYMBOLE;
}


/*7 ---PrePostChecker Defs--- */
void _ZNC14PrePostCheckerEPKs(PrePostChecker *const this)
{
    _ZNC23PrePostFloatDollarFixerEPKsKPcKPc((PrePostFloatDollarFixer *) this, "[[[[ ", " ]]]]");
    ((TextFormatter*)this)->m_vptr = PrePostCheckerVTable;
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void _ZND14PrePostCheckerEPKv(void *const this)
{
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    ((TextFormatter*)this)->m_vptr = PrePostFloatDollarFixerVTable;
    _ZND23PrePostFloatDollarFixerEPKv((PrePostFloatDollarFixer *) this);
}

void _ZNK14PrePostChecker24printThisSymbolUsingFuncEKPKs(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printThisSymbolUsingFunc()]");
    printf("Default symbol is %c\n", ((funcPtr_pvRc)((((TextFormatter*)this)->m_vptr)[_Z13defaultSymbolE]))(this));
}

void _ZNK14PrePostChecker23printThisSymbolDirectlyEKPKs(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printThisSymbolDirectly()]");

    printf("Default symbol is %c\n", _ZN23PrePostFloatDollarFixer14DEFAULT_SYMBOLE);
}

void _ZNK14PrePostChecker32printDollarSymbolByCastUsingFuncEKPKs(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastUsingFunc()]");
    printf("Default symbol is %c\n", ((funcPtr_pvRc)((((TextFormatter*)this)->m_vptr)[_Z13defaultSymbolE]))(this));
    /*printf("Default symbol is %c\n", ((PrePostDollarFixer*)(this))->getDefaultSymbol());*/
}

void _ZNK14PrePostChecker33printDollarSymbolByScopeUsingFuncEKPKs(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");

    printf("Default symbol is %c\n", _ZN18PrePostDollarFixer16getDefaultSymbolEKPKv(this));
}

void _ZNK14PrePostChecker31printDollarSymbolByCastDirectlyEKPKs(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastDirectly()]");

    printf("Default symbol is %c\n", _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE);
}

void _ZNK14PrePostChecker32printDollarSymbolByScopeDirectlyEKPKs(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeDirectly()]");

    printf("Default symbol is %c\n", _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE);
}



/*8 ---Multiplier--- */
void _ZND10Multiplier_dtorEPKs(Multiplier *const this)
{
    printf("--- Multiplier DTOR: times = %d\n", this->m_times);
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;
    _ZND20DefaultTextFormatterEPKv((DefaultTextFormatter *) this);
}

void _ZNC10Multiplier_dtorEPKsKPK10Multiplier(Multiplier *const this, const Multiplier *const other){
    _ZNC20DefaultTextFormatterEPKsKPKs((DefaultTextFormatter *) this, (DefaultTextFormatter *) other);
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;
    memcpy(&(this->m_times), &(other->m_times), sizeof(this->m_times));
}


void _ZNK10Multiplier5printEKPKvKPc(const void *const this, const char* text)
{
    int i, times = ((Multiplier*)this)->m_times;
    printf("%-60s | ", "[Multiplier::print(const char*)]");

    for (i = 0; i < times; ++i)
        printf("%s", text);
    printf("\n");
}
