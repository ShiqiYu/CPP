#pragma once
#include <iostream>
#include <cstring>

class MyString
{
  private:
    int buf_len;
    int * refcount;
    char * characters;
  public:
    MyString(int buf_len = 64, const char * data = NULL)
    {
        std::cout << "Constructor(int, char*)" << std::endl;
        this->buf_len = buf_len;
        this->refcount = new int[1]{1}; // initialized to 1
        this->characters = new char[buf_len]{};
        if(data)
            memcpy(this->characters, data, buf_len);
    }
    MyString(const MyString & ms)
    {
        std::cout << "Constructor(MyString&)" << std::endl;
        this->buf_len = ms.buf_len;
        this->refcount = ms.refcount;
        this->characters = ms.characters;
        this->refcount[0]++;
    }
    void release()
    {
        this->refcount[0]--;
        if(this->refcount[0] == 0)
        {
            this->buf_len = 0;
            delete this->refcount;
            delete this->characters;
        }
        else
        {
            this->buf_len = 0;
            this->refcount = NULL;
            this->characters = NULL;
        }
    }
    ~MyString()
    {
        release();
    }
    MyString & operator=(const MyString &ms)
    {
        release();
        this->buf_len = ms.buf_len;
        this->refcount = ms.refcount;
        this->characters = ms.characters;
        this->refcount[0]++;
        return *this;
    }
    friend std::ostream & operator<<(std::ostream & os, const MyString & ms)
    {
        os << "buf_len = " << ms.buf_len;
        os << ", refcount = " << ms.refcount[0];
        os << ", characters = " << static_cast<void*>(ms.characters);
        os << " [" << ms.characters << "]";
        return os;
    }
};
