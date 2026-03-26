#pragma once

namespace muduo
{

class copyable
{
protected:
    copyable(const copyable&) = default;
    copyable& operator=(const copyable&) = default;

    copyable() = default;
};

} // namespace moduo