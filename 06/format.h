#include <iostream>

enum class Error{
    RuntimeError,
    NoError
};

Error process(std::stringstream& str, size_t cur, size_t need) noexcept{
    return Error::RuntimeError;
}

template <class T, class... Args>
Error process(std::stringstream& str, size_t cur, size_t need, T&& val, Args&&... args) noexcept{
    if(cur<need){
        return process(str, cur+1, need, std::forward<Args>(args)...);
    }
    else{ 
        str << val; 
        return Error::NoError;
    }
}

template <class... Args>
std::string format(const char * text, Args&&... args){ 
    std::stringstream ans;
    size_t len_text = strlen(text);
    size_t i=0;
    while(i<len_text){
        if(text[i]=='{'){
            if(i+2>=len_text) throw std::runtime_error("");
            else{
                if(text[i+2]=='}' && std::isdigit(text[i+1])){
                    Error er = process(ans, 0, text[i+1]-'0', std::forward<Args>(args)...);
                    if(er==Error::RuntimeError) throw std::runtime_error("");
                    i+=3;
                }
                else throw std::runtime_error("");
            }
        }
        else if(text[i]=='}'){ //то есть закрывающая без открывающей
            throw std::runtime_error("");
        }
        else{
            ans << text[i];
            i+=1;
        }
    }
    return ans.str();

}

