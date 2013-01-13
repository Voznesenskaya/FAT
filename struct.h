#define CLUSTER_SIZE 8192 //байты
#define ELEMENT_COUNT_IN_CATALOG 256
#define CLUSTER_COUNT_FAT 1048576
#define FAT_SIZE 4194304
#define EOC 0x0FFFFFFF //конец цепочки кластеров
#define NOT_USED 0 //кластер свободен

struct File_Record
{
    char name[256]; //название 256
    long first_cluster; //первый кластер 4
    long size;//размер в байтах 4
    ushort mode;//режим и тип файла 2
    time_t ctime;//дата создания 4
    time_t mtime;//дата последнего изменения 4
    time_t atime;//дата последнего доступа 4
    ushort uid;//user id 2
    ushort gid;//group id 2
    long gen;//file generation number 4
};//288


