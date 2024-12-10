#ifndef LFONT_HPP
#define LFONT_HPP

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

class LFont
{
    public:

        LFont(int ptsize = 12, std::string filename = "");
        ~LFont();

        void free(bool clearFilename = true);

        bool load(std::string newFilename, int ptsize = 12);
        bool setPtSize(int ptsize);

        TTF_Font* get() const;
        int getPtSize() const;

    private:

        TTF_Font *font = NULL;
        int size = -1;

        std::string filename = "";
};

#endif