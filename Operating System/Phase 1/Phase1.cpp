#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class OS
{
public:
    char M[100][4] = {' '};
    char buffer[40];
    string line;
    char IR[4];
    char R[4];
    int IC;
    bool C;
    int SI;
    std::ifstream inputFile;
    fstream outFile;
    

    OS()
    {

        init();
        inputFile.open ("final_input.txt", std::ifstream::in);
    }

    void init()
    {
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                M[i][j] = ' ';
            }
        }

        for (int i = 0; i < 4; i++) // Initialize IR and R
        {
            IR[i] = ' ';
            R[i] = ' ';
        }

        IC = 0;
        C = false;
    }

    void startExecution()
    {
           IC=0;
        executeUserProgram();
    }

    void READ()
    {
        for (int i = 0; i <= 39; i++)
            buffer[i] = '\0';

            std::getline(inputFile, line);
            strcpy(buffer, line.c_str());
            int k = 0;
            int i = IR[2] - 48;
            i = i * 10;

            for (int l = 0; l < 10; ++l)
            {
                for (int j = 0; j < 4; ++j)
                {
                    M[i][j] = buffer[k];
                    k++;
                }
                if (k == 40)
                {
                    break;
                }
                i++;
            }
            cout<<"\n";
            printMemory();
        
    }

    void WRITE()
    {
            outFile.open("out.txt", ios::app);

            for (int i = 0; i <= 39; i++)
                buffer[i] = '\0';

            int k = 0;
            int i = IR[2] - 48;
            i = i * 10;

            for (int l = 0; l < 10; ++l)
            {
                for (int j = 0; j < 4; ++j)
                {
                    buffer[k] = M[i][j];
                    if (buffer[k]!='\0'){
                        outFile << buffer[k];
                    }
                    k++;
                }
                if (k == 40)
                {
                    break;
                }
                i++;
            }
            outFile << "\n";
            cout<<"\n";
            printMemory();

            outFile.close();
        
    }

    void TERMINATE()
    {
        cout<<"\nJob Completed\n\n";
         outFile.open("out.txt", ios::app);

            outFile << "\n";
            outFile << "\n";
            outFile.close();
        // write 2 blank lines in output file
        Load();
    }


    void MOS()
    {
        switch (SI)
        {
            case 1: 
                READ();
                break;
            case 2:
                WRITE();
                break;
            case 3:
                TERMINATE();
                break;
        }
    }

    void executeUserProgram()
    {
         while (true) 
        {
            for (int i = 0; i < 4; i++) // Load in register
            {
                IR[i] = M[IC][i];
            }
            cout<<"Instruction Register content= ";
            for (int i=0; i<4; i++)
                cout<<IR[i];
            IC++;

            if (IR[0] == 'G' && IR[1] == 'D') // GD
            {
                SI = 1;
                MOS();
            }
            else if (IR[0] == 'P' && IR[1] == 'D') // PD
            {
                SI = 2;
                MOS();
            }
            else if (IR[0] == 'H') // H
            {
                SI = 3;
                MOS();
                break;
            }
            else if (IR[0] == 'L' && IR[1] == 'R') // LR
            {
                int i = IR[2] - 48;
                i = i * 10 + (IR[3] - 48);

                for (int j = 0; j <= 3; j++)
                    R[j] = M[i][j];

                cout<<"\nGeneral Purpose Register = ";
                 for(int j=0;j<=3;j++)
                  cout<<R[j];

                cout << endl;
            }
            else if (IR[0] == 'S' && IR[1] == 'R') // SR
            {
                int i = IR[2] - 48;
                i = i * 10 + (IR[3] - 48);
                // cout<<i;
                for (int j = 0; j <= 3; j++)
                    M[i][j] = R[j];

                cout << endl;
                //printMemory();
            }
            else if (IR[0] == 'C' && IR[1] == 'R') // CR
            {
                int i = IR[2] - 48;
                i = i * 10 + (IR[3] - 48);
                // cout<<i;
                int count = 0;

                for (int j = 0; j <= 3; j++)
                    if (M[i][j] == R[j])
                        count++;

                if (count == 4)
                    C = true;

                // cout<<C;
            }
            else if (IR[0] == 'B' && IR[1] == 'T') // BT
            {
                if (C == true)
                {
                    int i = IR[2] - 48;
                    i = i * 10 + (IR[3] - 48);

                    IC = i;
                }
            }
        }
        
    }

    void Load()
    {
       
        int x = 0;
      while (std::getline(inputFile, line))
        {
            for (int i = 0; i <= 39; i++)
                buffer[i] = '\0';
            // cout<<"Line= "<<line<<endl; 

            strcpy(buffer, line.c_str());

            // cout<<"Buffer = ";
            // for(int i=0; i<40; i++)
            // {
            //     cout << buffer[i];
            // }
            // cout<<endl;

            if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
            {
                init();
                cout << "\nRegisters Initialized" << endl;
            }
            else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
            {
            
                cout<<"\nData card reached"<<endl;
                startExecution();
                
                // cout << "Job Executed successfully" << endl;
            }
            else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
            {
                x = 0;
                continue;
            }
           else{
                int k=0;

                for(;x<100;x++){
                    for (int j = 0; j< 4; j++)
                    {
                        
                        M[x][j]=buffer[k];
                        k++;
                        
                    }
                   
                    if(k==40||buffer[k]==' '||buffer[k]=='\n'){
                        break;
                    }
                }
                x++;
            }
        } 
    }

    void printMemory()
    {
        for (int i = 0; i < 100; i++)
            {
                cout << "M[" << i << "]\t";
                for (int j = 0; j < 4; j++)
                {
                    cout << M[i][j];
                }
                cout << endl;
            }
    }
};

            

int main()
{
    OS os;
    os.Load();
    //os.startExecution();
    cout<<"\n";
    //os.printMemory();
    return 0;
}