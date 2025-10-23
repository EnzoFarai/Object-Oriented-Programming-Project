#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;

// ============================================================================
// BASE CLASS - Demonstrates Polymorphism
// ============================================================================
class Question {
protected:
    string questionText;
    vector<string> options;
    int correctAnswer;
    string explanation;
    bool isAnswered;
    int userAnswer;

public:
    Question(string text, vector<string> opts, int correct, string explain)
        : questionText(text), options(opts), correctAnswer(correct), 
          explanation(explain), isAnswered(false), userAnswer(-1) {}

    virtual ~Question() {}

    virtual void displayQuestion(int questionNumber) const {
        cout << "\nQ" << questionNumber << ": " << questionText << "\n";
        for (size_t i = 0; i < options.size(); ++i) {
            cout << "  " << char('a' + i) << ") " << options[i] << "\n";
        }
    }

    virtual bool checkAnswer(int answer) {
        userAnswer = answer;
        isAnswered = true;
        return answer == correctAnswer;
    }

    virtual void showExplanation() const {
        cout << "\nExplanation: " << explanation << "\n";
    }

    bool getIsAnswered() const { return isAnswered; }
    int getUserAnswer() const { return userAnswer; }
    int getCorrectAnswer() const { return correctAnswer; }
};

// ============================================================================
// DERIVED CLASS - Demonstrates Polymorphism and Inheritance
// ============================================================================
class TimedQuestion : public Question {
private:
    int timeLimit;

public:
    TimedQuestion(string text, vector<string> opts, int correct, 
                  string explain, int limit)
        : Question(text, opts, correct, explain), timeLimit(limit) {}

    ~TimedQuestion() {}

    void displayQuestion(int questionNumber) const override {
        cout << "\nQ" << questionNumber << " (Time limit: " << timeLimit 
             << "s): " << questionText << "\n";
        for (size_t i = 0; i < options.size(); ++i) {
            cout << "  " << char('a' + i) << ") " << options[i] << "\n";
        }
    }

    int getTimeLimit() const { return timeLimit; }
};

// ============================================================================
// QUIZ MANAGER CLASS - Demonstrates Dynamic Memory Allocation
// ============================================================================
class QuizManager {
private:
    vector<Question*> questions;  // Dynamic memory allocation
    int score;
    int timeElapsed;

public:
    QuizManager() : score(0), timeElapsed(0) {}
    ~QuizManager() {
        for (Question* q : questions) {
            delete q;
        }
        questions.clear();
    }

    void addQuestion(Question* q) {
        questions.push_back(q);
    }

    void runQuiz() {
        cout << "Lesson 1\n";

        auto startTime = chrono::high_resolution_clock::now();

        for (size_t i = 0; i < questions.size(); ++i) {
            questions[i]->displayQuestion(i + 1);

            string input;
            cout << "Your answer (a-d) or 's' to skip: ";
            cin >> input;

            if (input == "s" || input == "S") {
                cout << "Question skipped.\n";
                questions[i]->checkAnswer(-1);
                questions[i]->showExplanation();
            } 
            else if (input.length() == 1 && input[0] >= 'a' && input[0] <= 'd') {
                int answerIndex = input[0] - 'a';
                bool isCorrect = questions[i]->checkAnswer(answerIndex);

                if (isCorrect) {
                    cout << "Correct!\n";
                    score++;
                } else {
                    cout << "Wrong. ";
                }
                questions[i]->showExplanation();
            } 
            else {
                cout << "Invalid input. Please try again.\n";
                i--;  // Repeat this question
                continue;
            }

            cout << "----------------------------------\n";
        }

        auto endTime = chrono::high_resolution_clock::now();
        timeElapsed = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();

        displayResults();
    }

