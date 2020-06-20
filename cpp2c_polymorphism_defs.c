#include "cpp2c_polymorphism_defs.h"
#include "stdlib.h"

/* 1---TextFormatter--- */
void TextFormatter_ctor(TextFormatter *const this, void(**vTable)(void)){/*defualt: TextFormatterVTable*/
    this->m_vptr = vTable;
}

void TextFormatter_dtor(TextFormatter *const this){}


/* 2---DefaultTextFormatter_Ider_next_id--- */
int DefaultTextFormatter_Ider_next_id = 0;

void DefaultTextFormatter_ctor(DefaultTextFormatter *const this, void(**vTable)(void)){/*defualt: DefaultTextFormatterVTable*/
    TextFormatter_ctor((TextFormatter*)this, vTable);
    ((TextFormatter*)this)->m_vptr = DefaultTextFormatterVTable;

    this->m_id = DefaultTextFormatter_Ider_next_id;
    DefaultTextFormatter_Ider_next_id++;

    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->m_id);
}

void DefaultTextFormatter_copy_ctor(DefaultTextFormatter *const this, const DefaultTextFormatter *const other, void(**vTable)(void)){/*defualt: DefaultTextFormatterVTable*/
    TextFormatter_ctor((TextFormatter*)this, vTable);
    /*that's what it does - changes vptr in overloaded copy ctor????*/

    this->m_id = DefaultTextFormatter_Ider_next_id;
    DefaultTextFormatter_Ider_next_id++;

    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other->m_id, this->m_id);
}

DefaultTextFormatter* const DefaultTextFormatter_copy_assign(DefaultTextFormatter *const this, const DefaultTextFormatter *const other){
    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other->m_id, this->m_id);
    return this;
}

void DefaultTextFormatter_dtor(DefaultTextFormatter *const this){
    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", this->m_id);

    TextFormatter_dtor((TextFormatter*)this);
}

void DefaultTextFormatter_print(const DefaultTextFormatter *const this, const char* text){
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
void PrePostFixer_ctor(PrePostFixer *const this, const char* prefix, const char* postfix, void(**vTable)(void)){/*defualt: PrePostFixerVTable*/
    DefaultTextFormatter_ctor((DefaultTextFormatter*)this, vTable);
    this->m_pre = prefix;
    this->m_post = postfix;

    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this->m_pre, this->m_post);
}

/*I declared:*/
void PrePostFixer_copy_ctor(PrePostFixer *const this, const PrePostFixer *const other, void(**vTable)(void)){/*defualt: PrePostFixerVTable*/
    DefaultTextFormatter_copy_ctor((DefaultTextFormatter*)this, (DefaultTextFormatter*)other, vTable);
    this->m_pre = other->m_pre;
    this->m_post = other->m_post;

    ((TextFormatter*)this)->m_vptr = PrePostFixerVTable;
}

void PrePostFixer_dtor(PrePostFixer *const this){
    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", this->m_pre, this->m_post);
    DefaultTextFormatter_dtor((DefaultTextFormatter*)this);
}

void PrePostFixer_print_cc(const PrePostFixer *const this, const char* text){
    printf("%-60s | ", "[PrePostFixer::print(const char*)]");
    printf("%s%s%s\n", this->m_pre, text, this->m_post);
}

void PrePostFixer_print_l_c(const PrePostFixer *const this, long num, char symbol){/*default '\0'*/
    printf("%-60s | ", "[PrePostFixer::print(long, char)]");
    printf("-->\n");

    if (symbol){
        printf("%-60s | ", "[PrePostFixer::print_num(long, char)]");
        printf("%s%c%ld%s\n", this->m_pre, symbol, num, this->m_post);
    }
    else{
        printf("%-60s | ", "[PrePostFixer::print_num(long)]");
        printf("%s%ld%s\n", this->m_pre, num, this->m_post);
    }
}

char PrePostFixer_getDefaultSymbol(const PrePostFixer *const this){
    return '\0';
}



/*4 ---PrePostDollarFixer Defs--- */
const char PrePostDollarFixer_DEFAULT_SYMBOL = '$';

void PrePostDollarFixer_ctor_cc_cc(PrePostDollarFixer *const this, const char* prefix, const char* postfix, void(**vTable)(void))/*defualt: PrePostDollarFixer*/
{
    PrePostFixer_ctor((PrePostFixer*)this, prefix, postfix, vTable);

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void PrePostDollarFixer_copy_ctor(PrePostDollarFixer *const this, const PrePostDollarFixer *const other, void(**vTable)(void))/*defualt: PrePostDollarFixer*/
{
    PrePostFixer_copy_ctor((PrePostFixer*)other, vTable);

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
}

void PrePostDollarFixer_dtor(PrePostDollarFixer *const this)
{
    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->m_pre, ((PrePostFixer*)this)->m_post);
    PrePostFixer_dtor((PrePostFixer*)this);
}

void PrePostDollarFixer_print_i_c(const PrePostDollarFixer *const this, int num, char symbol){
    printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");

    this[_Z5printElc];
}

void PrePostDollarFixer_print_l_c(const PrePostDollarFixer *const this, long num, char symbol)/*vitrual*/
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

char PrePostDollarFixer_getDefaultSymbol(const PrePostDollarFixer *const this)
{
    return PrePostDollarFixer_DEFAULT_SYMBOL;
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

*/

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


/*--------------------------------------------end of source-----------------------------------------------
 * -------------------------------------------------------------------------------------------------------
 * ------------------------------------------------------------------------------------------------------*/

