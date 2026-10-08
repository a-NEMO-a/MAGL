#ifndef _MAGL_SHADER_H_
#define _MAGL_SHADER_H_

#include <cstdint>

namespace magl {

    namespace graphics {
        
        struct hook {
            virtual std::uint32_t call (int x, int y) = 0;
            virtual ~hook() = default;
        };
    }
}

#endif /* _MAGL_SHADER_H_ */