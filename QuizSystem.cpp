#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

// functions outside the main  are global variable
//  we will discuss global variables later

void loadData(); // Don't bother about this code, you will learn it later.

const int qsize = 20; // Maximum number of questions
const int usize = 5;  // Maximum number of users
int questionNo = 0;   // QuestionNo checker variable
int deleteQuestionNo = 0;
int userNumber = 0;
int addedQuestion = 0;      // added question checker
int attemptedQuestions = 0; // attemped question checker
string quizAnswer = "0";
int person = 0;
int marks[usize] = {0, 0, 0, 0, 0};
bool flag = 1;
// variable area
bool qflag[qsize]; // use this array to check whether an element exist on an index or not.
string question[qsize];
string option1[qsize];
string option2[qsize];
string option3[qsize];
string option4[qsize];
string correctOption[qsize];

bool uflag[usize]; // use this array to check whether an element exist on an index or not.
string username[usize];
string passwords[usize];
int scores[usize]; // array will be used to save the score attempted.
/////////////////////////////FUNCTION START//////////////////////////////////////
void addQuestion()
{
    while (questionNo < qsize && question[questionNo] == " ") // add only question if there is free space
    {
        cout << "Enter the Question: ";
        cin.ignore();
        getline(cin, question[questionNo]);
        cout << "Enter Options: ";
        cin >> option1[questionNo] >> option2[questionNo] >> option3[questionNo] >> option4[questionNo];
        cout << "Enter the correct option: ";
        cin >> correctOption[questionNo];
        addedQuestion++;
        while (correctOption[questionNo] != option1[questionNo] && correctOption[questionNo] != option2[questionNo] && correctOption[questionNo] != option3[questionNo] && correctOption[questionNo] != option4[questionNo])
        {
            cout << "Correct option does not match any of the above options." << endl;
            cout << "Enter the correct option: ";
            cin >> correctOption[questionNo];
        }
        questionNo++;
    }
    if (questionNo >= qsize)
    {
        cout << "Maximum number of questions has been added already." << endl;
        questionNo = 0;
    }
}
void listQuestion()
{
    cout << left; // list the questions in table format
    cout << endl
         << setw(10) << "Q.1";
    cout << setw(40) << "Question";
    cout << setw(20) << "option 1" << setw(20) << "Option 2" << setw(20) << "Option 3" << setw(20) << "Option 4" << setw(20) << "Correct answer" << endl;
    cout << "*********************************************************************************************************************************************************";
    cout << endl;
    for (int i = 0; i < qsize; i++)
    {
        if (question[i] != " ")
        {
            cout << left;
            cout << setw(11) << i + 1;
            cout << setw(40) << question[i];
            cout << setw(20) << option1[i] << setw(20) << option2[i] << setw(20) << option3[i] << setw(20) << option4[i] << setw(20) << correctOption[i] << endl;
        }
    }
}
void deleteQuestion()
{
    listQuestion();
    cout << "Select the Question ID (Q.I) to delete a question: ";
    cin >> deleteQuestionNo;
    while ((deleteQuestionNo - 1) > questionNo)
    {
        cout << "Wrong Question Number Selected \n Select the Question ID (Q.I) to delete a question: ";
        cin >> deleteQuestionNo;
    }
    for (int i = 0; i < qsize; i++)
    {
        if ((deleteQuestionNo - 1) == i) // delete the question and its relevent answers by assigning to " ";
        {
            question[i - 1] = " ";
            option1[i - 1] = " ";
            option2[i - 1] = " ";
            option3[i - 1] = " ";
            option4[i - 1] = " ";
            correctOption[i - 1] = " ";
            cout << endl
                 << "Question Deleted Sussessfully! ";
            addedQuestion--;
            // listQuestion();
            break;
        }
    }
}
void updateQuestion(int x)
{
    cout << "Enter the Question: ";
    cin.ignore();
    getline(cin, question[x]);
    cout << "Enter Options: ";
    cin >> option1[x] >> option2[x] >> option3[x] >> option4[x];
    cout << "Enter the correct option: ";
    cin >> correctOption[x];
    cout << "Question d Successfully!" << endl;
}
void registerUser(string x, string y)
{
    if (userNumber < 5 || username[userNumber] == " ")
    {
        username[userNumber] = x;
        passwords[userNumber] = y;
        userNumber++;
    }
}
void deleteUser(string x)
{
    for (int i = 0; i < usize; i++)
    {
        if (x == username[i])
        {
            username[i] = " ";
            passwords[i] = " ";
            break;
        }
    }
}
void updateUser(string user, string newName, string newPass)
{
    for (int i = 0; i < usize; i++)
    {
        if (user == username[i])
        {
            username[i] = newName;
            passwords[i] = newPass;
            break;
        }
    }
}
void listStudents()
{
    cout << left;
    cout << setw(20) << "U.I" << setw(30) << "Username" << setw(20) << "Password" << endl;
    cout << "****************************************************************************" << endl;
    for (int i = 0; i < usize; i++)
    {
        if (username[i] != " ")
        {
            cout << setw(20) << i + 1 << setw(30) << username[i] << setw(20) << passwords[i] << endl;
        }
    }
}
void attemptQuiz(string x)
{
    int i = 0;
    flag = 1;
    for (int j = 0; j < usize; j++)
    {
        if (x == username[j])
        {
            while (flag == 1)
            {
                for (i = 0; i < addedQuestion - 1; i++)
                {
                    if (question[i] != " ")
                    {
                        cout << "Q " << i + 1 << "  " << question[i] << endl;
                        cout << "Options: " << endl;
                        cout << "a.  " << option1[i] << "    b.  " << option2[i] << "    c.  " << option3[i] << "    d.  " << option4[i] << endl;
                        cout << "Enter your answer: ";
                        cin >> quizAnswer;
                        cout << endl
                             << endl;
                        if (quizAnswer == correctOption[i])
                        {
                            marks[j] = 1 + marks[j];
                        }
                        attemptedQuestions++;
                    }
                    cout << "Do you want to proceed or submit quiz? (1/0): ";
                    cin >> flag;
                    if (flag == 0)
                    {
                        break;
                    }
                }
                if (flag == 1)
                    for (i = addedQuestion - 1; i < addedQuestion; i++)
                    {
                        if (question[i] != " ")
                        {
                            cout << "Q " << i + 1 << "  " << question[i] << endl;
                            cout << "Options: " << endl;
                            cout << "a.  " << option1[i] << "    b.  " << option2[i] << "    c.  " << option3[i] << "    d.  " << option4[i] << endl;
                            cout << "Enter your answer: ";
                            cin >> quizAnswer;
                            cout << endl
                                 << endl;
                            if (quizAnswer == correctOption[i])
                            {
                                marks[j] = 1 + marks[j];
                            }
                            attemptedQuestions++;
                        }
                        cout << "This is the last Question\n End Quiz by pressing 0: ";
                        cin >> flag;
                        if (flag == 0)
                        {
                            break;
                        }
                    }
            }

            person++;
        }
    }
}
void result(string x)
{
    cout << left;
    cout << "**********************************************************************" << endl;
    cout << setw(30) << "Username" << setw(25) << "Attained Marks" << setw(10) << "Total Marks" << endl;
    cout << "**********************************************************************" << endl;
    for (int i = 0; i < usize; i++)
    {
        if (x == username[i])
        {
            cout << setw(30) << x << setw(25) << marks[i] << setw(10) << addedQuestion << endl;
            break;
        }
    }
}
void adminResult()
{
    cout << left;
    cout << "**********************************************************************" << endl;
    cout << setw(30) << "Username" << setw(25) << "Attained Marks" << setw(10) << "Total Marks" << endl;
    cout << "**********************************************************************" << endl;
    for (int i = 0; i < usize; i++)
    {
        if (username[i] != " ")
        {
            cout << setw(30) << username[i] << setw(25) << marks[i] << setw(10) << addedQuestion << endl;
        }
    }
}
////////////////////////////FUNCTIONS END/////////////////////////////////////
int main()
{

    string user;
    string pwd;
    bool userSearchFlag = false;

    int input;

    int loggedInUserType = -10; // 1 for administrator, 2 for user

    // TODO-- Initializtion of all arrays
    // assign an intial values to all arrays here.

    int i = 0;
    for (int i = 0; i < usize; i++)
    {
        username[i] = " ";
        passwords[i] = " ";
    }
    for (int i = 0; i < qsize; i++)
    {
        question[i] = " ";
        option1[i] = " ";
        option2[i] = " ";
        option3[i] = " ";
        option4[i] = " ";
        correctOption[i] = " ";
    }

    loadData(); // Don't bother about this code, you will learn it later.

    // program header
    cout << "***************************************************************\n";
    cout << "                     Quiz System                               \n";
    cout << "***************************************************************\n";

    do
    {
        cout << endl;
        cout << "Choose the desired option\n";
        cout << left << setw(10) << "\t"
             << setw(25) << "1. Administrator Login"
             << setw(25) << "2. User Login"
             << setw(25) << "0. Exit";
        cout << endl;

        cout.unsetf(ios::left);
        cout.unsetf(ios::right);

        cout << "\tChoose an option: ";
        cin >> input;
        cout << endl;

        switch (input)
        {

        case 1:
            cout << "Enter the username: ";
            cin >> user;

            cout << "Enter Password: ";
            cin >> pwd;

            if (user == "Administrator" && pwd == "PF2020")
                loggedInUserType = 1;
            else
                loggedInUserType = -1;
            break;
        case 2:
            cout << "Enter the username: ";
            cin >> user;

            cout << "Enter Password: ";
            cin >> pwd;
            for (int i = 0; i < usize; i++)
            {
                if (user == username[i] && pwd == passwords[i]) // check if user is registered or not
                {
                    userSearchFlag = true;
                    break;
                }
                else
                    userSearchFlag == false;
            }

            if (userSearchFlag == true)
            {
                loggedInUserType = 2;
            }
            else
            {
                loggedInUserType = -1;
            }
            break;
        case 0:
            loggedInUserType = -10;
            cout << "Thank you for using system;" << endl;
            break;

        default:
            cout << "Invalid choice!!!";
            break;
        }

        if (loggedInUserType == 1) // administrator
        {
            do
            {
                cout << endl;
                cout << "Choose the desired option\n";
                cout << left << setw(20) << "\tQuestions"
                     << setw(15) << "1. Add"
                     << setw(15) << "2. Delete"
                     << setw(15) << "3. Update"
                     << setw(15) << "4. List";
                cout << endl;

                cout << setw(20) << "\tUsers"
                     << setw(15) << "5. Register"
                     << setw(15) << "6. Edit"
                     << setw(15) << "7. Delete"
                     << setw(15) << "8. List"
                     << endl;

                cout << left << setw(20) << "\t"
                     << setw(15) << "9. View Scores"
                     << setw(15) << " "
                     << setw(15) << "0. Logout";
                cout << endl;

                cout.unsetf(ios::left);
                cout.unsetf(ios::right);

                cout << "\tChoose an option: ";
                cin >> input;

                switch (input)
                {
                case 1:
                    addQuestion(); // calls the addQuestion function
                    break;
                case 2:
                    deleteQuestion(); // delete the question
                    break;
                case 3:
                {
                    int question; // update the previous question
                    listQuestion();
                    cout << "Select the question ID (Q.I) to update question: ";
                    cin >> question;
                    updateQuestion(question - 1);
                }
                break;
                case 4:
                    listQuestion(); // display list of all questions
                    break;
                case 5:
                {
                    string a, b;
                    if (i < 5)
                    {
                        cout << "Enter Username: ";
                        cin >> a;
                        cout << "Enter Password: ";
                        cin >> b;
                        i++;
                        registerUser(a, b); // register new students
                        cout << endl
                             << "User Registered Successfully!" << endl;
                    }
                    else
                        cout << endl
                             << "Maximum user account is already created." << endl;
                }
                break;
                case 6:
                {
                    string updateUsername, newUsername, newPassword;
                    cout << "Enter the username to update/edit: ";
                    cin >> updateUsername;
                    for (int i = 0; i < usize; i++)
                    {
                        if (updateUsername == username[i])
                        {
                            cout << "Enter the updated Username: ";
                            cin >> newUsername;
                            cout << "Enter the updated Password: ";
                            cin >> newPassword;
                            updateUser(updateUsername, newUsername, newPassword); // update student details
                            cout << "User updated Successfully! " << endl;
                            break;
                        }
                        if (i == 4)
                        {
                            cout << "Wrong Username Entered!\nEnter the username to edit/update ";
                            cout << " (or) press 0 to move back: ";
                            cin >> updateUsername;
                            if (updateUsername == "0")
                            {
                                break;
                            }
                            i = -1;
                        }
                    }
                }
                break;
                case 7:
                {
                    string deleteUsername;
                    cout << "Enter the username to delete: ";
                    cin >> deleteUsername;
                    for (int i = 0; i < usize; i++)
                    {
                        if (deleteUsername == username[i])
                        {
                            deleteUser(deleteUsername); // delete previous student
                            cout << "User deleted Successfully! " << endl;
                            break;
                        }
                        if (i == 4)
                        {
                            cout << "Wrong Username Entered!\nEnter the username to delete ";
                            cout << " (or) press 0 to move back: ";
                            cin >> deleteUsername;
                            if (deleteUsername == "0")
                            {
                                break;
                            }
                            i = -1;
                        }
                    }
                }
                break;
                case 8:
                    listStudents(); // display student records
                    break;
                case 9:
                    adminResult(); // display all student result
                    break;
                case 0:
                    cout << "Administrator is logged out" << endl;
                    break;

                default:
                    cout << "Invalid choice!!!";
                    break;
                }
            } while (input != 0);
            input = -1; // this statment is to make sure that do not exit from outer loop
        }
        else if (loggedInUserType == 2) // user
        {
            cout << endl;
            cout << "Choose the desired option\n";
            cout << left << setw(10) << "\t"
                 << setw(25) << "1. Attempt Quiz"
                 << setw(25) << "2. View Score"
                 << setw(25) << "0. Logout";
            cout << endl;

            cout.unsetf(ios::left);
            cout.unsetf(ios::right);

            cout << "\tChoose an option: ";
            cin >> input;

            do
            {
                switch (input)
                {

                case 1:
                    attemptQuiz(user); // allow particular user to take quiz
                    break;
                case 2:
                    result(user); // allow particular user to see its quiz result
                    break;

                case 0:
                    cout << "You are logged out" << endl;
                    break;

                default:
                    cout << "Invalid choice!!!";
                    break;
                }

                cout << endl;
                cout << "Choose the desired option\n";
                cout << left << setw(10) << "\t"
                     << setw(25) << "1. Attempt Quiz"
                     << setw(25) << "2. View Score"
                     << setw(25) << "0. Logout";
                cout << endl;

                cout.unsetf(ios::left);
                cout.unsetf(ios::right);

                cout << "\tChoose an option: ";
                cin >> input;

            } while (input != 0);
            input = -1; // this statment is to make sure that do not exit from outer loop
        }
        else if (loggedInUserType == -1)
        {
            cout << "You have entered invalid Credentials!!!" << endl;
        }
    } while (input != 0);

    return 0;
}

void loadData()
{
    ifstream inf1("UserList.csv");
    string line1, field1;
    vector<vector<string>> array1;
    vector<string> v1;
    string usr = "user";
    while (getline(inf1, line1))
    {
        v1.clear();
        stringstream ss(line1);
        while (getline(ss, field1, ','))
        {
            v1.push_back(field1);
        }
        array1.push_back(v1);
    }
    for (size_t i = 1; i < array1.size(); ++i)
    {
        uflag[i] = true;
        username[i] = array1[i][0];
        passwords[i] = array1[i][1];
    }
    inf1.close();

    ifstream in("QuesionsList.csv");
    string line, field;
    vector<vector<string>> array;
    vector<string> v;

    while (getline(in, line))
    {
        v.clear();
        stringstream ss(line);
        while (getline(ss, field, ','))
        {
            v.push_back(field);
        }
        array.push_back(v);
    }
    for (size_t i = 1; i < array.size(); ++i)
    {
        qflag[i] = true;
        question[i] = array[i][0];
        option1[i] = array[i][1];
        option2[i] = array[i][2];
        option3[i] = array[i][3];
        option4[i] = array[i][4];
        correctOption[i] = array[i][5];
    }
    in.close();
}
