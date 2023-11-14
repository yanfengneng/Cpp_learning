#include "myStrBlob.h"

ConstStrBlobPtr StrBlob::begin() const // should add const
{
    return ConstStrBlobPtr(*this);
}
ConstStrBlobPtr StrBlob::end() const // should add const
{
    return ConstStrBlobPtr(*this, data->size());
}

StrBlob& StrBlob::operator=(const StrBlob& sb)
{
    data = std::make_shared<vector<string>>(*sb.data);
    return *this;
}

int main()
{
    return 0;
}