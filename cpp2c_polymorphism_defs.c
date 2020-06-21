#include "cpp2c_polymorphism_defs.h"
#include "stdlib.h"


void(*TextFormatterVTable[2])(void)  = {(func_ptr_void_R_void)TextFormatter_dtor, (func_ptr_void_R_void)TextFormatter_print};
void(*DefaultTextFormatterVTable[2])(void)  = {(func_ptr_void_R_void)DefaultTextFormatter_dtor, (func_ptr_void_R_void)DefaultTextFormatter_print};
void(*PrePostFixerVTable[4])(void)  = {(func_ptr_void_R_void)PrePostFixer_dtor, (func_ptr_void_R_void)PrePostFixer_print_cc, (func_ptr_void_R_void)PrePostFixer_print_l_c, (func_ptr_void_R_void)PrePostFixer_getDefaultSymbol};
void(*PrePostDollarFixerVTable[4])(void)  = {(func_ptr_void_R_void)PrePostDollarFixer_dtor, (func_ptr_void_R_void)PrePostFixer_print_cc, (func_ptr_void_R_void)PrePostDollarFixer_print_l_c, (func_ptr_void_R_void)PrePostDollarFixer_getDefaultSymbol};
void(*PrePostHashFixerVTable[4])(void)  = {(func_ptr_void_R_void)PrePostHashFixer_dtor, (func_ptr_void_R_void)PrePostFixer_print_cc, (func_ptr_void_R_void)PrePostHashFixer_print_l_c, (func_ptr_void_R_void)PrePostHashFixer_getDefaultSymbol};
void(*PrePostFloatDollarFixerVTable[4])(void)  = {(func_ptr_void_R_void)PrePostFloatDollarFixer_dtor, (func_ptr_void_R_void)PrePostFixer_print_cc, (func_ptr_void_R_void)PrePostFixer_print_l_c, (func_ptr_void_R_void)PrePostFloatDollarFixer_getDefaultSymbol};
void(*PrePostCheckerVTable[4])(void)  = {(func_ptr_void_R_void)PrePostDollarFixer_dtor, (func_ptr_void_R_void)PrePostFixer_print_cc, (func_ptr_void_R_void)PrePostDollarFixer_print_l_c, (func_ptr_void_R_void)PrePostDollarFixer_getDefaultSymbol};
void(*MultiplierVTable[2])(void)  = {(func_ptr_void_R_void)Multiplier_dtor, (func_ptr_void_R_void)Multiplier_print_cc};



/* 1---TextFormatter--- */
void TextFormatter_dtor(void *const this){}


/* 2---DefaultTextFormatter_Ider_next_id--- */
int DefaultTextFormatter_Ider_next_id = 0;

void DefaultTextFormatter_ctor(DefaultTextFormatter *const this, func_ptr_void_R_void* vTable)/*defualt: DefaultTextFormatterVTable*/
{
    ((TextFormatter*)this)->m_vptr = vTable;/*TextFormatter ctor is inline*/
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;

    this->m_id = DefaultTextFormatter_Ider_next_id;
    DefaultTextFormatter_Ider_next_id++;

    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->m_id);
}

void DefaultTextFormatter_copy_ctor(DefaultTextFormatter *const this, const DefaultTextFormatter *const other, func_ptr_void_R_void* vTable)/*defualt: DefaultTextFormatterVTable*/
{
    ((TextFormatter*)this)->m_vptr = vTable;
    /*that's what it does - changes vptr in overloaded copy ctor????*/

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
        DefaultTextFormatter_ctor(&(ret[i]), DefaultTextFormatterVTable);
    }

    return ret;
}


/* 3---PrePostFixer--- */
void PrePostFixer_ctor(PrePostFixer *const this, const char* prefix, const char* postfix, func_ptr_void_R_void* vTable)/*defualt: PrePostFixerVTable*/
{
    DefaultTextFormatter_ctor((DefaultTextFormatter*)this, vTable);
    this->m_pre = prefix;
    this->m_post = postfix;

    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this->m_pre, this->m_post);
}

