#include <string>
#include "AccessController.h"

using namespace std;

class CampusArea{
    protected:
        string name;
        bool locked;
    public:
        CampusArea(string name);
        virtual bool secure(AccessController&) = 0;
        virtual bool reopen(AccessController&) = 0;
        bool isLocked();
        virtual ~CampusArea();
};