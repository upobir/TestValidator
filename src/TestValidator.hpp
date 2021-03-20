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
            if(nextChar == '\n'){
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
            lineCount = 1;
            tokenCount = 0;
            lastChar = ' ';
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
        void reportError(std::string &msg){
            os<<"Read "<<getTokenCount()<<" token(s) at line "<<getLineCount()<<std::endl;
            os<<"Error: "<<msg<<std::endl;
            assert(false);
        }
    public:
        Validator(std::istream &is, std::ostream &_os) : Reader(is), os(_os) { }
        ~Validator() { }

        bool readCharAndMatch(char &x, char expected, std::string msg = ""){
            bool success = readChar(x);
            if(!success || x != expected){
                if(msg.empty()){
                    msg = msg + "Character read failed. expected '" + expected + "', got ";
                    if(success)
                        msg = msg + "'" + x + "'";
                    else
                        msg = msg + "EOF";
                }
                reportError(msg);
                
            }
            return true;
        }
    };
}