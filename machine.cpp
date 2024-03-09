#include "machine.h"
// cpu implementation

cpu::cpu()
{
    PC = 0;
    for (int i = 0; i < 16; i++)
    {
        Register[i] = "00";
    }
}

void cpu::print()
{
    cout << "program counter: " << PC << endl;
    cout << "instruction register: " << IR << endl;
    cout << "Register values:\n";
    for (int i = 0; i < 16; i++)
    {
        if (i <= 9)
        {
            cout << '0' << char('0' + i) << "  " << Register[i] << endl;
        }
        else
        {
            cout << '0' << char('A' + (i - 10)) << "  " << Register[i] << endl;
        }
    }
}

void cpu::cycle(main_memory &m)
{
    IR = "";
    IR += m.memory[PC];
    IR += m.memory[PC + 1];
    PC += 2;
}

// =======================================

// main_memory implementation

main_memory::main_memory()
{
    cout <<"mem";
    size = 0;
    for (int i = 0; i < 256; i++)
    {
        memory[i] = "00";
    }
}

void main_memory::file()
{
    char file_name[100];
    cout << "Enter the file path: ";
    cin >> file_name;
    strcat(file_name, ".txt");
    fstream Data(file_name);
    string Byte;
    memory[0] = "";
    if (Data.fail())
    {
        cout << "ERROR Wrong Path";
        return;
    }
    while (!Data.eof())
    {
        Data >> Byte;
        for (int i = 2; i < Byte.size(); i++)
        {
            memory[size] += Byte[i];
            if (memory[size].size() == 2)
            {
                size++;
                memory[size] = "";
            }
        }
        if (memory[size].size() == 2)
        {
            size++;
            memory[size] = "";
        }
    }
    if (memory[size] == "")
    {
        memory[size] = "00";
    }
}

void main_memory::step_by_step()
{
    int steps;
    cout << "Enter the number of steps: ";
    cin >> steps;
    string step;
    memory[0] = "";
    while (steps--)
    {
        cout << "Enter the instruction: ";
        cin >> step;
        for (int i = 0; i < step.size(); i++)
        {
            memory[size] += step[i];
            if (memory[size].size() == 2)
            {
                size++;
                memory[size] = "";
            }
        }
        if (memory[size].size() == 2)
        {
            size++;
            memory[size] = "";
        }
    }
    if (memory[size] == "")
    {
        memory[size] = "00";
    }
}

void main_memory::print()
{
    for (int i = 0; i < 256; i++)
    {
        if (i / 16 <= 9)
        {
            if (i % 16 <= 9)
            {
                cout << char('0' + (i / 16)) << char('0' + (i % 16)) << "  " << memory[i] << endl;
            }
            else
            {
                cout << char('0' + (i / 16)) << char('A' + ((i % 16) - 10)) << "  " << memory[i] << endl;
            }
        }
        else
        {
            if (i % 16 <= 9)
            {
                cout << char('A' + (i / 16) - 10) << char('0' + (i % 16)) << "  " << memory[i] << endl;
            }
            else
            {
                cout << char('A' + (i / 16) - 10) << char('A' + ((i % 16) - 10)) << "  " << memory[i] << endl;
            }
        }
    }
}

// =======================================

// instruction implementation

instruction::instruction(cpu &c)
{
    op_code = c.IR[0];
    for (int i = 1; i < 4; i++)
    {
        operand[i - 1] = c.IR[i];
    }
}

void instruction::op_code_1(main_memory &m, cpu &c)
{
    int R_address; // register address
    if (operand[0] >= '0' and operand[0] <= '9')
    {
        R_address = operand[0] - '0';
    }
    else
    {
        R_address = operand[0] - 'A' + 10;
    }

    int M_address = 0; // memory address
    if (operand[1] >= '0' and operand[1] <= '9')
    {
        M_address += (operand[1] - '0') * 16;
    }
    else
    {
        M_address += (operand[1] - 'A' + 10) * 16;
    }

    if (operand[2] >= '0' and operand[2] <= '9')
    {
        M_address += (operand[2] - '0');
    }
    else
    {
        M_address += (operand[2] - 'A' + 10);
    }

    c.Register[R_address] = m.memory[M_address];
}

void instruction::op_code_2(main_memory &m, cpu &c)
{
    int R_address; // register address
    if (operand[0] >= '0' and operand[0] <= '9')
    {
        R_address = operand[0] - '0';
    }
    else
    {
        R_address = operand[0] - 'A' + 10;
    }

    c.Register[R_address] = operand[1];
    c.Register[R_address] += operand[2];
}

void instruction::op_code_3(main_memory &m, cpu &c)
{
    int R_address; // register address
    if (operand[0] >= '0' and operand[0] <= '9')
    {
        R_address = operand[0] - '0';
    }
    else
    {
        R_address = operand[0] - 'A' + 10;
    }

    if (operand[1] == '0' and operand[2] == '0')
    {
        cout << c.Register[R_address] << endl;
        return;
    }

    int M_address = 0; // memory address
    if (operand[1] >= '0' and operand[1] <= '9')
    {
        M_address += (operand[1] - '0') * 16;
    }
    else
    {
        M_address += (operand[1] - 'A' + 10) * 16;
    }

    if (operand[2] >= '0' and operand[2] <= '9')
    {
        M_address += (operand[2] - '0');
    }
    else
    {
        M_address += (operand[2] - 'A' + 10);
    }

    m.memory[M_address] = c.Register[R_address];
}

