//#include "preda.hpp"


//Preda::Preda(const Vect2D& position, const std::string& name) : CartesianObject2D(position), Fish(name), _daycycle(25*30, 25*5), _stamina(8){}

////Vect2D Preda::behaviour(Aquarius *a, Vect2D acc){
////    _daycycle++; //increase progress
////    std::cout<<_daycycle.getProgress()<<std::endl;
////    if(isAwake()){ //se è sveglio
////        _stamina-=1/50.0; //consumo energia

////        if(_stamina <= 0) {setIsGone();} //starved to death
////        std::cout<<_stamina.getVal()<<std::endl;

////        if(canSleep()){ //ha finito la sua giornata
////            std::cout<<"DORMI"<<std::endl;
////            _daycycle.setProgress(0);
////            sleep(); //vai a dormire
////            return Vect2D();  // turno finito
////        }

////        }else if(canWakeup()){ //Sta dormendo e ha dormito abbastanza
////            _daycycle.setProgress(0);
////            wakeup(); //svegliati
////        }else if(!canWakeup()) return Vect2D(); //dorme ed è notte

////        //è giorno ed è sveglio

////        auto fish = a->getAllFish();

//////        Vect2D alignement;
//////        Vect2D separation;
//////        Vect2D cohesion;
////        int count = 0;
////        for (auto& f : fish) {
////            //Deve scappare? Se no facciamo che è un pesce stupido e se ne frega, quindi va direttamente a Fish::behaviour per mangiare
////        }

////        return Fish::behaviour(a, acc);
////}

//bool Preda::isHungry() const{
//    return _stamina < 2;
//}

//bool Preda::canSleep() const{ return _daycycle.getProgress() >= _daycycle.getDayTime();  }

//bool Preda::canWakeup() const{ return _daycycle.getProgress() >= _daycycle.getNightTime(); }

//int Preda::getValoreNutrizionale() const{
//    return 2;
//}

//double Preda::getVisibility() const{
//    return 0; //TO DO
//}

//bool Preda::isInRange(const Vect2D &p) const{
//    return position.distance(p) < 80; //?
//}

//std::string Preda::getType() const{
//    return "preda";
//}

