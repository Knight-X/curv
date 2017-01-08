// Copyright Doug Moen 2016.
// Distributed under The MIT License.
// See accompanying file LICENSE.md or https://opensource.org/licenses/MIT

#include <curv/shape.h>
#include <curv/exception.h>
#include <curv/context.h>
#include <curv/gl_context.h>
#include <curv/function.h>

namespace curv {

void
Shape2D::print(std::ostream& out) const
{
    out << "shape2d";
    record_->print(out);
}

Value
Shape2D::getfield(Atom name) const
{
    return record_->getfield(name);
}

Function&
Shape2D::dist() const
{
    // TODO: fix exceptions to have proper context
    auto val = getfield("dist");
    if (val == missing)
        throw Exception({}, "Shape2D: dist function is missing");
    auto fun = val.dycast<Function>();
    if (fun == nullptr)
        throw Exception({}, "Shape2D: dist is not a function");
    if (fun->nargs_ != 1)
        throw Exception({}, "Shape2D: dist function does not have 1 parameter");
    return *fun;
}

GL_Value
Shape2D::gl_dist(GL_Value arg, GL_Frame& f) const
{
    Function& fun = dist();
    auto f2 = GL_Frame::make(fun.nslots_, f.gl, &f, nullptr);
    (*f2)[0] = arg;
    auto result = fun.gl_call(*f2);
    if (result.type != GL_Type::Num) {
        throw Exception(At_GL_Frame(&f),
            stringify("dist function returns ",result.type));
    }
    return result;
}

} // namespace curv
