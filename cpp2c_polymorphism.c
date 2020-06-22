#include "cpp2c_polymorphism_defs.h"
#include "stdlib.h"



void doPrePostFixer()
{
    PrePostFixer angleBrackets;
    printf("\n--- start doPrePostFixer() ---\n\n");

    _ZNC12PrePostFixerEPKsKPcKPc(&angleBrackets, "<<< ", " >>>");
    _ZN12PrePostFixer5printEKPKvKPc(&angleBrackets, "Hello World!");

    /*print 1 - ZN12PrePostFixer5printEKPKvlc(&angleBrackets, -777, '\0');*/
    printf("%-60s | ", "[PrePostFixer::print(long, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostFixer::print_num(long)]");
    printf("%s%ld%s\n", ((PrePostFixer*)&angleBrackets)->m_pre, (long)-777, ((PrePostFixer*)&angleBrackets)->m_post);


    /*print 2 - _ZN12PrePostFixer5printEKPKvlc(&angleBrackets, 350, '#');*/
    printf("%-60s | ", "[PrePostFixer::print(long, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostFixer::print_num(long, char)]");
    printf("%s%c%ld%s\n", ((PrePostFixer*)&angleBrackets)->m_pre, '#', (long)350, ((PrePostFixer*)&angleBrackets)->m_post);


    /*print 3 - _ZN12PrePostFixer5printEKPKvlc(&angleBrackets, 3, '\0');*/
    printf("%-60s | ", "[PrePostFixer::print(long, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostFixer::print_num(long)]");
    printf("%s%ld%s\n", ((PrePostFixer*)&angleBrackets)->m_pre, (long)3, ((PrePostFixer*)&angleBrackets)->m_post);


    printf("\n--- end doPrePostFixer() ---\n\n");
    _ZND12PrePostFixerEPKv(&angleBrackets);
}

void doPrePostDollarFixer()
{
    PrePostDollarFixer asterisks;
    printf("\n--- start doPrePostDollarFixer() ---\n\n");

    _ZNC18PrePostDollarFixerEPKsKPcKPc(&asterisks, "***** ", " *****");
    _ZNK18PrePostDollarFixer5printEKPKsic(&asterisks, -777, _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE);
    _ZNK18PrePostDollarFixer5printEKPKsic(&asterisks, 350, '#');
    _ZNK18PrePostDollarFixer5printEKPKsdc(&asterisks, 3.14f, _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE);

    printf("\n--- end doPrePostDollarFixer() ---\n\n");
    _ZND18PrePostDollarFixerEPKv(&asterisks);
}

void doPrePostChecker()
{
    PrePostChecker check;
    printf("\n--- start doPrePostChecker() ---\n\n");

    _ZNC14PrePostCheckerEPKs(&check);

    _ZNK14PrePostChecker24printThisSymbolUsingFuncEKPKs(&check);
    _ZNK14PrePostChecker23printThisSymbolDirectlyEKPKs(&check);
    _ZNK14PrePostChecker31printDollarSymbolByCastDirectlyEKPKs(&check);
    _ZNK14PrePostChecker32printDollarSymbolByScopeDirectlyEKPKs(&check);
    _ZNK14PrePostChecker32printDollarSymbolByCastUsingFuncEKPKs(&check);
    _ZNK14PrePostChecker33printDollarSymbolByScopeUsingFuncEKPKs(&check);

    printf("\n--- end doPrePostChecker() ---\n\n");
    _ZND14PrePostCheckerEPKv(&check);
}

void doPrePostFloatDollarFixer()
{
    PrePostFloatDollarFixer hashes;
    PrePostDollarFixer hashes2;

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    _ZNC23PrePostFloatDollarFixerEPKsKPcKPc(&hashes, "### ", " ###");
    _ZNK23PrePostFloatDollarFixer5printEKPKsf(&hashes, -777);
    _ZNK23PrePostFloatDollarFixer5printEKPKsfc(&hashes, 350, '#');
    _ZNK23PrePostFloatDollarFixer5printEKPKsf(&hashes, 3.14f);


    _ZNC18PrePostDollarFixerEPKsKPK18PrePostDollarFixer(&hashes2, (PrePostDollarFixer *) (&hashes));
    _ZNK18PrePostDollarFixer5printEKPKsdc(&hashes2, 7.5, _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE);
    _ZNK18PrePostDollarFixer5printEKPKsic(&hashes2, 100, _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE);

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");
    _ZND18PrePostDollarFixerEPKv(&hashes2);
    _ZND23PrePostFloatDollarFixerEPKv(&hashes);
}

