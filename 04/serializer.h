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

    template <class... Args>
    Error process(bool& val, Args&&... args){
        if(val){
            out_ << "true ";
        }
        else{
            out_ << "false ";
        }
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
    Error operator()(ArgsT&&... args){
        return loadProcess(args...);
    }

    template <class T>
    Error load(T& object){
        return object.serialize(*this);
    }

    Error loadProcess(bool& value){
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


    Error loadProcess(uint64_t& value){
        std::string text;
        in_ >> text;

        size_t text_size=text.size();
        if(text_size==0) return Error::CorruptedArchive;
        if (std::count_if(text.begin(), text.end(), isdigit) != text_size)
            return Error::CorruptedArchive;
        value = std::stoull(text);
        
        return Error::NoError;
    }

    template <class... Args>
    Error loadProcess(bool& value, Args&&... args){
        std::string text;
        in_ >> text;
    
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return loadProcess(args...);
    }

    template <class... Args>
    Error loadProcess(uint64_t& value, Args&&... args){
        std::string text;
        in_ >> text;

        size_t text_size=text.size();
        if(text_size==0) return Error::CorruptedArchive;
        if (std::count_if(text.begin(), text.end(), isdigit) != text_size)
            return Error::CorruptedArchive;
        value = std::stoull(text);
        
        return loadProcess(args...);
    }

private:
    std::istream& in_;    

};
