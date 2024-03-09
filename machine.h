#ifndef MACHINE_H
#define MACHINE_H
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class main_memory;
class cpu;
class machine;
class instruction;

class cpu
{
private:
    int PC;    // program counter
    string IR; // instruction register
    string Register[16];

public:
    // make constructor to initialize Register by "00" and pc to "00";
    cpu();

    // add functions to update data (PC and IR) and make IR take data from memory
    void cycle(main_memory &m);

    // a print function print PC, IR,and Registers value
    void print();

    // add function to change register value

    // add function to get value of one register

    // add friend function to make machine access to class
    friend class machine;

    // add friend function to make instruction access to class;
    friend class instruction;
};

class main_memory
{
private:
    string memory[256];
    int size;

public:
    // make constructor to initialize memory by "00";
    main_memory();

    // add functions to take data from file and save it in memory 2bytes by 2bytes
    void file();

    // add function to get one instruction
    void step_by_step();

    // a print function print memory value
    void print();

    // add friend function to make machine access to class
    friend class machine;

    // add friend function to make cpu access to class
    friend class cpu;

    // add friend function to make instruction access to class;
    friend class instruction;
};

class instruction
{
private:
    char op_code;
    char operand[3];

public:
    // add constructors to set values
    instruction(cpu &c);

    // add functions make instructions in machine language depend on op_code
    void op_code_1(main_memory &m, cpu &c);
    void op_code_2(main_memory &m, cpu &c);
    void op_code_3(main_memory &m, cpu &c);
    void op_code_4(main_memory &m, cpu &c);
    void op_code_5(main_memory &m, cpu &c);
    void op_code_B(main_memory &m, cpu &c);
    bool make(main_memory &m, cpu &c);
    // add friend function to make machine access to class
    friend class machine;
};

class machine
{
private:
    cpu c;
    main_memory m;
    int choise ;
public:
    // constructor to display main menu and take chiose
    machine();
    
    //function to take instructions to save it in memory
    void take_instructions();
    
    //function to make cycle
    bool make_cycle();
};

#endif