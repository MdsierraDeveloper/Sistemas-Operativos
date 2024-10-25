#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/*
gcc Prueba2.c -o prueba2
./prueba2 "Hola"
*/
void print_tree(){
	char cmd[500] = {""};
	sprintf(cmd, "pstree -lp %d", getpid());					 	
	system(cmd);
}

int main(int argc, char **argv){
	char *buffer;
	buffer = argv[1];


	//pipes[8][2] tambien se puede!!
	int fds[8][2];
	for(int i = 0; i<8; i++ )
	{
		if(pipe(fds[i]) == -1)
		{
			printf("Error tuberia creation");
			exit(1);
		}
	}
	
	


	printf("-> %s\n",buffer);	
	
	close(fds[0][0]);//cierro lectura dejo abierto escritura
	close(fds[3][1]);//cierro escritura, espero lectura
	close(fds[4][0]);
	close(fds[7][1]);
	
	//cerramos todas las demás
	for(int j =0; j < 8; j++){
		if(j != 0 || j != 3 || j != 4 || j != 7){
			close(fds[j][0]);
			close(fds[j][1]);
		}
	}
	
	write(fds[0][1], &buffer, sizeof(buffer));
	close(fds[0][1]);
	
	
	read(fds[3][0], buffer, sizeof(buffer));
	close(fds[3][0]);
	printf("-> %s\n",buffer);
	
	write(fds[4][1], &buffer, sizeof(buffer));
	close(fds[4][1]);
	
	read(fds[7][1], buffer, sizeof(buffer));
	close(fds[7][1]);
	printf("-> %s\n",buffer);
		
	
	for(int i=0; i<2; i++)
	{
		if(!fork())
		{
			switch(i){
			//escritura 1
			//lectura 0
				case 0: 
					//cierro escritura, espero lectura
					close(fds[0][1]); 
					close(fds[2][1]);
					
					//cierro lectura, espero escritura
					close(fds[1][0]);
					close(fds[3][0]);
					
					//cerramos automaticamente las demás
					for(int j =0; j < 8; j++){
							if(j>3){
								close(fds[j][0]);
								close(fds[j][1]);
							}
						}
					
					read(fds[0][0], buffer, sizeof(buffer));
					close(fds[0][0]);
					printf("-> %s\n",buffer);
					
					write(fds[1][1], &buffer, sizeof(buffer));
					close(fds[1][1]);
					
					read(fds[2][0], buffer, sizeof(buffer));
					close(fds[2][0]);
					printf("-> %s\n",buffer);
					
					write(fds[3][1], &buffer, sizeof(buffer));
					close(fds[3][1]);
					
					//hijo 1.1
					if(!fork()){
						close(fds[1][0]);//cerramos manualmente 
						close(fds[2][1]);
						//cerramos todas las demás
						for(int j =0; j < 8; j++){
							if(j != 1 || j != 2){
								close(fds[j][0]);
								close(fds[j][1]);
							}
						}
						
						read(fds[1][0], buffer, sizeof(buffer));
						close(fds[1][0]);
						printf("-> %s\n",buffer);
						
						write(fds[2][1], &buffer, sizeof(buffer));
						close(fds[2][1]);
					
					
			
						exit(1);
					}
					
					
			
					exit(1);
					
				case 1:
					//cierro escritura, espero lectura
					close(fds[4][1]); 
					close(fds[6][1]);
					
					//cierro lectura, espero escritura
					close(fds[5][0]);
					close(fds[7][0]);
					
					//cerramos automaticamente las demás
					for(int j =0; j < 8; j++){
							if(j<4){
								close(fds[j][0]);
								close(fds[j][1]);
							}
						}
				

						
					read(fds[4][0], buffer, sizeof(buffer));	
					close(fds[4][0]);				
					printf("-> %s\n",buffer);
					
					write(fds[5][1], &buffer, sizeof(buffer));
					close(fds[5][1]);
					
					read(fds[6][0], buffer, sizeof(buffer));
					close(fds[6][0]);
					printf("-> %s\n",buffer);
					
					write(fds[7][1], &buffer, sizeof(buffer));
					close(fds[7][1]);
											
					//hijo 2.1
					if(!fork()){
					//escritura 1
					//lectura 0
						close(fds[5][1]);
						close(fds[6][0]);
						
						for(int j =0; j < 8; j++){
							if(j != 5 || j != 6){
								close(fds[j][0]);
								close(fds[j][1]);
							}
						}
						
						read(fds[5][0], buffer, sizeof(buffer));
						close(fds[5][0]);
						printf("-> %s\n",buffer);
						
						write(fds[6][1], &buffer, sizeof(buffer));
						close(fds[6][1]);
						

						exit(1);
					}
					
					
					

					exit(1);
			
			}
		}	
	}
	
	print_tree();
	return EXIT_SUCCESS;
}
