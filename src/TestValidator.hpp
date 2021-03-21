#include <sstream>
#include <cctype>
#include <limits>
#include <cassert>

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
            else if(!isspace(nextChar) && isspace(lastChar)){
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
            if(peekChar() == '-'){
                nextChar();
                neg = true;
            }
            if(!isdigit(peekChar())){
                return false;
            }

            x = 0;
            while(isdigit(peekChar())){
                int d = nextChar()-'0';
                if(x > (std::numeric_limits<T>::max()-d)/10){
                    x = 0;
                    return false;
                }
                x = x * 10 + d;
            }

            if(neg)
                x = -x;
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

        void reportError(std::string &msg){
            os<<"Line Number: "<<getLineCount()<<std::endl;
            os<<"Token Number at current line: "<<getTokenCount()<<std::endl;
            os<<"Error: "<<msg<<std::endl;
            assert(false);
        }

        bool readCharAndMatch(char &x, char expected, std::string msg = ""){
            if(!readChar(x) || x != expected){
                if(msg.empty())
                    msg = msg + "Character read failed.";
                reportError(msg);
            }
            return true;
        }

        bool readSpaceChar(std::string msg = ""){
            if(nextChar() != ' '){
                if(msg.empty())
                    msg = msg + "Space read failed.";
                reportError(msg);
            }
            return true;
        }

        bool readEndOfLine(std::string msg = ""){
            if(nextChar() != '\n'){
                if(msg.empty())
                    msg = msg + "End of Line read failed.";
                reportError(msg);
            }
            return true;
        }

        bool readEndOfFile(std::string msg = ""){
            if(nextChar() != EOF){
                if(msg.empty())
                    msg = msg + "End of File read failed.";
                reportError(msg);
            }
            return true;
        }

        template<class T>
        bool readIntegerInRange(T &x, T lowerLimit, T upperLimit, std::string msg = ""){
            if(!readInteger(x) || x < lowerLimit || x > upperLimit){
                if(msg.empty())
                    msg = msg + "Integer read failed.";
                reportError(msg);
            }
            return true;
        }
    };
}