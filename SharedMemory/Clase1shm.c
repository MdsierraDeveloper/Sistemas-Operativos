

shm_id = shmget(IPC_PRIVATE, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

IPC_CREAT-> Si no existe creelo
S_IRUSR -> de permisos de lectura
S_IWUSR -> De permisos de escritura

ptr = (int*)shmat(shm_id, 0,0);
*ptr = 0;
Se convierte en una variable local

shmdt(ptr); se desacopla

HIGH PERFORMANCE COMPUTING

congruenciales multiplicativos pseudoaleatoriedad

El segmento se vuelve concurrente y por eso saca el mismo resultado muchas veces.
