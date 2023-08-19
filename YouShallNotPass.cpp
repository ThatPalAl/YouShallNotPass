#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int shift_passwords = 26486;

struct OnePassword {
    string name;
    string password;
    string login;
    string category;
};

class category {
public:
    category(const std::string& category_name) : name(category_name) {}

    std::string name;
};

/**
 * Declaration of all functions.
 */
void checkIfFileOpen(string &myFile);
void encryptPasswords(string &myFile);
void decryptPasswords(string &my_file);
void printMenu();
void printPasswordVector(vector<vector<string> > &passwords_in_vector);
void errorMessage();
void vectorToFile(vector<vector<string> > &password_vector, string myFilePath);
bool checkPasswordLength(string &new_password);
bool checkUppercaseOccurrence(string &new_password);
bool checkNumberOccurrence(string &new_password);

void sortPasswordByName2(vector<vector<string> > &password_vector);


int main() {
    /**
     * main_condition is a determinant whether the whole program will be able to start over, it's used in a main
     * while loop which drives the whole application.
     *
     * Before checking the MasterPassword - which allows user to protect all the passwords, we are declaring a path
     * to the file with passwords.
     *
     * The .txt used is supposed to have every password in a different row, every row is supposed to have 4 words,
     * one word is one type of data (Name, password, login or category), the white space (just one) between every word
     * is a determinant of the end of previous data and start of another one. For the best practice and in order to
     * let the program work efficiently, user should use Name category with a uppercase letter at the beginning.
     * If there is a will to connect more words as a input for one of the 4 data types, user should connect them so that
     * the wouldn't be separated from each other.
     *
     * Encrypting and decrypting is not at a stage that the development team wanted it to be, its able to encrypt and
     * decrypt the file, using the constant int variable declared at the beginning, the file is being decrypted,
     * every time someone exits the program (by using the NO answer after being questioned, whether the user wants
     * to continue), the file being encrypted when entering the program and all the encrypted data will be transferred
     * to the .txt file that is just temporarily for use. After finishing the program, by choosing no more operations
     * to be done- the .txt file will be override with no text and the process of getting the new information from our
     * file will need to be done from the start.
     */
    bool main_condition = true;
/**
 * the main path is leading to the hasla1 file without extension, its supposed to contain useless encrypted data,
 * after passing it as an arugment of the encryptPasswords function, it will take the main path as a instream and
 * shift the information inside by 26486 bits and then put this information into ofstream that sends it to same file
 * but with a .txt extensions, so its a different file.
 * Path already declared here:
 */

    string myFilePath = "/Users/aorgan/Documents/PJATK/Sem3/PJC/hasla1.txt";
//    encryptPasswords(myFilePath);
    ifstream myFile(myFilePath);

    /**
     * To input a path :
     */
//    string myFilePath;
//    cin >> myFilePath;
//    ifstream myFile(myFilePath+".txt");

    checkIfFileOpen(myFilePath);

    //declaring the master password - write a function to change it.
    string master_password = "Admin123";
    string master_password_entry;

    cout << "Welcome to 'You Shall Not Pass' password manager, please enter you master password to enter the vault: \n";
    cin >> master_password_entry;

    if (master_password_entry == master_password) {
        /**
         * password_in_vector is the 2 dimensional variable that will store the .txt content in order to make
         * all the operations on the passwords or other data much easier. Right after the master password is provided,
         * we check whether is correct and we can begin by transferring all the data to row and columns in the vector.
         *
         */
        vector<vector<string> > passwords_in_vector;
        string line;
        while (getline(myFile, line)) {
            vector<string> row;
            string word = "";
            for (int i = 0; i < line.size(); i++) {
                if (line[i] != ' ') {
                    word += line[i];
                } else if (word.size() > 0) {
                    row.push_back(word);
                    word = "";
                }
            }
            if (word.size() > 0) {
                row.push_back(word);
            }
            passwords_in_vector.push_back(row);
        }

        cout << "You have successfully enetered the key to open all your password" << endl;

        vector<category> categories;
        categories.push_back(category("Mail"));
        categories.push_back(category("SocialMedia"));
        categories.push_back(category("Work"));
        categories.push_back(category("Business"));
        categories.push_back(category("Health"));
        categories.push_back(category("Forum"));
        categories.push_back(category("Personal"));
        categories.push_back(category("Entertainment"));
        categories.push_back(category("Shopping"));
        categories.push_back(category("Holidays"));
        for (int i = 0; i < 10; i++) {
            categories.push_back(category("-"));
        }

        while (main_condition) {
            vector<category> categories;
             printMenu();

                int choice;
                cin >> choice;
                switch (choice) {
                    /**
                     * Search by password- which is revoked by entering the 1 number as a 1st choice from the main menu,
                     * is letting the user to find and return any results for 1. the name he provides, 2. login he
                     * provides or 3. Category he provides. Every occurrence in the .txt file will be returned so that
                     * the user can find the lost password if he's got a name of the password, has a login or
                     * remembers the category.
                     */
                    case 1: {
                        //search for a password
                        cout << "Search for a password by: \n 1.Name \n 2.Login \n 3.Category \n";
                        int search_choice;
                        cin >> search_choice;
                        if (search_choice == 1) {
                            cout << "Searching by name of the password, one result for each name." << endl;
                            string searchByName;
                            cin >> searchByName;
                            int counter = 0;
                            for (int i = 0; i < passwords_in_vector.size(); i++) {
                                if (searchByName == passwords_in_vector[i][0]) {
                                    counter++;
                                    cout << counter << ". ";
                                    cout << "Password for " + searchByName + " is: \n";
                                    cout << passwords_in_vector[i][1] << endl;
                                    cout << "Enter it to login to your account." << endl;
                                }
                            }

                        } else if (search_choice == 2) {
                            cout << "Searching by login, there might be multiple results, providing you with";
                            cout << "name and category also" << endl;
                            string searchByLogin;
                            cin >> searchByLogin;
                            int counter = 0;
                            for (int i = 0; i < passwords_in_vector.size(); i++) {
                                if (searchByLogin == passwords_in_vector[i][2]) {
                                    counter++;
                                    cout << counter << ". ";
                                    cout << "Name: " << passwords_in_vector[i][0];
                                    cout << ", Category: " << passwords_in_vector[i][3];
                                    cout << " and the Password/Passwords for is: \n";
                                    cout << passwords_in_vector[i][1] << endl;
                                }
                            }
                        } else if (search_choice == 3) {
                            cout << "Searching by category, there might be multiple results, providing you with all";
                            cout << " matching results for Category";
                            string searchByCategory;
                            cin >> searchByCategory;
                            int counter = 0;
                            for (auto &i: passwords_in_vector) {
                                if (searchByCategory == i[3]) {
                                    counter++;
                                    cout << counter << ". ";
                                    cout << "Name: " << i[0];
                                    cout << ", Login: " << i[2];
                                    cout << "and the Password/Passwords for is: \n";
                                    cout << i[1] << endl;
                                }
                            }
                        } else {
                            errorMessage();
                        }
                        break;
                    }
                    /**
                     * Case 2 is adding a password, after providing the data (Name, password, login, and choosing a
                     * category), these data will be send straight to the .txt file after restarting the app, user
                     * will always be able to get back to this data.
                     */
                    case 2: {
                        string entry_name;
                        string entry_password;
                        string entry_login;
                        string entry_category;

                        cout << "Add a new password \n";

                        cout << "Enter the name of the password(Twitter, Youtube, Mailwp etc.): ";
                        cin >> entry_name;

                        cout << "\nEnter the password itself: ";
                        cin >> entry_password;

                        cout << "\nEnter the login of the password: ";
                        cin >> entry_login;

                        cout << "\nChoose which category you want to assign to this password." << endl;
                        int index_add_category;
                        string choice_of_category;
                        for (int i = 0; i < categories.size(); i++) {
                            if (categories.at(i).name != "-") {
                                cout << i + 1 << ". " << categories.at(i).name << endl;
                            }
                        }
                        cout << "Here are all available categories - enter the number to choose one of them." << endl;

                        while (true) {
                            cout << "Enter the number (1-20) to choose the category" << endl;
                            cin >> index_add_category;
                            if (index_add_category >= 1 && index_add_category <= 20) {
                                break;
                            } else {
                                errorMessage();
                            }
                        }

                        std::ofstream streamOut(myFilePath, std::ios::app);

                        std::string s1 = entry_name;
                        std::string s2 = entry_password;
                        std::string s3 = entry_login;
                        std::string s4 = categories.at(index_add_category - 1).name;


                        streamOut << "\n" << s1 << " " << s2 << " " << s3 << " " << s4;
                        break;
                    }
                    /**
                     * Editing password is a functionality that allows user to pick from all the passwords that are
                     * printed out, the one that he wants to change. Ideally and in this scenario it is done by
                     * entering the 'Name' of the password as its the easiest ways to differ every data password.
                     * Password that will be set up needs to fulfil following rules:
                     * -needs to be at least 8 characters long
                     * -needs to have at least 1 uppercase letter
                     * -needs to have at least 1 number
                     * with completing all these points, adding a password will be completed and it will be updated
                     * in the txt file after the program is run again.
                     */
                    case 3: {
                        string password_to_change;
                        int index_password_to_change;
                        string new_password_edit;

                        printPasswordVector(passwords_in_vector);
                        cout << "Which password do you want to change? Enter the name:\n";
                        cin >> password_to_change;

                        for(int i = 0; i < passwords_in_vector.size(); i++){
                            if(passwords_in_vector[i][0] == password_to_change){
                                size_t size = passwords_in_vector.size();
                                index_password_to_change = i;
                                bool conditions = true;
                                cout << "Enter the new password for " << password_to_change << " : \n";
                                while(conditions){
                                    cin >> new_password_edit;
                                    if (checkNumberOccurrence(new_password_edit)
                                            && checkPasswordLength(new_password_edit)
                                            && checkUppercaseOccurrence(new_password_edit))
                                    {
                                            conditions = false;
                                    }
                                    else {
                                        cout << "Wrong password, please try again, remember that the password";
                                        cout << " you provide, must: " << endl;
                                        cout << "-Have at least 8 characters" << endl;
                                        cout << "-Have at least 1 upper letter" << endl;
                                        cout << "-Have at least 1 number" << endl;
                                    }
                                }
                                passwords_in_vector[i][1] = new_password_edit;
                                break;
                            }
                            else if(i == passwords_in_vector.size()){
                                cout << "No such Name, try that again" << endl;
                                break;
                            }
                        }
                        std::ofstream streamOut(myFilePath, std::ios::out);
                        for(int i = 0; i < passwords_in_vector.size(); i++) {
                           streamOut << passwords_in_vector[i][0] << " "
                                     << passwords_in_vector[i][1] << " "
                                     << passwords_in_vector[i][2] << " "
                                     << passwords_in_vector[i][3] << " \n";
                        }
                        break;
                    }
                    case 4: {
                        /**
                         * Delete password is a functionality that allows user to choose what will be the filter to
                         * delete the passwords by. If its the Name - then one specific password wil be deleted (as
                         * every password should have a unique name). If the password will be deleted by login -
                         * this functionality should delete all the passwords with this login used. Same logic applies
                         * to deleting the passwords by Category, every row within the .txt file, which contains
                         * such a Category or login should be deleted and replaced with the last row so that,
                         * the password file will not have any blank rows. If user chooses to delete the last password,
                         * which is on the last row, it should be replaced by "" empty string so that no changes are
                         * applied to the .txt apart from this row.
                         */
                        int delete_by_choice;
                        bool number_condition = true;
                        bool delete_number_value;

                        printPasswordVector(passwords_in_vector);

                        cout << "Select the password you want to delete." << endl;
                        while(number_condition){
                            cout << "Delete by 1. Name 2. Login  3. Category " << endl;
                            cin >> delete_by_choice;
                            if (delete_by_choice < 1 || delete_by_choice > 3) {
                                errorMessage();
                            }
                            else{
                                number_condition = false;
                                continue;
                            }
                        }
                        if(delete_by_choice == 1){
                            size_t size = passwords_in_vector.size();
                            int counter = 1;
                            string delete_password_by_name;
                            cout << "Enter the NAME of the password you want to delete: " << endl;
                            cin >> delete_password_by_name;
                            for(int i = 0; i < passwords_in_vector.size(); i++){
                                if(i == size - 1){
                                    passwords_in_vector[i][0] = "";
                                    passwords_in_vector[i][1] = "";
                                    passwords_in_vector[i][2] = "";
                                    passwords_in_vector[i][3] = "";
                                    break; // just one password at the end
                                }
                                if(delete_password_by_name == passwords_in_vector[i][0]){
                                    passwords_in_vector[i][0] = passwords_in_vector[size - counter][0];
                                    passwords_in_vector[i][1] = passwords_in_vector[size - counter][1];
                                    passwords_in_vector[i][2] = passwords_in_vector[size - counter][2];
                                    passwords_in_vector[i][3] = passwords_in_vector[size - counter][3];

                                    vectorToFile(passwords_in_vector, myFilePath);
                                    counter++; //if multiple passwords are supposed to be deleted, we have to replace it
                                    //with the last position, then the one before etc.
                                }
                            }
                            cout << "All passwords with name: " << delete_password_by_name << " have been deleted\n";
                        }
                        else if(delete_by_choice == 2){
                            size_t size = passwords_in_vector.size();
                            int counter = 1;
                            string delete_password_by_login;
                            cout << "Enter the login of the password/passwords you want to delete, be careful! This";
                            cout << " operation might delete MULTIPLE passwords" << endl;
                            cin >> delete_password_by_login;
                            for(int i = 0; i < passwords_in_vector.size(); i++){
                                if(delete_password_by_login == passwords_in_vector[i][2]){
                                    if(i == size - 1){
                                        passwords_in_vector[i][0] = "";
                                        passwords_in_vector[i][1] = "";
                                        passwords_in_vector[i][2] = "";
                                        passwords_in_vector[i][3] = "";
                                        break;
                                    }
                                    else {
                                        passwords_in_vector[i][0] = passwords_in_vector[size - counter][0];
                                        passwords_in_vector[i][1] = passwords_in_vector[size - counter][1];
                                        passwords_in_vector[i][2] = passwords_in_vector[size - counter][2];
                                        passwords_in_vector[i][3] = passwords_in_vector[size - counter][3];

                                        vectorToFile(passwords_in_vector, myFilePath);
                                        counter++;
                                    }
                                }
                            }

                        }
                        else if(delete_by_choice == 3){
                            size_t size = passwords_in_vector.size();
                            int counter = 1;
                            string delete_password_by_category;
                            cout << "Enter the category by which you want to delete password/passwords, ";
                            cout << "be careful, this operation might delete MULTIPLE passwords." << endl;
                            cin >> delete_password_by_category;
                            for(int i = 0; i < passwords_in_vector.size(); i++){
                                if(delete_password_by_category == passwords_in_vector[i][3]){
                                if(size - 1 == i){
                                    passwords_in_vector[i][0] = "";
                                    passwords_in_vector[i][1] = "";
                                    passwords_in_vector[i][2] = "";
                                    passwords_in_vector[i][3] = "";
                                    break;
                                }
                                else{
                                    passwords_in_vector[i][0] = passwords_in_vector[size - counter][0];
                                    passwords_in_vector[i][1] = passwords_in_vector[size - counter][1];
                                    passwords_in_vector[i][2] = passwords_in_vector[size - counter][2];
                                    passwords_in_vector[i][3] = passwords_in_vector[size - counter][3];

                                    vectorToFile(passwords_in_vector, myFilePath);
                                    counter++;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case 5: {
                        /**
                         * Categories are located in a different vector, so that the user can choose which one will be
                         * assigned to his password, he shouldn't enter them manually, there are 10 default categories,
                         * stored in the vector, user can add and delete categories but there is a limit of 20.
                         *
                         */
                        int first_blank_index;
                        string new_category;
                        for (int i = 0; i < 20; i++) {
                            if (categories.at(i).name == "-") {
                                first_blank_index = i;
                                cout << "You have " << first_blank_index - 1
                                     << " categories used, remember you have a limit of 20";
                                cout << "\n In order to add a new category provide the name here: " << endl;
                                cin >> new_category;
                                categories.at(first_blank_index).name = new_category;
                                break;
                            } else {
                                cout<< "Sorry, there is no more space, to add a new category, delete one first";
                                cout << endl;
                            }
                        }
                    }
                    case 6: {
                        int category_to_delete;
                        for (int i = 0; i < categories.size(); i++) {
                            cout << i + 1 << ". " << categories.at(i).name << " " << endl;
                        }
                        cout << "Enter the number (1 - 20) of the category you want to delete: ";
                        cin >> category_to_delete;
                        if (category_to_delete > 20 || category_to_delete < 1) {
                            cout << "Wrong number, try that agian";
                        } else {
                            categories.at(category_to_delete - 1).name = "-";
                        }
                        break;
                    }
                    /**
                     This functionality allows to sort all the password in the txt file by Name in alphabetical order.

                     */
                    case 7: {
                        sortPasswordByName2(passwords_in_vector);
                        printPasswordVector(passwords_in_vector);
                        cout << " ----------" << endl;
                        std::ofstream streamOut(myFilePath, std::ios::out);
                        for (int i = 0; i < passwords_in_vector.size(); i++) {
                            streamOut << passwords_in_vector[i][0] << " "
                                      << passwords_in_vector[i][1] << " "
                                      << passwords_in_vector[i][2] << " "
                                      << passwords_in_vector[i][3] << " \n";
                        }
                        break;
                    }
                    default: {
                        errorMessage();
                        break;
                    }
                }
                /**
                 * This code at the end of the while loop, allows user to make a decision after running one of the
                 * fucntionalities above, the question is whether he want to continue with any action in the
                 * password manager, there is a value of 1 which will be understandable as a will to continue with the
                 * program, a value of 2 wchich will be exiting the program, any other output will not aprooved.
                 */
            int main_condition_answer;
            bool sub_condition_answer = true;
            while(sub_condition_answer){
                cout << "Do you want to continue? Enter 1 - if yes and 2 - if no. \n";
                cin >> main_condition_answer;
                if(main_condition_answer == 1){
                    sub_condition_answer = false;
                    main_condition = true;
                }
                else if(main_condition_answer == 2){
                    main_condition = false;
                    /**
                     * Decrypting the file that we have been using, after finishing the operations the .txt file that
                     * was encrypted is override with a blank text (truncated)
                     */
                    ofstream my_decrypted_file(myFilePath, std::ios::trunc);
                    decryptPasswords(myFilePath);
                    cout << "Exiting the program... Goodbye!" << endl;

                    break;
                }
                else{
                    errorMessage();
                }
            }
        }
    }

    else {
        cout << "Wrong password, try again." << endl;
    }
}

/**
 * Function that checks, whether our .txt file is open and we can operate on it.
 * @param myFile
 */
void checkIfFileOpen(string &myFile){
    ifstream file(myFile);
    string line;
    if(file.is_open()){
        while(getline(file, line)){
            cout << line << endl;

        }
        file.close();
    }
    else{
        cout << "Unable to open file: " << myFile << endl;
    }
}

void encryptPasswords(string &my_file) {
    ifstream input_file(my_file);
    ofstream output_file(my_file +".txt");

    char c;
    while (input_file.get(c)) {
        output_file.put(c ^ shift_passwords);
    }

    input_file.close();
    output_file.close();
}

void decryptPasswords(string &my_file) {
    ifstream input_file(my_file);
    ofstream output_file(my_file.substr(0, my_file.length() - 4));

    char c;
    while (input_file.get(c)) {
        output_file.put(c ^ shift_passwords);
    }

    input_file.close();
    output_file.close();
}



/**
 * Function provided at the beginning of the program as we want to print out all the options every time user enters or
 * restarts the app.
 */
void printMenu(){
    cout << "Please choose one of the options below by using a proper number: " << endl;
    cout << "1. Search for a password." << endl; //working
    cout << "2. Add a new password." << endl; //working
    cout << "3. Edit password." << endl; //done - to check
    cout << "4. Delete password." << endl; //done - to check
    cout << "5. Add a category." << endl; // done but not working
    cout << "6. Delete a category." << endl; //kinda working
    cout << "7. Sort passwords by name" << endl; // to do
}

/**
 * Function that prints all the password that are currently located in the vector, that received the stream, with all
 * passwords from the .txt file.
 * @param passwords_in_vector
 */
void printPasswordVector(vector<vector<string> > &passwords_in_vector){
    for(int i = 0; i < passwords_in_vector.size(); i++){
        for(int j = 0; j < 4; j++){
            cout << passwords_in_vector[i][j] << " ";
        }
        cout << endl;
    }
}
/**
 * Function that is supposed to take a vector with passwords as an argument and sort the 1st column,(which is Name type)
 * in alphabetical order, it uses the sort function, that takes the beginning of the vector and the end of the range,
 * that it wants to sort, it uses a comparison function and determines which element should be ordered first and last.
 * @param password_vector
 */
void sortPasswordByName2(vector<vector<string> > &password_vector){
    sort(password_vector.begin(), password_vector.end());
}

/**
 * Every time we want to transfer, the current data from the vector (that might have some changes), we use the
 * vectorToFile function as it sends the current state and updates the .txt file with any changes.
 * @param password_vector
 * @param myFilePath
 */
void vectorToFile(vector<vector<string> > &password_vector, string myFilePath){
    std::ofstream streamOut(myFilePath, std::ios::out);
    for(int i = 0; i < password_vector.size(); i++) {
        streamOut << password_vector[i][0] << " "
                  << password_vector[i][1] << " "
                  << password_vector[i][2] << " "
                  << password_vector[i][3] << " \n";
        }
}
/**
 * Three function below are supposed to simplify the code in the edit or add password functionalities. They are
 * checking the 3 conditions to add a new password - length, big letter, number occurrence.
 * @param new_password
 * @return
 */
bool checkPasswordLength(string &new_password){
    if(new_password.length() < 8){
        return false;
    }
    else{
        return true;
    }
}

bool checkUppercaseOccurrence(string &new_password){
    int counter = 0;
    for(char c : new_password){
        if (c >= 'A' && c <= 'Z'){
            counter++;
        }
    }
    if(counter < 1){
        return false;
    }
    else{
        return true;
    }
}

bool checkNumberOccurrence(string &new_password){
    int counter = 0;
    for(char c : new_password){
        if(c >= '0' && c <= '9'){
            counter++;
        }
    }
    if(counter < 1){
        return false;
    }
    else{
        return true;
    }
}

void errorMessage(){
    cout << "Wrong input, try again" << endl;
}