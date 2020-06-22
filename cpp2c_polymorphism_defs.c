#include "cpp2c_polymorphism_defs.h"
#include "stdlib.h"
#include "memory.h"

/*VTables*/
funcPtr_void_R_void TextFormatterVTable[]  = {(funcPtr_void_R_void)TextFormatter_dtor, NULL};
funcPtr_void_R_void DefaultTextFormatterVTable[]  = {(funcPtr_void_R_void)DefaultTextFormatter_dtor, (funcPtr_void_R_void)DefaultTextFormatter_print};
funcPtr_void_R_void PrePostFixerVTable[]  = {(funcPtr_void_R_void)PrePostFixer_dtor, (funcPtr_void_R_void)PrePostFixer_print_cc, (funcPtr_void_R_void)PrePostFixer_print_l_c, (funcPtr_void_R_void)PrePostFixer_getDefaultSymbol};
funcPtr_void_R_void PrePostDollarFixerVTable[]  = {(funcPtr_void_R_void)PrePostDollarFixer_dtor, (funcPtr_void_R_void)PrePostFixer_print_cc, (funcPtr_void_R_void)PrePostDollarFixer_print_l_c, (funcPtr_void_R_void)PrePostDollarFixer_getDefaultSymbol};
funcPtr_void_R_void PrePostHashFixerVTable[]  = {(funcPtr_void_R_void)PrePostHashFixer_dtor, (funcPtr_void_R_void)PrePostFixer_print_cc, (funcPtr_void_R_void)PrePostHashFixer_print_l_c, (funcPtr_void_R_void)PrePostHashFixer_getDefaultSymbol};
funcPtr_void_R_void PrePostFloatDollarFixerVTable[]  = {(funcPtr_void_R_void)PrePostFloatDollarFixer_dtor, (funcPtr_void_R_void)PrePostFixer_print_cc, (funcPtr_void_R_void)PrePostFixer_print_l_c, (funcPtr_void_R_void)PrePostFloatDollarFixer_getDefaultSymbol};
funcPtr_void_R_void PrePostCheckerVTable[]  = {(funcPtr_void_R_void)PrePostChecker_dtor, (funcPtr_void_R_void)PrePostFixer_print_cc, (funcPtr_void_R_void)PrePostFixer_print_l_c, (funcPtr_void_R_void)PrePostFloatDollarFixer_getDefaultSymbol};
funcPtr_void_R_void MultiplierVTable[]  = {(funcPtr_void_R_void)Multiplier_dtor, (funcPtr_void_R_void)Multiplier_print_cc};



/* 1---TextFormatter--- */
void TextFormatter_dtor(void *const this){}


/* 2---DefaultTextFormatter_Ider_next_id--- */
int DefaultTextFormatter_Ider_next_id = 0;

void DefaultTextFormatter_ctor(DefaultTextFormatter *const this)
{
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;/*TextFormatter ctor is inline*/

    this->m_id = DefaultTextFormatter_Ider_next_id;
    DefaultTextFormatter_Ider_next_id++;

    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->m_id);
}

void DefaultTextFormatter_copy_ctor(DefaultTextFormatter *const this, const DefaultTextFormatter *const other)
{
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;

    this->m_id = DefaultTextFormatter_Ider_next_id;
    DefaultTextFormatter_Ider_next_id++;

    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other->m_id, this->m_id);
}

DefaultTextFormatter* const DefaultTextFormatter_copy_assign(DefaultTextFormatter *const this, const DefaultTextFormatter *const other)
{
    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other->m_id, this->m_id);
    return this;
}

void DefaultTextFormatter_dtor(void *const this)
{
    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", ((DefaultTextFormatter*)this)->m_id);

    ((TextFormatter*)this)->m_vptr = TextFormatterVTable;
    TextFormatter_dtor((TextFormatter*)this);
}

void DefaultTextFormatter_print(const void *const this, const char* text)
{
    printf("%-60s | ", "[DefaultTextFormatter::print(const char*)]");
    printf("%s\n", text);
}

DefaultTextFormatter* generateFormatterArray()
{
    DefaultTextFormatter* ret = (DefaultTextFormatter*)malloc(3* sizeof(DefaultTextFormatter));
    size_t i;
    for(i=0; i<3; i++){
        DefaultTextFormatter_ctor(&(ret[i]));
    }

    return ret;
}


/* 3---PrePostFixer--- */
void PrePostFixer_ctor(PrePostFixer *const this, const char* prefix, const char* postfix)
{
    DefaultTextFormatter_ctor((DefaultTextFormatter*)this);
    ((TextFormatter*)this)->m_vptr = PrePostFixerVTable;
    this->m_pre = prefix;
    this->m_post = postfix;

    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this->m_pre, this->m_post);
}