void runAsPrePostFixerRef(const PrePostFixer* const pp)
{
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");

    ((funcPtr_pvlcRv)((((TextFormatter*)pp)->m_vptr)[_Z5printElc]))(pp, 123, '\0');

    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerRef(const PrePostDollarFixer* const pp)
{
    printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");

    _ZNK18PrePostDollarFixer5printEKPKsic(pp, 123, _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE);

    printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerObj(const PrePostDollarFixer pp)
{
    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");

    _ZNK18PrePostDollarFixer5printEKPKsic(&pp, 123, _ZN18PrePostDollarFixer14DEFAULT_SYMBOLE);

    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");
}


void runAsPrePostHashFixerRef(const PrePostHashFixer* const pp)
{
    printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");

    _ZNK16PrePostHashFixer5printEKPKsic(pp, 123, _ZN16PrePostHashFixer14DEFAULT_SYMBOLE);

    printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}

void doMultiplier()
{
    Multiplier m1, m2, m3, m4;
    printf("\n--- start doMultiplier() ---\n\n");

    /*construct m1*/
    _ZNC20DefaultTextFormatterEPKs(&(m1.m_DefaultTextFormatterBase));
    ((TextFormatter*)&m1)->m_vptr = MultiplierVTable;
    m1.m_times = 3;
    printf("--- Multiplier CTOR: times = %d\n", m1.m_times);

    /*construct m2*/
    _ZNC20DefaultTextFormatterEPKs(&(m2.m_DefaultTextFormatterBase));
    ((TextFormatter*)&m2)->m_vptr = MultiplierVTable;
    m2.m_times = 5;
    printf("--- Multiplier CTOR: times = %d\n", m2.m_times);

    /*construct m3*/
    _ZNC10Multiplier_dtorEPKsKPK10Multiplier(&m3, &m1);

    /*construct m4*/
    _ZNC10Multiplier_dtorEPKsKPK10Multiplier(&m4, &m2);

    _ZNK10Multiplier5printEKPKvKPc(&m1, "abc ");
    _ZNK10Multiplier5printEKPKvKPc(&m2, "abc ");
    _ZNK10Multiplier5printEKPKvKPc(&m3, "abc ");
    _ZNK10Multiplier5printEKPKvKPc(&m4, "abc ");


    printf("\n--- start doMultiplier() ---\n\n");

    /*destructors*/
    printf("--- Multiplier DTOR: times = %d\n", ((Multiplier*)&m4)->m_times);
    ((TextFormatter*)&m4)->m_vptr = DefaultTextFormatterVTable;
    _ZND20DefaultTextFormatterEPKv((DefaultTextFormatter *) &m4);

    printf("--- Multiplier DTOR: times = %d\n", ((Multiplier*)&m3)->m_times);
    ((TextFormatter*)&m3)->m_vptr = DefaultTextFormatterVTable;
    _ZND20DefaultTextFormatterEPKv((DefaultTextFormatter *) &m3);

    printf("--- Multiplier DTOR: times = %d\n", ((Multiplier*)&m2)->m_times);
    ((TextFormatter*)&m2)->m_vptr = DefaultTextFormatterVTable;
    _ZND20DefaultTextFormatterEPKv((DefaultTextFormatter *) &m2);

    printf("--- Multiplier DTOR: times = %d\n", ((Multiplier*)&m1)->m_times);
    ((TextFormatter*)&m1)->m_vptr = DefaultTextFormatterVTable;
    _ZND20DefaultTextFormatterEPKv((DefaultTextFormatter *) &m1);
}

void doFormatterArray()
{
    int i;
    PrePostDollarFixer tempObj1;
    Multiplier tempObj2;
    PrePostChecker tempObj3;
    DefaultTextFormatter formatters[3], obj1, obj2, obj3;

    printf("\n--- start doFormatterArray() ---\n\n");

    /*obj1*/_ZNC18PrePostDollarFixerEPKsKPcKPc(&tempObj1, "!!! ", " !!!");
    _ZNC20DefaultTextFormatterEPKsKPKs(&obj1, (DefaultTextFormatter *) &tempObj1);
    _ZND18PrePostDollarFixerEPKv(&tempObj1);

    /*obj2*/_ZNC20DefaultTextFormatterEPKs(&(tempObj2.m_DefaultTextFormatterBase));
    ((TextFormatter*)&tempObj2)->m_vptr = MultiplierVTable;
    tempObj2.m_times = 4;
    printf("--- Multiplier CTOR: times = %d\n", tempObj2.m_times);
    _ZNC20DefaultTextFormatterEPKsKPKs(&obj2, (DefaultTextFormatter *) &tempObj2);
    /*Dtor*/    printf("--- Multiplier DTOR: times = %d\n", ((Multiplier*)&tempObj2)->m_times);
    ((TextFormatter*)&tempObj2)->m_vptr = DefaultTextFormatterVTable;
    _ZND20DefaultTextFormatterEPKv((DefaultTextFormatter *) &tempObj2);

    /*obj3*/_ZNC14PrePostCheckerEPKs(&tempObj3);
    _ZNC20DefaultTextFormatterEPKsKPKs(&obj3, (DefaultTextFormatter *) &tempObj3);
    _ZND14PrePostCheckerEPKv(&tempObj3);

    formatters[0] = obj1;
    formatters[1] = obj2;
    formatters[2] = obj3;


    for (i = 0; i < 3; ++i)
        _ZN20DefaultTextFormatter5printEKPKvKPc(&(formatters[i]), "Hello World!");

    printf("\n--- end doFormatterArray() ---\n\n");

    _ZND20DefaultTextFormatterEPKv(&obj3);
    _ZND20DefaultTextFormatterEPKv(&obj2);
    _ZND20DefaultTextFormatterEPKv(&obj1);

}

void doFormatterPtrs()
{
    int i;
    PrePostDollarFixer* obj1 = (PrePostDollarFixer*)malloc(sizeof(PrePostDollarFixer));
    Multiplier* obj2 = (Multiplier*)malloc(sizeof(Multiplier));
    PrePostChecker* obj3 = (PrePostChecker*)malloc(sizeof(PrePostChecker));
    DefaultTextFormatter* pfmt[3];

    printf("\n--- start doFormatterPtrs() ---\n\n");

    /*obj1*/_ZNC18PrePostDollarFixerEPKsKPcKPc(obj1, "!!! ", " !!!");

    /*obj2*/_ZNC20DefaultTextFormatterEPKs(&(obj2->m_DefaultTextFormatterBase));
    ((TextFormatter*)obj2)->m_vptr = MultiplierVTable;
    obj2->m_times = 4;
    printf("--- Multiplier CTOR: times = %d\n", obj2->m_times);

    /*obj3*/_ZNC14PrePostCheckerEPKs(obj3);

    pfmt[0] = (DefaultTextFormatter*)obj1;
    pfmt[1] = (DefaultTextFormatter*)obj2;
    pfmt[2] = (DefaultTextFormatter*)obj3;

    for (i = 0; i < 3; ++i)
        ((funcPtr_pvpRv) ((((TextFormatter *) (pfmt[i]))->m_vptr)[_Z5printEKPc]))(pfmt[i], "Hello World!");

    for (i = 2; i >= 0; --i){
        ((funcPtr_pvRv)((((TextFormatter*)(pfmt[i]))->m_vptr)[_Z4DtorEPKs]))(pfmt[i]);
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
        ((funcPtr_pvpRv) ((((TextFormatter *) (&(formatters[i])))->m_vptr)[_Z5printEKPc]))(&(formatters[i]), "Hello World!");

    for (i = 2; i >= 0; --i){
        _ZND20DefaultTextFormatterEPKv(&(formatters[i]));
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

    _ZNC16PrePostHashFixerEPKsi(&hfix, 4);
    runAsPrePostFixerRef((PrePostFixer*)&hfix);
    runAsPrePostDollarFixerRef((PrePostDollarFixer*)&hfix);

    _ZNC18PrePostDollarFixerEPKsKPK18PrePostDollarFixer(&temp, (PrePostDollarFixer *) &hfix);
    runAsPrePostDollarFixerObj(temp);
    _ZND18PrePostDollarFixerEPKv(&temp);

    runAsPrePostHashFixerRef((PrePostHashFixer*)&hfix);

    doMultiplier();

    doFormatterArray();
    doFormatterPtrs();
    doFormatterDynamicArray();

    printf("\n--- End main() ---\n\n");
    _ZND16PrePostHashFixerEPKv(&hfix);
    return 0;
}



