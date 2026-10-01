#pragma once

#include <memory>

namespace Literals {
    struct Literal {
        Literal() = default;
        virtual ~Literal() = 0;

        virtual std::unique_ptr<Literal> Copy() = 0;
    };
}