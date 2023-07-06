#ifndef MODE_H
#define MODE_H

class Mode {

    public:
        virtual bool step();
        virtual void reset();
        virtual void parse();

        int dataLength;
        char* data;
};

#endif