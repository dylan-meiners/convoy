#ifndef MODE_H
#define MODE_H

class Mode {

    public:
        virtual bool _step();
        virtual void reset();

        bool step() {

            _parse();
            _step();
        }

        int dataLength;
        uint8_t* data;

    private:
        virtual void _parse();
};

#endif