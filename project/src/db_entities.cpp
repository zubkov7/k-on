#include "db_entities.h"


bool User::operator==(const User &user) const {
    return id == user.id && login == user.login && password == user.password;
}

bool Song::operator==(const Song &song) const {
    return id == song.id && name == song.name && author == song.author && genre == song.genre &&
           duration == song.duration && date == song.date;
}

bool LikeDislike::operator==(const LikeDislike &like_dislike) const {
    return id == like_dislike.id && user_id == like_dislike.user_id && song_id == like_dislike.song_id &&
           value == like_dislike.value;
}

bool Listen::operator==(const Listen &listen) const {
    return id == listen.id && user_id == listen.user_id && song_id == listen.song_id && count == listen.count;
}
