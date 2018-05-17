/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: MBELE
 *
 * Created on 10 May 2017, 22:36
 */

#include <cstdlib>
#include <iostream>
#include <vector>

#include "Image.h"

using namespace std;
using namespace MBLLEB006;
/*
 * 
 */

int main(int argc, char** argv) {   

   cout << argc << endl;
   const string flag = argv[1];
   if(flag.substr(0,1) != "-"){
       /* Check if the first argument is not a flag.*/
       cout << "Unknown flag. Please read README.md file." << endl;
       exit(0);
   }

   if(!((argc < 4) && (argc > 5))){
	if((argc == 4)&&(string(argv[1]) == "-i")){
		/* The invert operation. */
		Image img;
		img << argv[2];

		cout << "Inverting an image..." << endl;
		!img;		
		cout << "Writing the results to " << argv[3] << "..." << endl;
		img >> argv[3];
		cout << "Operation complete. View the image " << argv[3] << " for results."<< endl;
		
	}
	else if(string(argv[1]) == "-l"){
		/* Mask operation. */
                cout << "Masking image "<< argv[2] <<" with " << argv[3] << endl;
                Image img_one, img_two, img_results;
                img_one << argv[2];
		img_two << argv[3];

                img_results = img_one / img_two;
                cout << "Writing the results to " << argv[4] << "..." << endl;
                img_results >> argv[4];
                cout << "Operation complete. View the image " << argv[4] << " for results."<< endl;

	}
	else if(string(argv[1]) == "-t"){
		/* Threshold operation. */
                cout << "Adding a Threshold of " << argv[3] << " to image " << argv[2] << endl;
                Image img;
                img << argv[2];

                img*stoi(argv[3]);
                cout << "Writing the results to " << argv[4] << "..." << endl;
                img >> argv[4];
                cout << "Operation complete. View the image " << argv[4] << " for results."<< endl;

	}
	else if(string(argv[1]) == "-s"){
		/* Subtract operator. */
		cout << "Subtracting image "<< argv[3] <<" from image " << argv[2] << endl;
                Image img_one, img_two, img_results;
                img_one << argv[2];
                img_two << argv[3];

                img_results = img_one - img_two;
                cout << "Writing the results to " << argv[4] << "..." << endl;
                img_results >> argv[4];
                cout << "Operation complete. View the image " << argv[4] << " for results."<< endl;

	}
	else if(string(argv[1]) == "-a"){
		/* Add operator. */
	 	cout << "Adding image "<< argv[2] <<" to image " << argv[3] << endl;
                Image img_one, img_two, img_results;
                img_one << argv[2];
                img_two << argv[3];

                img_results = img_one + img_two;
                cout << "Writing the results to " << argv[4] << "..." << endl;
                img_results >> argv[4];
                cout << "Operation complete. View the image " << argv[4] << " for results."<< endl;

	}
	else{
		/* Unknown operator. */
		cout << "Unkown operator. Abort!" << endl;
		exit(0);
	}
   }
   else{
	cout << "Unknown operation specified. Abort!" << endl;
	exit(0);
   }
   return 0;
}