/*I declared:*/
void PrePostFixer_copy_ctor(PrePostFixer *const this, const PrePostFixer *const other, func_ptr_void_R_void* vTable)/*defualt: PrePostFixerVTable*/
{
    DefaultTextFormatter_copy_ctor((DefaultTextFormatter*)this, (DefaultTextFormatter*)other, vTable);
    this->m_pre = other->m_pre;
    this->m_post = other->m_post;
}

void PrePostFixer_dtor(void *const this)
{
    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
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

void PrePostDollarFixer_ctor_cc_cc(PrePostDollarFixer *const this, const char* prefix, const char* postfix, func_ptr_void_R_void* vTable)/*defualt: PrePostDollarFixer*/
{
    PrePostFixer_ctor((PrePostFixer*)this, prefix, postfix, vTable);

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void PrePostDollarFixer_copy_ctor(PrePostDollarFixer *const this, const PrePostDollarFixer *const other, func_ptr_void_R_void* vTable)/*defualt: PrePostDollarFixer*/
{
    PrePostFixer_copy_ctor((PrePostFixer*)this,(PrePostFixer*)other, vTable);

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void PrePostDollarFixer_dtor(void *const this)
{
    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    PrePostFixer_dtor((PrePostFixer*)this);
}

void PrePostDollarFixer_print_i_c(const PrePostDollarFixer *const this, int num, char symbol)
{
    printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");

    ((func_ptr_pvoid_long_char_R_void)(((func_ptr_void_R_void*)this)[_Z5printElc]))(this, (long)num, symbol);
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

void PrePostHashFixer_ctor(PrePostHashFixer *const this, int prc, func_ptr_void_R_void* vTable)/*default prc: 4*/
{
    PrePostDollarFixer_ctor_cc_cc(((PrePostDollarFixer*)this), "===> ", " <===", vTable);
    this->m_precision = prc;

    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post, this->m_precision);

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostFixer*)this)->m_pre, PrePostHashFixer_DEFAULT_SYMBOL, this->m_precision, 9999.9999, ((PrePostFixer*)this)->m_post);
}

void PrePostHashFixer_dtor(void *const this)
{
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    PrePostDollarFixer_dtor((PrePostDollarFixer*)this);
}

/*default symbol is PrePostHashFixer_DEFAULT_SYMBOL*/
void PrePostHashFixer_print_i_c(const PrePostHashFixer *const this, int num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(int, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostFixer*)this)->m_pre, symbol, this->m_precision, num, ((PrePostFixer*)this)->m_post);
}

void PrePostHashFixer_print_l_c(const void *const this, long num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(long, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostFixer*)this)->m_pre, symbol, ((PrePostHashFixer*)this)->m_precision, num, ((PrePostFixer*)this)->m_post);
}

char PrePostHashFixer_getDefaultSymbol(const void *const this)
{
    return PrePostHashFixer_DEFAULT_SYMBOL;
}


/*6 ---PrePostFloatDollarFixer--- */
const char PrePostFloatDollarFixer_DEFAULT_SYMBOL = '@';

void PrePostFloatDollarFixer_ctor(PrePostFloatDollarFixer *const this, const char* prefix, const char* postfix, func_ptr_void_R_void* vTable)
{
    PrePostDollarFixer_ctor_cc_cc((PrePostDollarFixer*)this, prefix, postfix, vTable);
    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void PrePostFloatDollarFixer_dtor(void *const this)
{
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
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
void PrePostChecker_ctor(PrePostChecker *const this, func_ptr_void_R_void* vTable)
{
    PrePostFloatDollarFixer_ctor((PrePostFloatDollarFixer*)this, "[[[[ ", " ]]]]", vTable);
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void PrePostChecker_dtor(void *const this)
{
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    PrePostFloatDollarFixer_dtor((PrePostFloatDollarFixer*)this);
}

void printThisSymbolUsingFunc(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printThisSymbolUsingFunc()]");
    printf("Default symbol is %c\n", ((func_ptr_pvoid_R_char)(((func_ptr_void_R_void*)this)[_Z13defaultSymbolE]))(this));
}

void printThisSymbolDirectly(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printThisSymbolDirectly()]");

    printf("Default symbol is %c\n", PrePostFloatDollarFixer_DEFAULT_SYMBOL);
}

void printDollarSymbolByCastUsingFunc(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastUsingFunc()]");
    printf("Default symbol is %c\n", ((func_ptr_pvoid_R_char)(((func_ptr_void_R_void*)this)[_Z13defaultSymbolE]))(this));
    /*printf("Default symbol is %c\n", ((PrePostDollarFixer*)(this))->getDefaultSymbol());*/
}

