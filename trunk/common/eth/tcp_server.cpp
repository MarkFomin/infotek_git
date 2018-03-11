#include "tcp_server.h"

namespace eth {

    bool TCPServer::tcp_server__init(const char *sv_host_, unsigned short sv_port_) {

        sockaddr_in socket_sa;

        socket__ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        fcntl(socket__, F_SETFL, O_NONBLOCK);

        if (socket__ < 0)
        {
            printf("Error");
            return false;
        }

        bzero(&socket_sa, sizeof(socket_sa));

        socket_sa.sin_family = PF_INET;
        socket_sa.sin_port = htons(sv_port_);
        inet_pton(PF_INET, sv_host_, &(socket_sa.sin_addr));


        if (bind(socket__, (struct sockaddr *)(&socket_sa), sizeof(socket_sa)) == 0)
        {
            if (listen(socket__, 3) < 0)
            {
                return false;
            }
            return true;
        }

        return false;
    }

    void TCPServer::tcp_server__socket_add(fd_set &rd_, fd_set &wr_, int &n_) {

        int rd_sock = 0;
        int wr_sock = 0;

        FD_SET(socket__, &rd_);

        if (socket__ >= n_)
            n_ = socket__ + 1;

        for(std::map<Id, SocketInfo>::iterator it = sockets__.begin(); it != sockets__.end(); it++)
        {
            rd_sock = (it->second).socket;

            if (rd_sock > 0)
                FD_SET(rd_sock, &rd_);

            if (rd_sock >= n_)
                n_ = rd_sock + 1;
        }

        for(std::map<Id, SocketInfo>::iterator it = sockets__.begin(); it != sockets__.end(); it++)
        {
            wr_sock = (it->second).socket;

            if (wr_sock > 0)
                FD_SET(wr_sock, &wr_);

            if (wr_sock >= n_)
                n_ = wr_sock + 1;
        }

    }

    void TCPServer::tcp_server__socket_check (fd_set const &rd_, fd_set const &wr_){

        std::map<Id, SocketInfo>::iterator tmp_it;
        sockaddr_in socket_sa;
        int new_socket = 0;
        int valread = 0;
        int socket_sa_len = 0;

        unsigned char read_str_char[1024] = {'\0'};
        std::string read_str;
        std::string ip_str;

        bzero(&socket_sa, sizeof(socket_sa));
        socket_sa_len = sizeof(socket_sa);

        if (FD_ISSET(socket__, &rd_))
        {
            new_socket = accept(socket__, (struct sockaddr *)(&socket_sa), (socklen_t*)&socket_sa_len);

            if (new_socket >= 0)
            {

                id__++;

                sockets__.insert(std::pair<Id, SocketInfo>(id__, SocketInfo(new_socket, inet_ntoa(socket_sa.sin_addr), ntohs(socket_sa.sin_port))));

                tmp_it = sockets__.find(id__);

                tcp_server__connected(id__, (tmp_it->second).ip.c_str(), (tmp_it->second).port);

                send(new_socket, "Hello", 6, 0);
            }
        }

        for(std::map<Id, SocketInfo>::iterator it = sockets__.begin(); it != sockets__.end(); it++)
        {
            //std::map<Id, SocketInfo>::iterator it_tmp = it;

            if (FD_ISSET((it->second).socket, &rd_))
            {

                if (((valread = read((it->second).socket, read_str_char, 1024)) <= 0))
                {
                    tcp_server__disconnected((it->first));
                    close((it->second).socket);
                    sockets__.erase(it);
                }
                else
                {
                    tcp_server__recv((it->first), read_str_char, 1024);
                    it++;
                }
            }

            if(it == sockets__.end())
                break;
        }

        for(std::map<Id, SocketInfo>::iterator it = sockets__.begin(); it != sockets__.end(); it++)
        {
            if (FD_ISSET((it->second).socket, &wr_))
            {
                if ((it->second).send_len > 0)
                {
                    send((it->second).socket, (it->second).send_buf, (it->second).send_len, 0);
                    (it->second).send_len = 0;
                }

            }
        }


    }

    void TCPServer::tcp_server__send(TCPServer::Id id_, unsigned char const *v_, size_t &send_){

        std::map<Id, SocketInfo>::iterator tmp_it;

        tmp_it = sockets__.find(id_);

        memcpy((tmp_it->second).send_buf, v_, send_);

        (tmp_it->second).send_len = send_;

    }


}







