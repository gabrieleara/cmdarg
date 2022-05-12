// Copyright 2022 Gabriele Ara
// Licensed by GNU GENERAL PUBLIC LICENSE v3.0

// System headers
#include <iostream>
#include <sstream>

// Project headers
#include <cmdarg/actions.hpp>
#include <cmdarg/argument.hpp>

namespace cmdarg::actions {

template <class T>
using check_type = bool (*)(const T &v);

template <class T>
bool check_nocheck(const T &_v_unused) {
    return true;
}

template <class T>
bool check_positive(const T &v) {
    return v > 0;
}

template <class T>
bool check_negative(const T &v) {
    return v < 0;
}

template <class T>
bool check_nonnegative(const T &v) {
    return v >= 0;
}

template <class T>
bool check_nonpositive(const T &v) {
    return v <= 0;
}

template <class T>
bool check_nonzero(const T &v) {
    return v != 0;
}

template <class T>
int increment_number(std::string *dest, const Argument &opt,
                     const std::string &_src_unused) {
    std::istringstream iss{*dest};
    std::ostringstream oss;
    T val;

    iss >> val;
    if (!iss) val = 0;

    ++val;
    oss << val;
    *dest = oss.str();
    return 0;
}

template <class T>
int store_number(std::string *dest, const Argument &opt, const std::string &src,
                 check_type<T> check) {
    std::istringstream iss{src};
    std::ostringstream oss;
    T val;

    iss >> val;
    if (iss && check(val)) {
        // Value correctly read
        oss << val;
        *dest = oss.str();
        return 0;
    }

    std::cerr << "Error: argument ";

    if (opt.short_opt) {
        std::cerr << opt.short_opt << "/";
    }

    std::cerr << opt.long_opt << ": ";
    std::cerr << "invalid value: '" << val << "'";
    std::cerr << std::endl;
    return -1;
}

template <class T>
int store_number_nocheck(std::string *dest, const Argument &opt,
                         const std::string &src) {
    return store_number<T>(dest, opt, src, check_nocheck<T>);
}

template <class T>
int store_number_positive(std::string *dest, const Argument &opt,
                          const std::string &src) {
    return store_number<T>(dest, opt, src, check_positive<T>);
}

template <class T>
int store_number_negative(std::string *dest, const Argument &opt,
                          const std::string &src) {
    return store_number<T>(dest, opt, src, check_negative<T>);
}

template <class T>
int store_number_nonnegative(std::string *dest, const Argument &opt,
                             const std::string &src) {
    return store_number<T>(dest, opt, src, check_nonnegative<T>);
}

template <class T>
int store_number_nonpositive(std::string *dest, const Argument &opt,
                             const std::string &src) {
    return store_number<T>(dest, opt, src, check_nonpositive<T>);
}

template <class T>
int store_number_nonzero(std::string *dest, const Argument &opt,
                         const std::string &src) {
    return store_number<T>(dest, opt, src, check_nonzero<T>);
}

int store_string(std::string *dest, const Argument &opt,
                 const std::string &src) {
    // TODO(gabara): check length non zero
    *dest = src;
    return 0;
}

int store_bool(std::string *dest, bool value) {
    *dest = value ? "true" : "false";
    return 0;
}

int store_true(std::string *dest, const Argument &opt,
               const std::string &_src_unused) {
    return store_bool(dest, true);
}

int store_false(std::string *dest, const Argument &opt,
                const std::string &_src_unused) {
    return store_bool(dest, false);
}

int show_help_and_exit(std::string *dest, const Argument &opt,
                       const std::string &_src_unused) {
    store_true(dest, opt, _src_unused);
    // Very important! Help must always generate an error!
    // It will be handled correctly by the parser
    // implementation.
    return -1;
}

const Type store_int = store_number_nocheck<int>;
const Type store_long = store_number_nocheck<long>;
const Type store_long_long = store_number_nocheck<long long>;
const Type store_float = store_number_nocheck<float>;
const Type store_double = store_number_nocheck<double>;

const Type store_positive_int = store_number_positive<int>;
const Type store_positive_long = store_number_positive<long>;
const Type store_positive_long_long = store_number_positive<long long>;
const Type store_positive_float = store_number_positive<float>;
const Type store_positive_double = store_number_positive<double>;

const Type store_negative_int = store_number_negative<int>;
const Type store_negative_long = store_number_negative<long>;
const Type store_negative_long_long = store_number_negative<long long>;
const Type store_negative_float = store_number_negative<float>;
const Type store_negative_double = store_number_negative<double>;

const Type store_nonpositive_int = store_number_nonpositive<int>;
const Type store_nonpositive_long = store_number_nonpositive<long>;
const Type store_nonpositive_long_long = store_number_nonpositive<long long>;
const Type store_nonpositive_float = store_number_nonpositive<float>;
const Type store_nonpositive_double = store_number_nonpositive<double>;

const Type store_nonnegative_int = store_number_nonnegative<int>;
const Type store_nonnegative_long = store_number_nonnegative<long>;
const Type store_nonnegative_long_long = store_number_nonnegative<long long>;
const Type store_nonnegative_float = store_number_nonnegative<float>;
const Type store_nonnegative_double = store_number_nonnegative<double>;

const Type store_nonzero_int = store_number_nonzero<int>;
const Type store_nonzero_long = store_number_nonzero<long>;
const Type store_nonzero_long_long = store_number_nonzero<long long>;
const Type store_nonzero_float = store_number_nonzero<float>;
const Type store_nonzero_double = store_number_nonzero<double>;

/*
 * ┌───────────────────────────────────────────────┐
 * │               Increment Actions               │
 * └───────────────────────────────────────────────┘
 */
const Type increment_int = increment_number<int>;
const Type increment_long = increment_number<long>;
const Type increment_long_long = increment_number<long long>;
const Type increment_float = increment_number<float>;
const Type increment_double = increment_number<double>;

}  // namespace cmdarg::actions
