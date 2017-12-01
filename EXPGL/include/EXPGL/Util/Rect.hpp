//
//  Rect.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/21/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef Rect_hpp
#define Rect_hpp

#include <string>

namespace EXP {
    
    template <typename T>
    class Rect
    {
    public:
        Rect() {}
        ~Rect() {}
        
        template<typename X>
        explicit operator Rect<X>() const {
            return Rect<X>(static_cast<X>(rect[0]), static_cast<X>(rect[1]), static_cast<X>(rect[2]),
                             static_cast<X>(rect[3]));
        }
        friend bool operator < (const Rect<T> &r, T scalar)
        {
            return r.rect[0] < scalar && r.rect[1] < scalar && r.rect[2] < scalar && r.rect[3] < scalar;
        }
        friend bool operator <= (const Rect<T> &r, T scalar)
        {
            return r.rect[0] <= scalar && r.rect[1] <= scalar && r.rect[2] <= scalar && r.rect[3] <= scalar;
        }
        friend bool operator > (const Rect<T> &r, T scalar)
        {
            return r.rect[0] > scalar && r.rect[1] > scalar && r.rect[2] > scalar && r.rect[3] > scalar;
        }
        friend bool operator >= (const Rect<T> &r, T scalar)
        {
            return r.rect[0] >= scalar && r.rect[1] >= scalar && r.rect[2] >= scalar && r.rect[3] >= scalar;
        }
        friend bool operator == (const Rect<T> &r, T scalar)
        {
            return r.rect[0] == scalar && r.rect[1] == scalar && r.rect[2] == scalar && r.rect[3] == scalar;
        }
        friend Rect<T> operator * (const Rect<T> &first, const Rect<T> &second)
        {
            Rect<T> value;
            value.rect[0] = first.rect[0] * second.rect[0];
            value.rect[1] = first.rect[1] * second.rect[1];
            value.rect[2] = first.rect[2] * second.rect[2];
            value.rect[3] = first.rect[3] * second.rect[3];
            value.update_width();
            value.update_height();
            return value;
        }
        friend Rect<T> operator / (const Rect<T> &first, const Rect<T> &second)
        {
            Rect<T> value;
            value.rect[0] = first.rect[0] / second.rect[0];
            value.rect[1] = first.rect[1] / second.rect[1];
            value.rect[2] = first.rect[2] / second.rect[2];
            value.rect[3] = first.rect[3] / second.rect[3];
            value.update_width();
            value.update_height();
            return value;
        }
        friend Rect<T> operator - (const Rect<T> &first, const Rect<T> &second)
        {
            Rect<T> value;
            value.rect[0] = first.rect[0] - second.rect[0];
            value.rect[1] = first.rect[1] - second.rect[1];
            value.rect[2] = first.rect[2] - second.rect[2];
            value.rect[3] = first.rect[3] - second.rect[3];
            value.update_width();
            value.update_height();
            return value;
        }
        friend Rect<T> operator + (const Rect<T> &first, const Rect<T> &second)
        {
            Rect<T> value;
            value.rect[0] = first.rect[0] + second.rect[0];
            value.rect[1] = first.rect[1] + second.rect[1];
            value.rect[2] = first.rect[2] + second.rect[2];
            value.rect[3] = first.rect[3] + second.rect[3];
            value.update_width();
            value.update_height();
            return value;
        }
        T& operator[] (int x) {
            return rect[x];
        }
        Rect(T left, T top, T right, T bottom)
        {
            rect[0] = left;
            rect[1] = top;
            rect[2] = right;
            rect[3] = bottom;
            update_width();
            update_height();
        }
        void set_left(T left)
        {
            rect[0] = left;
            update_height();
        }
        void set_top(T top)
        {
            rect[1] = top;
            update_height();
        }
        void set_right(T right)
        {
            rect[2] = right;
            update_height();
        }
        void set_bottom(T bottom)
        {
            rect[3] = bottom;
            update_height();
        }
        void shift_x(T x)
        {
            rect[0] += x;
            rect[2] += x;
        }
        void shift_y(T y)
        {
            rect[1] += y;
            rect[3] += y;
        }
        void shift_xy(T x, T y)
        {
            shift_x(x);
            shift_y(y);
        }
        
        T get_left(void) const { return rect[0]; }
        T get_top(void) const { return rect[1]; }
        T get_right(void) const { return rect[2]; }
        T get_bottom(void) const { return rect[3]; }
        T get_width(void) const { return width; }
        T get_height(void) const { return height; }
        
        void clone(Rect<T> *other) const
        {
            other->set_left(get_left());
            other->set_top(get_top());
            other->set_right(get_right());
            other->set_bottom(get_bottom());
            other->update_width();
            other->update_height();
        }
        
        void clone_into(Rect<T> *other) const
        {
            other->set_left(get_left());
            other->set_top(get_top());
            other->set_right(get_right());
            other->set_bottom(get_bottom());
            other->update_width();
            other->update_height();
        }
        void update_height(void)
        {
            height = rect[3] - rect[1];
        }
        void update_width(void)
        {
            width = rect[2] - rect[0];
        }
        void expand(T x, T y)
        {
            rect[0] -= x;
            rect[2] += x;
            rect[1] -= y;
            rect[3] += y;
            update_width();
            update_height();
        }
        
        std::string get_string(void)
        {
            std::string res = "(";
            for (unsigned i = 0; i < 4; ++i)
            {
                res += std::to_string(rect[i]);
                if (i == 3)
                {
                    res += ")";
                }
                else
                {
                    res += ", ";
                }
            }
            return res;
        }
    private:
        T rect[4];
        T width;
        T height;
    };
}


#endif /* Rect_hpp */
