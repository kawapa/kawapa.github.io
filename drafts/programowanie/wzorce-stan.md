#include <iostream>
#include <string>

class State {
public:
    State() = default;
    virtual ~State() = default;
    virtual std::string getDescription() = 0;
    virtual State* getNextState() = 0;
};

// State::~State() {}

class PurchasedState : public State {
    State* nextState = nullptr;
public:
    PurchasedState(State* nextState) { 
        this->nextState = nextState;
    }

    std::string getDescription() override {
        return "Current State: PURCHASED - Will be shipping soon\n";
    }

    State* getNextState() override {
        return nextState;
    }    
};

class InTransitState : public State {
    State* nextState = nullptr;
public:
    InTransitState(State* nextState) {   
        this->nextState = nextState;
    }

    std::string getDescription() override {
        return "Current State: IN_TRANSIT - Your item is on the way\n";
    }

    State* getNextState() override {
        return nextState;
    }    
};

class DeliveredState : public State {
    State* nextState = nullptr;
public:
    DeliveredState(State* nextState)  { 
        this->nextState = nextState;
    }

    std::string getDescription() override {
        return "Current State: DELIVERED - Your item has arrived!\n";
    }

    State* getNextState() override {
        return nextState;
    }    
};

class Purchase {
private:
    std::string productName;
    State* currentState;

public:
    Purchase(const std::string& productName, State* initialState)
        : productName(productName), currentState(initialState)
    { }

    std::string getDescription() { return currentState->getDescription(); }
    void goToNextState() {
        if (currentState->getNextState()) {
            currentState = currentState->getNextState();
        }
    }  
};

int main() {
    auto* deliveredState = new DeliveredState(nullptr);
    auto* inTransitState = new InTransitState(deliveredState);
    auto* purchasedState = new PurchasedState(inTransitState);

    Purchase* purchase = new Purchase("Shoes", purchasedState);
    std::cout << purchase->getDescription() << '\n';
    purchase->goToNextState();
    std::cout << purchase->getDescription() << '\n';
    purchase->goToNextState();
    std::cout << purchase->getDescription() << '\n';

    delete deliveredState;
    delete inTransitState;
    delete purchasedState;
    delete purchase;

    return 0;
}