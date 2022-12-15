#include "simulator.h"

using namespace std;

int simulate()
{
    int bitStreamSize = inputSignals[0]->getSize();
    for (int i = 0; i < inputSignals.size(); i++)
    {
        if (inputSignals[i]->getSize() != bitStreamSize)
        {
            cout << "Bit streams need to have the same lenght" << endl;
            return 1;
        }
    }

    vector<Node*>::iterator out;
    for(int i = 0; i < bitStreamSize; i++) {
        for (out = outputSignals.begin(); out != outputSignals.end(); out++)
        {
            (*out)->computeOut(i);
            cout << (*out)->getName() << " = " << (*out)->getValue(i) << "\t";
        }
        cout << endl;
    }

    inputSignals.insert(inputSignals.end(), outputSignals.begin(), outputSignals.end());
    create_file(inputSignals);
    return 0;
}
