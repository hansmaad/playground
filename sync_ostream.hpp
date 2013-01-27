#ifndef SYNC_OSTREAM_HPP
#define SYNC_OSTREAM_HPP

#include <mutex>
#include <ostream>

class sync_ostream
{
public:
    typedef std::unique_lock<std::mutex> lock_type;
    
    sync_ostream(std::ostream& s) :
        stream(s)
    {}
    
    template<typename T>
    void write(const T& t)
    {
        stream << t;
    }
    
    lock_type get_lock()
    {
        return lock_type(mutex);
    }
    
private:
    std::mutex mutex;    
    std::ostream& stream;
};

class sync_ostream_transaction
{
public:
    sync_ostream_transaction(sync_ostream& s) :
        stream(s), lock(s.get_lock())
    {}
    
    template<typename T>
    void write(const T& t) const
    {
        const_cast<sync_ostream&>(stream).write(t);
    }
private:
    sync_ostream& stream;
    sync_ostream::lock_type lock;    
};

template<typename T>
sync_ostream_transaction operator<<(
    sync_ostream& stream, const T& t)
{
    sync_ostream_transaction transaction(stream);
    transaction.write(t);
    return transaction;
}

template<typename T>
const sync_ostream_transaction& operator<<(
    const sync_ostream_transaction& stream, const T& t)
{
    stream.write(t);    
    return stream; 
}

#endif  // SYNC_OSTREAM_HPP

