//
// Created by atyub on 7/14/2022.
//

#include "Int4MMH.h"

std::ostream& operator<<(std::ostream& os, const Int4MMH& i)
{
    return os << i.data;
}

bool operator<(const Int4MMH& n1, const Int4MMH& n2)
{
    return n1.data < n2.data;
}

bool operator>(const Int4MMH& n1, const Int4MMH& n2)
{
    return n1.data > n2.data;
}

bool operator==(const Int4MMH& n1, const Int4MMH& n2)
{
    return n1.data == n2.data;
}
