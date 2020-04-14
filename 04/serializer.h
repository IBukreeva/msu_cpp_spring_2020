#pragma once
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
    Error operator()(ArgsT&&... args)
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

    template <class T, class... Args>
    Error process(T&& val, Args&&... args){
        Error er1 = process(val);
        Error er2 = process(std::forward<Args>(args)...);
        if( er1==Error::CorruptedArchive || er2==Error::CorruptedArchive)
            return Error::CorruptedArchive;
        
        return Error::NoError;
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
    Error operator()(ArgsT&&... args){
        return process(args...);
    }

    template <class T>
    Error load(T& object){
        return object.serialize(*this);
    }

    Error process(bool& value){
        std::string text;
        in_ >> text;
    
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }

    Error process(uint64_t& value){
        std::string text;
        in_ >> text;

        size_t text_size=text.size();
        if(text_size==0) return Error::CorruptedArchive;
        if (std::count_if(text.begin(), text.end(), isdigit) != text_size)
            return Error::CorruptedArchive;
        value = std::stoull(text);
        
        return Error::NoError;
    }

    template <class T, class... ArgsT>
    Error process(T&& val, ArgsT&&... args){
        Error er1 = process(val);
        Error er2 = process(std::forward<ArgsT>(args)...);
        if (er1==Error::CorruptedArchive || er2==Error::CorruptedArchive)
            return Error::CorruptedArchive;

        return Error::NoError;
    }

private:
    std::istream& in_;    

};
