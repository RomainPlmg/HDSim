#include "simulator.h"

using namespace std;

int simulate()
{
    int bitStreamSize = inputSignals[0]->getSize();
    for (int i = 0; i < inputSignals.size(); i++)
    {
        if (inputSignals[i]->getSize() != bitStreamSize)
        {
            cout << "Bit streams need to have the same length" << endl;
            return 1;
        }
    }

   
    vector<vector<Node*>> cycles;
    vector<Node*>::iterator out;
    for (out = outputSignals.begin(); out != outputSignals.end(); out++) {
            (*out)->detectCycle(cycles);
    }

    if(cycles.size() != 0) {
        cycles.push_back({});
        for(size_t i = 0; i < (cycles.size() - 1); i++) {
            cycles[i][0]->suppChild(cycles[i][1]);
            cycles[cycles.size() - 1].push_back(new VirtualInput(cycles[i][1]));
            cycles[i][0]->addChild(cycles[cycles.size() - 1][0]);
        }
        for (out = outputSignals.begin(); out != outputSignals.end(); out++)
        {
            for(size_t j = 0; j < outputSignals.size(); j++) {
                (*out)->computeOut(j);
                cout << (*out)->getName() << " = " << (*out)->getValue(j) << "\t";
            }
        }
    }
    else {
        for (out = outputSignals.begin(); out != outputSignals.end(); out++)
        {
            (*out)->computeOut();
            cout << (*out)->getName() << " = " << (*out)->getValue() << "\t";
        }
        cout << endl;
    }

    inputSignals.insert(inputSignals.end(), outputSignals.begin(), outputSignals.end());
    create_file(inputSignals);
    return 0;
}
