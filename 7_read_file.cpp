#include <iostream>
#include <fstream>

namespace namespace_read_file
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
            this->chunk = new char[32];
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

        ~Oneline() {
            delete this->chunk;
        }
    };
}

int main(void)
{
    std::string file_path = "./4_array.cpp";
    namespace_read_file::Util* ptr = new namespace_read_file::Oneline(file_path);
    ptr->read_file();
    // delete ptr;
    return 0;
}