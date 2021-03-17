#include <sstream>
#include <cctype>
#include <limits>

namespace TestValidator{
    class Reader {
    private:
        std::istream& is;
        int lineCount;
        int tokenCount;
        char lastChar;
    public:
        Reader(std::istream& _is);
        ~Reader();
        char readChar();
        char peekChar();

        bool readAndMatchSpace();
        bool readAndMatchNewline();
        bool readAndMatchEOF();

        bool readInt(int &x);
    };
    
    Reader::Reader(std::istream &_is): is(_is) { 
        lineCount = 1;
        tokenCount = 0;
        lastChar = ' ';
    }
    
    Reader::~Reader() { }

    char Reader::readChar(){
        char nextChar = is.get();
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

    char Reader::peekChar(){
        return is.peek();
    }

    bool Reader::readAndMatchSpace(){
        char nextchar = readChar();
        if(nextchar == ' ')
            return true;
        else
            return false;
    }

    bool Reader::readAndMatchNewline(){
        char nextchar = readChar();
        if(nextchar == '\n')
            return true;
        else
            return false;
    }

    bool Reader::readAndMatchEOF(){
        char nextchar = readChar();
        if(nextchar == EOF)
            return true;
        else
            return false;
    }

    bool Reader::readInt(int &x){
        bool neg = false;
        if(peekChar() == '-'){
            readChar();
            neg = true;
        }
        if(!isdigit(peekChar())){
            return false;
        }

        x = 0;
        while(isdigit(peekChar())){
            int d = readChar()-'0';
            if(x > (std::numeric_limits<int>::max()-d)/10){
                x = 0;
                return false;
            }
            x = x * 10 + d;
        }

        if(neg)
            x = -x;
        return true;
    }
}