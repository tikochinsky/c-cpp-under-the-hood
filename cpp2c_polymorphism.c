#include "cpp2c_polymorphism_defs.h"
#include "stdlib.h"



void doPrePostFixer()
{
    PrePostFixer angleBrackets;
    printf("\n--- start doPrePostFixer() ---\n\n");

    PrePostFixer_ctor(&angleBrackets, "<<< ", " >>>");
    PrePostFixer_print_cc(&angleBrackets,"Hello World!");
    PrePostFixer_print_l_c(&angleBrackets, -777, '\0');
    PrePostFixer_print_l_c(&angleBrackets, 350, '#');
    PrePostFixer_print_l_c(&angleBrackets, 3, '\0');

    printf("\n--- end doPrePostFixer() ---\n\n");
    PrePostFixer_dtor(&angleBrackets);
}

void doPrePostDollarFixer()
{
    PrePostDollarFixer asterisks;
    printf("\n--- start doPrePostDollarFixer() ---\n\n");

    PrePostDollarFixer_ctor_cc_cc(&asterisks, "***** ", " *****");
    PrePostDollarFixer_print_i_c(&asterisks, -777, PrePostDollarFixer_DEFAULT_SYMBOL);
    PrePostDollarFixer_print_i_c(&asterisks, 350, '#');
    PrePostDollarFixer_print_d_c(&asterisks, 3.14f, PrePostDollarFixer_DEFAULT_SYMBOL);

    printf("\n--- end doPrePostDollarFixer() ---\n\n");
    PrePostDollarFixer_dtor(&asterisks);
}

void doPrePostChecker()
{
    PrePostChecker check;
    printf("\n--- start doPrePostChecker() ---\n\n");

    PrePostChecker_ctor(&check);

    PrePostChecker_printThisSymbolUsingFunc(&check);
    PrePostChecker_printThisSymbolDirectly(&check);
    PrePostChecker_printDollarSymbolByCastDirectly(&check);
    PrePostChecker_printDollarSymbolByScopeDirectly(&check);
    PrePostChecker_printDollarSymbolByCastUsingFunc(&check);
    PrePostChecker_printDollarSymbolByScopeUsingFunc(&check);

    printf("\n--- end doPrePostChecker() ---\n\n");
    PrePostChecker_dtor(&check);
}

void doPrePostFloatDollarFixer()
{
    PrePostFloatDollarFixer hashes;
    PrePostDollarFixer hashes2;

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    PrePostFloatDollarFixer_ctor(&hashes, "### ", " ###");
    PrePostFloatDollarFixer_print_f(&hashes, -777);
    PrePostFloatDollarFixer_print_f_c(&hashes, 350, '#');
    PrePostFloatDollarFixer_print_f(&hashes, 3.14f);


    PrePostDollarFixer_copy_ctor(&hashes2, (PrePostDollarFixer*)(&hashes));
    PrePostDollarFixer_print_d_c(&hashes2, 7.5, PrePostDollarFixer_DEFAULT_SYMBOL);
    PrePostDollarFixer_print_i_c(&hashes2, 100, PrePostDollarFixer_DEFAULT_SYMBOL);

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");
    PrePostDollarFixer_dtor(&hashes2);
    PrePostFloatDollarFixer_dtor(&hashes);
}

