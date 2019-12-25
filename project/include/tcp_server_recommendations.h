#ifndef K_ON_TCP_SERVER_RECOMMENDATIONS_H
#define K_ON_TCP_SERVER_RECOMMENDATIONS_H

#include <string>
#include <boost/property_tree/ptree.hpp>

#include "tcp_server.h"
#include "db_recommendation_system.h"


class TcpServerRecommendations : public TcpServer {
public:
    TcpServerRecommendations(unsigned short port, const std::string &database, const std::string &host,
                             const std::string &user, const std::string &password);

private:
    DbRecommendationSystem recommendation_system;

private:
    std::string handle_request(const std::string &request) const override;

    std::string songs_to_answer(const std::vector<Song> &songs) const;

    std::string on_recommendations(const boost::property_tree::ptree &root) const;
    std::string on_top(const boost::property_tree::ptree &root) const;
    std::string on_recent(const boost::property_tree::ptree &root) const;
    std::string on_similar(const boost::property_tree::ptree &root) const;
    std::string on_update(const boost::property_tree::ptree &root) const;
};


#endif  // K_ON_TCP_SERVER_RECOMMENDATIONS_H
