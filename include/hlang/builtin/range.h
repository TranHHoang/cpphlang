#pragma once

#include <functional>

namespace HLang {
    class Continue : public std::exception { };
    class Break : public std::exception { };
    class Return : public std::exception { };

    template<typename T>
    class Range {
    public:
        Range() = default;

        Range(T start, T end) : start(start), end(end) {}

        template<typename TReturnType>
        std::pair<bool, TReturnType> loopThrough(std::function<TReturnType()> &func) {
            TReturnType result;
            for (decltype(start) __range_iterator__ = start; __range_iterator__ != end; ++__range_iterator__) {
                try {
                    result = func();
                }
                catch (const Continue& c) {
                    continue;
                }
                catch (const Break& b) {
                    break;
                }
                catch (const Return& r) {
                    return {true, result};
                }
            }

            return {false, result};
        }

    private:
        T start, end;
    };
}