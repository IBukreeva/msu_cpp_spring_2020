enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {   
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {   
        return process(args...);
    }
    
private:
    std::ostream& out_;

    Error process(bool& val){
        if(val){
            out_ << "true ";
        }
        else{
            out_ << "false ";
        }
        return Error::NoError;
    }

    Error process(uint64_t& val){
        out_ << val << " ";
        return Error::NoError;
    }

    template <class... Args>
    Error process(bool& val, Args&&... args){
        if(val)
            out_ << "true ";
        else
            out_ << "false ";
        return process(std::forward<Args>(args)...);
    }

    template <class... Args>
    Error process(uint64_t& val, Args&&... args){
        out_ << val<< " ";
        return process(std::forward<Args>(args)...);
    }

};



class Deserializer
{
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args){
        return load(args...);
    }

    template <class T>
    Error load(T& object){
        return object.deserialize(*this);
    }

    Error load(bool* value){
        std::string text;
        in_ >> text;
    
        if (text == "true")
            *value = true;
        else if (text == "false")
            *value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }


    Error load(uint64_t* value){
        std::string text;
        in_ >> text;

        size_t text_size=text.size();
        if(text_size==0) return Error::CorruptedArchive;
        if(text[0]=='-') return Error::CorruptedArchive;
        *value=0;
        for(size_t i=0;i<text_size;i++){  //нашла только stoi, а ничего про uint64_t не нашла, и поэтому написала так
            if(text[i]<'0' || text[i]>'9') 
                return Error::CorruptedArchive;
            *value=*value*10+text[i]-'0';
        }
        
        return Error::NoError;
    }

    template <class... Args>
    Error load(bool* value, Args&&... args){
        std::string text;
        in_ >> text;
    
        if (text == "true")
            *value = true;
        else if (text == "false")
            *value = false;
        else
            return Error::CorruptedArchive;

        return load(args...);
    }

    template <class... Args>
    Error load(uint64_t* value, Args&&... args){
        std::string text;
        in_ >> text;

        size_t text_size=text.size();
        if(text_size==0) return Error::CorruptedArchive;
        if(text[0]=='-') return Error::CorruptedArchive;
        *value=0;
        for(size_t i=0;i<text_size;i++){
            if(text[i]<'0' || text[i]>'9') 
                return Error::CorruptedArchive;
            *value=*value*10+text[i]-'0';
        }
        
        return load(args...);
    }

private:
    std::istream& in_;    

};
