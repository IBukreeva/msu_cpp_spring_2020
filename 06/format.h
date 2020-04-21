#include <string>
#include <sstream>
#include <vector>

template<class T>
std::string argsToStr(T&& val){
    std::stringstream ans;
    ans << val;
    return ans.str();
}

template <class... Args>
std::string format(const std::string& text, Args&&... args){ 
    std::stringstream answer;
    size_t len_text = text.size();
    std::vector<std::string> arg_data = {argsToStr(std::forward<Args>(args))... };
    size_t ind_arg = 0;
    size_t size_arg = arg_data.size();

    bool flaq = false; //этот флаг имеет состояния: false - ничего не происходит, true - открыта фигурная скобка
    
    for(size_t i=0; i<len_text; i++){
        if(flaq){ //то мы ждем или цифру, или закрывающую скобку
            if(std::isdigit(text[i])){
                ind_arg *= 10; 
                ind_arg += text[i]-'0';
            }
            else if(text[i]=='}'){
                if(ind_arg>=size_arg)
                    throw std::runtime_error("not so many args");
                else{
                    answer << arg_data[ind_arg];
                    flaq = false;
                }
            }
            else
                throw std::runtime_error("opening bracket without closing one");
            
        }
        else { //то мы ждем открывающую скобку или не закрывающую скобку или любой другой символ
            if(text[i]=='{'){
                flaq = true;
                ind_arg = 0;
            }
            else if(text[i]=='}')
                throw std::runtime_error("closing bracket without the opening");
            else 
                answer<<text[i];
        }
    }

    if(flaq){ //то есть строка закончилась, а скобочку не закрыли
        throw std::runtime_error("no closing bracket in the end");
    }
    return answer.str();

}

