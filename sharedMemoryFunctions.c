#include "sharedMemoryFunctions.h"

/*
 shmget() is used to create an shared mempory segment.
 We set permissions to 644, i.e. rw-r--r--.
 Also, SMHKEY is set to IPC_PRIVATE, so that shmget() nessesarily creates
 a new shared memory.
 */
int creatingSHM(size_t size){
 int shmID;
 shmID = shmget(SMHKEY, size, PERMISSIONS);
 if (shmID == -1){
     perror("Shared memory segment could not be created!");
     exit(EXIT_FAILURE);
 }
 return shmID;
}

/*
Once you created a shmID with shmget() you need the OS
to give you the address of the shared memory segment.
Thats what shmat()("shared memory attach") is for.
It returns a (void *) pointer since it is up to us 
to decide what kind of data is stored in the segment.
The second and third arguments of shmat are set to zero
unless you want to do some fancy stuff.
*/
void *attachingSHM( int shmID){
    char *shmAdress;
    shmAdress = shmat(shmID, (void*) 0, 0);
    if (shmAdress == (char *) (-1)){
        perror("Error trying to attach shared memory segment!");
        exit(EXIT_FAILURE);
    }
 return shmAdress;
}
/*
delete the SHM with shmctl(): the IPC_RMID flag makes sure that the segment is destroyed
only after all processes detached from it. 
The third argument is complicated, so we set it to NULL.
*/
int deletingSHM (int shmID){
    int res;
    res = shmctl(shmID, IPC_RMID, NULL);
    if (res != 0){
        perror("Could not delete Shared Memory segment!");
        exit (EXIT_FAILURE);
    }
    return res;
}


void detachingSHM (void *shmAdress){
    if ((shmdt(shmAdress)) == -1){
        perror("Could not detach from shared memory segment!");
        exit (EXIT_FAILURE);
    }
}