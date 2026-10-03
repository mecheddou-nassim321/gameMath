#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum questionLevel { Easy = 1, Med = 2, Hard = 3, MixQ = 4 };
enum operationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };
struct stquestion {
    short number1;
    short number2;
    questionLevel livelQuestion;
    operationType optype;
    int correct_answer = 0;
    bool result_answer = false;
    int player_Answer = 0;
};
struct stquizz {
    stquestion questionList[100];
    short numberOfquestion = 0;
    questionLevel level;
    operationType op;
    short theRightAnswer = 0;
    short theWrongAnswer = 0;
    bool ispass = false;
};
string getOperation(operationType op) {
    switch (op) {
    case operationType::Add:
        return "+";
    case operationType::Sub:
        return "-";
    case operationType::Mul:

        return "*";
    case operationType::Div:
        return "/";
    default:
        return "Mix";


    }

}

int RandomNumber(int From, int To) {
    int randNum = rand() % (To - From + 1) + From; return randNum;
}

questionLevel readQuestionLevel() {
    int reponse;
    cout << "enter your Level question 1:[Easy] ,2:[Med],3:[Hard],4:[Mix]" << endl;
    cin >> reponse;
    return (questionLevel)reponse;
}
operationType readoperation() {
    int numbreOp;
    cout << "enter your operation type 1:[Add],2:[Sub],3:[Mul],4:[Div],5:[Mix]" << endl;
    cin >> numbreOp;
    return (operationType)numbreOp;
}
operationType getoperationType() {
    return (operationType)RandomNumber(1, 4);
}
string getLevel(questionLevel level) {
    string array[4] = { "Easy","Med","Hard","Mix" };
    return array[level - 1];


}
void SetScreenColor(bool right) {
    if (right) {
        system("color 2F");
    }
    else {
        system("color 4F");
    }
}
void printQuestion(stquizz& Quizz, short question_number) {
    cout << "question[" << question_number + 1 << "]" << Quizz.numberOfquestion << "\n";
    cout << Quizz.questionList[question_number].number1 << endl;
    cout << getOperation(Quizz.questionList[question_number].optype);
    cout << Quizz.questionList[question_number].number2 << " ";

    cout << "-------------------\n";


}
void correctTheQuestionAnswer(stquizz& Quizz, short nombreOfQuestion) {
    if (Quizz.questionList[nombreOfQuestion].player_Answer != Quizz.questionList[nombreOfQuestion].correct_answer) {
        Quizz.questionList[nombreOfQuestion].result_answer = false;
        Quizz.theWrongAnswer++;
        cout << "this right answer is" << endl;
        cout << Quizz.questionList[nombreOfQuestion].correct_answer;
        cout << "\n";

    }
    else {
        Quizz.questionList[nombreOfQuestion].result_answer = true;
        Quizz.theRightAnswer++;

    }
    SetScreenColor(Quizz.questionList[nombreOfQuestion].result_answer);

}
int readAnswer() {
    int answer;
    cin >> answer;
    return answer;
}
int simpleClculator(int number1, int number2, operationType op) {
    switch (op) {
    case operationType::Add:
        return number1 + number2;
    case operationType::Sub:
        return number1 - number2;
    case operationType::Mul:
        return number1 * number2;
    case operationType::Div:
        return number1 / number2;
    default:
        return number1 + number2;
    }

}
stquestion genratorQuestion(questionLevel level, operationType op) {
    stquestion question;
    if (level == questionLevel::MixQ)
    {
        level = (questionLevel)RandomNumber(1, 3);
    }

    if (op == operationType::MixOp) {
        op = (operationType)getoperationType();
    }
    question.optype = op;
    switch (level) {
    case questionLevel::Easy:
        question.number1 = RandomNumber(1, 10);
        question.number2 = RandomNumber(1, 10);
        question.correct_answer = simpleClculator(question.number1, question.number2, op);
        question.livelQuestion = level;
        return question;
    case questionLevel::Med:
        question.number1 = RandomNumber(20, 50);
        question.number2 = RandomNumber(20, 50);
        question.correct_answer = simpleClculator(question.number1, question.number2, op);
        question.livelQuestion = level;
        return question;
    case questionLevel::Hard:
        question.number1 = RandomNumber(50, 100);
        question.number2 = RandomNumber(50, 100);
        question.correct_answer = simpleClculator(question.number1, question.number2, op);
        question.livelQuestion = level;
        return question;
    case questionLevel::MixQ:
        question.number1 = RandomNumber(1, 100);
        question.number2 = RandomNumber(1, 100);
        question.correct_answer = simpleClculator(question.number1, question.number2, op);
        question.livelQuestion = level;
        return question;

    }

    return question;

}

void askandCorrectListAnswer(stquizz& Quizz) {
    for (short question = 0; question < Quizz.numberOfquestion; question++) {
        printQuestion(Quizz, question);
        cout << "Votre réponse : ";  // Ajoutez cette ligne
        Quizz.questionList[question].player_Answer = readAnswer();
        correctTheQuestionAnswer(Quizz, question);
    }
    Quizz.ispass = (Quizz.theRightAnswer >= Quizz.theWrongAnswer);
}
void generateQuizQuestions(stquizz& Quizz) {
    for (short question = 0; question < Quizz.numberOfquestion; question++) {
        Quizz.questionList[question] = genratorQuestion(Quizz.level, Quizz.op);
    }
}
string GetFinalResultsText(bool Pass) {
    if (Pass) return"PASS :-)";
    else
        return"Fail :-(";
}
void printQuizzResult(stquizz Quizz) {
    cout << "------------------------------------------------------------------\n";
    cout << "Finale result" << GetFinalResultsText(Quizz.ispass) << endl;
    cout << "level of quizz" << getLevel(Quizz.level) << endl;
    cout << "type of operation " << getOperation(Quizz.op);
    cout << "nombre of right answer:" << Quizz.theRightAnswer << endl;
    cout << "nombre of the wrong answer" << Quizz.theWrongAnswer << endl;
    cout << "______________________________\n";

}
short readHowManyQuestion() {
    int number = 1;
    do {
        cout << "how do you want to answer" << endl;
        cin >> number;
    } while (number < 1 || number>10);
    return number;
}
void playMath() {
    stquizz Quizz;
    Quizz.numberOfquestion = readHowManyQuestion();
    Quizz.level = readQuestionLevel();
    Quizz.op = readoperation();
    generateQuizQuestions(Quizz);
    askandCorrectListAnswer(Quizz);
    printQuizzResult(Quizz);

}
void setScreent() {
    system("cls");
    system("color 0F");

}
void startMath() {
    string reponse = "Y";
    do {
        setScreent();
        playMath();
        cout << "do you want cheak another answer" << endl;
        cin >> reponse;

    } while (reponse == "Y" || reponse == "y");
}




int main() {
    srand((unsigned)time(NULL));
    /* questionLevel chosenLevel = choisequestionLevel();
     operationType chosenOperation = choiseoperationtype();
     generateRandomNumber(numberOfquestion(), chosenLevel, chosenOperation);*/
    startMath();


    return 0;
}