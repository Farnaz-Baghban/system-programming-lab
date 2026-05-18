#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <errno.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_EVENTS 1024
#define BUFFER_SIZE 8192
#define WWW_ROOT "./www"

typedef enum {
    STATE_REQUEST, STATE_HEADERS, STATE_RESPONSE} conn_state;

typedef struct{
    int fd; 
    // every connection in linux has a file
    //1-fd is a number. 2-fd is listed in process table 3-epoll relies on this number(fd) to function
    conn_state state; 
    //state-machine: STATE_REQUEST, STATE_HEADERS, STATE_RESPONSE , this way is another way to manage HTTP  without multithread

    char read_buff[BUFFER_SIZE];
    //we read raw data with this 

    int read_len;
    char write_buf[BUFFER_SIZE];
    //storing the HTTP request in this buffer

    int write_len;

    //-------------------------------------------
    // kernel + sendfile() can send file without copying
    int file_fd;//fd on the disk
    off_t file_offset;// current reading point
    off_t file_size;//file size
    int keep_alive;
    
} connection;
connection *connections[100000];

int set_nonblocking(int fd){
    //fcntl is a multi-purpose POSIX system-call for file descriptors
    int flags = fcntl(fd, F_GETFL,0); //ask kernel what flags doese this fd have(e. O_APPEND, O_CREATE, O_NONBLOCK, O_WRONLY, O_RDONLY)
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK); //we add a flag (NONBLOCK)->means not-blocking I/O on fd 
}

const char *get_mime_type(const char *path){
    // MIME detection based on mime-suffix -- hat is mime?
    const char *ext = strchr(path,"."); //wstrchr->finds the first ccurrence of "." in string(path here)
    if(!ext) return "text/plain";
    if (!strcmp(ext, ".html")) return "text/html";
    if (!strcmp(ext, ".css")) return "text/css";
    if (!strcmp(ext, ".js")) return "application/javascript";
    if (!strcmp(ext, ".png")) return "image/png";
    if (!strcmp(ext, ".jpg")) return "image/jpeg";
    if (!strcmp(ext, ".gif")) return "image/gif";

    return "application/octet-stream";
}
void close_connection(int epfd, connection *conn){
    epoll_ctl(epfd, EPOLL_CTL_DEL, conn->fd, NULL);
    close(conn->fd);
    if(conn->file_fd>0)
        close(conn->file_fd);
    connections[conn->fd]=NULL;
    free(conn);
}

void send_error(connection *conn, int code, const char *msg){
    conn->write_len = sprintf(conn->write_buf, 
    "HTTP/1.1 %d %s \r\n"
    "Content-Length: %ld\r\n"
    "Content-Ttpe: text/plain\r\n"
    "Connection: close\r\n"
    "\r\n"
    "%s",
    code, msg, strlen(msg), msg 
    );
}

int parse_request(connection *conn, char *method, char *path){
    char *line = strtok(conn->read_buff, "\r\n");
    if (!line)
        return -1;
}//this function still doese no real parsing


// ---------------------------------------------
// ---------------------------------------------
// to do next:
// this server has no main loop
// no accept handler
// no epoll event loop
// no request sending
// no complee static file serving
//   ---- summary:
// this project is a skeleton not a real server
// it is written for study purposes only
