#ifndef DYNAMIC_LOAD_H
#define DYNAMIC_LOAD_H

namespace dl
{
    class SharedLibrary
    {
    private:
        void *handle;
    public:
        SharedLibrary(const char *filename);
        ~SharedLibrary();
        void *Sym(const char *symbol);
    };
} // namespace dl

#endif // DYNAMIC_LOAD_H