void printDollarSymbolByScopeUsingFunc(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");

    printf("Default symbol is %c\n", PrePostDollarFixer_getDefaultSymbol(this));
}

void printDollarSymbolByCastDirectly(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastDirectly()]");

    printf("Default symbol is %c\n", PrePostDollarFixer_DEFAULT_SYMBOL);
}

void printDollarSymbolByScopeDirectly(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeDirectly()]");

    printf("Default symbol is %c\n", PrePostDollarFixer_DEFAULT_SYMBOL);
}



/*8 ---Multiplier--- */
void Multiplier_dtor(Multiplier *const this)
{
    printf("--- Multiplier DTOR: times = %d\n", this->m_times);
    DefaultTextFormatter_dtor(this);
}

void Multiplier_print_cc(const void *const this, const char* text)
{
    printf("%-60s | ", "[Multiplier::print(const char*)]");

    for (int i = 0; i < ((Multiplier*)this)->m_times; ++i)
        printf("%s", text);
    printf("\n");
}


/*---------------------------------------------source------------------------------------------------
 * --------------------------------------------------------------------------------------------------
 * --------------------------------------------------------------------------------------------------*/

/*
//// DefaultTextFormatter Defs ////////////


DefaultTextFormatter::DefaultTextFormatter()
:   id(Ider::getId())
{
    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", id);
}

DefaultTextFormatter::~DefaultTextFormatter()
{
    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", id);
}

DefaultTextFormatter::DefaultTextFormatter(const DefaultTextFormatter& other)
:   id(Ider::getId())
{
    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other.id, id);
}

DefaultTextFormatter& DefaultTextFormatter::operator=(const DefaultTextFormatter& other)
{
    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other.id, id);
    return *this;
}

void DefaultTextFormatter::print(const char* text) const
{
    printFunc("[DefaultTextFormatter::print(const char*)]");    
    printf("%s\n", text);
}

DefaultTextFormatter* generateFormatterArray()
{
    return new DefaultTextFormatter[3];
}
*/


