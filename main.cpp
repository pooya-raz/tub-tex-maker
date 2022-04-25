#include <iostream>
#include "services/TubMediaWikiService.h"

int main() {

    TubMediaWikiService tub;
    std::cout << tub.getQuery("query") << std::endl;
    return 0;
}
