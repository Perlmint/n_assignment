//
//  ArrayPrinter.hpp
//  aaaa
//
//  Created by Gyusun Yeom on 2016. 12. 8..
//  Copyright © 2016년 Gyusun Yeom. All rights reserved.
//

#ifndef ArrayPrinter_hpp
#define ArrayPrinter_hpp

template<typename T>
class ArrayPrinter
{
public:
    ArrayPrinter(T const *data, size_t size)
    : _data(data)
    , _size(size)
    {}
    
    template<typename OT>
    friend std::ostream& operator<<(std::ostream &stream, const ArrayPrinter<OT> &val);
    
private:
    T const *_data = nullptr;
    size_t _size = 0;
};

template<typename T>
std::ostream& operator<<(std::ostream &stream, const ArrayPrinter<T> &val)
{
    bool first = true;
    for (size_t i = 0; i < val._size; ++i) {
        if (!first) {
            stream << " ";
        }
        stream << val._data[i];
        first = false;
    }
    
    return stream;
}

#endif /* ArrayPrinter_hpp */
