#include <iostream>
#include <fstream>

#include "fixed_point.hpp"
#include "bad.hpp"

#define CURR_TYPE FixedPoint<20,20>

//OverflowMode number_mode = OverflowMode::CAP_MODE;
const double precision = 0.01;

bool currtype_equal(CURR_TYPE a, CURR_TYPE b){
    // If they are close enough
    return (a - b) < CURR_TYPE(precision) && (b - a) < CURR_TYPE(precision);
}

bool currtype_equal(CURR_TYPE a, double b){
    // If they are close enough
    return (a - b) < CURR_TYPE(precision) && (b - a) < CURR_TYPE(precision);
}

int main(){
    // start reading tests.txt
    std::ifstream infile("tests.txt");
    std::ofstream outfile("results.txt");
    char optype;
    double num1, num2, num3;
    int n, m;
    while(infile >> optype){
        switch (optype){
            case '!':{
                infile >> n >> m;
                outfile << "Creating FixedPoint<" << n << ", " << m << ">" << std::endl;
                break;
            }
            case '#':{// Assignment test
                infile >> num1 >> num2;
                //auto p1 = (CURR_TYPE)get_type(n, m);
                CURR_TYPE* p1 = new CURR_TYPE;
                *p1 = num1;
                // now need to check if they are equal
                if(currtype_equal(*p1, num2)){
                    outfile << "OK " << num1 << " == " << num2 << " " << *p1 << std::endl;
                } else {
                    outfile << "FAIL " << num1 << " != " << num2 << " " << *p1 << std::endl;
                }
                break;
            }
            case '+':{// Addition test
                infile >> num1 >> num2 >> num3;
                //auto p1 = (CURR_TYPE)get_type(n, m);
                CURR_TYPE* p1 = new CURR_TYPE;
                *p1 = num1;
                //auto p2 = (CURR_TYPE)get_type(n, m);
                CURR_TYPE* p2 = new CURR_TYPE;
                *p2 = num2;
                // now need to check if they are equal
                if(currtype_equal(*p1 + *p2, num3)){
                    outfile << "OK " << num1 << " + " << num2 << " == " << num3 << "==" << *p1 + *p2 << std::endl;
                } else {
                    outfile << "FAIL " << num1 << " + " << num2 << " == " << *p1 << " + " << *p2 << " == " << *p1+*p2 << " != " << num3  << std::endl;
                }
                break;
            }
            case '-':{// Subtraction test
                infile >> num1 >> num2 >> num3;
                //auto p1 = (CURR_TYPE)get_type(n, m);
                CURR_TYPE* p1 = new CURR_TYPE;
                *p1 = num1;
                // auto p2 = (CURR_TYPE)get_type(n, m);
                CURR_TYPE* p2 = new CURR_TYPE;
                *p2 = num2;
                // now need to check if they are equal
                if(*p1 - *p2 == num3){
                    outfile << "OK " << num1 << " - " << num2 << " == " << num3 << "==" << *p1 - *p2 << std::endl;
                } else {
                    outfile << "FAIL " << num1 << " - " << num2 << " == " << *p1 << " - " << *p2 << " == " << *p1-*p2 << " != " << num3  << std::endl;
                }
                break;
            }
            case '*':{// Multiplication test
                infile >> num1 >> num2 >> num3;
                //auto p1 = (CURR_TYPE)get_type(n, m);
                CURR_TYPE* p1 = new CURR_TYPE; 
                *p1 = num1;
                //auto p2 = (CURR_TYPE)get_type(n, m);
                CURR_TYPE* p2 = new CURR_TYPE;
                *p2 = num2;
                // now need to check if they are equal
                if(*p1 * *p2 == num3){
                    outfile << "OK " << num1 << " * " << num2 << " == " << num3 << "==" << *p1 * *p2 << std::endl;
                } else {
                    outfile << "FAIL " << num1 << " * " << num2 << " == " << *p1 << " * " << *p2 << " == " << *p1 * *p2 << " != " << num3  << std::endl;
                }
                break;
            }
            default:{
                std::cout << "Unknown optype: " << optype << std::endl;
                return 0;
            }
        }
    }
    
}
