#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <ErrorHandling.h>

int server;
int client;
FILE* file;

void signalHandler(int signum){
    syslog(LOG_DAEMON, "SIG RECEIVED");

    if(server)
        close(server);
    if(client)
        close(client);
    if(file)
        fclose(file);
    
    exit(0);
}

int main(int argc, char* argv[]){
    openlog("ServerDaemon", LOG_PID, LOG_DAEMON);
    openlog("ServerDaemon", LOG_PID, LOG_ERR);
    signal(SIGTERM, signalHandler);
    signal(SIGHUP, signalHandler);

    server = Socket(AF_INET, SOCK_STREAM, 0);
    

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(55555);

    Bind(server, (struct sockaddr*) &server_addr, sizeof(server_addr));

    Listen(server, 1);
    syslog(LOG_DAEMON, "Listening...");

    
    struct sockaddr_in client_addr;
    socklen_t clien_addr_len = sizeof(client_addr);

    file = Fopen("/home/f1xdsl/testc/serverfile.txt", "w+");
    while(1){
        client = Accept(server, (struct sockaddr*) &client_addr, &clien_addr_len);

        syslog(LOG_DAEMON, "Accepted.");

        ssize_t nread;
        char buf[256];
        while(nread = Read(client, buf, 256) > 0){
            syslog(LOG_DAEMON, "Writing...");
            fputs(buf, file);
        }
        syslog(LOG_DAEMON, "Writed.");
    }
    
    closelog();
    return 0;
}
