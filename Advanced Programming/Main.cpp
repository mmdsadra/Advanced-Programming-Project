#include <iostream>
#include <string>

using namespace std;

class Tag;
class Permission;
Permission* permissions[100] = { NULL };
class User;
User* users[100] = { NULL };


struct DateTime {
    int year, month, day, hour, minute, second;
};

class Permission {
    string title;
public:
    Permission(string t) : title(t) {}

    static Permission* create(string t) {
        Permission* tm = new Permission(t);
        return tm;
    }
    void print() {
        cout << title;
    }

    string titleR() {
        return title;
    }
};

class User {
    string username;
    string password;
    Permission* permissions[100] = { NULL };

public:
    string name;
    User(string n, string u, string p) : name(n), username(u), password(p) {}

    static User* create(string n, string u, string p) {
        User* tm = new User(n, u, p);
        int i = 0;
        while (users[i] != NULL) {
            i++;
        }
        users[i] = tm;
        return tm;
    }

    void addPermission(Permission* permission) {
        int i = 0;
        while (permissions[i] != NULL) {
            if (permissions[i] == permission)
                return;
            i++;
        }
        permissions[i] = permission;
    }

    void print() {
        cout << "Name: " << name << endl;
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
        int i = 0;
        cout << "Permissions: " << endl;
        while (permissions[i] != NULL) {
            permissions[i]->print();
            cout << endl;
            i++;
        }
    }

    bool checkAuth(string u, string p) {
        if (username == u && password == p)
            return true;
        return false;
    }

    bool hasPermission(string t) {
        int i = 0;
        while (permissions[i] != NULL)
        {
            if (permissions[i++]->titleR() == t)
                return true;
        }
        return false;
    }
};

class Tag {
    string title;
public:
    Tag(string t) : title(t) {}

    static Tag* create(string t) {
        Tag* tm = new Tag(t);
        int i = 0;
        while (tags[i] != NULL) {
            i++;
        }
        tags[i] = tm;
        return tm;
    }

    static void printAll() {
        int i = 0;
        while (tags[i] != NULL) {
            tags[i]->print();
            cout << endl;
        }
    }

    void print() {
        cout << title;
    }
}*tags[100] = { NULL };

class Question {
protected:
    string question;
    DateTime createdAt;
    User user;
    Tag* tag[100] = { NULL };
    bool isPublished = false;

public:
    string type;

    Question(string q, DateTime ti, User u, string ty) : question(q), createdAt(ti), user(u), type(ty) {}

    void publish() {
        this->isPublished = true;
    }
    void unpublish() {
        this->isPublished = false;
    }

    //prints all detail:
    virtual void print() = 0;

    //prints question and index:
    virtual void printAll() = 0;

    virtual void list() = 0;

    virtual void edit(){}

    void addTag(Tag* t) {
        int i = 0;
        while (tag[i] != NULL) {
            if (tag[i] == t)
                return;
            i++;
        }
        tag[i] = t;
    }
}*questions[100] = { NULL };

class Descriptive : public Question {
    string answer;
public:
    Descriptive(string q, DateTime t, User u) : Question(q, t, u, "descriptive") {}

    void addAnswer(string ans) {
        answer = ans;
    }

    void print() {
        cout << "Question: " << question << endl;
        cout << "Answer: " << answer << endl;
        cout << "Created time: " << createdAt.year << ", " << createdAt.month << ", " << createdAt.day << ", " << createdAt.hour << ", " << createdAt.minute << ", " << createdAt.second << endl;
        user.print();
        if (isPublished)
            cout << "Published" << endl;
        else
            cout << "Not published" << endl;
        int i = 0;
        while (tag[i] != NULL) {
            cout << "Tag " << i << ": ";
            tag[i]->print();
            cout << '\n';
        }
    }

    void printAll() {
        cout << "Question: " << question << endl;
        cout << "Type: " << type << endl;
        int i = 0;
        while (questions[i] != NULL)
            i++;
        cout << "Index: " << i << endl;
    }

