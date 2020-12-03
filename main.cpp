#include <list>
#include <string>
class Move {
   private:
    std::string x;
    std::string y;

   public:
};

class HistoryMove : public Move {
   private:
   public:
};

class ForwardMove : public Move {
};

class Pezzo {
   private:
    enum color { white,
                 black };
    color colore;

   public:
    Pezzo(bool isWhite) : colore(isWhite ? color::white : color::black){};
    virtual Pezzo* clone() const = 0;
    virtual ~Pezzo() {}
    virtual bool operator==(const Pezzo& f) const {
        return typeid(*this) == typeid(f) && colore == f.colore;
    }
    bool isWhite() const { return colore == color::white; };
    bool isBlack() const { return colore == color::black; };
    std::list<ForwardMove*> generateNextMoves() const {
        auto l = new std::list<ForwardMove*>();
        l->push_back();
    }
};

class Board {
   private:
   public:
};

class Game {
   private:
    Board board;
    HistoryMove* History;

   public:
}