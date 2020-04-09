#include "bigint.h"
/*/

BigInt operator + (const BigInt& left, const BigInt& right)
/*/

BigInt::BigInt(int x){
    int abs_x = abs(x); 
    std::string tmp = std::to_string(abs_x);
    number = new char[tmp.size()];
    if(!number)
       std::cout <<"no memory\n";
    else{
        number_len = tmp.size();
        std::reverse(tmp.begin(), tmp.end());
        sprintf(number, "%s", tmp.c_str());
        if(x<0) sign = '-';
        else sign = '+';
    }
}

BigInt::BigInt(int64_t x){
    int64_t abs_x = abs(x); 
    std::string tmp = std::to_string(abs_x);
    number = new char[tmp.size()];
    if(!number) //и тогда ничего нельзя дальше делать
       std::cout <<"no memory\n";
    else{
        number_len = tmp.size();
        std::reverse(tmp.begin(), tmp.end());
        sprintf(number, "%s", tmp.c_str());
        if(x<0) sign = '-';
        else sign = '+';
    }
}

BigInt::BigInt(const BigInt& bInt){

    number = new char[bInt.number_len];
    if (!number){
        std::cout<<"memory error";
    }
    else{
        number_len = bInt.number_len;
        strcpy(number, bInt.number);
        sign = bInt.sign;
    }
}

BigInt::~BigInt(){
    delete[] number;
    number_len=0;
    sign = '0';
}

BigInt::BigInt(const char* str_copied, const char& sign_copied){
    number = new char[strlen(str_copied)];
    if(!number)
        std::cout<< "no memory";
    else{
        sign = sign_copied;
        strcpy(number, str_copied);
        number_len = strlen(number);
    }
}

BigInt& BigInt::operator = (const BigInt& copied){
    
    if(this==&copied)
        return *this;
    char* ptr = new char[copied.number_len];
    delete[] number;
    number = ptr;
    strcpy(number, copied.number);
    number_len= copied.number_len;
    sign = copied.sign;
    return *this;
}

bool BigInt::operator== (const BigInt& bInt) const{
    if(strcmp(this->number, bInt.number)==0 ){
        if(this->number_len==1 && this->number[0]=='0'){ return true;} //отдельно +0 и -0
        else if(this->sign==bInt.sign) return true;
        else return false;}
    else{
        return false;}
}

bool BigInt::operator!= (const BigInt& bInt) const{
    return !(*this==bInt);
}

bool BigInt::operator > (const BigInt& bInt) const{
    return !(*this<bInt || *this==bInt);
}

bool BigInt::operator < (const BigInt& bInt) const{
    if((this->number_len==bInt.number_len) && (this->number_len==1) && this->number[0]=='0' && bInt.number[0]=='0') 
        return false;
    if(sign=='-'){
        if(bInt.sign=='-')

            if(number_len==bInt.number_len){

                for(int i=number_len-1;i>=0;i--){
                    if(number[i]<bInt.number[i]){
                        return false;}
                    if(number[i]>bInt.number[i]){
                        return true;}
                }
                return false;
            }
            else 
                return (this->number_len>bInt.number_len);
        else 
            return true;
    }
    else{
        if(bInt.sign=='-')
            return false;
        else{

            if(number_len==bInt.number_len){
                for(int i=number_len-1;i>=0;i--){
                    if(number[i]<bInt.number[i]){
                        return true;}
                    if(number[i]>bInt.number[i]){
                        return false;}
                }
                return false;
            }
            else 
                return (this->number_len<bInt.number_len);

        }
    }
    
}

bool BigInt::operator<= (const BigInt& bInt) const{
    return !(*this>bInt);
}

bool BigInt::operator>= (const BigInt& bInt) const{
    return !(*this<bInt);
}

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------

BigInt operator - (const BigInt& bInt){
    char sign_tmp;
    if(bInt.sign=='-')
        sign_tmp='+';
    else
        sign_tmp='-';
    return BigInt(bInt.number, sign_tmp);
}

BigInt operator - (const BigInt& left, const BigInt& right){
    return left + (-right);
}

void rmLeadZeros(std::string* str){
    size_t size = str->size();
    size_t i=1;
    while (true){
        if((*str)[size-i]=='0'){
            str->pop_back();
            i++;
        }
        else break;
    }
    if (str->size()==0){
        *str+="0";
    }
}

BigInt operator + (const BigInt& left, const BigInt& right){
    if(left.sign=='-'){
        if(right.sign=='-'){
            std::string result(""); //это строка результата сложения
            uint carry=0; uint sum_tmp = 0; //переменные для промежуточных вычислений
            size_t min_len = std::min(left.number_len, right.number_len);
            size_t max_len = std::max(left.number_len, right.number_len);
            for(size_t i=0;i<min_len;i++){
                sum_tmp = left.number[i]+right.number[i]-2*'0'+carry;
                result+= ((sum_tmp)%10+'0');
                carry = sum_tmp/10;
            }
            const BigInt* ptr = &right;
            if(max_len==left.number_len) ptr = &left;

            for(size_t i=min_len; i<max_len;i++){
                sum_tmp = ptr->number[i]-'0'+carry;
                result+= (sum_tmp)%10+'0';
                carry = sum_tmp/10;
            }
            if(carry!=0)  result+= (carry+'0');
            return BigInt(result.c_str(), left.sign);
        }


        else{ // типа -5 + 11 или 5 11 -11 +5
            std::string result("");
            const BigInt* ptr_big = &left;
            const BigInt* ptr_sml = &right;
            char res_sign = '-';
            if(right>-left){
                ptr_big = &right; ptr_sml = &left;
                res_sign = '+';
            }
            size_t min_len = ptr_sml->number_len, max_len = ptr_big->number_len;
            int debt = 0; //то есть есть ли долг от предыдущего
            for(size_t i=0; i<min_len;i++){
                if(ptr_big->number[i]-debt<ptr_sml->number[i]){
                    result+= (ptr_big->number[i]-debt-ptr_sml->number[i]+10)+'0';
                    debt=1;
                }
                else{
                    result+= (ptr_big->number[i]-debt-ptr_sml->number[i])+'0';
                    debt=0;
                }
            }

            for(size_t i=min_len; i<max_len;i++){
                if(ptr_big->number[i]-debt<'0'){
                    result+= (ptr_big->number[i]-debt+10);
                    debt=1;
                }
                else{
                    result+= (ptr_big->number[i]-debt);
                    debt=0;
                }
            }
            rmLeadZeros(&result);
            if(result=="0") res_sign='+';
            return BigInt(result.c_str(), res_sign);
        }
    }
    else{
        BigInt tmp = -((-left)+(-right));//для класса важен знак нуля, но пользователю нужно передавать только +0
        if(strcmp(tmp.number, "0")==0 && tmp.sign=='-'){
            tmp = -tmp;
        }
        return tmp;
    }
}

std::ostream& operator <<(std::ostream &os, const BigInt& bInt){
    std::string str(bInt.number);
    if(bInt.sign=='-'){
        os << '-';
    }
    std::reverse(str.begin(), str.end());
    os << str;
    return os;
}