#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

string dataSetIsValid(char* dataSet)
{
    for(int i = 0; i < 8; i++)
    {
        for(int k = i + 1; k < 9; k++)
        {
            if(*(dataSet + i) == *(dataSet + k))
            {
                stringstream ss;
                ss << *(dataSet + i);
                return ss.str();
            }
        }
    }

    return "";
}

string getInvalidRow(char *puzzle)
{
    string invalidNumber;
    for(int i = 0; i < 9; i++)
    {
        invalidNumber = dataSetIsValid((puzzle + i));
        if(invalidNumber != "")
        {
            stringstream ss;
            ss << invalidNumber << " repeats in row " << i + 1;
            return ss.str();
        }
    }
    return "";
}

string getInvalidColumn(char **puzzle)
{
    char *column = new char[9];
    string invalidNumber;
    for(int i = 0; i < 9; i++)
    {
        for(int k = 0; k < 9; k++)
        {
            *(column + k) = *(*(puzzle + k) + i);

        }
        invalidNumber = dataSetIsValid(column);
        if(dataSetIsValid(column) != "")
        {
            stringstream ss;
            ss << invalidNumber << " repeats in column " << i + 1;
            return ss.str();

        }

    }
    return "";
}

string getInvalidSection(char *puzzle)
{
    int rowOffSet = 0;
    int colOffSet = 0;
    char section[9];
    while(colOffSet <=6)
    {
        int arrayIndex = 0;
        for(int row = rowOffSet; row < rowOffSet + 3; row++)
        {

            for(int col = colOffSet; col < colOffSet + 3; col++)
            {
                *(section + arrayIndex) = *(*(puzzle + row) + col);
                arrayIndex++;

            }


        }
        string invalidValue = dataSetIsValid(section);
        if(invalidValue != "")
        {
            stringstream ss;
            ss << invalidValue << " repeats in section at row " << (rowOffSet / 3) + 1 << " column " << (colOffSet / 3) + 1;
            return ss.str();
        }

        rowOffSet += 3;
        if(rowOffSet > 6)
        {
            rowOffSet = 0;
            colOffSet += 3;
        }
    }
    return "";
}


int main()
{
    fstream inputStream ("puzzles.txt", ios::in);
    fstream outputStream ("solutions.txt", ios::out);
    string puzzleNumber;
    char puzzle[9][9];

    do
    {
        getline(inputStream, puzzleNumber); //set the puzzle number to the first line
        cout << puzzleNumber << "\n";

        string puzzleRow;
        for(int row = 0; row < 9; row++)
        {
            getline(inputStream, puzzleRow);

            for(int column = 0; column < 9; column++)
            {
                *(*(puzzle + row) + column) = puzzleRow.at(column);

            }

        }

        getline(inputStream, puzzleRow);

        string invalidMessage = getInvalidRow(puzzle);
        if(invalidMessage != "")
        {
            cout << invalidMessage << "\n";
        }
        else
        {
            invalidMessage = getInvalidColumn(puzzle);
            if(invalidMessage != "")
            {
                cout << invalidMessage << "\n";
            }
            else
            {
                invalidMessage = getInvalidSection(puzzle);
                if(invalidMessage != "")
                {
                    cout << invalidMessage << "\n";
                }
                else
                {
                    cout << "Valid" << "\n";
                }
            }
        }

        cout << "\n";

    }while(!inputStream.eof());

    inputStream.close();

    return 0;
}
