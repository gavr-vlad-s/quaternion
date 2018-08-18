#ifndef QUATERNION_H
#define QUATERNION_H
#include <exception>

namespace quat {
    template<typename T>
    class quat_t;

    template<typename T>
    class quat_t{
    public:
        quat_t()                            = default;
        explicit quat_t(const T& z){
            x[0] = z; x[1] = T{}; x[2] = T{}; x[3] = T{};
        }
        quat_t(const quat_t<T>&)            = default;
        quat_t& operator=(const quat_t<T>&) = default;
        ~quat_t()                           = default;

        quat_t(const T x0, const T x1, const T x2, const T x3) {
            x[0] = x0; x[1] = x1; x[2] = x2; x[3] = x3;
        }

        quat_t<T>& operator+=(const quat_t<T>& rhs);
        quat_t<T>& operator-=(const quat_t<T>& rhs);
        quat_t<T>& operator*=(const quat_t<T>& rhs);
        quat_t<T>& operator/=(const quat_t<T>& rhs);
        quat_t<T>& operator+=(const T& rhs);
        quat_t<T>& operator-=(const T& rhs);
        quat_t<T>& operator*=(const T& rhs);
        quat_t<T>& operator/=(const T& rhs);

        bool operator==(const quat_t<T>& rhs);
        bool operator!=(const quat_t<T>& rhs);
        quat_t<T> operator+(const quat_t<T>& rhs);

        const T& operator[](int i) const;
        const T& at(int i) const;
    private:
        T x[4];
    };

    static const char* invalid_index_str = "Invalid index of a quaternion component.";

    class at_exception_t : public std::exception{
    public:
        at_exception_t()                                 = default;
        at_exception_t(const at_exception_t&)            = default;

        virtual ~at_exception_t()                        = default;
        at_exception_t& operator=(const at_exception_t&) = default;

        virtual const char* what() const noexcept;
    };

    const char* at_exception_t::what() const noexcept
    {
        return invalid_index_str;
    }

    template<typename T>
    quat_t<T>& quat_t<T>::operator+=(const quat_t<T>& rhs)
    {
        x[0] += rhs.x[0];
        x[1] += rhs.x[1];
        x[2] += rhs.x[2];
        x[3] += rhs.x[3];
        return  *this;
    }

    template<typename T>
    quat_t<T>& quat_t<T>::operator-=(const quat_t<T>& rhs)
    {
        x[0] -= rhs.x[0];
        x[1] -= rhs.x[1];
        x[2] -= rhs.x[2];
        x[3] -= rhs.x[3];
        return  *this;
    }

    template<typename T>
    quat_t<T>& quat_t<T>::operator*=(const quat_t<T>& rhs)
    {
        T x0;
        T x1;
        T x2;
        T x3;

        x0 = x[0] * rhs.x[0] - x[1] * rhs.x[1] - x[2] * rhs.x[2] - x[3] * rhs.x[3];
        x1 = x[0] * rhs.x[1] + x[1] * rhs.x[0] + x[2] * rhs.x[3] - x[3] * rhs.x[2];
        x2 = x[0] * rhs.x[2] - x[1] * rhs.x[3] + x[2] * rhs.x[0] + x[3] * rhs.x[1];
        x3 = x[0] * rhs.x[3] + x[1] * rhs.x[2] - x[2] * rhs.x[1] + x[3] * rhs.x[0];

        x[0] = x0;
        x[1] = x1;
        x[2] = x2;
        x[3] = x3;
        return  *this;
    }

    template<typename T>
    quat_t<T>& quat_t<T>::operator+=(const T& rhs)
    {
        x[0] += rhs;
        x[1] += rhs;
        x[2] += rhs;
        x[3] += rhs;
        return *this;
    }

    template<typename T>
    quat_t<T>& quat_t<T>::operator-=(const T& rhs)
    {
        x[0] -= rhs;
        x[1] -= rhs;
        x[2] -= rhs;
        x[3] -= rhs;
        return *this;
    }

    template<typename T>
    quat_t<T>& quat_t<T>::operator*=(const T& rhs)
    {
        x[0] *= rhs;
        x[1] *= rhs;
        x[2] *= rhs;
        x[3] *= rhs;
        return *this;
    }

    template<typename T>
    quat_t<T>& quat_t<T>::operator/=(const T& rhs)
    {
        x[0] /= rhs;
        x[1] /= rhs;
        x[2] /= rhs;
        x[3] /= rhs;
        return *this;
    }