    static Descriptive* create(string question, DateTime createdAt, User user) {
        Descriptive* tm = new Descriptive(question, createdAt, user);
        return tm;
    }

    Descriptive* edit(string question, DateTime createdAt, User user) {
        this->question = question;
        this->createdAt = createdAt;
        this->user = user;
        return this;
    }

    void list() {
        int i = 0;
        while (questions[i] != NULL) {
            if (questions[i]->type == "descriptive")
                questions[i]->print();
            i++;
        }
    }
};

class FourChoice : public Question {
    string A, B, C, D;
    char answer;
public:
    FourChoice(string q, DateTime ti, User u, string a, string b, string c, string d, char ans)
        : Question(q, ti, u, "four-choice") {
        A = a;
        B = b;
        C = c;
        D = d;
        answer = ans;
    }

    void print() {
        cout << "Question: " << question << endl;
        cout << "A: " << A << endl;
        cout << "B: " << B << endl;
        cout << "C: " << C << endl;
        cout << "D: " << D << endl;
        cout << "Answer: " << answer << endl;
        cout << "Created time: " << createdAt.year << ", " << createdAt.month << ", " << createdAt.day << ", " << createdAt.hour << ", " << createdAt.minute << ", " << createdAt.second << endl;
        user.print();
        if (isPublished)
            cout << "Published" << endl;
        else
            cout << "Not published" << endl;
        int i = 0;
        while (tag[i] != NULL) {
            cout << "Tag " << i << ": ";
            tag[i]->print();
            cout << '\n';
        }
    }

    void printAll() {
        cout << "Question: " << question << endl;
        cout << "Type: " << type << endl;
        int i = 0;
        while (questions[i] != NULL)
            i++;
        cout << "Index: " << i << endl;
    }

    static FourChoice* create(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer) {
        FourChoice* tm = new FourChoice(question, createdAt, user, A, B, C, D, answer);
        return tm;
    }

    FourChoice* edit(string question, DateTime createdAt, User user, string A, string B, string C, string D, char answer) {
        this->question = question;
        this->createdAt = createdAt;
        this->user = user;
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
        this->answer = answer;
        return this;
    }

    void list() {
        int i = 0;
        while (questions[i] != NULL) {
            if (questions[i]->type == "four-choice")
                questions[i]->print();
            i++;
        }
    }

};

class Auth {
public:
    static User* auth;

    static User* login(string username, string password) {
        int i = 0;
        while (users[i] != NULL) {
            if (users[i]->checkAuth(username, password)) {
                auth = users[i];
                return users[i];
            }
        }
        return NULL;
    }
    static void logout() {
        auth = NULL;
    }

    static User* whoami() {
        auth->print();
    }
};

User* Auth::auth = NULL;

void tagMenu() {
    int choice;
    while (true) {
        cout << "Tag Menu:" << endl;
        cout << "1. Add Tag" << endl;
        cout << "2. View All Tags" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            string title;
            cout << "Enter tag title: ";
            cin >> title;
            Tag::create(title);
            cout << "Tag added successfully!" << endl;
        }
        else if (choice == 2) {
            Tag::printAll();
        }
        else if (choice == 3) {
            break;
        }
    }
}

void userMenu() {
    int choice;
    while (true) {
        cout << "User Menu:" << endl;
        cout << "1. Add User" << endl;
        cout << "2. View All Users" << endl;
        cout << "3. Add Permission to a User" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            if (Auth::auth->hasPermission("add-user"))
            {
                string name, username, password;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                User::create(name, username, password);
                cout << "User added successfully!" << endl;
            }
            else {
                cout << "cant add user. no permission" << endl;
            }
        }
        else if (choice == 2) {
            int i = 0;
            while (users[i] != NULL) {
                users[i]->print();
                cout << endl;
                i++;
            }
        }
        else if (choice == 3) {
            string name, username, password, per;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter Permission: ";
            cin >> per;
            int i = 0;
            while (users[i] != NULL)
            {
                if (users[i]->name == name) {
                    Permission* tmp = new Permission(per);
                    users[i]->addPermission(tmp);
                }
                i++;
            }
            cout << "Permission added" << endl;
        }
        else if (choice == 4) {
            break;
        }
    }
}

