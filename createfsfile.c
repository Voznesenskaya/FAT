#include "fsfileops.h"
#include <string.h>

long Create()
{
    long i;

    FILE *file;
    if((file=fopen(fsfilename,"wb"))==0)
    {
        puts ("Can't open output file.");
        return -1;
    }

    long free_cluster_count = CLUSTER_COUNT_FAT;
    long free_cluster = 0;

    fwrite(&free_cluster_count, sizeof(free_cluster_count), 1, file);
    fwrite(&free_cluster, sizeof(free_cluster), 1, file);

    // Заполняем таблицу fat
    WriteValueFat(0, NOT_USED);
    for (i=1; i<CLUSTER_COUNT_FAT; i++)
    {
        WriteValueFat(i, NOT_USED);
    }

    printf("Fat is created \n");
    fclose(file);
    return 0;
}

void PrintFileSystemInfo()
{
    printf("========================\n");
    printf("File system info:\n");
    printf("free_cluster_count = %ld\n", ReadFreeClusterCount());
    printf("cluster_count = %d\n", CLUSTER_COUNT_FAT);
    printf("cluster_size = %d\n", CLUSTER_SIZE);
    printf("========================\n");
}

long CreateRootCatalog()
{
    struct File_Record mas[ELEMENT_COUNT_IN_CATALOG];
    memset(mas, 0, sizeof(mas));

    struct File_Record temp;
    temp.first_cluster = FindFreeCluster();

    printf("first cluster catalog %ld \n", temp.first_cluster);
    WriteFile(mas, sizeof(struct File_Record)*ELEMENT_COUNT_IN_CATALOG, &temp, 0);
    return 0;
}

void PrintRootCatalog(const char *path)
{
    long i;
    long index = GetNumberFirstClusterByPath(path);
    printf ("index %ld\n", index);

    struct File_Record temporary_catalog[ELEMENT_COUNT_IN_CATALOG];
    if(ReadCatalog(temporary_catalog, index) < 0)
        return;

    for (i=0; i<ELEMENT_COUNT_IN_CATALOG; i++)
    {
        printf("File Record in Catalog %ld\n", i);
        printf("name: %s \n", temporary_catalog[i].name);
        printf("first %ld\n", temporary_catalog[i].first_cluster);
        printf("size %ld\n", temporary_catalog[i].size);
        printf("mode %d\n", temporary_catalog[i].mode);
        printf("gen %ld\n", temporary_catalog[i].gen);
    }
}

int main(int argc, char *argv[])
{
    fsfilename = FILE_PATH;
    Create();
    CreateRootCatalog();
    PrintRootCatalog("/");
    PrintFileSystemInfo();
}
