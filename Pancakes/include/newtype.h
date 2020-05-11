
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
using namespace nana;

class myform : public nana::form {
    button b;
    label t;

public:
    myform(const char* my_msg) : b(*this, rectangle(10, 40, 100, 20)),
        t(*this, rectangle(10, 10, 100, 20)) {
        b.caption(my_msg);
        t.caption(my_msg);
        b.events().click(API::exit_all);
    }
};