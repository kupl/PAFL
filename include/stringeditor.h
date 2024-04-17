#ifndef __STRINGEDITOR_H__
#define __STRINGEDITOR_H__

#include <sstream>
#include <charconv>


namespace StringEditor
{
/*
    Reservation unit
*/
    static constexpr uint64_t KiB(uint64_t kib)
    {
        return kib * 1024;
    }


    static constexpr uint64_t MiB(uint64_t mib)
    {
        return mib * 1024 * 1024;
    }


    static constexpr uint64_t GiB(uint64_t Gib)
    {
        return Gib * 1024 * 1024 * 1024;
    }


/*
    Output string stream
*/
    template <class T>
    static std::string& append(std::string& str, T val)
    {
        char buf[KiB(1)];
        auto result_ptr = std::to_chars(buf, buf + KiB(1), val).ptr;
        return str.append(buf, result_ptr - buf);
    }


    static std::string& append(std::string& str, bool val)
    {
        val ? str.push_back('1') : str.push_back('0');
        return str;
    }


    static std::string& append(std::string& str, const std::string& val)
    {
        return str.append(val);
    }


    static std::string& append(std::string& str, const char* val)
    {
        return str.append(val);
    }


    static void eraseEndIf(std::string& buffer, char end)
    {
        if (buffer.ends_with(end))
            buffer.pop_back();
    }


    static void eraseEndIf(std::string& buffer, const std::string& end)
    {
        if (buffer.ends_with(end))
            buffer.erase(buffer.size() - end.size());
    }


    static void replaceEndIf(std::string& buffer, char end, const std::string& new_end)
    {
        if (buffer.ends_with(end)) {

            buffer.pop_back();
            buffer.append(new_end);
        }
    }


    static void replaceEndIf(std::string& buffer, char end, char new_end)
    {
        if (buffer.ends_with(end)) {

            buffer.pop_back();
            buffer.push_back(new_end);
        }
    }


    static void replaceEndIf(std::string& buffer, char end, const char* new_end)
    {
        if (buffer.ends_with(end)) {

            buffer.pop_back();
            buffer.append(new_end);
        }
    }


    static void replaceEndIf(std::string& buffer, const std::string& end, const std::string& new_end)
    {
        if (buffer.ends_with(end)) {

            buffer.erase(buffer.size() - end.size());
            buffer.append(new_end);
        }
    }


    static void replaceEndIf(std::string& buffer, const std::string& end, char new_end)
    {
        if (buffer.ends_with(end)) {

            buffer.erase(buffer.size() - end.size());
            buffer.push_back(new_end);
        }
    }


    static void replaceEndIf(std::string& buffer, const std::string& end, const char* new_end)
    {
        if (buffer.ends_with(end)) {

            buffer.erase(buffer.size() - end.size());
            buffer.append(new_end);
        }
    }


/*
    Input string stream
*/
    static std::string read(const char* path)
    {
        std::FILE* fp = std::fopen(path, "rb");
        if (std::fseek(fp, 0, SEEK_END))
            return std::string();
        auto size = std::ftell(fp);
        std::rewind(fp);

        std::string buf(size, 0);
        std::fread(buf.data(), size, 1, fp);
        std::fclose(fp);
        return buf;
    }


    template <class T>
    static T cin(std::istringstream& iss)
    {
        T ret;
        iss >> ret;
        return ret;
    }
}
#endif
