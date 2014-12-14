//namespace psy {
//
//
//template <class T>
//Logger& Logger::operator << (const T& value)
//{
//    line << value;
//    if (line.str().find('\n') not_eq std::string::npos)
//    {
//        log();
//        line.str( std::string() );
//        line.clear();
//    }
//    return *this;
//}
//
//
//inline Logger& Logger::operator << ( std::ostream&(*f)(std::ostream&) )
//{
//    log();
//    line.str( std::string() );
//    line.clear();
//    return *this;
//}
//
//
//}
