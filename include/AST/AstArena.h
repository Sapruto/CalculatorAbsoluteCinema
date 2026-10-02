#pragma once

#include <memory>
#include <vector>
#include <type_traits>
#include <utility>

#include "ASTFwd.h"
#include "Node.h"

namespace AST {
    class AstArena {
    private:
        std::vector<std::unique_ptr<Node>> exprs;

    public:
        template<class T, class... Args>
        T* make(Args&&... args) {
            static_assert(std::is_base_of_v<Node, T>,
                        "AstArena can only own Node subclasses");
            auto p = std::make_unique<T>(std::forward<Args>(args)...);
            T* raw = p.get();
            exprs.push_back(std::move(p));
            return raw;
        }
    };
}