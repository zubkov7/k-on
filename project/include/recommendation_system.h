#ifndef PROJECT_INCLUDE_RECOMMENDATION_SYSTEM_H_
#define PROJECT_INCLUDE_RECOMMENDATION_SYSTEM_H_

class RecommendationSystem() {
public:
    RecommendationSystem();
    ~RecommendationSystem();

    void get_recommendation();      // вычисляет рекомендации для пользователей
    void update_recommendation();   // меняет рекомендации в соответствии с изменением, например, поставленным
                                    // лайком
    void get_popular();             // вычисляет список популярных в мире аудиозаписей
    void get_similar();             // вычисляет список аудиозаписей, похожих на данную
    void get_new();                 // вычисляет список новинок
private:
    // методы алгоритмов
};

#endif  // PROJECT_INCLUDE_RECOMMENDATION_SYSTEM_H_
