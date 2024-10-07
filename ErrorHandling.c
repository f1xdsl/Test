
#include <ErrorHandling.h>

void handle_error(const char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
};

int Socket(int domain, int type, int protocol){
    int serverSock = socket(domain, type, protocol);
    if(serverSock == -1){
        handle_error("SOCKET ERROR");
    }
    return serverSock;
};

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    if(bind(sockfd, addr, addrlen) == -1){
        handle_error("BINDING ERROR");
    }
};

void Listen(int sockfd, int backlog){
    if(listen(sockfd, 1) == -1){
        handle_error("LISTENING ERROR");
    }
};

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    int clientSock = accept(sockfd,  addr, addrlen);
    
    if(clientSock == -1){
        handle_error("ACCEPTING ERROR");
    }
    return clientSock;
};

ssize_t Read (int fd, void *buf, size_t count){
    ssize_t readRes = read(fd, buf, count);

    if(readRes == -1){
        handle_error("READING ERROR");
    }
    return readRes;
};

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int clientSock = connect(sockfd, addr, addrlen);

    if(clientSock == -1){
        handle_error("CONNECTING ERROR");
    }
    return clientSock;
};

void Inet_pton(int af, const char *src, void *dst){
    int res = inet_pton(af, src, dst);
    
    if(res == 0){
        syslog(LOG_DAEMON, "inet_pton error: src does not  contain  a  character"
        "string  representing  a valid network address in the specified address family");
        exit(EXIT_FAILURE);
    }
    else if(res == -1){
        handle_error("INET_PTON ERROR");
    }
};

FILE *Fopen(const char *pathname, const char *mode){
    FILE* res_file = fopen(pathname, mode);

    if(res_file == NULL){
        handle_error("OPENING FILE ERROR");
    }
    return res_file;
};