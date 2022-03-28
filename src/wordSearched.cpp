#include <iostream>
#include <colours.h>

class wordSearched {

    private:
    std:: string objective;
    int number_thread;
    int start;
    int end;
    int line;
    std::string word_before;
    std::string word;
    std::string word_after;

    public:
    wordSearched(std::string objective, int number_thread, int start, int end, int line, std::string word_before, std::string word, std::string word_after);
    void toString();

};

wordSearched::wordSearched(std::string objective, int number_thread, int start, int end, int line, std::string word_before, std::string word, std::string word_after) {
    this-> objective = objective;
    this-> number_thread= number_thread;
    this-> start = start;
    this-> end = end;
    this-> line = line;
    this-> word_before = word_before;
    this-> word = word;
    this-> word_after = word_after;
}

void wordSearched::toString(){
    std::cout<< RESULT("[Hilo ")<< RED <<std::to_string(this->number_thread) << RESULT(" inicio: ")<< RED<< std::to_string(this->start)<<  RESULT(" – final: ")<< RED << std::to_string(this->end)<<  RESULT("] :: línea ")<< RED <<std::to_string(this->line)<<RESULT(" :: ")<< CIAN <<"... "+this->word_before<<" "<< ULINE <<this->word<< RESET<< CIAN<<" "<<this->word_after<<" ..."<<std::endl;
}


