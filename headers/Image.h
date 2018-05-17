/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Image.h
 * Author: MBELE
 *
 * Created on 10 May 2017, 23:04
 */

#include <vector>
#include <memory>
#include <deque>

#ifndef IMAGE_H
#define IMAGE_H

namespace MBLLEB006{
    class Image {
    public:
        class iterator{
            friend Image;
        private:
            unsigned char *ptr;
            // construct only via Image class (begin/end)
            iterator(unsigned char *p) : ptr(p) {}  

        public:
            /**
             * @Brief Copy constructor
             * 
             * @param rhs
             */
            iterator(const iterator & rhs) : ptr(rhs.ptr) {}
            
            /**
             * @Brief Move constructor
             * 
             * @param rhs
             */
            iterator(iterator && rhs) : ptr(rhs.ptr)
            { rhs.ptr = nullptr;}
            
            /**
             * @Brief Copy assignment operator
             * 
             * @param rhs
             * @return 
             */
            iterator & operator=(const iterator & rhs){
                if(this != &rhs){
                    this->ptr = rhs.ptr;
                }
                return *this;
            }
            
            /**
             * @Brief Move assignment operator
             * 
             * @param rhs
             * @return 
             */
            iterator & operator=(iterator && rhs){
                if(this != &rhs){
                    this->ptr = std::move(rhs.ptr);
                    rhs.ptr = nullptr;
                }
                return *this;
            }

            /**
             * @Brief Check for equality between two iterators
             * 
             * @param rhs
             * @return 
             */
            bool operator==(const iterator & rhs){
                return (this->ptr == rhs.ptr);
            }
            /**
             * @Brief Check for equality between two iterators
             * 
             * @param rhs
             * @return 
             */
            bool operator!=(const iterator & rhs){
                return (this->ptr != rhs.ptr);
            }

            /**
             * @Brief Dereference operator
             * 
             * @param rhs
             * @return 
             */
            unsigned char& operator*(){
                return *(ptr);
            }
            /**
             * @Brief post ++ operator
             * 
             * @param rhs
             * @return 
             */
            iterator operator++(const int){
                iterator temp(*this);
                this->ptr += 1;
                return temp;
            }
            
            /**
             * @Brief pre ++ operator
             * 
             * @param rhs
             * @return 
             */
            iterator& operator++(){
                this->ptr += 1;
                return *this;
            }

            /**
             * @Brief -- operator
             * 
             * @param rhs
             * @return 
             */
            iterator operator--(const int){
                iterator temp(*this);
                this->ptr -= 1;
                return temp;
            }
            
            /**
             * @Brief pre-- operator
             * 
             * @param rhs
             * @return 
             */
            iterator & operator--(){
                this->ptr -= 1;
                return *this;
            }

        };
        /**
         * @Brief Default constructor
         */
        Image(): height(10), width(10), header("P5\n10 10\n255")
        {this->data = std::unique_ptr<unsigned char[]>(new unsigned char[height*width]);}
        /**
         * @Brief Initialise an Image object of a given file
         * 
         * @param filename
         */
        Image(const char* filename);

        /**
         * @Brief Default destructor
         */
        virtual ~Image();

        /**
         * @Brief Copy constructor
         * 
         * @param orig
         */
        Image(const Image& orig);
        
        /**
         * @Brief move constructor
         * 
         * @param orig
         */
        Image(Image&& orig);

        /**
         * @Brief Returns a read/write iterator that points to the first
         * element of the data.
         * @return 
         */
        iterator begin(void){return iterator(data.get());}

        /**
         * @Brief Returns a read/write iterator that points to the last
         * element of the data.
         * @return 
         */
        iterator end(void){
            MBLLEB006::Image::iterator it((data.get() + (height*width) - 1));
            return it;
        }
        
        /**
         * @Brief + operator on two Image objects
         * 
         * @param rhs
         * @return 
         */
        Image&  operator+(const Image& rhs);
        /**
         * @Brief: - operator on two Image objects
         * @param ths
         * @return 
         */
        Image& operator-(const Image& rhs);
        /**
         * @Brief move = operator on two Image objects
         * 
         * @param rhs
         * @return 
         */
	Image& operator=(Image&& rhs);  
        
        /**
         * @Brief Copy = operator
         * 
         * @param rhs
         * @return 
         */
	Image& operator=(const Image& rhs);
        
        /**
         * @Brief mask / operator
         * 
         * @param rhs
         * @return 
         */
	Image& operator/(const Image& rhs);
        
        /**
         * @Brief inverter operator
         * 
         * @return 
         */
        Image& operator!(void);
        
        /**
         * @Brief Threshold operator
         * 
         * @param f
         * @return 
         */
        Image& operator*(const int f);
        /**
         * @Brief >> operator
         * 
         * @param filename
         * @return 
         */
        Image& operator>>(const char* filename);

        /**
         * @Brief >> operator
         * 
         * @param filename
         * @return 
         */
        Image& operator<<(const char* filename);
        
    private:
        int width;                                  // The Width of the Image
        int height;                                 // The Height of the Image
        std::string header;                         // The header of the Image
        std::unique_ptr<unsigned char[]> data;      // The container for the Image data

        /**
         * @Brief Read the data from a given image file
         *
         * @param filename
         * @return
         */
        int load(const char* filename);

        /**
         * @Brief Write the data to a given file.
         *
         * @param filename
         * @return
         */
        int save(const char* filename);
    };
}
#endif /* IMAGE_H */