    template<typename T>
    quat_t<T> operator+(const quat_t<T>& lhs, const quat_t<T>& rhs)
    {
        quat_t<T> result = lhs;
        result += rhs;
        return result;
    }

    template<typename T>
    quat_t<T> operator-(const quat_t<T>& lhs, const quat_t<T>& rhs)
    {
        quat_t<T> result = lhs;
        result -= rhs;
        return result;
    }

    template<typename T>
    quat_t<T> operator*(const quat_t<T>& lhs, const quat_t<T>& rhs)
    {
        quat_t<T> result = lhs;
        result *= rhs;
        return result;
    }

    template<typename T>
    quat_t<T> operator+(const quat_t<T>& lhs, const T& rhs)
    {
        quat_t<T> result = lhs;
        result += rhs;
        return result;
    }

    template<typename T>
    quat_t<T> operator-(const quat_t<T>& lhs, const T& rhs)
    {
        quat_t<T> result = lhs;
        result -= rhs;
        return result;
    }

    template<typename T>
    quat_t<T> operator*(const quat_t<T>& lhs, const T& rhs)
    {
        quat_t<T> result = lhs;
        result *= rhs;
        return result;
    }

    template<typename T>
    quat_t<T> operator+(const T& lhs, const quat_t<T>& rhs)
    {
        return quat_t<T>{lhs + rhs[0], lhs + rhs[1], lhs + rhs[2], lhs + rhs[3]};
    }

    template<typename T>
    quat_t<T> operator-(const T& lhs, const quat_t<T>& rhs)
    {
        return quat_t<T>{lhs - rhs[0], lhs - rhs[1], lhs - rhs[2], lhs - rhs[3]};
    }

    template<typename T>
    quat_t<T> operator*(const T& lhs, const quat_t<T>& rhs)
    {
        return quat_t<T>{lhs * rhs[0], lhs * rhs[1], lhs * rhs[2], lhs * rhs[3]};
    }

    template<typename T>
    bool quat_t<T>::operator==(const quat_t<T>& rhs)
    {
        return (x[0] == rhs.x[0]) && (x[1] == rhs.x[1]) &&
               (x[2] == rhs.x[2]) && (x[3] == rhs.x[3]);
    }

    template<typename T>
    bool quat_t<T>::operator!=(const quat_t<T>& rhs)
    {
        return (x[0] != rhs.x[0]) || (x[1] != rhs.x[1]) ||
               (x[2] != rhs.x[2]) || (x[3] != rhs.x[3]);
    }

    template<typename T>
    quat_t<T> conj(const quat_t<T>& q)
    {
        return quat_t<T>{q[0], -q[1], -q[2], -q[3]};
    }

    template<typename T>
    const T& quat_t<T>::operator[](int i) const
    {
        return x[i];
    }

    template<typename T>
    const T& quat_t<T>::at(int i) const
    {
        if((i < 0) || (i > 3)){
            return x[i];
        }else{
            throw at_exception_t{};
        }
    }

    template<typename T>
    T norm_in_square(const quat_t<T>& q)
    {
        quat_t<T> temp = q * conj(q);
        return temp[0];
    }

    template<typename T>
    quat_t<T> operator+(const quat_t<T>& lhs)
    {
       return lhs;
    }

    template<typename T>
    quat_t<T> operator-(const quat_t<T>& lhs)
    {
       return quat_t<T>{-lhs[0], -lhs[1], -lhs[2], -lhs[3]};
    }

    template<typename T>
    quat_t<T> inv(const quat_t<T>& lhs)
    {
        quat_t<T> result = conj(lhs);
        result /= norm_in_square(lhs);
        return result;
    }

    template<typename T>
    quat_t<T>& quat_t<T>::operator/=(const quat_t<T>& rhs)
    {
        quat_t<T> temp{*this};
        temp *= inv(rhs);
        x[0] = temp.x[0];
        x[1] = temp.x[1];
        x[2] = temp.x[2];
        x[3] = temp.x[3];
        return *this;
    }

    template<typename T>
    quat_t<T> operator/(const quat_t<T>& lhs, const quat_t<T>& rhs)
    {
        quat_t<T> result = lhs;
        result /= rhs;
        return result;
    }

    template<typename T>
    quat_t<T> operator/(const quat_t<T>& lhs, const T& rhs)
    {
        quat_t<T> result = lhs;
        result /= rhs;
        return result;
    }

    template<typename T>
    quat_t<T> operator/(const T& lhs, const quat_t<T>& rhs)
    {
        quat_t<T> result = lhs * inv(rhs);
        return result;
    }
};
#endif