void runAsPrePostFixerRef(const PrePostFixer* const pp)
{
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");

    ((funcPtr_pvoid_long_char)((((TextFormatter*)pp)->m_vptr)[_Z5printElc]))(pp, 123, '\0');

    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerRef(const PrePostDollarFixer* const pp)
{
    printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");

    PrePostDollarFixer_print_i_c(pp, 123, PrePostDollarFixer_DEFAULT_SYMBOL);

    printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerObj(const PrePostDollarFixer pp)
{
    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");

    PrePostDollarFixer_print_i_c(&pp, 123, PrePostDollarFixer_DEFAULT_SYMBOL);

    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");
}


void runAsPrePostHashFixerRef(const PrePostHashFixer* const pp)
{
    printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");

    PrePostHashFixer_print_i_c(pp, 123, PrePostHashFixer_DEFAULT_SYMBOL);

    printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}

void doMultiplier()
{
    Multiplier m1, m2, m3, m4;
    printf("\n--- start doMultiplier() ---\n\n");

    /*construct m1*/
    DefaultTextFormatter_ctor(&(m1.m_DefaultTextFormatterBase));
    ((TextFormatter*)&m1)->m_vptr = MultiplierVTable;
    m1.m_times = 3;
    printf("--- Multiplier CTOR: times = %d\n", m1.m_times);

    /*construct m2*/
    DefaultTextFormatter_ctor(&(m2.m_DefaultTextFormatterBase));
    ((TextFormatter*)&m2)->m_vptr = MultiplierVTable;
    m2.m_times = 5;
    printf("--- Multiplier CTOR: times = %d\n", m2.m_times);

    /*construct m3*/
    Multiplier_copy_ctor(&m3, &m1);

    /*construct m4*/
    Multiplier_copy_ctor(&m4, &m2);

    Multiplier_print_cc(&m1, "abc ");
    Multiplier_print_cc(&m2, "abc ");
    Multiplier_print_cc(&m3, "abc ");
    Multiplier_print_cc(&m4, "abc ");


    printf("\n--- start doMultiplier() ---\n\n");

    Multiplier_dtor(&m4);
    Multiplier_dtor(&m3);
    Multiplier_dtor(&m2);
    Multiplier_dtor(&m1);
}

void doFormatterArray()
{
    int i;
    PrePostDollarFixer tempObj1;
    Multiplier tempObj2;
    PrePostChecker tempObj3;
    DefaultTextFormatter formatters[3], obj1, obj2, obj3;

    printf("\n--- start doFormatterArray() ---\n\n");

    /*obj1*/PrePostDollarFixer_ctor_cc_cc(&tempObj1, "!!! ", " !!!");
    DefaultTextFormatter_copy_ctor(&obj1, (DefaultTextFormatter*)&tempObj1);
    PrePostDollarFixer_dtor(&tempObj1);

    /*obj2*/DefaultTextFormatter_ctor(&(tempObj2.m_DefaultTextFormatterBase));
    ((TextFormatter*)&tempObj2)->m_vptr = MultiplierVTable;
    tempObj2.m_times = 4;
    printf("--- Multiplier CTOR: times = %d\n", tempObj2.m_times);
    DefaultTextFormatter_copy_ctor(&obj2, (DefaultTextFormatter*)&tempObj2);
    Multiplier_dtor(&tempObj2);

    /*obj3*/PrePostChecker_ctor(&tempObj3);
    DefaultTextFormatter_copy_ctor(&obj3, (DefaultTextFormatter*)&tempObj3);
    PrePostChecker_dtor(&tempObj3);

    formatters[0] = obj1;
    formatters[1] = obj2;
    formatters[2] = obj3;


    for (i = 0; i < 3; ++i)
        DefaultTextFormatter_print(&(formatters[i]), "Hello World!");

    printf("\n--- end doFormatterArray() ---\n\n");

    DefaultTextFormatter_dtor(&obj3);
    DefaultTextFormatter_dtor(&obj2);
    DefaultTextFormatter_dtor(&obj1);

}

void doFormatterPtrs()
{
    int i;
    PrePostDollarFixer* obj1 = (PrePostDollarFixer*)malloc(sizeof(PrePostDollarFixer));
    Multiplier* obj2 = (Multiplier*)malloc(sizeof(Multiplier));
    PrePostChecker* obj3 = (PrePostChecker*)malloc(sizeof(PrePostChecker));
    DefaultTextFormatter* pfmt[3];

    printf("\n--- start doFormatterPtrs() ---\n\n");

    /*obj1*/PrePostDollarFixer_ctor_cc_cc(obj1, "!!! ", " !!!");

    /*obj2*/DefaultTextFormatter_ctor(&(obj2->m_DefaultTextFormatterBase));
    ((TextFormatter*)obj2)->m_vptr = MultiplierVTable;
    obj2->m_times = 4;
    printf("--- Multiplier CTOR: times = %d\n", obj2->m_times);

    /*obj3*/PrePostChecker_ctor(obj3);

    pfmt[0] = (DefaultTextFormatter*)obj1;
    pfmt[1] = (DefaultTextFormatter*)obj2;
    pfmt[2] = (DefaultTextFormatter*)obj3;

    for (i = 0; i < 3; ++i)
        ((funcPtr_pvoid_pchar_R_void) ((((TextFormatter *) (pfmt[i]))->m_vptr)[_Z5printEKPc]))(pfmt[i], "Hello World!");

    for (i = 2; i >= 0; --i){
        ((funcPtr_void_R_void)((((TextFormatter*)(pfmt[i]))->m_vptr)[_Z4DtorEPKs]))(pfmt[i]);
        free(pfmt[i]);
    }

    printf("\n--- end doFormatterPtrs() ---\n\n");
}

void doFormatterDynamicArray()
{
    int i;
    DefaultTextFormatter* formatters;

    printf("\n--- start doFormatterDynamicArray() ---\n\n");

    formatters = generateFormatterArray();
    
    for (i = 0; i < 3; ++i)
        ((funcPtr_pvoid_pchar_R_void) ((((TextFormatter *) (&(formatters[i])))->m_vptr)[_Z5printEKPc]))(&(formatters[i]), "Hello World!");

    for (i = 2; i >= 0; --i){
        DefaultTextFormatter_dtor(&(formatters[i]));
    }
    free(formatters);

    printf("\n--- start doFormatterDynamicArray() ---\n\n");
}


int main()
{
    PrePostHashFixer hfix;
    PrePostDollarFixer temp;
    printf("\n--- Start main() ---\n\n");

    doPrePostFixer();
    doPrePostDollarFixer();
    doPrePostFloatDollarFixer();
    doPrePostChecker();

    PrePostHashFixer_ctor(&hfix, 4);
    runAsPrePostFixerRef((PrePostFixer*)&hfix);
    runAsPrePostDollarFixerRef((PrePostDollarFixer*)&hfix);

    PrePostDollarFixer_copy_ctor(&temp, (PrePostDollarFixer*)&hfix);
    runAsPrePostDollarFixerObj(temp);
    PrePostDollarFixer_dtor(&temp);

    runAsPrePostHashFixerRef((PrePostHashFixer*)&hfix);

    doMultiplier();

    doFormatterArray();
    doFormatterPtrs();
    doFormatterDynamicArray();

    printf("\n--- End main() ---\n\n");
    PrePostHashFixer_dtor(&hfix);
    return 0;
}