/* PrePostFixer Defs

PrePostFixer::PrePostFixer(const char* prefix, const char* postfix)
:   pre(prefix)
,   post(postfix)
{
    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", pre, post);
}


PrePostFixer::~PrePostFixer()
{
    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", pre, post);
}

void PrePostFixer::print(const char* text) const
{
    printFunc("[PrePostFixer::print(const char*)]");
    printf("%s%s%s\n", pre, text, post);
}


//// PrePostDollarFixer Defs ////////////

PrePostDollarFixer::PrePostDollarFixer(const char* prefix, const char* postfix)
:   PrePostFixer(prefix, postfix)
{
    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", getPrefix(), getPostfix());
}

PrePostDollarFixer::PrePostDollarFixer(const PrePostDollarFixer& other)
:   PrePostFixer(other)
{
    printf("--- PrePostDollarFixer Copy CTOR: \"%s\"...\"%s\"\n", getPrefix(), getPostfix());
}

PrePostDollarFixer::~PrePostDollarFixer()
{
    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", getPrefix(), getPostfix());
}

void PrePostDollarFixer::print(int num, char symbol) const
{
    printFunc("[PrePostDollarFixer::print(int, char)]"); 
    printf("-->\n");

    print(long(num), symbol);
}

void PrePostDollarFixer::print(long num, char symbol) const
{
    printFunc("[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");

    PrePostFixer::print(num, symbol);
}

void PrePostDollarFixer::print(double num, char symbol) const
{
    printFunc("[PrePostDollarFixer::print(double, char)]"); 
    printf("%s%c%f%s\n", getPrefix(), symbol, num, getPostfix());
}



//// PrePostHashFixer Defs ////////////

PrePostHashFixer::PrePostHashFixer(int prc)
:   PrePostDollarFixer("===> ", " <===")
,   precision(prc)
{
    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", getPrefix(), getPostfix(), precision);   

    print(9999.9999);
}

PrePostHashFixer::~PrePostHashFixer()
{
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", getPrefix(), getPostfix());
}
    
void PrePostHashFixer::print(int num, char symbol) const
{
    printFunc("[PrePostHashFixer::print(int, char)]"); 
    printf("-->\n");

    print(double(num), symbol);
}

void PrePostHashFixer::print(long num, char symbol) const
{
    printFunc("[PrePostHashFixer::print(long, char)]"); 
    printf("-->\n");

    print(double(num), symbol);
}


//// PrePostFloatDollarFixer Defs ////////////

PrePostFloatDollarFixer::PrePostFloatDollarFixer(const char* prefix, const char* postfix)
:   PrePostDollarFixer(prefix, postfix)
{
    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", getPrefix(), getPostfix());
}

PrePostFloatDollarFixer::~PrePostFloatDollarFixer()
{
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n", getPrefix(), getPostfix());
}

void PrePostFloatDollarFixer::print(float num) const
{
    printFunc("[PrePostFloatDollarFixer::print(float)]");
    printf("-->\n");

    print(num, DEFAULT_SYMBOL);
}

void PrePostFloatDollarFixer::print(float num, char symbol) const
{
    printFunc("[PrePostFloatDollarFixer::print(float, char)]"); 

    printf("%s%c%.2f%s\n", getPrefix(), symbol, num, getPostfix());
}



//// PrePostChecker Defs ////////////

PrePostChecker::PrePostChecker()
:   PrePostFloatDollarFixer("[[[[ ", " ]]]]")
{
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", getPrefix(), getPostfix());
}    

PrePostChecker::~PrePostChecker()
{
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", getPrefix(), getPostfix());
}

void PrePostChecker::printThisSymbolUsingFunc() const
{
    printFunc("[PrePostChecker::printThisSymbolUsingFunc()]");

    printf("Default symbol is %c\n", this->getDefaultSymbol());
}

void PrePostChecker::printThisSymbolDirectly() const
{
    printFunc("[PrePostChecker::printThisSymbolDirectly()]");

    printf("Default symbol is %c\n", this->DEFAULT_SYMBOL);
}

void PrePostChecker::printDollarSymbolByCastUsingFunc() const
{
    printFunc("[PrePostChecker::printDollarSymbolByCastUsingFunc()]");

    printf("Default symbol is %c\n", ((PrePostDollarFixer*)(this))->getDefaultSymbol());
}

void PrePostChecker::printDollarSymbolByScopeUsingFunc() const
{
    printFunc("[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");

    printf("Default symbol is %c\n", this->PrePostDollarFixer::getDefaultSymbol());
}

void PrePostChecker::printDollarSymbolByCastDirectly() const
{
    printFunc("[PrePostChecker::printDollarSymbolByCastDirectly()]");

    printf("Default symbol is %c\n", ((PrePostDollarFixer*)(this))->DEFAULT_SYMBOL);
}

void PrePostChecker::printDollarSymbolByScopeDirectly() const
{
    printFunc("[PrePostChecker::printDollarSymbolByScopeDirectly()]");

    printf("Default symbol is %c\n", this->PrePostDollarFixer::DEFAULT_SYMBOL);
}


//// Multiplier Defs ////////////
    
void Multiplier::print(const char* text) const
{
    printFunc("[Multiplier::print(const char*)]");
    
    for (int i = 0; i < times; ++i)
        printf("%s", text);
    printf("\n");
}
*/

/*--------------------------------------------end of source-----------------------------------------------
 * -------------------------------------------------------------------------------------------------------
 * ------------------------------------------------------------------------------------------------------*/

