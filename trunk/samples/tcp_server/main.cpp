#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../../common/eth/tcp_server.h"
#include <string>
#include <map>

#define DEFAULT_TEST_SERVER_TCP_PORT 5972

bool work=true;


class TestServer: private eth::TCPServer {
  
public:
  TestServer(char const *sv_ip_, unsigned short sv_port_):srv_ip__(sv_ip_), srv_port__(sv_port_) {};
  ~TestServer(){};
  
  // Инициализация объекта
  bool init(){
    return tcp_server__init(srv_ip__.c_str(), srv_port__);
  }
  
  // Добавить сокеты "на прослушку" (для коннекшенов по умолчанию ожидается только чтение)
  void socket_add(fd_set &rd_, fd_set &wr_, int &n_) {
    tcp_server__socket_add(rd_, wr_, n_);
  }
  
  // Проверить события на сокете
  void socket_check (fd_set const &rd_, fd_set const &wr_){
    tcp_server__socket_check(rd_, wr_);
  }
  
  void send(TCPServer::Id id_, unsigned char const *v_, size_t &send_){
    tcp_server__send(id_, v_, send_);
  }
private:
  
  std::string    srv_ip__;
  unsigned short srv_port__;
  
  // Получение данных
  virtual void tcp_server__recv(TCPServer::Id id_, unsigned char const *buf_, size_t len_){
    
    std::string buf((char const *)buf_, len_);
    
    printf("tcp_server__recv(%zd):%s", len_, buf.c_str());
    
    
    //Для теста отправим то что пришло от клиета обратно...
    
    send(id_, buf_, len_);
  };
  
  // Оповещение о наличии соединения
  virtual void tcp_server__connected(TCPServer::Id id_, char const *cl_ip_, unsigned short cl_port_){
    
    printf("tcp_server__connected(%zd) %s:%d\n", id_, cl_ip_, cl_port_);
    
    std::string str = "Test TCP server:\n";
    size_t try_send = str.length();
    send(id_, (unsigned char const *)str.c_str(), try_send);
  };
  
  // Оповещение о разрыве соединения
  virtual void tcp_server__disconnected(Id id_){
    
    printf("tcp_server__disconnected(%zd)\n", id_);
  };
  
};

int main(){
  
  
  TestServer tcp_serv("127.0.0.1", DEFAULT_TEST_SERVER_TCP_PORT);
  
  if (tcp_serv.init()==false) {
    printf("TestServer init error\n");
    return 1;
  }
  
  printf("Start TCP TestServer\n");
  
  fd_set  fds_rd, fds_wr;
  timeval tv;
  int     n;
  int     retcode = 0;
  
  while (work) {
    
    FD_ZERO(&fds_rd);
    FD_ZERO(&fds_wr);
    n=0;
    
    tcp_serv.socket_add(fds_rd, fds_wr, n);
    
    tv.tv_sec=1;
    tv.tv_usec=0;
    switch (select(n, &fds_rd, &fds_wr, NULL, &tv)) {
      
      case -1:
        if(work==false) break;
        if (errno==EINTR) {
          if (work==true) {
            printf("\nWARNING: main(): select(): %s\n", strerror(errno));
          }
          retcode=1;
        }
        printf("ERROR: main(): select(): %s\n", strerror(errno));
        work=false;
        break;
        
      case 0:
        break;
        
      default:
        
        tcp_serv.socket_check(fds_rd, fds_wr);

        
        break;
        
    }
    
  }
  
  
  return retcode;
}
