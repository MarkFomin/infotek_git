#include "tcp_server.h"

namespace eth {

    bool TCPServer::tcp_server__init(const char *sv_host_, unsigned short sv_port_) {

        sockaddr_in socket_sa;

        socket__ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (socket__ < 0)
        {
            printf("Error");
            return false;
        }

        bzero(&socket_sa, sizeof(socket_sa));

        socket_sa.sin_family = PF_INET;
        socket_sa.sin_port = sv_port_;
        inet_pton(PF_INET, sv_host_, &(socket_sa.sin_addr));


        if(bind(socket__, (struct sockaddr *)(&socket_sa), sizeof(socket_sa)) > 0)
            return true;

        return false;
    }

    void TCPServer::tcp_server__socket_add(fd_set &rd_, fd_set &wr_, int &n_) {

        int rd_sock = 0;
        int wr_sock = 0;

        FD_SET(socket__, &rd_);

        if (socket__ > n_)
            n_ = socket__ + 1;

        for(std::map<Id, SocketInfo>::iterator it = sockets__.begin(); it != sockets__.end(); it++)
        {
            rd_sock = (it->second).socket;

            if (rd_sock > 0)
                FD_SET(rd_sock, &rd_);

            if (rd_sock > n_)
                n_ = rd_sock + 1;
        }

        for(std::map<Id, SocketInfo>::iterator it = sockets__.begin(); it != sockets__.end(); it++)
        {
            wr_sock = (it->second).socket;

            if (wr_sock > 0)
                FD_SET(wr_sock, &wr_);

            if (wr_sock > n_)
                n_ = wr_sock + 1;
        }

    }

    void TCPServer::tcp_server__socket_check (fd_set const &rd_, fd_set const &wr_){

        //SocketInfo new_connect;
        sockaddr_in socket_sa;
        int new_socket = 0;
        int valread = 0;
        std::string read_str;

        if (FD_ISSET(socket__, &rd_))
        {
            if (new_socket = accept(socket__, (struct sockaddr *)(&socket_sa), (socklen_t*)sizeof(socket_sa)) > 0)
            {
                //new_connect(new_socket, socket_sa.sin_addr.s_addr, socket_sa.sin_port);
                //new_connect.socket = new_socket;
                //new_connect.port = socket_sa.sin_port;
                //memcpy(new_connect.ip, inet_ntoa(socket_sa.sin_addr.s_addr), sizeof(inet_ntoa(socket_sa.sin_addr.s_addr)));
                //tmp.socket = new_socket;
                //tmp.port = socket_sa.sin_port;
                //memcpy(tmp.ip, inet_ntoa(socket_sa.sin_addr.s_addr), sizeof(inet_ntoa(socket_sa.sin_addr.s_addr)));

                id__++;
                sockets__.insert(std::pair<Id, SocketInfo>(id__, SocketInfo(new_socket, 0, socket_sa.sin_port)));

                tcp_server__connected(id__, sockets__[id__].ip, sockets__[id__].port);

            }
        }

        for(std::map<Id, SocketInfo>::iterator it = sockets__.begin(); it != sockets__.end();)
        {
            std::map<Id, SocketInfo>::iterator it_tmp = it;

            if (FD_ISSET((it->second).socket, &rd_))
            {
                if (valread = read((it->second).socket, read_str, 1024) == 0)
                {
                    eth::TCPServer::tcp_server__disconnected((it->first));
                    close((it->second).socket);
                    sockets__.erase(it);
                }
                else
                {
                    tcp_server__recv((it->first), read_str, 1024);
                    it++;
                }
            }

            if (it == it_tmp)
                it++;
        }

        for(std::map<Id, SocketInfo>::iterator it = sockets__.begin(); it != sockets__.end(); it++)
        {
            if (FD_ISSET((it->second).socket, &wr_))
            {
                if ((it->second).send_len > 0)
                    send((it->second).socket, (it->second).send_buf, (it->second).send_len, 0);
            }
        }


    }

    void TCPServer::tcp_server__send(TCPServer::Id id_, unsigned char const *v_, size_t &send_){

        memcpy(sockets__[id_].send_buf, v_, send_);

    }


}







