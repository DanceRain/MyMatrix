#include <odb/core.hxx>
#include <odb/forward.hxx>
#include <string>

#pragma db object
class Account
{
public:
    Account(const string& account_num, const string& account_pwd);
    
public:
    const string& account_num() const
    {
        return m_account_num;    
    }

private:
    Account();
    friend class odb::access;
    #pragma db id auto;
    unsigned long m_id;
    string m_account_num;
    string m_account_pwd;
}
