#include <sstream>
#include <cctype>
#include <limits>
#include <cassert>
#include <regex>

namespace TestValidator{
    class Reader {
    private:
        std::istream& is;
        int lineCount;
        int tokenCount;

        int lastChar;
    protected:
        int getLineCount(){
            return lineCount;
        }

        int getTokenCount(){
            return tokenCount;
        }

        int nextChar(){
            int nextChar = is.get();
            if(lastChar == '\n'){
                lineCount++;
                tokenCount = 0;
            }
            if(!isspace(nextChar) && (lastChar == '\n' ||isspace(lastChar))){
                tokenCount++;
            }
            lastChar = nextChar;
            return nextChar;
        }

        int peekChar() {
            return is.peek();
        }
    public:
        Reader(std::istream& _is): is(_is) { 
            lineCount = 0;
            tokenCount = 0;
            lastChar = '\n';
        }

        ~Reader() { }

        bool readChar(char &x){
            if(peekChar() == EOF) 
                return false;
            x = nextChar();
            return true;
        }

        template<class T>
        bool readInteger(T &x){
            bool neg = false;
            T maxAllowed = std::numeric_limits<T>::max();
            if(peekChar() == '-'){
                nextChar();
                if(std::numeric_limits<T>::min() == 0){
                    return false;
                }
                maxAllowed = std::numeric_limits<T>::min();
                neg = true;
            }

            if(!isdigit(peekChar())){
                return false;
            }

            x = 0;
            while(isdigit(peekChar())){
                int d = nextChar()-'0';
                if(neg){
                    d = -d;
                }
                int threshold = (maxAllowed-d)/10;
                if((maxAllowed <= x && x < threshold) || (maxAllowed >= x && x > threshold)){
                    x = 0;
                    return false;
                }
                x = x * 10 + d;
            }
            return true;
        }
    };

    class Validator : protected Reader {
    private:
        std::ostream &os;
    protected:
        
    public:
        Validator(std::istream &is, std::ostream &_os) : Reader(is), os(_os) { }
        ~Validator() { }

        void reportError(std::string msg, std::string defaultMessage = "Undefined"){
            os<<"Line "<<getLineCount()<<", Token "<<getTokenCount()<<std::endl;

            if(msg.empty()) msg = defaultMessage;
            os<<"Error: "<<msg<<std::endl<<std::endl;
            throw "Validation Error";
        }

        /// constraint checkers
        template<class T>
        bool checkNumberIsBetween(T &x, T lowerLimit, T upperLimit, std::string msg = ""){
            if(x < lowerLimit || x > upperLimit){
                reportError(msg, "Number out of bounds");
            }
            return true;
        }

        bool checkCharMatchesClass(char &x, std::string charClass, std::string msg = ""){
            std::string format("%1[");
            format.insert(format.end(), charClass.begin(), charClass.end());
            format.push_back(']');

            char dummy[2] = {x, 0};
            char dummy2[2] = {0, 0};


            if(sscanf(dummy, format.c_str(), dummy2) != 1){
                reportError(msg, "Character doesn't match character class");
            }

            return true;
        }

        bool checkCondition(bool condition, std::string msg = ""){
            if(!condition){
                reportError(msg, "Condition failed");
            }
            return true;
        }

        /// readers
        template<class T>
        bool readInteger(T &x, std::string msg = ""){
            if(!Reader::readInteger(x)){
                reportError(msg, "Integer read failed.");
            }
            return true;
        }

        bool readChar(char &x, std::string msg = ""){
            if(!Reader::readChar(x)){
                reportError(msg, "Character read failed.");
            }
            return true;
        }


        /// readers & constraint checkers
        template<class T>
        bool readIntegerBetween(T &x, T lowerLimit, T upperLimit, std::string msg = ""){
            readInteger(x, msg);
            checkNumberIsBetween(x, lowerLimit, upperLimit, msg);
            return true;
        }

        bool readCharAndMatchClass(char &x, std::string charClass, std::string msg = ""){
            readChar(x, msg);
            checkCharMatchesClass(x, charClass, msg);
            return true;
        }

        bool readSpaceChar(std::string msg = ""){
            if(nextChar() != ' '){
                reportError(msg, "Space read failed.");
            }
            return true;
        }

        bool readEndOfLine(std::string msg = ""){
            if(nextChar() != '\n'){
                reportError(msg, "End of Line read failed.");
            }
            return true;
        }

        bool readEndOfFile(std::string msg = ""){
            if(nextChar() != EOF){
                reportError(msg, "End of File read failed.");
            }
            return true;
        }
    };
}