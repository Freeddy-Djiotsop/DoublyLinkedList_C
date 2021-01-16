#include <stdio.h>
#include <stdlib.h>

typedef int L_datentyp;

typedef struct l_knoten
{
    L_datentyp zahl;
    struct l_knoten *previous;
    struct l_knoten *next;

}L_knoten;

typedef struct liste
{
    L_knoten *anf;
    L_knoten *pos;
    L_knoten *pos_vorg;
}Liste;

void L_create(Liste *l)
{
    l->anf=NULL;
    l->pos=NULL;
    l->pos_vorg=NULL;
}

int l_empty(Liste *l){return l->anf==NULL;}

void l_read(L_datentyp *zahl)
{
    printf("Ganze Zahl eingeben:\t");
    scanf("%d", zahl);
    getchar();
}

void l_insert(L_datentyp *zahl, Liste *l)
{
    l_read(zahl);
    if(!*zahl)//Wenn eine 0 eingegeben wurde, dann nicht einfügen
        return;
    L_knoten *neu=NULL;

    if( (neu=(L_knoten*)malloc(sizeof(L_knoten))) == NULL)
    {
        printf("Kein Speicherplatz mehr\n");
        return EXIT_FAILURE;
    }

    neu->zahl = *zahl;
    neu->next = l->pos;
    neu->previous = l->pos_vorg;

    if(l->pos !=NULL)//Falls pos durch Operationen nicht mehr am Ende zeigt, Die Operationen helfen an beliebige Stelle der Liste einzufügen
        l->pos->previous=neu;

    if(l->pos_vorg !=NULL)//wird ausgefuehrt ab dem zweiten Element
        l->pos_vorg->next=neu;

    if(l->anf==l->pos)//Da ich immer vor pos einfügen, setze anf erneut falls ein Element eingefuegt ist wenn pos gerade an anfang der list steht
        l->anf = neu;

    l->pos_vorg = neu;//weil ich immer vor pos einfuege

    //In dieser Umsetzung zeigt pos ohne Operation wie l_reset immer am Ende der Liste, also auf Null
    //pos_vorg auf dem letzten Element bzw. vor pos
    //der neue Element wird immer vor pos eingefügt
    //und danach mit dem an der Liste angehaengt mit
    //und am Ende pos_vorg zeigt auf ihm
}

void l_reset(Liste *l)
{
    l->pos=l->anf;
    l->pos_vorg=l->anf->previous;//oder NULL
}

void l_advance(Liste *l)
{
    if(l->anf==l->pos)
        l->pos=l->pos->next;
    else if(l->pos==NULL)
    {
        printf("Unmoeglich, da wir schon nicht mehr auf der Liste zeigen\nReset wird empholen!!\n");
        return;
    }
    else
    {
        l->pos_vorg=l->pos;
        l->pos=l->pos->next;
    }
}

void l_regress(Liste *l)
{
    if(l->pos==NULL&&l->anf==l->pos_vorg)//Falls nur ein Datum gespeichert ist und man ruf l_regress auf
    {
        printf("Unmoeglich, da wir nicht mehr auf der Liste zeigen\nReset wird empholen!!\n");
        return;
    }
    else if(l->pos_vorg==l->anf)//Nur ein Datum gespeichert
        l->pos=l->pos_vorg;
    else
    {
        l->pos=l->pos_vorg;
        l->pos_vorg=l->pos_vorg->previous;
    }

}

void l_summe(L_datentyp *zahl, Liste *l)
{
        l_reset(l);
        do
        {
            *zahl +=l->pos->zahl;
            l_advance(l);

        }while(l->pos!=NULL);

    printf("Die Summe ist:%10d\n", *zahl);
}

void l_in_umgekehrt_und_in_urspruenglich(Liste *l)
{
    printf("Zahlen in umgekehrter Reihenfolge :\n");

    if(l->pos_vorg==l->anf)//Wenn nur ein Datum gespeicheert ist
    {
        printf("%5d", l->anf->zahl);
    }
    else
    do
    {
        l_regress(l);
        printf("%5d", l->pos->zahl);

    }while(l->anf!=l->pos);

    printf("\nZahlen in urspruenglicher Reihenfolge :\n");
    if(l->pos_vorg==l->anf&&l->anf!=l->pos)//Wenn nur ein Datum gespeicheert ist
    //l->anf!=l->pos besagt dass die Zahlen in umgekehrter Reihenfolge ausgegeben wurde
    //Also wenn l->anf!=l->pos nicht stimmt fuehre ich while-Schleife aus
    {
        printf("%5d", l->anf->zahl);
    }
    else
    while(l->pos!=NULL)
    {
        printf("%5d", l->pos->zahl);
        l_advance(l);
    }

}

int main()
{
    Liste l;
    L_datentyp zahl=2, summe=0;

    printf("Zahlen eigeben und mit 0 beenden\n\n");

    L_create(&l);
    do
    {
        l_insert(&zahl,&l);
    }while(zahl);

    if(l_empty(&l))
        return 0;
    l_summe(&summe, &l);
    l_in_umgekehrt_und_in_urspruenglich(&l);

    return EXIT_SUCCESS;
}