    void displayResults() {
        cout << "\n=============================\n";
        cout << "        Quiz Complete!       \n";
        cout << "=============================\n";
        cout << "Score: " << score << " / " << questions.size() << "\n";
        cout << "Time: " << timeElapsed << " seconds\n";
        cout << "Percentage: " << fixed << setprecision(1) 
             << (score * 100.0 / questions.size()) << "%\n";

        if (score == (int)questions.size()) {
            cout << "Perfect! You're a C++ expert!\n";
        } else if (score >= (int)(questions.size() * 0.75)) {
            cout << "Great job! You understand C++ OOP concepts well.\n";
        } else if (score >= (int)(questions.size() * 0.5)) {
            cout << "Good effort! Review the concepts and try again.\n";
        } else {
            cout << "Keep practicing — C++ concepts will become clearer!\n";
        }
        cout << "=============================\n";
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    QuizManager* quizManager = new QuizManager();

    quizManager->addQuestion(new Question(
        "What was the primary purpose of creating C++?",
        {"To replace the C programming language entirely",
         "To add object orientation to the C programming language",
         "To create a simpler alternative to Java",
         "To improve web development capabilities"},
        1,
        "The prime purpose of C++ programming was to add object orientation to the C programming language."
    ));

    quizManager->addQuestion(new Question(
        "In object-oriented programming, what is an object?",
        {"A programming language feature for memory management",
         "A function that performs operations on data",
         "An instance of a class",
         "A variable that stores multiple values"},
        2,
        "An object is an instance of a class. For example, if 'fruit' is a class, then 'fruit mango;' creates an object 'mango'."
    ));

    quizManager->addQuestion(new Question(
        "What is encapsulation in C++?",
        {"The process of hiding implementation details",
         "Wrapping up of data and functions into a single unit (class)",
         "Creating multiple functions with the same name",
         "The ability of objects to acquire properties of other objects"},
        1,
        "Encapsulation is the wrapping up of data and functions into a single unit (called class)."
    ));

    quizManager->addQuestion(new Question(
        "Which of the following best describes polymorphism in C++?",
        {"The ability to create new classes from existing ones",
         "The process of hiding data from direct access",
         "The ability to take more than one form",
         "The organization of data and functions into objects"},
        2,
        "Polymorphism is the ability to take more than one form. Using a single function name to perform different types of tasks is function overloading."
    ));

    quizManager->addQuestion(new Question(
        "What is the key difference between procedural and object-oriented programming?",
        {"Procedural programming uses classes while OOP uses functions",
         "OOP gives importance to data over functions",
         "Procedural programming supports inheritance while OOP does not",
         "OOP follows a top-down approach while procedural follows bottom-up"},
        1,
        "Procedural programming gives importance to functions over data, while OOP gives importance to data over functions."
    ));

    quizManager->addQuestion(new Question(
        "What does information hiding accomplish in C++?",
        {"It prevents functions from accessing any data",
         "It insulates data from direct access by the program",
         "It hides the source code from users",
         "It encrypts data for security purposes"},
        1,
        "Information hiding insulates data from direct access by the program. Attributes are data members, and functions are member functions."
    ));

    quizManager->addQuestion(new Question(
        "What is inheritance in C++?",
        {"The process of creating multiple objects from a class",
         "The ability to use the same function name for different operations",
         "The process by which objects of one class acquire properties of another class",
         "The organization of classes into hierarchical structures"},
        2,
        "Inheritance is the process by which objects of one class acquire properties of another class."
    ));

    quizManager->addQuestion(new Question(
        "Which of the following is NOT a feature of object-oriented programming?",
        {"Code reusability through inheritance",
         "Data hiding through encapsulation",
         "Virtual classes in procedural programming",
         "Message passing between objects"},
        2,
        "Virtual classes do not exist in procedural programming. They are a feature of OOP."
    ));

    quizManager->addQuestion(new Question(
        "How do objects interact with each other in object-oriented programming?",
        {"Through direct data sharing",
         "By means of message passing",
         "Through global variables",
         "Using external files"},
        1,
        "Objects interact by means of message passing, allowing communication while maintaining encapsulation."
    ));

    quizManager->addQuestion(new Question(
        "What is the relationship between classes and objects?",
        {"Classes are instances of objects",
         "Objects are instances of classes",
         "Classes and objects are the same thing",
         "Objects define classes"},
        1,
        "Objects are instances of classes. A class defines the blueprint, and objects are created from it."
    ));

    quizManager->addQuestion(new Question(
        "Which of the following is an example of procedural programming language?",
        {"C++",
         "Java",
         "Python",
         "C"},
        3,
        "C is an example of a procedural programming language. C++, Java, and Python support OOP."
    ));

    quizManager->addQuestion(new Question(
        "What is the main benefit of inheritance in object-oriented programming?",
        {"It makes programs run faster",
         "It reduces memory usage",
         "It provides code reusability and expandability",
         "It eliminates the need for functions"},
        2,
        "Inheritance provides code reusability and expandability."
    ));

    quizManager->runQuiz();

    delete quizManager;

    return 0;
}
