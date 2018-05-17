/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Image.cpp
 * Author: MBELE
 * 
 * Created on 10 May 2017, 23:04
 */
#include <memory>
#include <iostream>
#include <fstream>
#include "Image.h"

using namespace std;
using namespace MBLLEB006;

Image::Image(const char* filename){
    load(filename);
}

Image::Image(const Image& orig) {
    this->height = orig.height;
    this->width = orig.width;
    this->header = orig.header;
    
    this->data = unique_ptr<unsigned char[]>(new unsigned char[height*width]);
    
    Image::iterator it_begin = begin(),it_end = end(), it_orig(orig.data.get());
    for(it_begin = begin(); it_begin != it_end; it_begin++){
        *it_begin = *it_orig;
        it_orig++;
    }
}

Image::Image(Image&& orig){
    this->width = orig.width;
    this->height = orig.height;
    this->header = orig.header;
    
    this->data = std::move(orig.data);
    
    orig.data = nullptr;
}
Image::~Image() {
}

int Image::load(const char* filename){
        ifstream file(filename, ios::in | ios::binary);

        if(file.is_open()){
            string line;
            getline(file, line);
            file >> ws;
            header = line + "\n";

            getline(file, line);
            header += line + "\n";
            
            /* Read all the comments. */
            while(line[0] == '#'){
                getline(file, line);
                file >> ws;
                header += line + "\n";
            }

            /* Get the row and column numbers. */
            string::size_type size_t;
            int index = line.find(" ");

            height = std::stoi(line.substr(0, index), &size_t);
            width = std::stoi(line.substr(index + 1), &size_t);

            /* Get the 255. */
            std::getline(file, line);
            file >> ws;
            header += line + "\n";

            /* Read the data. */
            unsigned char * memblock;
            
            memblock = new unsigned char [width*height];
            file.read ((char*)memblock, width*height);
                
            data = unique_ptr<unsigned char[]>(memblock);       
        }
        else{
                cout << "Image could not be opened. System Abort!" << endl;
		exit(0);
        }
        file.close();
        
        return 0;
}

int Image::save(const char* filename){
    ofstream file(filename, ios::out | ios::binary);
    
    if(file.is_open()){
        file << header;
        
        for(int i = 0; i < (height*width); i++){
            file << (data.get())[i];  
        }
    }
    else{
        cout << "Image could not be opened. Sytem Abort!" << endl;
	exit(0);
    }
    file.close();
    
    return 0;
}
Image& Image::operator +(const Image& rhs){
    /* Assume that the sizes of this Images are equal. */
    
    MBLLEB006::Image::iterator it_rhs(rhs.data.get());
    MBLLEB006::Image::iterator it_lhs(this->data.get());
    
    for(it_lhs = this->begin(); it_lhs != this->end(); it_lhs++){
        unsigned int temp = ((unsigned int)(*it_lhs) + (unsigned int)(*it_rhs));
        unsigned int results =  temp>255 ? (255):temp;
        *it_lhs = (unsigned char)results;
        it_rhs++;
    }
    return *this;
}

Image& Image::operator -(const Image& rhs){
    MBLLEB006::Image::iterator it_rhs(rhs.data.get());
    MBLLEB006::Image::iterator it_lhs(this->data.get());
    
    for(it_lhs = this->begin(); it_lhs != this->end(); it_lhs++){
        int temp = ((unsigned int)(*it_lhs) - (unsigned int)(*it_rhs));
        unsigned int results =  temp<0 ? (0):temp;
        *it_lhs = (unsigned char)results;
        it_rhs++;
    }
    return *this;    
}

Image& Image::operator /(const Image& rhs){
    MBLLEB006::Image::iterator it_rhs(rhs.data.get());
    MBLLEB006::Image::iterator it_lhs(this->data.get());
    
    for(it_lhs = this->begin(); it_lhs != this->end(); it_lhs++){
        *it_lhs = ((unsigned int)*it_rhs == 255) ? *it_lhs:(unsigned char)0;
        it_rhs++;
    }
    return *this;
}

Image& Image::operator *(const int f){
    MBLLEB006::Image::iterator it(this->data.get());
    
    for(it = this->begin(); it != this->end(); it++){
        *it = ((unsigned int)*it > f) ? (unsigned char)255:(unsigned char)0;
    }
    return *this;
}

Image& Image::operator =(Image&& rhs){
    this->height = rhs.height;
    this->width = rhs.width;
    this->header = rhs.header;
    
    this->data = move(rhs.data);
    
    rhs.data = nullptr;
    return *this;
}

Image& Image::operator =(const Image& rhs){
    this->width = rhs.width;
    this->height = rhs.height;
    this->header = rhs.header;
    
    unique_ptr<unsigned char[]> temp(new unsigned char[height*width]);
    this->data = std::move(temp);
    
    Image::iterator it_begin = begin(),it_end = end(), it_rhs(rhs.data.get());
    for(it_begin = begin(); it_begin != it_end; it_begin++){
        *it_begin = *it_rhs;
        it_rhs++;
    }
    return *this;
}

Image& Image::operator !(){
    MBLLEB006::Image::iterator it(this->data.get());
    
    for(it = this->begin(); it != this->end(); it++){
        *it = (unsigned char)(255 - (unsigned int)*it);
    }
    return *this;
}

Image& Image::operator >>(const char* filename){
    save(filename);
    return *this;
}

Image& Image::operator <<(const char* filename){
    load(filename);
    return *this;
}
