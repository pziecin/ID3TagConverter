#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ID3Tag
{
    char tag[4];
    char title[31];
    char artist[31];
    char album[31];
    char year[5];
    char comment[31];
    char genre[2];
} ID3Tag;

void czytaj_tagi(FILE * f, ID3Tag tags)
{
    fread (tags.tag, 1, 3, f);
    fread (tags.title, 1, 30, f);
    fread (tags.artist, 1, 30, f);
    fread (tags.album, 1, 30, f);
    fread (tags.year, 1, 4, f);
    fread (tags.comment, 1, 30, f);
    fread (tags.genre, 1, 1, f);
}

void nadpisz_tagi(FILE * f, ID3Tag tags)
{
    fwrite (tags.tag, 1, 3, f);
    fwrite (tags.title, 1, 30, f);
    fwrite (tags.artist, 1, 30, f);
    fwrite (tags.album, 1, 30, f);
    fwrite (tags.year, 1, 4, f);
    fwrite (tags.comment, 1, 30, f);
    fwrite (tags.genre, 1, 1, f);
}

void wypisz_tagi(FILE * f, ID3Tag tags)
{
    fprintf (stdout, "%s\n", tags.tag);
    printf("Tytul utworu: ");
    fprintf (stdout, "%s\n", tags.title);
    printf("Wykonawca: ");
    fprintf (stdout, "%s\n", tags.artist);
    printf("Album: ");
    fprintf (stdout, "%s\n", tags.album);
    printf("Rok: ");
    fprintf (stdout, "%s\n", tags.year);
    printf("Komentarz: ");
    fprintf (stdout, "%s\n", tags.comment);
    printf("Rodzaj: ");
    fprintf (stdout, "%d\n", tags.genre[0]);
}

int main()
{
    ID3Tag tags;
    FILE * f;
    char sciezka[80];
    int numer;

    printf("Witaj w programie do edycji tagow ID3!\nPodaj sciezke mp3.\n");

    scanf ("%s", sciezka);
    fflush(stdin);
    f = fopen (sciezka, "r+");

    if (f == NULL)
    {
        printf ("Nie moge otworzyc pliku\n");
        return 2;
    }

            fseek (f, -128, SEEK_END);

            czytaj_tagi(f, tags);

            fseek (f, -128, SEEK_END);

            strcpy(tags.tag, "TAG");
            printf("Tytul utworu:");
            scanf("%[^\n]s", tags.title);       //fgets(tags.title, 31, stdin);
            fflush(stdin);

            printf("Wykonawca:");
            scanf("%[^\n]s", tags.artist);
            fflush(stdin);

            printf("Album:");
            scanf("%[^\n]s", tags.album);
            fflush(stdin);

            printf("Rok:");
            scanf("%[^\n]s", tags.year);
            fflush(stdin);

            printf("Komentarz:");
            scanf("%[^\n]s", tags.comment);
            fflush(stdin);

            printf("Rodzaj:");
            scanf("%[^\n]s", tags.genre);
            fflush(stdin);

            nadpisz_tagi(f, tags);

            fclose (f);

            wypisz_tagi(f,tags);
   return 0;
}
