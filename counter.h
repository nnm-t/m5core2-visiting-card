#pragma once

#include "config.h"

#include <functional>

#include <Arduino.h>
#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif
#include <LovyanGFX.h>

class Counter
{
    static constexpr const size_t count_num_default = 30;
    static constexpr const size_t count_min_default = 10;
    static constexpr const size_t count_max_default = 100;

    const size_t _count_num_min;
    const size_t _count_num_max;

    bool _is_enabled = true;
    size_t _count_num;
    size_t _count = 0;
    std::function<void()> _on_ticked = nullptr;

public:
    Counter(const size_t count_num = count_num_default, const size_t count_num_min = count_min_default, const size_t count_num_max = count_max_default) : _count_num(count_num), _count_num_min(count_num_min), _count_num_max(count_num_max)
    {

    }

    void begin(std::function<void()>&& on_ticked);

    void update();

    bool is_enabled() const
    {
        return _is_enabled;
    }

    void set_enabled(const bool is_enabled)
    {
        _is_enabled = is_enabled;
    }

    size_t get_count() const
    {
        return _count;
    }

    size_t get_count_num() const
    {
        return _count_num;
    }

    size_t get_count_num_min() const
    {
        return _count_num_min;
    }

    size_t get_count_num_max() const
    {
        return _count_num_max;
    }

    void set_count_num(const size_t count_num);
};