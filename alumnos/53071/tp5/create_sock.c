#include "http_h.h"

int create_sock(int puerto){
    int sd;
    int *sdc;
    int sd_conn;
		int val=1;
		socklen_t largo = sizeof(struct sockaddr *);
    		struct sockaddr_in server_dir;


                sd = socket(AF_INET, SOCK_STREAM,0); //creo el socket
                if (sd<0){
                    perror("socket()");
                    return -1;
                }

                pthread_t tid1;
                pthread_attr_t atributo;
                pthread_attr_init(&atributo);
                pthread_attr_setdetachstate(&atributo, PTHREAD_CREATE_DETACHED);

                server_dir.sin_family = AF_INET;//familia de direcciones
                server_dir.sin_port = htons(puerto);//host to network short
                //server_dir.sin_addr =192.168.3.9; el numero tiene qe star en hexa o bin
                server_dir.sin_addr.s_addr = INADDR_ANY; //la utilizo para que cuando cambie de maquina utilice el puerto 5000 y la ip de la maquina 
                //inet_aton( argv[1], &server_dir.sin_addr); 

                setsockopt(sd,SOL_SOCKET, SO_REUSEADDR,(void *)&val,sizeof(val));//funcion para que no quede ocupado el socket al establecer nueva conexion

                if ((bind(sd,(struct sockaddr *)&server_dir,sizeof(server_dir)))<0){
                    perror("bind()");
                    return -1;
                }


                if((listen(sd,10))<0){ //escucha nuevas conexiones, 10 es la cantidad de conexiones a la vez que permite
                    perror("listen()");
                    return -1;
                }

                signal(SIGCHLD,SIG_IGN);//no permite que queden procesos zombies en el sistema


                //while(1){
                while( (sd_conn = accept(sd, (struct sockaddr *) &server_dir, &largo)) > 0){
                    sdc=malloc(sizeof (int));
                    *sdc=sd_conn;
                    //*sdc = accept(sd,(struct sockaddr *)&server_dir,&largo); //acepta conexiones al socket
                    if ((pthread_create(&tid1,&atributo,&http,(void *)sdc))!=0){
                        perror("pthread");
                        return -1;
                    }
                    //usleep(100);
                    // close(sdc);
                }
return 0;
}
