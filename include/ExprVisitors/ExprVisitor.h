#pragma once

#include "../AST/Exprs.h"
#include "../AST/Literals.h"

#include <concepts>
#include <utility>

namespace AST {
    template<class... Ts>
    struct Overloaded : Ts... { using Ts::operator()...; };

    template<std::derived_from<Expr> ExprT, std::invocable<ExprT*> Func>
    decltype(auto) Visit(ExprT* e, Func&& func) {
        return std::forward<Func>(func)(e);
    }

    template<typename ExprT, typename Func>
    requires (std::derived_from<std::remove_cvref_t<ExprT>, Expr> && std::invocable<Func, ExprT&&>)
    decltype(auto) Visit(ExprT&& e, Func&& func) {
        return std::forward<Func>(func)(std::forward<ExprT>(e));
    }
}