void questionMenu() {
    int choice;
    while (true) {
        cout << "Question Menu:" << endl;
        cout << "1. Add Descriptive Question" << endl;
        cout << "2. Add Four-Choice Question" << endl;
        cout << "3. View All Questions" << endl;
        cout << "4. View All Descriptive Questions" << endl;
        cout << "5. View All Four-Choice Questions" << endl;
        cout << "6. Edit Question" << endl;
        cout << "7. Delete Question" << endl;
        cout << "8. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            if (Auth::auth->hasPermission("add-descriptive-question"))
            {

                string question;
                DateTime createdAt;
                User* user = Auth::auth;
                cout << "Enter question: ";
                cin.ignore(); // to ignore the newline character left by cin
                getline(cin, question);
                cout << "Enter created time (year month day hour minute second): ";
                cin >> createdAt.year >> createdAt.month >> createdAt.day >> createdAt.hour >> createdAt.minute >> createdAt.second;
                Descriptive* q = Descriptive::create(question, createdAt, *user);
                int i = 0;
                while (questions[i] != NULL) {
                    i++;
                }
                questions[i] = q;
                cout << "Descriptive Question added successfully!" << endl;
            }
            else
            {
                cout << "cant do this" << endl;
            }
        }
        else if (choice == 2) {
            if (Auth::auth->hasPermission("add-four-choice-question"))
            {
                string question, A, B, C, D;
                char answer;
                DateTime createdAt;
                User* user = Auth::auth;
                cout << "Enter question: ";
                cin.ignore();
                getline(cin, question);
                cout << "Enter option A: ";
                getline(cin, A);
                cout << "Enter option B: ";
                getline(cin, B);
                cout << "Enter option C: ";
                getline(cin, C);
                cout << "Enter option D: ";
                getline(cin, D);
                cout << "Enter answer (A/B/C/D): ";
                cin >> answer;
                cout << "Enter created time (year month day hour minute second): ";
                cin >> createdAt.year >> createdAt.month >> createdAt.day >> createdAt.hour >> createdAt.minute >> createdAt.second;
                FourChoice* q = FourChoice::create(question, createdAt, *user, A, B, C, D, answer);
                int i = 0;
                while (questions[i] != NULL) {
                    i++;
                }
                questions[i] = q;
                cout << "Four-Choice Question added successfully!" << endl;
            }
            else {
                cout << "cant add four choise questions" << endl;
            }
        }
        else if (choice == 3) {
            int i = 0;
            while (questions[i] != NULL) {
                questions[i]->print();
                cout << endl;
                i++;
            }
        }
        else if (choice == 4) {
            cout << "If you need ID enter 1 else enter 0: ";
            int x;
            cin >> x;
            int i = 0;
            if (x)
            {
                while (questions[i] != NULL) {
                    if (questions[i]->type == "descriptive")
                    {
                        questions[i]->print();
                        cout << "ID: " << i << endl;
                    }
                    i++;
                }
            }
            else {
                while (questions[i] != NULL) {
                    if (questions[i]->type == "descriptive")
                    {
                        questions[i]->print();
                        cout << endl;
                    }
                    i++;
                }
            }
        }
        else if (choice == 5) {
            cout << "If you need ID enter 1 else enter 0: ";
            int x;
            cin >> x;
            int i = 0;
            if (x)
            {
                while (questions[i] != NULL) {
                    if (questions[i]->type == "four-choice")
                    {
                        questions[i]->print();
                        cout <<"ID: " << i << endl;
                    }
                    i++;
                }
            }
            else {
                while (questions[i] != NULL) {
                    if (questions[i]->type == "four-choice")
                    {
                        questions[i]->print();
                        cout << endl;
                    }
                    i++;
                }
            }
        }
        else if (choice == 6) {
            int index;
            cout << "Enter question index to edit: ";
            cin >> index;
            if (questions[index]->type == "descriptive") {
                if (Auth::auth->hasPermission("edit-descriptive-question"))
                {
                    string question;
                    DateTime createdAt;
                    User* user = Auth::auth;
                    cout << "Enter new question: ";
                    cin.ignore();
                    getline(cin, question);
                    cout << "Enter new created time (year month day hour minute second): ";
                    cin >> createdAt.year >> createdAt.month >> createdAt.day >> createdAt.hour >> createdAt.minute >> createdAt.second;
                    ((Descriptive*)questions[index])->edit(question, createdAt, *user);
                    cout << "Descriptive Question edited successfully!" << endl;
                }
                else {
                    cout << "cant edit descriptive" << endl;
                }
            }
            else if (questions[index]->type == "four-choice") {
                if (Auth::auth->hasPermission("edit-four-choice-question"))
                {
                    string question, A, B, C, D;
                    char answer;
                    DateTime createdAt;
                    User* user = Auth::auth;
                    cout << "Enter new question: ";
                    cin.ignore();
                    getline(cin, question);
                    cout << "Enter new option A: ";
                    getline(cin, A);
                    cout << "Enter new option B: ";
                    getline(cin, B);
                    cout << "Enter new option C: ";
                    getline(cin, C);
                    cout << "Enter new option D: ";
                    getline(cin, D);
                    cout << "Enter new answer (A/B/C/D): ";
                    cin >> answer;
                    cout << "Enter new created time (year month day hour minute second): ";
                    cin >> createdAt.year >> createdAt.month >> createdAt.day >> createdAt.hour >> createdAt.minute >> createdAt.second;
                    ((FourChoice*)questions[index])->edit(question, createdAt, *user, A, B, C, D, answer);
                    cout << "Four-Choice Question edited successfully!" << endl;
                }
                else {
                    cout << "cant change four choise questions" << endl;
                }
            }
        }
        else if (choice == 7) {
            int index;
            cout << "Enter question index to delete: ";
            cin >> index;
            for (int i = index; questions[i] != NULL; i++) {
                questions[i] = questions[i + 1];
            }
            cout << "Question deleted successfully!" << endl;
        }
        else if (choice == 8) {
            break;
        }
    }
}