/*I declared:*/
void PrePostFixer_copy_ctor(PrePostFixer *const this, const PrePostFixer *const other)
{
    DefaultTextFormatter_copy_ctor((DefaultTextFormatter*)this, (DefaultTextFormatter*)other);
    memcpy(&(this->m_pre), &(other->m_pre), strlen(other->m_pre)+1);
    memcpy(&(this->m_post), &(other->m_post), strlen(other->m_post)+1);
}

void PrePostFixer_dtor(void *const this)
{
    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;
    DefaultTextFormatter_dtor((DefaultTextFormatter*)this);
}

void PrePostFixer_print_cc(const void *const this, const char* text)
{
    printf("%-60s | ", "[PrePostFixer::print(const char*)]");
    printf("%s%s%s\n", ((PrePostFixer*)this)->m_pre, text, ((PrePostFixer*)this)->m_post);
}

void PrePostFixer_print_l_c(const void *const this, long num, char symbol)/*default '\0'*/
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

char PrePostFixer_getDefaultSymbol(const void *const this)
{
    return '\0';
}



/*4 ---PrePostDollarFixer Defs--- */
const char PrePostDollarFixer_DEFAULT_SYMBOL = '$';

void PrePostDollarFixer_ctor_cc_cc(PrePostDollarFixer *const this, const char* prefix, const char* postfix)
{
    PrePostFixer_ctor((PrePostFixer*)this, prefix, postfix);
    ((TextFormatter*)this)->m_vptr = PrePostDollarFixerVTable;

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void PrePostDollarFixer_copy_ctor(PrePostDollarFixer *const this, const PrePostDollarFixer *const other)
{
    PrePostFixer_copy_ctor((PrePostFixer*)this,(PrePostFixer*)other);
    ((TextFormatter*)this)->m_vptr = PrePostDollarFixerVTable;

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void PrePostDollarFixer_dtor(void *const this)
{
    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    ((TextFormatter*)this)->m_vptr = PrePostFixerVTable;
    PrePostFixer_dtor((PrePostFixer*)this);
}

void PrePostDollarFixer_print_i_c(const PrePostDollarFixer *const this, int num, char symbol)
{
    printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");

    ((funcPtr_pvoid_long_char_R_void)((((TextFormatter*)this)->m_vptr)[_Z5printElc]))(this, (long)num, symbol);
}

void PrePostDollarFixer_print_l_c(const void *const this, long num, char symbol)/*vitrual*/
{
    printf("%-60s | ", "[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");

    PrePostFixer_print_l_c((PrePostFixer*)this, num, symbol);
}

void PrePostDollarFixer_print_d_c(const PrePostDollarFixer *const this, double num, char symbol)
{
    printf("%-60s | ", "[PrePostDollarFixer::print(double, char)]");
    printf("%s%c%f%s\n", ((PrePostFixer*)this)->m_pre, symbol, num, ((PrePostFixer*)this)->m_post);
}

char PrePostDollarFixer_getDefaultSymbol(const void *const this)
{
    return PrePostDollarFixer_DEFAULT_SYMBOL;
}




/*5 ---PrePostHashFixer--- */
const char PrePostHashFixer_DEFAULT_SYMBOL = '#';

void PrePostHashFixer_ctor(PrePostHashFixer *const this, int prc)/*default prc: 4*/
{
    PrePostDollarFixer_ctor_cc_cc((PrePostDollarFixer*)this, "===> ", " <===");
    ((TextFormatter*)this)->m_vptr = PrePostHashFixerVTable;

    this->m_precision = prc;

    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post, this->m_precision);

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostFixer*)this)->m_pre, PrePostHashFixer_DEFAULT_SYMBOL, this->m_precision, 9999.9999, ((PrePostFixer*)this)->m_post);
}

void PrePostHashFixer_dtor(void *const this)
{
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    ((TextFormatter*)this)->m_vptr = PrePostDollarFixerVTable;
    PrePostDollarFixer_dtor((PrePostDollarFixer*)this);
}

void PrePostHashFixer_print_i_c(const PrePostHashFixer *const this, int num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(int, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostFixer*)this)->m_pre, symbol, this->m_precision, (double)num, ((PrePostFixer*)this)->m_post);
}

/*default symbol is PrePostHashFixer_DEFAULT_SYMBOL*/
void PrePostHashFixer_print_l_c(const void *const this, long num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(long, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostFixer*)this)->m_pre, symbol, ((PrePostHashFixer*)this)->m_precision, (double)num, ((PrePostFixer*)this)->m_post);
}

