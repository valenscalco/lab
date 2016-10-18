#include "http_h.h"

char *types(char *mime){

    char *extension=malloc(256*sizeof(char));
    memset(extension,0,256*(sizeof (char)));

    if (strcmp(extension,"html") == 0){
        strncpy(mime,"text/html",256);
    }

    if (strcmp(extension,"jpg") == 0){
        strncpy(mime,"image/jpeg",256);
    }

    if (strcmp(extension,"pdf") == 0){
        strncpy(mime,"application/pdf",256);
    }

    if (strcmp(extension,"txt") == 0){
        strncpy(mime,"text/plain",256);
    }

    if (strcmp(extension,"png") == 0){
        strncpy(mime,"image/png",256);
    }

    if (strcmp(extension,"mp3") == 0){
        strncpy(mime,"audio/mpeg",256);
    }

    if (strcmp(extension,"mp4") == 0){
        strncpy(mime,"video/mp4",256);
    }

    if (strcmp(extension,"gif") == 0){
        strncpy(mime,"image/gif",256);
    }

    if (strcmp(extension,"json") == 0){
        strncpy(mime,"application/json",256);
    }

    if (strcmp(extension,"error") == 0){
        strncpy(mime,"error",256);
    } 


    //printf("extension==%s\n\n",extension);
    //printf("mime==%s\n\n",mime);
    return mime;
}
