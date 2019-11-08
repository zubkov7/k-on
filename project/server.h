#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>

class Web_server{
	public:
		Web_server(){};
		~Web_server(){};
		void start();
		void restart();
		void stop();
	private:
		string user;
		int pid;
		void read_config();
		void kill-master();
		HTTP_master create_master();
}


Class HTTP_master{
	public:
		HTTP_worker create_worker();
		void clean_worker();
		void kill_worker();
		bool connect(user , worker);
		int num_workers;
		int worker_pid[num_workers];
		~HTTP_master(){};
	private:
		HTTP_master(){};
}

class HTTP_worker{
	public:
		void start_work();
		HTTP_worker(){};
		~HTTP_worker(){};
		status_code status;
		int timeout;
		request request;
	private:
		void socket();
    //accept connect
		void accept();
    //recreate parser and write it in buffer
		void read_request();
    //switch(req.method)
		void process_request();
    //if req is OK
    		void send_file();
    //if bad request
		void send_bad_response();
    //does connection time end
		bool check_deadline();
    //insert dinamic data into html in special places(for example '$$$')
		void insert_dinamic();
}
#endif
