#include "counter.h"

void Counter::begin(std::function<void()>&& on_ticked)
{
    _on_ticked = on_ticked;
}

void Counter::update()
{
    if (++_count < _count_num)
    {
        return;
    }

    _count = 0;

    if (_on_ticked != nullptr)
    {
        _on_ticked();
    }
}

void Counter::set_count_num(const size_t count_num)
{
    if (!_is_enabled)
    {
        return;
    }

    if (count_num < _count_num_min)
    {
        _count_num = _count_num_min;
        return;
    }

    if (count_num > _count_num_max)
    {
        _count_num = _count_num_max;
        return;
    }

    _count_num = count_num;
}