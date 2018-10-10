#pragma once

#include <AK/HashMap.h>
#include <AK/MappedFile.h>
#include <AK/OwnPtr.h>
#include <AK/Vector.h>

class ELFLoader;

class ExecSpace {
public:
    struct Area {
        Area(String&& n, char* m, unsigned s)
            : name(std::move(n))
            , memory(m)
            , size(s)
        {
        }

        String name;
        char* memory { 0 };
        unsigned size { 0 };
    };

    struct PtrAndSize {
        PtrAndSize() { }
        PtrAndSize(char* p, unsigned s)
            : ptr(p)
            , size(s)
        {
        }

        char* ptr { nullptr };
        unsigned size { 0 };
    };

    ExecSpace();
    ~ExecSpace();

    bool loadELF(MappedFile&&);

    char* symbolPtr(const char* name);

    char* allocateArea(String&& name, unsigned size);
    void addSymbol(String&& name, char* ptr, unsigned size);

private:
    void initializeBuiltins();

    Vector<OwnPtr<Area>> m_areas;
    HashMap<String, PtrAndSize> m_symbols;
};