void mainMenu() {
    int choice;
    while (true) {
        if (Auth::auth == NULL) {
            cout << "1. Login" << endl;
            cout << "2. View Questions" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            if (choice == 1) {
                string username, password;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                User* user = Auth::login(username, password);
                if (user != NULL) {
                    cout << "Login successful!" << endl;
                }
                else {
                    cout << "Invalid username or password!" << endl;
                }
            }
            else if (choice == 2) {
                int i = 0;
                while (questions[i] != NULL) {
                    questions[i]->print();
                    cout << endl;
                    i++;
                }
            }
            else if (choice == 3) {
                break;
            }
        }
        else {
            cout << "Welcome, " << Auth::auth->name << "!" << endl;
            cout << "1. Questions Menu" << endl;
            cout << "2. Tags Menu" << endl;
            cout << "3. Users Menu" << endl;
            cout << "4. Logout" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            if (choice == 1) {
                questionMenu();
            }
            else if (choice == 2) {
                tagMenu();
            }
            else if (choice == 3) {
                userMenu();
            }
            else if (choice == 4) {
                Auth::logout();
                cout << "Logged out successfully!" << endl;
            }
            else if (choice == 5) {
                break;
            }
        }
    }
}

int main() {
    permissions[0] = Permission::create("add-descriptive-question");
    permissions[1] = Permission::create("add-four-choice-question");
    permissions[2] = Permission::create("edit-descriptive-question");
    permissions[3] = Permission::create("edit-four-choice-question");
    permissions[4] = Permission::create("add-user");
    User::create("Main", "admin", "123456");
    users[0]->addPermission(Permission::create("add-user"));

    mainMenu();

    return 0;
}
