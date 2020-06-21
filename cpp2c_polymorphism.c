#include "cpp2c_polymorphism_defs.h"




void doPrePostFixer()
{
    PrePostFixer angleBrackets;
    printf("\n--- start doPrePostFixer() ---\n\n");

    PrePostFixer_ctor(&angleBrackets, "<<< ", " >>>", PrePostFixerVTable);
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

    PrePostDollarFixer_ctor_cc_cc(&asterisks, "***** ", " *****", PrePostDollarFixerVTable);
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

    PrePostChecker_ctor(&check, PrePostCheckerVTable);

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

    PrePostFloatDollarFixer_ctor(&hashes, "### ", " ###", PrePostFloatDollarFixerVTable);
    PrePostFloatDollarFixer_print_f(&hashes, -777);
    PrePostFloatDollarFixer_print_f_c(&hashes, 350, '#');
    PrePostFloatDollarFixer_print_f(&hashes, 3.14f);


    PrePostDollarFixer_copy_ctor(&hashes2, (PrePostDollarFixer*)(&hashes), PrePostDollarFixerVTable);
    PrePostDollarFixer_print_d_c(&hashes2, 7.5, PrePostDollarFixer_DEFAULT_SYMBOL);
    PrePostDollarFixer_print_i_c(&hashes2, 100, PrePostDollarFixer_DEFAULT_SYMBOL);

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");
    PrePostFloatDollarFixer_dtor(&hashes);
    PrePostDollarFixer_dtor(&hashes2);
}

void runAsPrePostFixerRef(const PrePostFixer* const pp)
{
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");

    ((funcPtr_pvoid_long_char)((((TextFormatter*)pp)->m_vptr)[_Z5printElc]))(pp, 123, '\0');

    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}
/*
void runAsPrePostDollarFixerRef(const PrePostDollarFixer& pp)
{
    printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");

    pp.print(123);

    printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerObj(const PrePostDollarFixer pp)
{
    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");

    pp.print(123);

    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");
}

void runAsPrePostHashFixerRef(const PrePostHashFixer& pp)
{
    printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");

    pp.print(123);

    printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}

void doMultiplier()
{
    printf("\n--- start doMultiplier() ---\n\n");

    Multiplier m1(3);
    Multiplier m2 = 5;
    Multiplier m3 = m1;
    Multiplier m4(m2);

    m1.print("abc ");
    m2.print("abc ");
    m3.print("abc ");
    m4.print("abc ");

    printf("\n--- start doMultiplier() ---\n\n");
}

void doFormatterArray()
{
    printf("\n--- start doFormatterArray() ---\n\n");

    DefaultTextFormatter formatters[] =
    {
        PrePostDollarFixer("!!! ", " !!!"),
        Multiplier(4),
        PrePostChecker()
    };

    for (int i = 0; i < 3; ++i)
        formatters[i].print("Hello World!");

    printf("\n--- end doFormatterArray() ---\n\n");
}

void doFormatterPtrs()
{
    printf("\n--- start doFormatterPtrs() ---\n\n");

    DefaultTextFormatter* pfmt[] =
    {
        new PrePostDollarFixer("!!! ", " !!!"),
        new Multiplier(4),
        new PrePostChecker()
    };

    for (int i = 0; i < 3; ++i)
        pfmt[i]->print("Hello World!");

    for (int i = 2; i >= 0; --i)
        delete pfmt[i];

    printf("\n--- end doFormatterPtrs() ---\n\n");
}

void doFormatterDynamicArray()
{
    printf("\n--- start doFormatterDynamicArray() ---\n\n");

    DefaultTextFormatter* formatters = generateFormatterArray();
    
    for (int i = 0; i < 3; ++i)
        formatters[i].print("Hello World!");

    delete[] formatters;

    printf("\n--- start doFormatterDynamicArray() ---\n\n");
}
 */

int main()
{
    PrePostHashFixer hfix;
    printf("\n--- Start main() ---\n\n");

    doPrePostFixer();
    doPrePostDollarFixer();
    doPrePostFloatDollarFixer();
    doPrePostChecker();

    PrePostHashFixer_ctor(&hfix, 4, PrePostHashFixerVTable);
    runAsPrePostFixerRef((PrePostFixer*)&hfix);
   /* runAsPrePostDollarFixerRef(hfix);
    runAsPrePostDollarFixerObj(hfix);
    runAsPrePostHashFixerRef(hfix);

    doMultiplier();

    doFormatterArray();
    doFormatterPtrs();
    doFormatterDynamicArray();*/

    printf("\n--- End main() ---\n\n");
    PrePostHashFixer_dtor(&hfix);
    return 0;
}



