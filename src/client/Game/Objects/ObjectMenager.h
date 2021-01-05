#ifndef IRE_OBJECT_MENAGER_H
#define IRE_OBJECT_MENAGER_H

namespace ire::client::objects
{
    struct ObjectMenager
    {
        enum struct States
        {
            Planning,
            Building
        };
    };
}

#endif //!IRE_OBJECT_MENAGER_H