void instruction::op_code_4(main_memory &m, cpu &c)
{
    int R_address; // register address
    if (operand[1] >= '0' and operand[1] <= '9')
    {
        R_address = operand[1] - '0';
    }
    else
    {
        R_address = operand[1] - 'A' + 10;
    }

    int S_address; // register address
    if (operand[2] >= '0' and operand[2] <= '9')
    {
        S_address = operand[2] - '0';
    }
    else
    {
        S_address = operand[2] - 'A' + 10;
    }

    c.Register[S_address] = c.Register[R_address];
}

void instruction::op_code_5(main_memory &m, cpu &c)
{
    int R_address; // register address
    if (operand[0] >= '0' and operand[0] <= '9')
    {
        R_address = operand[0] - '0';
    }
    else
    {
        R_address = operand[0] - 'A' + 10;
    }

    int S_address; // register address
    if (operand[1] >= '0' and operand[1] <= '9')
    {
        S_address = operand[1] - '0';
    }
    else
    {
        S_address = operand[1] - 'A' + 10;
    }

    int T_address; // register address
    if (operand[2] >= '0' and operand[2] <= '9')
    {
        T_address = operand[2] - '0';
    }
    else
    {
        T_address = operand[2] - 'A' + 10;
    }

    string S_H = c.Register[S_address], T_H = c.Register[T_address], sum_H = "";
    int S_D = 0, T_D = 0, sum_D;

    if (S_H[0] >= '0' and S_H[0] <= '9')
    {
        S_D += (S_H[0] - '0') * 16;
    }
    else
    {
        S_D += (S_H[0] - 'A' + 10) * 16;
    }

    if (S_H[1] >= '0' and S_H[1] <= '9')
    {
        S_D += (S_H[1] - '0');
    }
    else
    {
        S_D += (S_H[1] - 'A' + 10);
    }

    if (T_H[0] >= '0' and T_H[0] <= '9')
    {
        T_D += (T_H[0] - '0') * 16;
    }
    else
    {
        T_D += (T_H[0] - 'A' + 10) * 16;
    }

    if (T_H[1] >= '0' and T_H[1] <= '9')
    {
        T_D += (T_H[1] - '0');
    }
    else
    {
        T_D += (T_H[1] - 'A' + 10);
    }

    sum_D = S_D + T_D;
    while (sum_H.size() < 2)
    {
        char x;
        if (sum_D % 16 <= 9)
        {
            x = '0' + sum_D % 16;
        }
        else
        {
            x = 'A' + (sum_D % 16 - 10);
        }

        sum_H = x + sum_H;
    }

    c.Register[R_address] = sum_H;
}

void instruction::op_code_B(main_memory &m, cpu &c)
{
    int R_address; // register address
    if (operand[0] >= '0' and operand[0] <= '9')
    {
        R_address = operand[0] - '0';
    }
    else
    {
        R_address = operand[0] - 'A' + 10;
    }

    int M_address = 0; // memory address
    if (operand[1] >= '0' and operand[1] <= '9')
    {
        M_address += (operand[1] - '0') * 16;
    }
    else
    {
        M_address += (operand[1] - 'A' + 10) * 16;
    }

    if (operand[2] >= '0' and operand[2] <= '9')
    {
        M_address += (operand[2] - '0');
    }
    else
    {
        M_address += (operand[2] - 'A' + 10);
    }

    if (c.Register[0] == c.Register[R_address])
    {
        c.PC = M_address;
    }
}

bool instruction::make(main_memory &m, cpu &c)
{
    if (op_code == '1')
    {
        op_code_1(m, c);
    }
    else if (op_code == '2')
    {
        op_code_2(m, c);
    }
    else if (op_code == '3')
    {
        op_code_3(m, c);
    }
    else if (op_code == '4')
    {
        op_code_4(m, c);
    }
    else if (op_code == '5')
    {
        op_code_5(m, c);
    }
    else if (op_code == 'B')
    {
        op_code_B(m, c);
    }
    else
    {
        return false;
    }
    return true;
}

// =======================================

// machine implementation

machine::machine()
{
    cout << "select what are you want\n\n";
    cout << "1->Enter instruction line by line and show status step by step\n";
    cout << "2->Enter instruction by file and show status step by step\n";
    cout << "3->Enter instruction line by line and show status in the end\n";
    cout << "4->Enter instruction by file and show status in the end\n";
    cin >> choise;
}

void machine::take_instructions()
{
    if (choise == 1 or choise == 3)
    {
        m.step_by_step();
    }
    else
    {
        m.file();
    }
}

bool machine::make_cycle()
{
    c.cycle(m);
    instruction i(c);
    if ((choise == 1 or choise == 2) and i.make(m, c))
    {
        c.print();
        m.print();
        return true;
    }
    else if (i.make(m, c))
    {
        return true;
    }
    else
    {
        c.print();
        m.print();
        return false;
    }
    return false;
}
