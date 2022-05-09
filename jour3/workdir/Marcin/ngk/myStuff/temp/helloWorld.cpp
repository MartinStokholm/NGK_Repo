#include <restinio/all.hpp>
#include <iostream>

using std::string;

struct book_t{

    book_t() = default;

// constructor for a book
    book_t(string auth, string title)
    : 
    m_author{std::move(auth)},
    m_title{std::move(title)}
    {}


    string m_author;
    string m_title;
};

int main(void){
    

    

    return 0;
}