char PrePostHashFixer_getDefaultSymbol(const void *const this)
{
    return PrePostHashFixer_DEFAULT_SYMBOL;
}


/*6 ---PrePostFloatDollarFixer--- */
const char PrePostFloatDollarFixer_DEFAULT_SYMBOL = '@';

void PrePostFloatDollarFixer_ctor(PrePostFloatDollarFixer *const this, const char* prefix, const char* postfix)
{
    PrePostDollarFixer_ctor_cc_cc((PrePostDollarFixer*)this, prefix, postfix);
    ((TextFormatter*)this)->m_vptr = PrePostFloatDollarFixerVTable;
    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void PrePostFloatDollarFixer_dtor(void *const this)
{
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    ((TextFormatter*)this)->m_vptr = PrePostDollarFixerVTable;
    PrePostDollarFixer_dtor((PrePostDollarFixer*)this);
}

void PrePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer *const this, float num)
{
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float)]");
    printf("-->\n");

    PrePostFloatDollarFixer_print_f_c(this, num, PrePostFloatDollarFixer_DEFAULT_SYMBOL);
}

void PrePostFloatDollarFixer_print_f_c(const PrePostFloatDollarFixer *const this, float num, char symbol)
{
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float, char)]");
    printf("%s%c%.2f%s\n", ((PrePostFixer*)this)->m_pre, symbol, num, ((PrePostFixer*)this)->m_post);
}

char PrePostFloatDollarFixer_getDefaultSymbol(const void *const this)
{
    return PrePostFloatDollarFixer_DEFAULT_SYMBOL;
}


/*7 ---PrePostChecker Defs--- */
void PrePostChecker_ctor(PrePostChecker *const this)
{
    PrePostFloatDollarFixer_ctor((PrePostFloatDollarFixer*)this, "[[[[ ", " ]]]]");
    ((TextFormatter*)this)->m_vptr = PrePostCheckerVTable;
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void PrePostChecker_dtor(void *const this)
{
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    ((TextFormatter*)this)->m_vptr = PrePostFloatDollarFixerVTable;
    PrePostFloatDollarFixer_dtor((PrePostFloatDollarFixer*)this);
}

void PrePostChecker_printThisSymbolUsingFunc(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printThisSymbolUsingFunc()]");
    printf("Default symbol is %c\n", ((funcPtr_pvoid_R_char)((((TextFormatter*)this)->m_vptr)[_Z13defaultSymbolE]))(this));
}

void PrePostChecker_printThisSymbolDirectly(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printThisSymbolDirectly()]");

    printf("Default symbol is %c\n", PrePostFloatDollarFixer_DEFAULT_SYMBOL);
}

void PrePostChecker_printDollarSymbolByCastUsingFunc(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastUsingFunc()]");
    printf("Default symbol is %c\n", ((funcPtr_pvoid_R_char)((((TextFormatter*)this)->m_vptr)[_Z13defaultSymbolE]))(this));
    /*printf("Default symbol is %c\n", ((PrePostDollarFixer*)(this))->getDefaultSymbol());*/
}

void PrePostChecker_printDollarSymbolByScopeUsingFunc(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");

    printf("Default symbol is %c\n", PrePostDollarFixer_getDefaultSymbol(this));
}

void PrePostChecker_printDollarSymbolByCastDirectly(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastDirectly()]");

    printf("Default symbol is %c\n", PrePostDollarFixer_DEFAULT_SYMBOL);
}

void PrePostChecker_printDollarSymbolByScopeDirectly(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeDirectly()]");

    printf("Default symbol is %c\n", PrePostDollarFixer_DEFAULT_SYMBOL);
}



/*8 ---Multiplier--- */
void Multiplier_dtor(Multiplier *const this)
{
    printf("--- Multiplier DTOR: times = %d\n", this->m_times);
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;
    DefaultTextFormatter_dtor((DefaultTextFormatter*)this);
}

void Multiplier_copy_ctor(Multiplier *const this, const Multiplier *const other){
    DefaultTextFormatter_copy_ctor((DefaultTextFormatter*)this, (DefaultTextFormatter*)other);
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;
    memcpy(&(this->m_times), &(other->m_times), sizeof(this->m_times));
}


void Multiplier_print_cc(const void *const this, const char* text)
{
    int i, times = ((Multiplier*)this)->m_times;
    printf("%-60s | ", "[Multiplier::print(const char*)]");

    for (i = 0; i < times; ++i)
        printf("%s", text);
    printf("\n");
}
