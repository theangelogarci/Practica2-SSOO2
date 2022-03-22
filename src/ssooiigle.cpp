
#include <iostream>
#include <cctype>
#include <fstream>
#include <regex>
#include <filesystem>
#include <vector>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <string.h>
#include <functional>

#include <colours.h>
#include "WordSearched.cpp"

void arguments_control(char *argv[],std::string &file, std::string &objective, int &nThreads);
int number_of_lines(std::string file);
void find_word(int thread,std::vector<std::string> assignedLines, int begin, int end, std::string objective);
std::map<int, std::vector<std::string>> shareLines(std::string file, int nLines, int nThreads);
std::vector<std::string> splitLine(std::string line);
std::string analizeWord(std::string word);
void printResult();

std::mutex access;
std::vector<std::thread> vThreads;
std::map<int,std::vector<WordSearched>> vWords;

int main(int argc, char *argv[]){
    std::string file;
    std::string objetive;
    std::map<int, std::vector<std::string>> assignedLines;
    int nThreads;
    int nLines;
    int sizeForThreads;
    int begin, end;
    if(argc!=4){
        std::cerr <<ERROR("[ERROR]-- ")<<WARNING(UNDERLINE("The number of arguments is incorrect.") ) <<std::endl;
        exit(EXIT_FAILURE);
    } 
    arguments_control(argv,file,objetive,nThreads);

    nLines=number_of_lines(file);

    if(nLines<nThreads){
        std::cerr << ERROR("[ERROR]-- ")<<WARNING(UNDERLINE("Text has more threads than lines.") )  <<std::endl;
        exit(EXIT_FAILURE);
    }
    sizeForThreads = nLines/nThreads;
    assignedLines=shareLines(file,nLines,nThreads);
    for (int i = 0; i < nThreads; i++) {
        begin=i*sizeForThreads+1;
        end=begin+sizeForThreads-1;

        if(nLines%nThreads!= 0 && i==nThreads-1){ //Aquí se realiza un ajuste para el ultimo hilo en el caso que no sea exacta la división de total de lineas entre el número de hilos.
            end++;
        }
        vThreads.push_back(std::thread(find_word, i, assignedLines[i], begin, end, objetive));
    }

    std::for_each(vThreads.begin(), vThreads.end(), std::mem_fn(&std::thread::join));
    printResult();

    return EXIT_SUCCESS;
}

/* Devuelve el número de lineas de un archivo.*/
int number_of_lines(std::string file){
    int numLines = 0; 
    std::ifstream File(file); 

    while (File.good()) 
    { 
        std::string line; 
        std::getline(File, line); 
        ++numLines; 
    } 
    return numLines;
}

/* Controlar los argumentos que pasamos a la hora de ejecutarlo*/
void arguments_control( char *argv[],std::string &file, std::string &objective, int &nThreads){
    std::string archivo =LIBROS + std::string(argv[1]);
    std::ifstream File(archivo);
    if(File.good()){
        file=archivo;
    }else{
        std::cerr << ERROR("[ERROR]-- ")<<WARNING(UNDERLINE("File doesn`t exist.") )  <<std::endl;
        exit(EXIT_FAILURE);
    }
    
    objective=argv[2];
    if(isdigit(atoi(argv[3]))==0){
        nThreads=atoi(argv[3]);
    }else{
        std::cerr << ERROR("[ERROR]-- ")<<WARNING(UNDERLINE("Please, introduce a valid number of threads.") )  <<std::endl;
        exit(EXIT_FAILURE);
    }

