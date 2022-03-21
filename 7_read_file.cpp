#include <iostream>
#include <fstream>

namespace rf
{

    class Util
    {
    public:
        std::string file_path;
        virtual void read_file() = 0;
        Util(std::string file_path)
        {
            this->file_path = file_path;
            std::cout << "read file from " << this->file_path << std::endl;
        };
    };

    class Oneline : public virtual Util
    {

    private:
        char * chunk;

    public:
        Oneline(std::string file_path) : Util(file_path)
        {
            char chunk[32];
            this->chunk = chunk;
        }

        void read_file()
        {
            std::ifstream read;
            read.open(file_path);
            while (read.getline(this->chunk, 32))
            {
                std::cout << this->chunk << std::endl;
            }
            std::cout << std::endl;
        }
    };
}

int main(void)
{
    std::string file_path = "./4_array.cpp";
    rf::Util *ptr;
    rf::Oneline one(file_path);
    ptr = &one;
    ptr->read_file();
    return 0;
}