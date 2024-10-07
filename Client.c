#include <sys/types.h>
#include <sys/socket.h>
#include <ErrorHandling.h>


int main(){

    int client = Socket(AF_INET, SOCK_STREAM, 0);

    client = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in client_addr;
    
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(55555);
    Inet_pton(AF_INET, "127.0.0.1", &client_addr.sin_addr);
    Connect(client, (struct sockaddr*) &client_addr, sizeof(client_addr));

    FILE* file = Fopen("/home/f1xdsl/testc/clientfile.txt", "r");
    char buf[256];
    while(fgets(buf, 256, file) != NULL){
        write(client, buf, sizeof(buf));    
    }
    fclose(file);
    close(client);
    return 0;
}