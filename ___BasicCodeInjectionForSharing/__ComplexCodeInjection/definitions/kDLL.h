#ifndef __KDLL_H
#define __KDLL_H

// Flattened copy of nitroKernel/include/kDLL.h for the injection build, same
// treatment already applied to definitions/kPrint.h in this folder. The real
// header pulls in kTypes.h -> k_Init.h -> RPM_Api.h for the kernel's own
// init plumbing (_InitClass, rpm::mgr::ModuleManager), which only exists to
// build NitroKernel.elf itself and isn't available to injected battle code.
// Only the public k::dll API that A4/A8 actually call is kept here.

#define LIBRARY_PATH_PREFIX "lib/"
#define LIBRARY_PATH_SUFFIX ".dll"

#include "k_DllExport.h"

namespace k {
    namespace dll {
        namespace detail {
            class LibraryState;
        }

        typedef detail::LibraryState* LibraryHandle;

        /**
         * @brief Loads a shared library. Duplicate load calls for one library will be redirected to the same handle.
         *
         * @param name Friendly name of the requested shared library.
         * @return A handle to the shared library, or nullptr if the library could not be loaded.
         */
        K_PUBLIC LibraryHandle LoadLibrary(const char* name);
        /**
         * @brief Releases a shared library. The library won't be truly released until all parent contexts call this function.
         *
         * @param name Friendly name of the shared library to be deleted.
         */
        K_PUBLIC void ReleaseLibrary(const char* name);
        /**
         * @brief Releases a shared library without string lookup slowdown. The library won't be truly released until all parent contexts call this function.
         *
         * @param handle Handle of the shared library to be deleted.
         */
        K_PUBLIC void ReleaseLibrary(LibraryHandle handle);
        /**
         * @brief Finds an exported procedure inside a dynamically linked module.
         *
         * @param handle Handle to the module to search within.
         * @param procName Name of the procedure to search for.
         * @return Pointer to the procedure (with the Thumb bit set), or nullptr if not found.
         */
        K_PUBLIC void* GetProcAddress(LibraryHandle handle, const char* procName);
    }
}

#endif
